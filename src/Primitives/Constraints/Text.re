[@react.component]
let make = (~text: string) => {
  let (isCalculating, setIsCalculating) = React.useState(() => true);
  let (width, setWidth) = React.useState(() => 0.);
  let (height, setHeight) = React.useState(() => 0.);

  let measuredRef =
    ReactDOM.Ref.callbackDomRef(node => {
      switch (Js.Nullable.toOption(node)) {
      | None => ()
      | Some(node) =>
        setWidth(_ => Webapi.Dom.Element.getBoundingClientRect(node)->Webapi.Dom.DomRect.width);
        setHeight(_ => Webapi.Dom.Element.getBoundingClientRect(node)->Webapi.Dom.DomRect.height);
      };

      setIsCalculating(_ => false);
    });

  <div>
    <span ref=measuredRef> text->React.string </span>
    <svg width="500" height="500">
      <rect width={width->Js.Float.toString} height={height->Js.Float.toString} />
    </svg>
  </div>;
};
