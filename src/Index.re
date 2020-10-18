// Entry point

[@bs.val] external document: Js.t({..}) = "document";

// We're using raw DOM manipulations here, to avoid making you read
// ReasonReact when you might precisely be trying to learn it for the first
// time through the examples later.
let style = document##createElement("style");
document##head##appendChild(style);
style##innerHTML #= ExampleStyles.style;

let makeContainer = text => {
  let container = document##createElement("div");
  container##className #= "container";

  let title = document##createElement("div");
  title##className #= "containerTitle";
  title##innerText #= text;

  let content = document##createElement("div");
  content##className #= "containerContent";

  let () = container##appendChild(title);
  let () = container##appendChild(content);
  let () = document##body##appendChild(container);

  content;
};

// // All 4 examples.
// ReactDOMRe.render(
//   <BlinkingGreeting>
//     {React.string("Hello!")}
//   </BlinkingGreeting>,
//   makeContainer("Blinking Greeting"),
// );

// ReactDOMRe.render(
//   <ReducerFromReactJSDocs />,
//   makeContainer("Reducer From ReactJS Docs"),
// );

// ReactDOMRe.render(
//   <FetchedDogPictures />,
//   makeContainer("Fetched Dog Pictures"),
// );

// ReactDOMRe.render(
//   <ReasonUsingJSUsingReason />,
//   makeContainer("Reason Using JS Using Reason"),
// );

// ReasonML version of Kiwi example.

let v = Kiwi.mkVarExpression;
let n = Kiwi.mkNumExpression;

// // Create a solver
// let solver = Kiwi.mkSolver();

// // Create edit variables
// let left = Kiwi.mkVariable();
// let width = Kiwi.mkVariable();
// solver->Kiwi.addEditVariable(left, Kiwi.Strength.strong);
// solver->Kiwi.addEditVariable(width, Kiwi.Strength.strong);

// // Create and add a constraint

// let centerX = Kiwi.mkVariable();
// // solver->Kiwi.addConstraint(Kiwi.(v(left) - v(right) + v(width) == n(0.)));
// solver->Kiwi.addConstraint(Kiwi.(v(left) + v(width) / 2. == v(centerX)));

// solver->Kiwi.suggestValue(left, 20.);
// solver->Kiwi.suggestValue(width, 500.);

// // Solve the constraints
// solver->Kiwi.updateVariables();
// type assertion('a) = (~actual: 'a, ~expected: 'a, ~message: string=?) => unit;
// // [@bs.module "assert"] external strictEqual: assertion('a) = "strictEqual";
// // strictEqual(~actual=right->Kiwi.value(), ~expected=500.);
// Js.log2("left", left->Kiwi.value());
// Js.log2("width", width->Kiwi.value());
// Js.log2("centerX", centerX->Kiwi.value());
// // Js.log2("left - right + width", left->Kiwi.value() -. centerX->Kiwi.value() +.
// // width->Kiwi.value());

// ReactDOMRe.render(
//   <svg>
//     <rect x={left->Kiwi.value()->Js.Float.toString} y="5" width={width->Kiwi.value()->Js.Float.toString} height="10" />
//   </svg>,
//   makeContainer("Kiwi Test"),
// );

// equidistant circles test

let solver = Kiwi.mkSolver();
let aCenter = Kiwi.mkVariable();
solver->Kiwi.addEditVariable(aCenter, Kiwi.Strength.strong);
let bCenter = Kiwi.mkVariable();
solver->Kiwi.addEditVariable(bCenter, Kiwi.Strength.strong);
let cCenter = Kiwi.mkVariable();
// solver->Kiwi.addEditVariable(cCenter, Kiwi.Strength.strong);
let dCenter = Kiwi.mkVariable();
// solver->Kiwi.addEditVariable(dCenter, Kiwi.Strength.strong);

let gap = Kiwi.mkVariable();
// solver->Kiwi.addEditVariable(gap, Kiwi.Strength.strong);

solver->Kiwi.addConstraint(Kiwi.(v(bCenter) - v(aCenter) == v(gap)));
solver->Kiwi.addConstraint(Kiwi.(v(cCenter) - v(bCenter) == v(gap)));
solver->Kiwi.addConstraint(Kiwi.(v(dCenter) - v(cCenter) == v(gap)));

solver->Kiwi.suggestValue(aCenter, 20.);
solver->Kiwi.suggestValue(bCenter, 50.);
solver->Kiwi.updateVariables();
solver->Kiwi.removeEditVariable(aCenter);
solver->Kiwi.removeEditVariable(bCenter);

// start editing gap with a weak stay on aCenter
solver->Kiwi.addEditVariable(gap, Kiwi.Strength.strong);
let aStay = Kiwi.mkStay(aCenter);
solver->Kiwi.addConstraint(aStay);
solver->Kiwi.suggestValue(gap, 40.);
solver->Kiwi.updateVariables();
solver->Kiwi.removeEditVariable(gap);

Js.log2("aCenter", aCenter->Kiwi.value());
Js.log2("bCenter", bCenter->Kiwi.value());
// Js.log2("cCenter", cCenter->Kiwi.value());
// Js.log2("dCenter", dCenter->Kiwi.value());

ReactDOMRe.render(
  <svg>
    <line x1="0." y1="20." x2="100." y2="20." stroke="black" />
    // <Draggable>
    //   <circle cx={aCenter->Kiwi.value()->Js.Float.toString} cy="20" r="10" />
    // </Draggable>
    <Draggable position={x: aCenter->Kiwi.value(), y: 20.,}>
      <circle cx="0" cy="0" r="10" fill="blue" />
    </Draggable>
    <Draggable position={x: bCenter->Kiwi.value(), y: 20.,}>
      <circle cx="0" cy="0" r="10" fill="blue" />
    </Draggable>
    <Draggable position={x: cCenter->Kiwi.value(), y: 20.,}>
      <circle cx="0" cy="0" r="10" fill="blue" />
    </Draggable>
    <Draggable position={x: dCenter->Kiwi.value(), y: 20.,}>
      <circle cx="0" cy="0" r="10" fill="blue" />
    </Draggable>
  </svg>,
  makeContainer("Kiwi Circles"),
);

// ReactDOMRe.render(
//   <Draggable>
//     <div>{"drag me!"|>React.string}</div>
//   </Draggable>,
//   makeContainer("Drag Test"),
// );