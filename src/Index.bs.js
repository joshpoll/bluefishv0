'use strict';

var React = require("react");
var ReactDom = require("react-dom");
var Text$Bluefishv0 = require("./Primitives/Constraints/Text.bs.js");
var BarChart$Bluefishv0 = require("./BarChart/BarChart.bs.js");
var TextLayout$Bluefishv0 = require("./TextDiagram/TextLayout.bs.js");
var ExampleStyles$Bluefishv0 = require("./ExampleStyles.bs.js");
var GeoffreyDiagramDeclarative$Bluefishv0 = require("./GeoffreyDiagramDeclarative.bs.js");

var style = document.createElement("style");

document.head.appendChild(style);

style.innerHTML = ExampleStyles$Bluefishv0.style;

function makeContainer(text) {
  var container = document.createElement("div");
  container.className = "container";
  var title = document.createElement("div");
  title.className = "containerTitle";
  title.innerText = text;
  var content = document.createElement("div");
  content.className = "containerContent";
  container.appendChild(title);
  container.appendChild(content);
  document.body.appendChild(container);
  return content;
}

ReactDom.render(React.createElement(BarChart$Bluefishv0.make, {}), makeContainer("Bar Chart"));

ReactDom.render(React.createElement(TextLayout$Bluefishv0.make, {}), makeContainer("Text Layout"));

ReactDom.render(React.createElement("div", undefined, React.createElement(Text$Bluefishv0.make, {
              text: "foo"
            }), React.createElement(Text$Bluefishv0.make, {
              text: "this is a very long string"
            })), makeContainer("Text Test"));

ReactDom.render(React.createElement(GeoffreyDiagramDeclarative$Bluefishv0.make, {}), makeContainer("Kiwi Circles Declarative"));

exports.style = style;
exports.makeContainer = makeContainer;
/* style Not a pure module */
