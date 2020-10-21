// Hard-coded version of Geoffrey's diagram using Kiwi and Draggable
open Kiwi;
open KiwiDeclarative;

let v = mkVarExpression;
let n = mkNumExpression;

let initSolver = (aCenterX, aCenterY, bCenterX, bCenterY, cCenter, dCenter, gap, guide) => {
  let solver = mkSolver();
  let variables =
    Belt.Map.fromArray(
      [|
        (aCenterX, Suggest(50., Strength.strong)),
        (aCenterY, Derived),
        (bCenterX, Derived),
        (bCenterY, Derived),
        (gap, Suggest(100., Strength.strong)),
        (guide, Suggest(50., Strength.strong)),
      |],
      ~id=(module VariableComparable),
    );

  let constraints = [
    Kiwi.Ops.(v(bCenterX) - v(aCenterX) == v(gap)),
    Kiwi.Ops.(v(aCenterY) == v(guide)),
    Kiwi.Ops.(v(bCenterY) == v(guide)),
  ];

  let solver = solver->KiwiDeclarative.solve(~variables, ~constraints);

  // // equal spacing circles
  // let aConstraints = [|
  //   Kiwi.Ops.(v(bCenterX) - v(aCenterX) == v(gap)),
  //   Kiwi.Ops.(v(aCenterY) == v(guide)),
  // |];
  // solver->addConstraint(aConstraints[0]);
  // solver->addConstraint(Kiwi.Ops.(v(cCenter) - v(bCenterX) == v(gap)));
  // solver->addConstraint(Kiwi.Ops.(v(dCenter) - v(cCenter) == v(gap)));

  // // equal y pos
  // solver->addConstraint(aConstraints[1]);
  // solver->addConstraint(Kiwi.Ops.(v(bCenterY) == v(guide)));

  Js.log("declarative");
  Js.log2("aCenterX Name", aCenterX->name());
  Js.log2("aCenterX", aCenterX->value());
  Js.log2("bCenterX", bCenterX->value());
  Js.log2("cCenter", cCenter->value());
  Js.log2("dCenter", dCenter->value());
  Js.log2("gap", gap->value());
  Js.log2("guide", guide->value());
  // (solver, aConstraints);
  solver;
};

[@react.component]
let make = () => {
  let ((aCenterX, aCenterY), _) = React.useState(() => (mkVariable(~name="aCenterX", ()), mkVariable(~name="aCenterY", ())));
  let ((bCenterX, bCenterY), _) = React.useState(() => (mkVariable(~name="bCenterX", ()), mkVariable(~name="bCenterY", ())));
  let (cCenter, _) = React.useState(() => mkVariable(~name="cCenter", ()));
  let (dCenter, _) = React.useState(() => mkVariable(~name="dCenter", ()));
  let (gap, _) = React.useState(() => mkVariable(~name="gap", ()));
  let (guide, _) = React.useState(() => mkVariable(~name="guide", ()));
  let (solver, setSolver) =
    React.useState(() =>
      initSolver(aCenterX, aCenterY, bCenterX, bCenterY, cCenter, dCenter, gap, guide)
    );
  let (foo, setFoo) = React.useState(() => 0);

  // let onStart = (~e, ~data: Draggable.draggableData) => {
  //   // TODO: for some reason setFoo triggers the cassowary variables to update...
  //   setFoo(x => 1 - x);
  //   solver->removeConstraint(aConstraints[0]);
  //   solver->removeConstraint(aConstraints[1]);
  //   Js.log2("onStart: aCenterX", aCenterX->value());
  //   let gapStay = mkStay(gap);
  //   solver->addConstraint(gapStay);
  //   let guideStay = mkStay(guide);
  //   solver->addConstraint(guideStay);
  //   let bCenterXStay = mkStay(bCenterX);
  //   solver->addConstraint(bCenterXStay);
  //   solver->addEditVariable(aCenterX, Strength.strong);
  //   solver->addEditVariable(aCenterY, Strength.strong);
  //   solver->suggestValue(aCenterX, data.x);
  //   solver->suggestValue(aCenterY, data.y);
  //   solver->updateVariables();
  //   solver->removeEditVariable(aCenterY);
  //   solver->removeEditVariable(aCenterX);
  //   solver->removeConstraint(bCenterXStay);
  //   solver->removeConstraint(guideStay);
  //   solver->removeConstraint(gapStay);
  //   None;
  // };

  // let onDrag = (~e, ~data: Draggable.draggableData) => {
  //   // TODO: for some reason setFoo triggers the cassowary variables to update...
  //   setFoo(x => 1 - x);
  //   Js.log2("onDrag: aCenterX", aCenterX->value());
  //   let gapStay = mkStay(gap);
  //   solver->addConstraint(gapStay);
  //   let guideStay = mkStay(guide);
  //   solver->addConstraint(guideStay);
  //   solver->addEditVariable(aCenterX, Strength.strong);
  //   solver->suggestValue(aCenterX, data.x);
  //   solver->updateVariables();
  //   solver->removeEditVariable(aCenterX);
  //   solver->removeConstraint(guideStay);
  //   solver->removeConstraint(gapStay);
  //   None;
  // };

  let onDragGuide = (~e, ~data: Draggable.draggableData) => {
    // TODO: for some reason setFoo triggers the cassowary variables to update...
    setFoo(x => 1 - x);
    setSolver(solver => {
      let variables =
        Belt.Map.fromArray(
          [|
            // no stays on affected variables, weak stays on unaffected variables, strong suggests on edits
            (aCenterX, Stay(Strength.weak)),
            (aCenterY, Derived),
            (bCenterX, Stay(Strength.weak)),
            (bCenterY, Derived),
            (gap, Stay(Strength.weak)),
            (guide, Suggest(data.y, Strength.strong)),
          |],
          ~id=(module VariableComparable),
        );

      let constraints = [
        Kiwi.Ops.(v(bCenterX) - v(aCenterX) == v(gap)),
        Kiwi.Ops.(v(aCenterY) == v(guide)),
        Kiwi.Ops.(v(bCenterY) == v(guide)),
      ];

      solver->KiwiDeclarative.solve(~variables, ~constraints);
    });
    None;
  };

  <div>
    foo->React.int
    <svg width="500" height="500">
      // TODO: dragging this line should move everything with y = 50

        <g>
          <line
            x1={(aCenterX->value() -. 30. -. 2.)->Js.Float.toString}
            y1={guide->value()->Js.Float.toString}
            x2={(bCenterX->value() +. 30. +. 2.)->Js.Float.toString}
            y2={guide->value()->Js.Float.toString}
            stroke="gray"
            strokeWidth="11"
          />
          <line
            x1={(aCenterX->value() -. 30.)->Js.Float.toString}
            y1={guide->value()->Js.Float.toString}
            x2={(bCenterX->value() +. 30.)->Js.Float.toString}
            y2={guide->value()->Js.Float.toString}
            stroke="lightblue"
            strokeWidth="8"
          />
        </g>
        /* onStart */
        /* onDrag */
        <Draggable position={x: aCenterX->value(), y: aCenterY->value()}>
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
