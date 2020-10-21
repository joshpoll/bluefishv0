// ReasonML version of Kiwi example.

// Create a solver
let solver = Kiwi.mkSolver();

// Create edit variables
let left = Kiwi.mkVariable();
let width = Kiwi.mkVariable();
solver->Kiwi.addEditVariable(left, Kiwi.Strength.strong);
solver->Kiwi.addEditVariable(width, Kiwi.Strength.strong);
solver->Kiwi.suggestValue(left, 100.);
solver->Kiwi.suggestValue(width, 400.);

// Create and add a constraint
let v = Kiwi.mkVarExpression;
let n = Kiwi.mkNumExpression;

let right = Kiwi.mkVariable();
solver->Kiwi.addConstraint(Kiwi.Ops.(v(left) - v(right) + v(width) == n(0.)));

// Solve the constraints
solver->Kiwi.updateVariables();
type assertion('a) = (~actual: 'a, ~expected: 'a, ~message: string=?) => unit;
// [@bs.module "assert"] external strictEqual: assertion('a) = "strictEqual";
// strictEqual(~actual=right->Kiwi.value(), ~expected=500.);
