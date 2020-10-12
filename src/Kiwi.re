// Kiwi interface

type solver;
type variable;

module Strength = {
  [@bs.val] [@bs.module "kiwi.js"] [@bs.scope "Strength"] external strong: float = "strong";
};

module Operator = {
  type t;

  [@bs.val] [@bs.module "kiwi.js"] [@bs.scope "Operator"] external le: t = "Le";
  [@bs.val] [@bs.module "kiwi.js"] [@bs.scope "Operator"] external ge: t = "Ge";
  [@bs.val] [@bs.module "kiwi.js"] [@bs.scope "Operator"] external eq: t = "Eq";
};

[@bs.new] [@bs.module "kiwi.js"] external mkSolver: unit => solver = "Solver";
[@bs.new] [@bs.module "kiwi.js"] external mkVariable: unit => variable = "Variable";

[@bs.send] external addEditVariable: (solver, variable, float) => unit = "addEditVariable";
[@bs.send] external suggestValue: (solver, variable, float) => unit = "suggestValue";

/* TODO: constraint/expr language using operator overloading */
// expressions can be created by plus, minus, multiply, divide

// expressions
type expression;

[@bs.new] [@bs.module "kiwi.js"] external mkNumExpression: float => expression = "Expression";
[@bs.new] [@bs.module "kiwi.js"] external mkVarExpression: variable => expression = "Expression";
[@bs.send] external plus: (expression, expression) => expression = "plus";
[@bs.send] external minus: (expression, expression) => expression = "minus";
[@bs.send] external multiply: (expression, float) => expression = "multiply";
[@bs.send] external divide: (expression, float) => expression = "divide";
let (+) = plus;
let (-) = minus;
let (*) = multiply;
let (/) = divide;

// constraints
type constraint_;

[@bs.new] [@bs.module "kiwi.js"] external mkConstraint: (expression, Operator.t, expression) => constraint_ = "Constraint";

let (<=) = (e1, e2) => mkConstraint(e1, Operator.le, e2);
let (>=) = (e1, e2) => mkConstraint(e1, Operator.ge, e2);
let (==) = (e1, e2) => mkConstraint(e1, Operator.eq, e2);

[@bs.send] external addConstraint: (solver, constraint_) => unit = "addConstraint";
[@bs.send] external updateVariables: (solver, unit) => unit = "updateVariables";
[@bs.send] external value: (variable, unit) => float = "value";