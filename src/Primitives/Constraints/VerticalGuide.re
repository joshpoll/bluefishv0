[@react.component]
let make = (~height, ~onDrag: Draggable.draggableEventHandler, ~xPos) => {
  <Draggable axis="y" onDrag position={x: xPos, y: 0.}>
    <g>
      <line x1="0" x2="0" y1="0" y2=height stroke="black" strokeWidth="3" opacity="0" />
      <line
        x1="0"
        x2="0"
        y1="0"
        y2=height
        stroke="red"
        strokeWidth="3"
        strokeDasharray="4"
      />
    </g>
  </Draggable>;
};
