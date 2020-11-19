// https://medium.com/trabe/measuring-elements-in-react-6bf343b65347
// TODO: this doesn't work. try giving every node the same class, selecting all those nodes, then
// measuring them. switch initialization to be in an effect0 so can render and measure before
// initialization.
// alternatively, each text element should have an exposed ref callback that will give an updated
// size. still need to initialize before use. callback is used to update the text on every edit.
// for now we will hardcode

let containerStyle =
  ReactDOM.Style.make(
    ~display="inline-block",
    ~position="absolute",
    ~visibility="hidden",
    ~zIndex="-1",
    (),
  );

[@bs.val] external document: Js.t({..}) = "document";

type dimensions = {
  width: float,
  height: float,
};

let measureDomNode = (node/* , enhanceMeasurableNode */) => {
  let container = document##createElement("div");
  container##style #= containerStyle;

  // let clonedNode = Webapi.Dom.cloneNode(node.cloneNode(true);
  // const content = enhanceMeasurableNode(clonedNode);
  let content = node;

  container##appendChild(content);

  document##body##appendChild(container);

  let height = container##clientHeight;
  let width = container##clientWidth;

  container##parentNode##removeChild(container);
  {width, height};
};
