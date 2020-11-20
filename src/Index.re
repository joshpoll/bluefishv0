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

// ReactDOMRe.render(
//   // <svg>
//   //   <line x1="0." y1="20." x2="100." y2="20." stroke="black" />
//   //   <Draggable onDrag={onDrag} position={x: aCenter->Kiwi.value(), y: 20.,}>
//   //     <circle cx="0" cy="0" r="10" fill="blue" />
//   //   </Draggable>
//   //   <Draggable position={x: bCenter->Kiwi.value(), y: 20.,}>
//   //     <circle cx="0" cy="0" r="10" fill="blue" />
//   //   </Draggable>
//   //   <Draggable position={x: cCenter->Kiwi.value(), y: 20.,}>
//   //     <circle cx="0" cy="0" r="10" fill="blue" />
//   //   </Draggable>
//   //   <Draggable position={x: dCenter->Kiwi.value(), y: 20.,}>
//   //     <circle cx="0" cy="0" r="10" fill="blue" />
//   //   </Draggable>
//   // </svg>,
//   <GeoffreyDiagram />,
//   makeContainer("Kiwi Circles"),
// );

ReactDOMRe.render(<BarChart />, makeContainer("Bar Chart"));

ReactDOMRe.render(<TextLayout />, makeContainer("Text Layout")) /* )*/;

ReactDOMRe.render(
  <div> <Text text="foo" /> <Text text="this is a very long string" /> </div>,
  makeContainer("Text Test"),
);

ReactDOMRe.render(<GeoffreyDiagramDeclarative />, makeContainer("Kiwi Circles Declarative")) /* )*/;

// ReactDOMRe.render(
//   <Draggable>
//     <div>{"drag me!"|>React.string}</div>
//   </Draggable>,
//   makeContainer("Drag Test"),
