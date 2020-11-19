// Hard-coded version of Geoffrey's diagram using Kiwi and Draggable
open Kiwi;
open KiwiDeclarative;

let v = mkVarExpression;
let n = mkNumExpression;

let mkPoint = (~name, ()) => (
  mkVariable(~name=name ++ "X", ()),
  mkVariable(~name=name ++ "Y", ()),
);

[@react.component]
let make = () => {
  let (courseNumGuide, _) = React.useState(() => mkVariable(~name="courseNumGuide", ()));

  let (courseNum1, _) = React.useState(() => Box.mk(~name="courseNum1"));
  let (courseNum2, _) = React.useState(() => Box.mk(~name="courseNum2"));
  let (courseNum3, _) = React.useState(() => Box.mk(~name="courseNum3"));

  // let ((courseNum1ULX, courseNum1ULY), _) =
  //   React.useState(() => mkPoint(~name="courseNum1UL", ()));
  // let ((courseNum1BRX, courseNum1BRY), _) =
  //   React.useState(() => mkPoint(~name="courseNum1BR", ()));
  // let (courseNum1Width, _) = React.useState(() => mkVariable(~name="courseNum1Width", ()));
  // let (courseNum1Height, _) = React.useState(() => mkVariable(~name="courseNum1Height", ()));

  // let ((courseNum2ULX, courseNum2ULY), _) =
  //   React.useState(() => mkPoint(~name="courseNum2UL", ()));
  // let ((courseNum2BRX, courseNum2BRY), _) =
  //   React.useState(() => mkPoint(~name="courseNum2BR", ()));
  // let (courseNum2Width, _) = React.useState(() => mkVariable(~name="courseNum2Width", ()));
  // let (courseNum2Height, _) = React.useState(() => mkVariable(~name="courseNum2Height", ()));

  // let ((courseNum3ULX, courseNum3ULY), _) =
  //   React.useState(() => mkPoint(~name="courseNum3UL", ()));
  // let ((courseNum3BRX, courseNum3BRY), _) =
  //   React.useState(() => mkPoint(~name="courseNum3BR", ()));
  // let (courseNum3Width, _) = React.useState(() => mkVariable(~name="courseNum3Width", ()));
  // let (courseNum3Height, _) = React.useState(() => mkVariable(~name="courseNum3Height", ()));

  let (constraints, _) =
    React.useState(() =>
      courseNum1->Box.constraints
      @ courseNum2->Box.constraints
      @ courseNum3->Box.constraints
      @ [
        Kiwi.Ops.(v(courseNum1->Box.x2) == v(courseNumGuide)),
        Kiwi.Ops.(v(courseNum2->Box.x2) == v(courseNumGuide)),
        Kiwi.Ops.(v(courseNum3->Box.x2) == v(courseNumGuide)),
      ]
    );
  let (solver, setSolver) =
    React.useState(() => {
      let solver = mkSolver();
      let variables =
        Belt.Map.fromArray(
          [|
            (courseNumGuide, Suggest(40.5, Strength.strong)),
            (courseNum1->Box.x1, Derived),
            (courseNum1->Box.y1, Derived),
            (courseNum1->Box.x2, Derived),
            (courseNum1->Box.y2, Suggest(20.81, Strength.strong)),
            (courseNum1->Box.width, Suggest(40.5, Strength.strong)),
            (courseNum1->Box.height, Suggest(20.81, Strength.strong)),
            (courseNum2->Box.x1, Derived),
            (courseNum2->Box.y1, Derived),
            (courseNum2->Box.x2, Derived),
            (courseNum2->Box.y2, Suggest(20.81, Strength.strong)),
            (courseNum2->Box.width, Suggest(40.5, Strength.strong)),
            (courseNum2->Box.height, Suggest(20.81, Strength.strong)),
            (courseNum3->Box.x1, Derived),
            (courseNum3->Box.y1, Derived),
            (courseNum3->Box.x2, Derived),
            (courseNum3->Box.y2, Suggest(20.81, Strength.strong)),
            (courseNum3->Box.width, Suggest(39.86, Strength.strong)),
            (courseNum3->Box.height, Suggest(20.81, Strength.strong)),
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
    // setSolver(solver => {
    //   let variables =
    //     Belt.Map.fromArray(
    //       [|
    //         // no stays on affected variables, weak stays on unaffected variables, strong suggests on edits
    //         (aCenterX, Stay(Strength.weak)),
    //         (aCenterY, Derived),
    //         (bCenterX, Stay(Strength.weak)),
    //         (bCenterY, Derived),
    //         (gap, Stay(Strength.weak)),
    //         (guide, Suggest(data.y, Strength.strong)),
    //         // (guide2, Derived),
    //         // (vertGap, Stay(Strength.weak)),
    //         (guide2, Stay(Strength.weak)),
    //         (vertGap, Derived),
    //         (vertGuide1, Stay(Strength.weak)),
    //         (vertGuide2, Stay(Strength.weak)),
    //       |],
    //       ~id=(module VariableComparable),
    //     );

    //   solver->KiwiDeclarative.solve(~variables, ~constraints);
    // });
    None;
  };

  let onDragGuide2 = (~e, ~data: Draggable.draggableData) => {
    // TODO: for some reason setFoo triggers the cassowary variables to update...
    setFoo(x => 1 - x);
    // setSolver(solver => {
    //   let variables =
    //     Belt.Map.fromArray(
    //       [|
    //         // no stays on affected variables, weak stays on unaffected variables, strong suggests on edits
    //         (cCenterX, Stay(Strength.weak)),
    //         (cCenterY, Derived),
    //         (dCenterX, Stay(Strength.weak)),
    //         (dCenterY, Derived),
    //         (gap, Stay(Strength.weak)),
    //         // (guide, Derived),
    //         (guide, Stay(Strength.weak)),
    //         (guide2, Suggest(data.y, Strength.strong)),
    //         // (vertGap, Stay(Strength.weak)),
    //         (vertGap, Derived),
    //         (vertGuide1, Stay(Strength.weak)),
    //         (vertGuide2, Stay(Strength.weak)),
    //       |],
    //       ~id=(module VariableComparable),
    //     );

    //   solver->KiwiDeclarative.solve(~variables, ~constraints);
    // });
    None;
  };

  let onDragVertGuide1 = (~e, ~data: Draggable.draggableData) => {
    // TODO: for some reason setFoo triggers the cassowary variables to update...
    setFoo(x => 1 - x);
    // setSolver(solver => {
    //   let variables =
    //     Belt.Map.fromArray(
    //       [|
    //         // no stays on affected variables, weak stays on unaffected variables, strong suggests on edits
    //         (cCenterX, Stay(Strength.weak)),
    //         (cCenterY, Derived),
    //         (dCenterX, Stay(Strength.weak)),
    //         (dCenterY, Derived),
    //         (gap, Derived),
    //         (guide, Stay(Strength.weak)),
    //         (guide2, Stay(Strength.weak)),
    //         (vertGap, Derived),
    //         (vertGuide1, Suggest(data.x, Strength.strong)),
    //         (vertGuide2, Stay(Strength.weak)),
    //       |],
    //       ~id=(module VariableComparable),
    //     );

    //   solver->KiwiDeclarative.solve(~variables, ~constraints);
    // });
    None;
  };

  let onDragVertGuide2 = (~e, ~data: Draggable.draggableData) => {
    // TODO: for some reason setFoo triggers the cassowary variables to update...
    setFoo(x => 1 - x);
    // setSolver(solver => {
    //   let variables =
    //     Belt.Map.fromArray(
    //       [|
    //         // no stays on affected variables, weak stays on unaffected variables, strong suggests on edits
    //         (cCenterX, Stay(Strength.weak)),
    //         (cCenterY, Derived),
    //         (dCenterX, Stay(Strength.weak)),
    //         (dCenterY, Derived),
    //         (gap, Derived),
    //         (guide, Stay(Strength.weak)),
    //         (guide2, Stay(Strength.weak)),
    //         (vertGap, Derived),
    //         (vertGuide1, Stay(Strength.weak)),
    //         (vertGuide2, Suggest(data.x, Strength.strong)),
    //       |],
    //       ~id=(module VariableComparable),
    //     );

    //   solver->KiwiDeclarative.solve(~variables, ~constraints);
    // });
    None;
  };

  <div>
    foo->React.int
    <svg width="500" height="500">
      // <g>
      //   <line
      //     x1={(aCenterX->value() -. 30. -. 2.)->Js.Float.toString}
      //     y1={guide->value()->Js.Float.toString}
      //     x2={(bCenterX->value() +. 30. +. 2.)->Js.Float.toString}
      //     y2={guide->value()->Js.Float.toString}
      //     stroke="gray"
      //     strokeWidth="11"
      //   />
      //   <line
      //     x1={(aCenterX->value() -. 30.)->Js.Float.toString}
      //     y1={guide->value()->Js.Float.toString}
      //     x2={(bCenterX->value() +. 30.)->Js.Float.toString}
      //     y2={guide->value()->Js.Float.toString}
      //     stroke="lightblue"
      //     strokeWidth="8"
      //   />
      // </g>
      /* onStart */
      /* onDrag */

        <VerticalGuide height="500" onDrag=onDragVertGuide1 xPos=40. />
        <VerticalGuide height="500" onDrag=onDragVertGuide1 xPos=50. />
        <HorizontalGuide width="500" onDrag=onDragVertGuide1 yPos=50. />
        // <HorizontalGap width="10" onDrag=onDragVertGuide1 xPos=40. yPos=45. />
        <VerticalGap height="10" onDrag=onDragVertGuide1 xPos=150. yPos=50. />
        <VerticalGap height="12" onDrag=onDragVertGuide1 xPos=100. yPos=75. />
        <g transform="translate(0, 50)">
          <text
            x={courseNum1->Box.x1->value()->Js.Float.toString}
            y={courseNum1->Box.y1->value()->Js.Float.toString}
            style={ReactDOM.Style.make(~font="18px light sans-serif", ())}>
            "6.170"->React.string
          </text>
          <g transform="translate(50, 0)">
            <text x="0" y="0" style={ReactDOM.Style.make(~font="bold 18px sans-serif", ())}>
              "Software Studio"->React.string
            </text>
            <text x="0" y="20" style={ReactDOM.Style.make(~font="italic 16px serif", ())}>
              "Jackson & Satyanarayan"->React.string
            </text>
          </g>
        </g>
        <g transform="translate(0, 100)">
          <text
            x={courseNum2->Box.x1->value()->Js.Float.toString}
            y={courseNum2->Box.y1->value()->Js.Float.toString}
            style={ReactDOM.Style.make(~font="18px light sans-serif", ())}>
            "6.810"->React.string
          </text>
          <g transform="translate(50, 0)">
            <text x="0" y="0" style={ReactDOM.Style.make(~font="bold 18px sans-serif", ())}>
              "Engineering Interactive Technologies"->React.string
            </text>
            <text x="0" y="20" style={ReactDOM.Style.make(~font="italic 16px serif", ())}>
              "Mueller"->React.string
            </text>
          </g>
        </g>
        <g transform="translate(0, 150)">
          <text
            x={courseNum3->Box.x1->value()->Js.Float.toString}
            y={courseNum3->Box.y1->value()->Js.Float.toString}
            style={ReactDOM.Style.make(~font="18px light sans-serif", ())}>
            "6.811"->React.string
          </text>
          <g transform="translate(50, 0)">
            <text x="0" y="0" style={ReactDOM.Style.make(~font="bold 18px sans-serif", ())}>
              "Principles and Practice of Assistive Technology"->React.string
            </text>
            <text x="0" y="20" style={ReactDOM.Style.make(~font="italic 16px serif", ())}>
              "Miller, Greenberg, Keane"->React.string
            </text>
          </g>
        </g>
      </svg>
  </div>;
  // <Draggable position={x: aCenterX->value(), y: aCenterY->value()}>
  //   <circle cx="0" cy="0" r="20" fill="lightblue" stroke="gray" strokeWidth="2" />
  // </Draggable>
  // <Draggable position={x: bCenterX->value(), y: bCenterY->value()}>
  //   <circle cx="0" cy="0" r="20" fill="lightblue" stroke="gray" strokeWidth="2" />
  // </Draggable>
  // <HorizontalGuide width="500" onDrag=onDragGuide yPos={guide->value()} />
  // <Draggable position={x: cCenterX->value(), y: cCenterY->value()}>
  //   <circle cx="0" cy="0" r="20" fill="lightblue" stroke="gray" strokeWidth="2" />
  // </Draggable>
  // <Draggable position={x: dCenterX->value(), y: dCenterY->value()}>
  //   <circle cx="0" cy="0" r="20" fill="lightblue" stroke="gray" strokeWidth="2" />
  // </Draggable>
  // <HorizontalGuide width="500" onDrag=onDragGuide2 yPos={guide2->value()} />
  // <VerticalGuide height="500" onDrag=onDragVertGuide1 xPos={vertGuide1->value()} />
  // <VerticalGuide height="500" onDrag=onDragVertGuide2 xPos={vertGuide2->value()} />
  // <HorizontalGap
  //   onDrag=onDragVertGuide2
  //   width={(gap->value() -. 50.)->Js.Float.toString}
  //   xPos={aCenterX->value() +. 25.}
  //   yPos={guide->value()}
  // />
  // <HorizontalGap
  //   onDrag=onDragVertGuide2
  //   width={(gap->value() -. 50.)->Js.Float.toString}
  //   xPos={cCenterX->value() +. 25.}
  //   yPos={guide2->value()}
  // />
  // <Draggable position={x: cCenter->value(), y: 50.}>
  //   <circle cx="0" cy="0" r="20" fill="lightblue" stroke="gray" strokeWidth="2" />
  // </Draggable>
  // <Draggable position={x: dCenter->value(), y: 50.}>
  //   <circle cx="0" cy="0" r="20" fill="lightblue" stroke="gray" strokeWidth="2" />
  // </Draggable>
};
