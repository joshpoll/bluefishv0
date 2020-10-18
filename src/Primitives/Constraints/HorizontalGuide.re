[@react.component]
let make = (~width, ~onDrag: Draggable.draggableEventHandler, ~yPos) => {
  <Draggable axis="y" onDrag position={x: 0., y: yPos}>
    <g>
      <line x1="0" x2=width y1="0" y2="0" stroke="black" strokeWidth="3" opacity="0" />
      <line
        x1="0"
        x2=width
        y1="0"
        y2="0"
        stroke="red"
        strokeWidth="3"
        strokeDasharray="4"
      />
    </g>
  </Draggable>;
};
