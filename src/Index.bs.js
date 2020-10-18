'use strict';

var Kiwi = require("kiwi");
var React = require("react");
var ReactDom = require("react-dom");
var Kiwi$Bluefishv0 = require("./Kiwi.bs.js");
var ReactDraggable = require("react-draggable");
var ExampleStyles$Bluefishv0 = require("./ExampleStyles.bs.js");

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

function v(prim) {
  return new Kiwi.Expression(prim);
}

function n(prim) {
  return new Kiwi.Expression(prim);
}

var solver = new Kiwi.Solver();

var aCenter = new Kiwi.Variable();

solver.addEditVariable(aCenter, Kiwi.Strength.strong);

var bCenter = new Kiwi.Variable();

solver.addEditVariable(bCenter, Kiwi.Strength.strong);

var cCenter = new Kiwi.Variable();

var dCenter = new Kiwi.Variable();

var gap = new Kiwi.Variable();

solver.addConstraint(Kiwi$Bluefishv0.$eq(Kiwi$Bluefishv0.$neg(new Kiwi.Expression(bCenter), new Kiwi.Expression(aCenter)), new Kiwi.Expression(gap)));

solver.addConstraint(Kiwi$Bluefishv0.$eq(Kiwi$Bluefishv0.$neg(new Kiwi.Expression(cCenter), new Kiwi.Expression(bCenter)), new Kiwi.Expression(gap)));

solver.addConstraint(Kiwi$Bluefishv0.$eq(Kiwi$Bluefishv0.$neg(new Kiwi.Expression(dCenter), new Kiwi.Expression(cCenter)), new Kiwi.Expression(gap)));

solver.suggestValue(aCenter, 20);

solver.suggestValue(bCenter, 50);

solver.updateVariables();

solver.removeEditVariable(aCenter);

solver.removeEditVariable(bCenter);

solver.addEditVariable(gap, Kiwi.Strength.strong);

var aStay = Kiwi$Bluefishv0.mkStay(aCenter);

solver.addConstraint(aStay);

solver.suggestValue(gap, 40);

solver.updateVariables();

solver.removeEditVariable(gap);

console.log("aCenter", aCenter.value());

console.log("bCenter", bCenter.value());

ReactDom.render(React.createElement("svg", undefined, React.createElement("line", {
              stroke: "black",
              x1: "0.",
              x2: "100.",
              y1: "20.",
              y2: "20."
            }), React.createElement(ReactDraggable.default, {
              position: {
                x: aCenter.value(),
                y: 20
              },
              children: React.createElement("circle", {
                    cx: "0",
                    cy: "0",
                    fill: "blue",
                    r: "10"
                  })
            }), React.createElement(ReactDraggable.default, {
              position: {
                x: bCenter.value(),
                y: 20
              },
              children: React.createElement("circle", {
                    cx: "0",
                    cy: "0",
                    fill: "blue",
                    r: "10"
                  })
            }), React.createElement(ReactDraggable.default, {
              position: {
                x: cCenter.value(),
                y: 20
              },
              children: React.createElement("circle", {
                    cx: "0",
                    cy: "0",
                    fill: "blue",
                    r: "10"
                  })
            }), React.createElement(ReactDraggable.default, {
              position: {
                x: dCenter.value(),
                y: 20
              },
              children: React.createElement("circle", {
                    cx: "0",
                    cy: "0",
                    fill: "blue",
                    r: "10"
                  })
            })), makeContainer("Kiwi Circles"));

exports.style = style;
exports.makeContainer = makeContainer;
exports.v = v;
exports.n = n;
exports.solver = solver;
exports.aCenter = aCenter;
exports.bCenter = bCenter;
exports.cCenter = cCenter;
exports.dCenter = dCenter;
exports.gap = gap;
exports.aStay = aStay;
/* style Not a pure module */
