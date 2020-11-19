[@react.component]
let make = (~onDrag: Draggable.draggableEventHandler, ~height, ~xPos, ~yPos) => {
  <Draggable onDrag position={x: xPos, y: yPos}>
    <g>
      // <line x1="0" x2=width y1="0" y2="0" stroke="black" strokeWidth="3" opacity="0" />
      <line x1="-5" x2="5" y1="0" y2="0" stroke="lightblue" strokeWidth="2" />
      <line
        x1="0"
        x2="0"
        y1="0"
        y2=height
        stroke="lightblue"
        strokeWidth="4"
        // strokeDasharray="4"
      />
      <line x1="-5" x2="5" y1=height y2=height stroke="lightblue" strokeWidth="2" />
    </g>
  </Draggable>;
};
