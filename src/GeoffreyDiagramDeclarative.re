// Hard-coded version of Geoffrey's diagram using Kiwi and Draggable
open Kiwi;
open KiwiDeclarative;

let v = mkVarExpression;
let n = mkNumExpression;

[@react.component]
let make = () => {
  let ((aCenterX, aCenterY), _) =
    React.useState(() => (mkVariable(~name="aCenterX", ()), mkVariable(~name="aCenterY", ())));
  let ((bCenterX, bCenterY), _) =
    React.useState(() => (mkVariable(~name="bCenterX", ()), mkVariable(~name="bCenterY", ())));
  let ((cCenterX, cCenterY), _) =
    React.useState(() => (mkVariable(~name="cCenterX", ()), mkVariable(~name="cCenterY", ())));
  let ((dCenterX, dCenterY), _) =
    React.useState(() => (mkVariable(~name="dCenterX", ()), mkVariable(~name="dCenterY", ())));
  let (gap, _) = React.useState(() => mkVariable(~name="gap", ()));
  let (vertGap, _) = React.useState(() => mkVariable(~name="vertGap", ()));
  let (guide, _) = React.useState(() => mkVariable(~name="guide", ()));
  let (guide2, _) = React.useState(() => mkVariable(~name="guide2", ()));
  let (vertGuide1, _) = React.useState(() => mkVariable(~name="vertGuide1", ()));
  let (vertGuide2, _) = React.useState(() => mkVariable(~name="vertGuide2", ()));
  let (constraints, _) =
    React.useState(() =>
      [
        Kiwi.Ops.(v(bCenterX) - v(aCenterX) == v(gap)),
        Kiwi.Ops.(v(aCenterY) == v(guide)),
        Kiwi.Ops.(v(bCenterY) == v(guide)),
        Kiwi.Ops.(v(dCenterX) - v(cCenterX) == v(gap)), /* TODO: different gap? */
        Kiwi.Ops.(v(cCenterY) == v(guide2)),
        Kiwi.Ops.(v(dCenterY) == v(guide2)),
        Kiwi.Ops.(v(aCenterY) - v(cCenterY) == v(vertGap)),
        Kiwi.Ops.(v(bCenterY) - v(dCenterY) == v(vertGap)),
        Kiwi.Ops.(v(aCenterX) == v(vertGuide1)),
        Kiwi.Ops.(v(cCenterX) == v(vertGuide1)),
        Kiwi.Ops.(v(bCenterX) == v(vertGuide2)),
        Kiwi.Ops.(v(dCenterX) == v(vertGuide2)),
      ]
    );
  let (solver, setSolver) =
    React.useState(() => {
      let solver = mkSolver();
      let variables =
        Belt.Map.fromArray(
          [|
            (aCenterX, Suggest(50., Strength.strong)),
            (aCenterY, Derived),
            (bCenterX, Derived),
            (bCenterY, Derived),
            (cCenterX, Derived),
            (cCenterY, Derived),
            (dCenterX, Derived),
            (dCenterY, Derived),
            (gap, Suggest(100., Strength.strong)),
            (guide, Suggest(50., Strength.strong)),
            (guide2, Suggest(100., Strength.strong)),
            (vertGap, Derived),
            (vertGuide1, Derived),
            (vertGuide2, Derived),
          |],
          ~id=(module VariableComparable),
        );

      solver->KiwiDeclarative.solve(~variables, ~constraints);
    });
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
            (guide2, Derived),
            (vertGap, Stay(Strength.weak)),
            (vertGuide1, Stay(Strength.weak)),
            (vertGuide2, Stay(Strength.weak)),
          |],
          ~id=(module VariableComparable),
        );

      solver->KiwiDeclarative.solve(~variables, ~constraints);
    });
    None;
  };

  <div>
    foo->React.int
    <svg width="500" height="500">
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

        <Draggable position={x: cCenterX->value(), y: cCenterY->value()}>
          <circle cx="0" cy="0" r="20" fill="lightblue" stroke="gray" strokeWidth="2" />
        </Draggable>
        <Draggable position={x: dCenterX->value(), y: dCenterY->value()}>
          <circle cx="0" cy="0" r="20" fill="lightblue" stroke="gray" strokeWidth="2" />
        </Draggable>
      </svg>
  </div>;
  // <Draggable position={x: cCenter->value(), y: 50.}>
  //   <circle cx="0" cy="0" r="20" fill="lightblue" stroke="gray" strokeWidth="2" />
  // </Draggable>
  // <Draggable position={x: dCenter->value(), y: 50.}>
  //   <circle cx="0" cy="0" r="20" fill="lightblue" stroke="gray" strokeWidth="2" />
  // </Draggable>
};
