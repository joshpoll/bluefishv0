let v = Kiwi.mkVarExpression;

type variables = {
  x1: Kiwi.variable,
  x2: Kiwi.variable,
  y1: Kiwi.variable,
  y2: Kiwi.variable,
  width: Kiwi.variable,
  height: Kiwi.variable
  };

type constraints = list(Kiwi.constraint_);

type t = {
  variables,
  constraints
};

let mk = (~name) => {
  let x1 = Kiwi.mkVariable(~name=name ++ "_x1", ());
  let x2 = Kiwi.mkVariable(~name=name ++ "_x2", ());
  let y1 = Kiwi.mkVariable(~name=name ++ "_y1", ());
  let y2 = Kiwi.mkVariable(~name=name ++ "_y2", ());
  let width = Kiwi.mkVariable(~name=name ++ "_width", ());
  let height = Kiwi.mkVariable(~name=name ++ "_height", ());

  {variables: {
    x1,
    x2,
    y1,
    y2,
    width,
    height,
  },
  constraints: [
    Kiwi.Ops.(v(x2) - v(x1) == v(width)),
    Kiwi.Ops.(v(y2) - v(y1) == v(height)),
  ]};
};

let variables = (b) => [b.x1, b.x2, b.y1, b.y2, b.width, b.height];
let constraints = (b) => b.constraints;

let x1 = (b) => b.variables.x1;
let x2 = (b) => b.variables.x2;
let y1 = (b) => b.variables.y1;
let y2 = (b) => b.variables.y2;
let width = (b) => b.variables.width;
let height = (b) => b.variables.height;
