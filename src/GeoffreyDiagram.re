// Hard-coded version of Geoffrey's diagram using Kiwi and Draggable
open Kiwi;

let v = mkVarExpression;
let n = mkNumExpression;

let initSolver = (aCenterX, aCenterY, bCenterX, bCenterY, cCenter, dCenter, gap, guide) => {
  let solver = mkSolver();
  solver->addEditVariable(aCenterX, Strength.strong);
  solver->addEditVariable(bCenterX, Strength.strong);
  // solver->addEditVariable(cCenter, Strength.strong);
  // solver->addEditVariable(dCenter, Strength.strong);
  // solver->addEditVariable(gap, Strength.strong);

  // equal spacing circles
  let aConstraints = [|Kiwi.Ops.(v(bCenterX) - v(aCenterX) == v(gap)), Kiwi.Ops.(v(aCenterY) == v(guide))|];
  solver->addConstraint(aConstraints[0]);
  solver->addConstraint(Kiwi.Ops.(v(cCenter) - v(bCenterX) == v(gap)));
  solver->addConstraint(Kiwi.Ops.(v(dCenter) - v(cCenter) == v(gap)));

  // equal y pos
  solver->addConstraint(aConstraints[1]);
  solver->addConstraint(Kiwi.Ops.(v(bCenterY) == v(guide)));

  solver->suggestValue(aCenterX, 50.);
  solver->suggestValue(bCenterX, 80.);
  solver->updateVariables();
  solver->removeEditVariable(aCenterX);
  solver->removeEditVariable(bCenterX);

  // start editing gap with a weak stay on aCenter
  solver->addEditVariable(gap, Strength.strong);
  solver->addEditVariable(guide, Strength.strong);
  let aStay = mkStay(aCenterX);
  solver->addConstraint(aStay);
  solver->suggestValue(gap, 100.);
  solver->suggestValue(guide, 50.);
  solver->updateVariables();
  solver->removeEditVariable(gap);
  solver->removeEditVariable(guide);
  solver->removeConstraint(aStay);

  aCenterX->setName("aCenterX");
  Js.log2("aCenterX Name", aCenterX->name());
  Js.log2("aCenterX", aCenterX->value());
  Js.log2("bCenterX", bCenterX->value());
  Js.log2("cCenter", cCenter->value());
  Js.log2("dCenter", dCenter->value());
  Js.log2("gap", gap->value());
  Js.log2("guide", guide->value());
  (solver, aConstraints);
};

[@react.component]
let make = () => {
  let ((aCenterX, aCenterY), _) = React.useState(() => (mkVariable(), mkVariable()));
  let ((bCenterX, bCenterY), _) = React.useState(() => (mkVariable(), mkVariable()));
  let (cCenter, _) = React.useState(() => mkVariable());
  let (dCenter, _) = React.useState(() => mkVariable());
  let (gap, _) = React.useState(() => mkVariable());
  let (guide, _) = React.useState(() => mkVariable());
  let ((solver, aConstraints), _) =
    React.useState(() =>
      initSolver(aCenterX, aCenterY, bCenterX, bCenterY, cCenter, dCenter, gap, guide)
    );
  let (foo, setFoo) = React.useState(() => 0);

  let onStart = (~e, ~data: Draggable.draggableData) => {
    // TODO: for some reason setFoo triggers the cassowary variables to update...
    setFoo(x => 1 - x);
    solver->removeConstraint(aConstraints[0]);
    solver->removeConstraint(aConstraints[1]);
    Js.log2("onStart: aCenterX", aCenterX->value());
    let gapStay = mkStay(gap);
    solver->addConstraint(gapStay);
    let guideStay = mkStay(guide);
    solver->addConstraint(guideStay);
    let bCenterXStay = mkStay(bCenterX);
    solver->addConstraint(bCenterXStay);
    solver->addEditVariable(aCenterX, Strength.strong);
    solver->addEditVariable(aCenterY, Strength.strong);
    solver->suggestValue(aCenterX, data.x);
    solver->suggestValue(aCenterY, data.y);
    solver->updateVariables();
    solver->removeEditVariable(aCenterY);
    solver->removeEditVariable(aCenterX);
    solver->removeConstraint(bCenterXStay);
    solver->removeConstraint(guideStay);
    solver->removeConstraint(gapStay);
    None;
  };

  let onDrag = (~e, ~data: Draggable.draggableData) => {
    // TODO: for some reason setFoo triggers the cassowary variables to update...
    setFoo(x => 1 - x);
    Js.log2("onDrag: aCenterX", aCenterX->value());
    let gapStay = mkStay(gap);
    solver->addConstraint(gapStay);
    let guideStay = mkStay(guide);
    solver->addConstraint(guideStay);
    solver->addEditVariable(aCenterX, Strength.strong);
    solver->suggestValue(aCenterX, data.x);
    solver->updateVariables();
    solver->removeEditVariable(aCenterX);
    solver->removeConstraint(guideStay);
    solver->removeConstraint(gapStay);
    None;
  };

  let onDragGuide = (~e, ~data: Draggable.draggableData) => {
    // TODO: for some reason setFoo triggers the cassowary variables to update...
    setFoo(x => 1 - x);
    let gapStay = mkStay(gap);
    solver->addConstraint(gapStay);
    let aCenterXStay = mkStay(aCenterX);
    solver->addConstraint(aCenterXStay);
    solver->addEditVariable(guide, Strength.strong);
    solver->suggestValue(guide, data.y);
    solver->updateVariables();
    solver->removeEditVariable(guide);
    solver->removeConstraint(aCenterXStay);
    solver->removeConstraint(gapStay);
    None;
  };

  Js.log2("make: aCenter", aCenterX->value());

  <div>
    foo->React.int
    <svg width="500" height="500">
      // TODO: dragging this line should move everything with y = 50

        <g>
          <line
            x1={(aCenterX->value() -. 30. -. 2.)->Js.Float.toString}
            y1={guide->value()->Js.Float.toString}
            x2={(dCenter->value() +. 30. +. 2.)->Js.Float.toString}
            y2={guide->value()->Js.Float.toString}
            stroke="gray"
            strokeWidth="11"
          />
          <line
            x1={(aCenterX->value() -. 30.)->Js.Float.toString}
            y1={guide->value()->Js.Float.toString}
            x2={(dCenter->value() +. 30.)->Js.Float.toString}
            y2={guide->value()->Js.Float.toString}
            stroke="lightblue"
            strokeWidth="8"
          />
        </g>
        <Draggable /* onStart */ onDrag position={x: aCenterX->value(), y: aCenterY->value()}>
          <circle cx="0" cy="0" r="20" fill="lightblue" stroke="gray" strokeWidth="2" />
        </Draggable>
        <Draggable position={x: bCenterX->value(), y: bCenterY->value()}>
          <circle cx="0" cy="0" r="20" fill="lightblue" stroke="gray" strokeWidth="2" />
        </Draggable>
        <HorizontalGuide width="500" onDrag=onDragGuide yPos={guide->value()} />
      </svg>
  </div>;
  // <Draggable position={x: cCenter->value(), y: 50.}>
  //   <circle cx="0" cy="0" r="20" fill="lightblue" stroke="gray" strokeWidth="2" />
  // </Draggable>
  // <Draggable position={x: dCenter->value(), y: 50.}>
  //   <circle cx="0" cy="0" r="20" fill="lightblue" stroke="gray" strokeWidth="2" />
  // </Draggable>
};
