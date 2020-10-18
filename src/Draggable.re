// Draggable interface

type draggableData = {
  node: React.element, /* TODO: actually an HTML element. does it matter? */
  // invariant: lastX + deltaX === x
  x: float,
  y: float,
  deltaX: float,
  deltaY: float,
  lastX: float,
  lastY: float,
};

type draggableEventHandler = (~e: React.element, ~data: draggableData) => option(bool);

type position = {
  x: float,
  y: float,
};

/* TODO: add more props */
[@bs.module "react-draggable"] [@react.component]
external make:
  (
    ~axis: string=?,
    ~onStart: draggableEventHandler=?,
    ~onDrag: draggableEventHandler=?,
    ~onStop: draggableEventHandler=?,
    ~position: position=?,
    ~children: React.element
  ) =>
  React.element =
  "default";
