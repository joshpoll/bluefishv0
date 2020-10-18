// Hard-coded version of Geoffrey's diagram using Kiwi and Draggable
let v = Kiwi.mkVarExpression;
let n = Kiwi.mkNumExpression;

let initSolver = (aCenterX, aCenterY, bCenterX, bCenterY, cCenter, dCenter, gap, guide) => {
  let solver = Kiwi.mkSolver();
  solver->Kiwi.addEditVariable(aCenterX, Kiwi.Strength.strong);
  solver->Kiwi.addEditVariable(bCenterX, Kiwi.Strength.strong);
  // solver->Kiwi.addEditVariable(cCenter, Kiwi.Strength.strong);
  // solver->Kiwi.addEditVariable(dCenter, Kiwi.Strength.strong);
  // solver->Kiwi.addEditVariable(gap, Kiwi.Strength.strong);

  // equal spacing circles
  solver->Kiwi.addConstraint(Kiwi.(v(bCenterX) - v(aCenterX) == v(gap)));
  solver->Kiwi.addConstraint(Kiwi.(v(cCenter) - v(bCenterX) == v(gap)));
  solver->Kiwi.addConstraint(Kiwi.(v(dCenter) - v(cCenter) == v(gap)));

  // equal y pos
  solver->Kiwi.addConstraint(Kiwi.(v(aCenterY) == v(guide)));
  solver->Kiwi.addConstraint(Kiwi.(v(bCenterY) == v(guide)));

  solver->Kiwi.suggestValue(aCenterX, 50.);
  solver->Kiwi.suggestValue(bCenterX, 80.);
  solver->Kiwi.updateVariables();
  solver->Kiwi.removeEditVariable(aCenterX);
  solver->Kiwi.removeEditVariable(bCenterX);

  // start editing gap with a weak stay on aCenter
  solver->Kiwi.addEditVariable(gap, Kiwi.Strength.strong);
  solver->Kiwi.addEditVariable(guide, Kiwi.Strength.strong);
  let aStay = Kiwi.mkStay(aCenterX);
  solver->Kiwi.addConstraint(aStay);
  solver->Kiwi.suggestValue(gap, 100.);
  solver->Kiwi.suggestValue(guide, 50.);
  solver->Kiwi.updateVariables();
  solver->Kiwi.removeEditVariable(gap);
  solver->Kiwi.removeEditVariable(guide);
  solver->Kiwi.removeConstraint(aStay);

  Js.log2("aCenterX", aCenterX->Kiwi.value());
  Js.log2("bCenterX", bCenterX->Kiwi.value());
  Js.log2("cCenter", cCenter->Kiwi.value());
  Js.log2("dCenter", dCenter->Kiwi.value());
  Js.log2("gap", gap->Kiwi.value());
  Js.log2("guide", guide->Kiwi.value());
  solver;
};

[@react.component]
let make = () => {
  let ((aCenterX, aCenterY), _) = React.useState(() => (Kiwi.mkVariable(), Kiwi.mkVariable()));
  let ((bCenterX, bCenterY), _) = React.useState(() => (Kiwi.mkVariable(), Kiwi.mkVariable()));
  let (cCenter, _) = React.useState(() => Kiwi.mkVariable());
  let (dCenter, _) = React.useState(() => Kiwi.mkVariable());
  let (gap, _) = React.useState(() => Kiwi.mkVariable());
  let (guide, _) = React.useState(() => Kiwi.mkVariable());
  let (solver, _) =
    React.useState(() =>
      initSolver(aCenterX, aCenterY, bCenterX, bCenterY, cCenter, dCenter, gap, guide)
    );
  let (foo, setFoo) = React.useState(() => 0);

  let onDrag = (~e, ~data: Draggable.draggableData) => {
    // TODO: for some reason setFoo triggers the cassowary variables to update...
    setFoo(x => 1 - x);
    Js.log2("onDrag: aCenterX", aCenterX->Kiwi.value());
    let gapStay = Kiwi.mkStay(gap);
    solver->Kiwi.addConstraint(gapStay);
    let guideStay = Kiwi.mkStay(guide);
    solver->Kiwi.addConstraint(guideStay);
    solver->Kiwi.addEditVariable(aCenterX, Kiwi.Strength.strong);
    solver->Kiwi.suggestValue(aCenterX, data.x);
    solver->Kiwi.updateVariables();
    solver->Kiwi.removeEditVariable(aCenterX);
    solver->Kiwi.removeConstraint(guideStay);
    solver->Kiwi.removeConstraint(gapStay);
    None;
  };

  let onDragGuide = (~e, ~data: Draggable.draggableData) => {
    // TODO: for some reason setFoo triggers the cassowary variables to update...
    setFoo(x => 1 - x);
    let gapStay = Kiwi.mkStay(gap);
    solver->Kiwi.addConstraint(gapStay);
    let aCenterXStay = Kiwi.mkStay(aCenterX);
    solver->Kiwi.addConstraint(aCenterXStay);
    solver->Kiwi.addEditVariable(guide, Kiwi.Strength.strong);
    solver->Kiwi.suggestValue(guide, data.y);
    solver->Kiwi.updateVariables();
    solver->Kiwi.removeEditVariable(guide);
    solver->Kiwi.removeConstraint(aCenterXStay);
    solver->Kiwi.removeConstraint(gapStay);
    None;
  };

  Js.log2("make: aCenter", aCenterX->Kiwi.value());

  <div>
    foo->React.int
    <svg width="500" height="500">
      // TODO: dragging this line should move everything with y = 50

        <g>
          <line
            x1={(aCenterX->Kiwi.value() -. 30. -. 2.)->Js.Float.toString}
            y1={guide->Kiwi.value()->Js.Float.toString}
            x2={(dCenter->Kiwi.value() +. 30. +. 2.)->Js.Float.toString}
            y2={guide->Kiwi.value()->Js.Float.toString}
            stroke="gray"
            strokeWidth="11"
          />
          <line
            x1={(aCenterX->Kiwi.value() -. 30.)->Js.Float.toString}
            y1={guide->Kiwi.value()->Js.Float.toString}
            x2={(dCenter->Kiwi.value() +. 30.)->Js.Float.toString}
            y2={guide->Kiwi.value()->Js.Float.toString}
            stroke="lightblue"
            strokeWidth="8"
          />
        </g>
        <Draggable onDrag position={x: aCenterX->Kiwi.value(), y: aCenterY->Kiwi.value()}>
          <circle cx="0" cy="0" r="20" fill="lightblue" stroke="gray" strokeWidth="2" />
        </Draggable>
        <Draggable position={x: bCenterX->Kiwi.value(), y: bCenterY->Kiwi.value()}>
          <circle cx="0" cy="0" r="20" fill="lightblue" stroke="gray" strokeWidth="2" />
        </Draggable>

        <HorizontalGuide width="500" onDrag=onDragGuide yPos={guide->Kiwi.value()} />
      </svg>
  </div>;
  // <Draggable position={x: cCenter->Kiwi.value(), y: 50.}>
  //   <circle cx="0" cy="0" r="20" fill="lightblue" stroke="gray" strokeWidth="2" />
  // </Draggable>
  // <Draggable position={x: dCenter->Kiwi.value(), y: 50.}>
  //   <circle cx="0" cy="0" r="20" fill="lightblue" stroke="gray" strokeWidth="2" />
  // </Draggable>
};
