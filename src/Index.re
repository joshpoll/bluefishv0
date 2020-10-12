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

// All 4 examples.
ReactDOMRe.render(
  <BlinkingGreeting>
    {React.string("Hello!")}
  </BlinkingGreeting>,
  makeContainer("Blinking Greeting"),
);

ReactDOMRe.render(
  <ReducerFromReactJSDocs />,
  makeContainer("Reducer From ReactJS Docs"),
);

ReactDOMRe.render(
  <FetchedDogPictures />,
  makeContainer("Fetched Dog Pictures"),
);

ReactDOMRe.render(
  <ReasonUsingJSUsingReason />,
  makeContainer("Reason Using JS Using Reason"),
);

// ReasonML version of Kiwi example.

// Create a solver
let solver = Kiwi.mkSolver();

// Create edit variables
let left = Kiwi.mkVariable();
let width = Kiwi.mkVariable();
solver->Kiwi.addEditVariable(left, Kiwi.Strength.strong);
solver->Kiwi.addEditVariable(width, Kiwi.Strength.strong);
solver->Kiwi.suggestValue(left, 100.);
solver->Kiwi.suggestValue(width, 400.);

// Create and add a constraint
let v = Kiwi.mkVarExpression;
let n = Kiwi.mkNumExpression;

let right = Kiwi.mkVariable();
// solver->Kiwi.addConstraint(Kiwi.(v(left) - v(right) + v(width) == n(0.)));
solver->Kiwi.addConstraint(Kiwi.(v(left) + v(width) == v(right)));

// Solve the constraints
solver->Kiwi.updateVariables();
type assertion('a) = (~actual: 'a, ~expected: 'a, ~message: string=?) => unit;
// [@bs.module "assert"] external strictEqual: assertion('a) = "strictEqual";
// strictEqual(~actual=right->Kiwi.value(), ~expected=500.);
Js.log2("left", left->Kiwi.value());
Js.log2("width", width->Kiwi.value());
Js.log2("right", right->Kiwi.value());
Js.log2("left - right + width", left->Kiwi.value() -. right->Kiwi.value() +. width->Kiwi.value());