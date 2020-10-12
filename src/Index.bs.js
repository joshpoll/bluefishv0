'use strict';

var React = require("react");
var KiwiJs = require("kiwi.js");
var ReactDom = require("react-dom");
var Kiwi$Bluefishv0 = require("./Kiwi.bs.js");
var ExampleStyles$Bluefishv0 = require("./ExampleStyles.bs.js");
var BlinkingGreeting$Bluefishv0 = require("./BlinkingGreeting/BlinkingGreeting.bs.js");
var FetchedDogPictures$Bluefishv0 = require("./FetchedDogPictures/FetchedDogPictures.bs.js");
var ReducerFromReactJSDocs$Bluefishv0 = require("./ReducerFromReactJSDocs/ReducerFromReactJSDocs.bs.js");
var ReasonUsingJSUsingReason$Bluefishv0 = require("./ReasonUsingJSUsingReason/ReasonUsingJSUsingReason.bs.js");

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

ReactDom.render(React.createElement(BlinkingGreeting$Bluefishv0.make, {
          children: "Hello!"
        }), makeContainer("Blinking Greeting"));

ReactDom.render(React.createElement(ReducerFromReactJSDocs$Bluefishv0.make, {}), makeContainer("Reducer From ReactJS Docs"));

ReactDom.render(React.createElement(FetchedDogPictures$Bluefishv0.make, {}), makeContainer("Fetched Dog Pictures"));

ReactDom.render(React.createElement(ReasonUsingJSUsingReason$Bluefishv0.make, {}), makeContainer("Reason Using JS Using Reason"));

var solver = new KiwiJs.Solver();

var left = new KiwiJs.Variable();

var width = new KiwiJs.Variable();

solver.addEditVariable(left, KiwiJs.Strength.strong);

solver.addEditVariable(width, KiwiJs.Strength.strong);

solver.suggestValue(left, 100);

solver.suggestValue(width, 400);

function v(prim) {
  return new KiwiJs.Expression(prim);
}

function n(prim) {
  return new KiwiJs.Expression(prim);
}

var right = new KiwiJs.Variable();

solver.addConstraint(Kiwi$Bluefishv0.$eq(Kiwi$Bluefishv0.$plus(new KiwiJs.Expression(left), new KiwiJs.Expression(width)), new KiwiJs.Expression(right)));

solver.updateVariables();

console.log("left", left.value());

console.log("width", width.value());

console.log("right", right.value());

console.log("left - right + width", left.value() - right.value() + width.value());

exports.style = style;
exports.makeContainer = makeContainer;
exports.solver = solver;
exports.left = left;
exports.width = width;
exports.v = v;
exports.n = n;
exports.right = right;
/* style Not a pure module */
