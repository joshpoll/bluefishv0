// Hard-coded version of Geoffrey's diagram using Kiwi and Draggable
let v = Kiwi.mkVarExpression;
let n = Kiwi.mkNumExpression;

let initSolver = (aCenter, bCenter, cCenter, dCenter, gap) => {
  let solver = Kiwi.mkSolver();
  solver->Kiwi.addEditVariable(aCenter, Kiwi.Strength.strong);
  solver->Kiwi.addEditVariable(bCenter, Kiwi.Strength.strong);
  // solver->Kiwi.addEditVariable(cCenter, Kiwi.Strength.strong);
  // solver->Kiwi.addEditVariable(dCenter, Kiwi.Strength.strong);
  // solver->Kiwi.addEditVariable(gap, Kiwi.Strength.strong);

  solver->Kiwi.addConstraint(Kiwi.(v(bCenter) - v(aCenter) == v(gap)));
  solver->Kiwi.addConstraint(Kiwi.(v(cCenter) - v(bCenter) == v(gap)));
  solver->Kiwi.addConstraint(Kiwi.(v(dCenter) - v(cCenter) == v(gap)));

  solver->Kiwi.suggestValue(aCenter, 50.);
  solver->Kiwi.suggestValue(bCenter, 80.);
  solver->Kiwi.updateVariables();
  solver->Kiwi.removeEditVariable(aCenter);
  solver->Kiwi.removeEditVariable(bCenter);

  // start editing gap with a weak stay on aCenter
  solver->Kiwi.addEditVariable(gap, Kiwi.Strength.strong);
  let aStay = Kiwi.mkStay(aCenter);
  solver->Kiwi.addConstraint(aStay);
  solver->Kiwi.suggestValue(gap, 100.);
  solver->Kiwi.updateVariables();
  solver->Kiwi.removeEditVariable(gap);
  solver->Kiwi.removeConstraint(aStay);

  Js.log2("aCenter", aCenter->Kiwi.value());
  Js.log2("bCenter", bCenter->Kiwi.value());
  Js.log2("cCenter", cCenter->Kiwi.value());
  Js.log2("dCenter", dCenter->Kiwi.value());
  solver;
};

[@react.component]
let make = () => {
  let (aCenter, setACenter) = React.useState(() => Kiwi.mkVariable());
  let (bCenter, setBCenter) = React.useState(() => Kiwi.mkVariable());
  let (cCenter, _) = React.useState(() => Kiwi.mkVariable());
  let (dCenter, _) = React.useState(() => Kiwi.mkVariable());
  let (gap, _) = React.useState(() => Kiwi.mkVariable());
  let (solver, _) = React.useState(() => initSolver(aCenter, bCenter, cCenter, dCenter, gap));
  let (foo, setFoo) = React.useState(() => 0);

  let onDrag = (~e, ~data: Draggable.draggableData) => {
    // TODO: for some reason setFoo triggers the cassowary variables to update...
    setFoo(x => 1 - x);
    Js.log2("onDrag: aCenter", aCenter->Kiwi.value());
    let gapStay = Kiwi.mkStay(gap);
    solver->Kiwi.addConstraint(gapStay);
    solver->Kiwi.addEditVariable(aCenter, Kiwi.Strength.strong);
    solver->Kiwi.suggestValue(aCenter, data.x);
    solver->Kiwi.updateVariables();
    solver->Kiwi.removeEditVariable(aCenter);
    solver->Kiwi.removeConstraint(gapStay);
    None;
  };

  Js.log2("make: aCenter", aCenter->Kiwi.value());

  <div>
    foo->React.int
    <svg width="500" height="500">
      // TODO: dragging this line should move everything with y = 50

        <Draggable>
          <line
            x1="0"
            x2="500"
            y1="50."
            y2="50."
            stroke="red"
            strokeWidth="3"
            strokeDasharray="4"
          />
        </Draggable>
        <g>
          <line
            x1={(aCenter->Kiwi.value() -. 30. -. 2.)->Js.Float.toString}
            y1="50."
            x2={(dCenter->Kiwi.value() +. 30. +. 2.)->Js.Float.toString}
            y2="50."
            stroke="gray"
            strokeWidth="11"
          />
          <line
            x1={(aCenter->Kiwi.value() -. 30.)->Js.Float.toString}
            y1="50."
            x2={(dCenter->Kiwi.value() +. 30.)->Js.Float.toString}
            y2="50."
            stroke="lightblue"
            strokeWidth="8"
          />
        </g>
        <Draggable onDrag position={x: aCenter->Kiwi.value(), y: 50.}>
          <circle cx="0" cy="0" r="20" fill="lightblue" stroke="gray" strokeWidth="2" />
        </Draggable>
        <Draggable position={x: bCenter->Kiwi.value(), y: 50.}>
          <circle cx="0" cy="0" r="20" fill="lightblue" stroke="gray" strokeWidth="2" />
        </Draggable>
        <Draggable position={x: cCenter->Kiwi.value(), y: 50.}>
          <circle cx="0" cy="0" r="20" fill="lightblue" stroke="gray" strokeWidth="2" />
        </Draggable>
        <Draggable position={x: dCenter->Kiwi.value(), y: 50.}>
          <circle cx="0" cy="0" r="20" fill="lightblue" stroke="gray" strokeWidth="2" />
        </Draggable>
      </svg>
  </div>;
};
