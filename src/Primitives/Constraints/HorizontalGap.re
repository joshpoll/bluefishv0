[@react.component]
let make = (~onDrag: Draggable.draggableEventHandler, ~width, ~xPos, ~yPos) => {
  <Draggable onDrag position={x: xPos, y: yPos}>
    <g>
      // <line x1="0" x2=width y1="0" y2="0" stroke="black" strokeWidth="3" opacity="0" />
      <line x1="0" x2="0" y1="-5" y2="5" stroke="red" strokeWidth="2" />
      <line
        x1="0"
        x2=width
        y1="0"
        y2="0"
        stroke="red"
        strokeWidth="4"
        // strokeDasharray="4"
      />
      <line x1=width x2=width y1="-5" y2="5" stroke="red" strokeWidth="2" />
    </g>
  </Draggable>;
};
