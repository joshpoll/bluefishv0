'use strict';

var React = require("react");
var ReactDom = require("react-dom");
var ExampleStyles$Bluefishv0 = require("./ExampleStyles.bs.js");
var GeoffreyDiagram$Bluefishv0 = require("./GeoffreyDiagram.bs.js");
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

ReactDom.render(React.createElement(GeoffreyDiagram$Bluefishv0.make, {}), makeContainer("Kiwi Circles"));

ReactDom.render(React.createElement(GeoffreyDiagramDeclarative$Bluefishv0.make, {}), makeContainer("Kiwi Circles Declarative"));

exports.style = style;
exports.makeContainer = makeContainer;
/* style Not a pure module */
