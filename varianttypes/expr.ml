(* 
 * Name: Dylan Groff
 * Date: 
 * Course: CSCI 330 - Programming Languages
 * Assignment: Variant Types
 *
 * Assignment Attribution:
 *   This lab is based on code by Chris Stone (lab from CSE 130 by Sorin Lerner at UCSD)
 *
 * Description: 
 *)

let pi = 4.0 *. (atan 1.0)

type expr = 
    VarX
  | VarY
  | Sine     of expr
  | Cosine   of expr
  | Average  of expr * expr
  | Times    of expr * expr
  | Thresh   of expr * expr * expr * expr	
  | Square   of expr
  | Maximum  of expr * expr * expr
(* TODO: add two new "types" of expressions *)

type rng = int * int -> int
type builder_fun = rng * int -> expr

let rec exprToString e =
  match e with 
    VarX -> "x"
  | VarY -> "y"
  | Sine expr -> "sin(pi*" ^ exprToString expr ^ ")"
  | Cosine expr -> "cos(pi*" ^ exprToString expr ^ ")"
  | Average (expr1,expr2) -> "((" ^ exprToString expr1 ^ "+" ^ exprToString expr2 ^ ")/2)"
  | Times (expr1,expr2) -> exprToString expr1 ^ "*" ^ exprToString expr2
  | Thresh (expr1,expr2,expr3,expr4) -> "(" ^ exprToString expr1 ^ "<" ^ exprToString expr2 ^ "?" ^ exprToString expr3 ^ ":" 
  ^ exprToString expr4 ^ ")"
  | Square expr -> "(" ^ exprToString expr ^ ")^2"
  | Maximum (expr1,expr2,expr3) -> "max(" ^ exprToString expr1 ^ "," ^ exprToString expr2 ^ "," ^ exprToString expr3 ^ ")"

(* build functions:
     Use these helper functions to generate elements of the expr
     datatype rather than using the constructors directly.  This
     provides a little more modularity in the design of your program *)

let buildX()                       = VarX
let buildY()                       = VarY
let buildSine(e)                   = Sine(e)
let buildCosine(e)                 = Cosine(e)
let buildAverage(e1,e2)            = Average(e1,e2)
let buildTimes(e1,e2)              = Times(e1,e2)
let buildThresh(a,b,a_less,b_less) = Thresh(a,b,a_less,b_less)
let buildSquare(e)                 = Square(e)
let buildMaximum(e1,e2,e3)         = Maximum(e1,e2,e3)

(* TODO: add two new buildXXXXXXX functions *)


let rec eval (e, x, y) =
  match e with 
    VarX -> x
  | VarY -> y
  | Sine expr -> sin (pi *. eval (expr,x,y))
  | Cosine expr -> cos (pi *. eval (expr,x,y))
  | Average (expr1,expr2) -> (eval (expr1,x,y) +. eval (expr2,x,y)) /. 2.0
  | Times (expr1,expr2) -> eval (expr1,x,y) *. eval (expr2,x,y)
  | Thresh (expr1,expr2,expr3,expr4) -> if eval (expr1,x,y) < eval (expr2,x,y) then eval (expr3,x,y) else eval (expr4,x,y)
  | Square expr -> eval (expr,x,y) *. eval (expr,x,y)
  | Maximum (expr1,expr2,expr3) -> max (max (eval (expr1,x,y)) (eval (expr2,x,y))) (eval (expr3,x,y)) 
                                  (* Takes the max of first two expr and then takes the max of the result and the third expr *)

(* (eval_fn e (x,y)) evaluates the expression e at the point (x,y) and then
 * verifies that the result is between -1 and 1.  If it is, the result is returned.  
 * Otherwise, an exception is raised.
 *)
let eval_fn e (x,y) = 
  let rv = eval (e,x,y) in
  assert (-1.0 <= rv && rv <= 1.0);
  rv

let sampleExpr =
      buildCosine(buildSine(buildTimes(buildCosine(buildAverage(buildCosine(
      buildX()),buildTimes(buildCosine (buildCosine (buildAverage
      (buildTimes (buildY(),buildY()),buildCosine (buildX())))),
      buildCosine (buildTimes (buildSine (buildCosine
      (buildY())),buildAverage (buildSine (buildX()), buildTimes
      (buildX(),buildX()))))))),buildY())))

let sampleExpr2 =
  buildThresh(buildX(),buildY(),buildSine(buildX()),buildCosine(buildY()))




(******************* Functions you need to write **********)

(* build: (int*int->int) * int -> Expr 
   Build an expression tree.  The second argument is the depth, 
   the first is a random function.  A call to rand(2,5) will give
   you a random number in the range [2,5)  
   (2 inclusive, and 5 exclusive).

   Your code should call buildX, buildSine, etc. to construct
   the expression.
*)
let rec build (rand,depth) = 
  if (depth > 0) then
    let randOp = rand (0,5) in
    match randOp with
      0 -> buildAverage (build (rand,depth - 1),build (rand,depth - 1))
    | 1 -> buildTimes (build (rand,depth - 1),build (rand,depth - 1))
    | 2 -> buildCosine (build (rand,depth - 1))
    | 3 -> buildThresh (build (rand,depth - 1),build (rand,depth - 1),build (rand,depth - 1),build (rand,depth - 1))
    | 4 -> buildSine (build (rand,depth - 1))
    | _ -> buildY () (* Garbage case just for the compiler, will never execute *)
  else
    let randVar = rand (0,2) in
    match randVar with
      0 -> buildX ()
    | 1 -> buildY ()
    | _ -> buildY () (* Garbage case just for the compiler, will never execute *)
  


let rec build2 (rand,depth) = 
  if (depth > 0) then
    let randOp = rand (0,7) in
    match randOp with
      0 -> buildAverage (build2 (rand,depth - 1),build2 (rand,depth - 1))
    | 1 -> buildTimes (build2 (rand,depth - 1),build2 (rand,depth - 1))
    | 2 -> buildCosine (build2 (rand,depth - 1))
    | 3 -> buildThresh (build2 (rand,depth - 1),build2 (rand,depth - 1),build2 (rand,depth - 1),build2 (rand,depth - 1))
    | 4 -> buildSine (build2 (rand,depth - 1))
    | 5 -> buildSquare (build2 (rand,depth - 1))
    | 6 -> buildMaximum (build2 (rand,depth - 1),build2 (rand,depth - 1),build2 (rand,depth - 1))
    | _ -> buildY () (* Garbage case just for the compiler, will never execute *)
  else
    let randVar = rand (0,2) in
    match randVar with
      0 -> buildX ()
    | 1 -> buildY ()
    | _ -> buildY () (* Garbage case just for the compiler, will never execute *)

(* g1,c1 : unit -> ((int*int->int) * int -> Expr) * int * int * int
 * these functions should return the parameters needed to create your 
 * top color / grayscale pictures.
 * they should return (function,depth,seed1,seed2)
 * Function should be build or build2 (whichever you used to create
 * the image)
 *)

(* emitGrayscale (eval_fn (build (makeRand,8)),150,"art_g_test1") *)
let g1 () = (build2,11,7,180)

let c1 () = (build2,9,6,400)

(* Test Cases *)

let _ = exprToString (Thresh(VarX,VarY,VarX,(Times(Sine(VarX),Cosine(Average(VarX,VarY))))))
(* string = "(x<y?x:sin(pi*x)*cos(pi*((x+y)/2)))" *)

let _ = eval (Sine(Average(VarX,VarY)),0.5,-0.5) (* float = 0.0 *)
let _ = eval (Sine(Average(VarX,VarY)),0.3,0.3) (* float = 0.809016994375 *)