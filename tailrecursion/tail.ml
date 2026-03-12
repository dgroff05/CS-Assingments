(* Author:      Dylan Groff
 * Instructor:  Dr. Zoppetti
 * Date:        9/24/25
 * Assignment:  Lab 2 - Tail Recursion
 * Description: Implement several functions in OCaml using tail recursion.
 *)

(* 
	***** PROVIDE COMMENT BLOCKS AND IMPLEMENTATIONS FOR THE FOLLOWING FUNCTIONS ***** 
	***** INCLUDE TYPE SIGNATURES ***** 
*)

(* float -> float -> float
 * Computes the square root of x to a tolerance tol using tail recursion.
 *)
let rec sqrt tol x = 
	let rec sqrtHelper tol x y =
		if abs_float (x -. (y *. y)) <= tol then
			y
		else
			sqrtHelper tol x ((y +. (x /. y)) /. 2.0)

	in sqrtHelper tol x x
;;

(* float -> float
 * Computes the square root of a float with a set tolerance of 0.00001
 *)
let rec sqrt2 = 
	sqrt 0.00001
;;

(* int -> int
 * Computes the factorial of x using "if-then-else" structure.
 *)
let rec factorial1 x = 
	if x = 0 then
		1
	else 
		x * factorial1 (x - 1)
;;

(* int -> int
 * Computes the factorial of x using pattern matching structure.
 *)
let rec factorial2 x = 
	match x with
	| 0 -> 1
	| _ -> x * factorial2 (x - 1)
;;

(* int -> int
 * Computes the factorial of x using tail recursion structure.
 *)
let rec factorial3 x =
	let rec factorial3Helper x factorial =
		match x with
		| 0 -> 1 * factorial
		| _ -> factorial3Helper (x - 1) (factorial * x)
	in factorial3Helper x 1
;;

(* int -> int
 * Computes the xth fibonacci number using tail recursion 
 * and pattern matching.
 *
 * When you try to compute larger numbers, they turn negative. This is what 
 * happened when I tried to compute the fibonachi of 150. This is because
 * the number was too large to be contained in a signed int. A signed int is 
 * typically 4 bytes long and in this case, does not have enough bytes to 
 * contain the number. This causes the number to overflow and wrap around
 * which makes the number appear negative based on its most significant bit 
 * becoming a 1.
 *)
let rec fibonacci x = 
	let rec fibonacciHelper x a b =
		match x with
		| 0 -> a
		| _ -> fibonacciHelper (x - 1) b (a + b)
	in fibonacciHelper x 0 1
;;

(* list -> list
 * Reverses a list using tail recusrion. (Unused)
 *)
let rec rev l = failwith "to be written"

(* function -> list -> list
 * Returns a new list containing each element from the given list with the 
 * function applied to it.
 *)
let rec map f l = 
	if l = []then
		[]
	else
		[f (List.hd l)] @ map f (List.tl l)
;;

(* function -> list -> list
 * Returns a new list containing each element from the given list with the 
 * function applied to it. This version is implemented tail recursively.
 *)
let rec map2 f l = 
	let rec map2Helper f l newList =
		match l with
		| [] -> newList
		| _::tl -> map2Helper f (List.tl l) (newList @ [f (List.hd l)])
	in map2Helper f l []
;;

(* int -> int -> int list
 * Takes two ints and returns a list of all ints in the range [a, b] 
 * inclusively. Returns an empty list if a > b. Implemented with tail 
 * recursion.
 *)
let rec range a b = 
	let rec rangeHelper a b list = 
		if a > b then
			list
		else
			rangeHelper (a + 1) b (list @ [a])
	in rangeHelper a b []
;; 


(* Computes a value which is the square roots of the numbers 1 through 20 to a
 * tolerance of 0.00001.
 *)
let roots : float list = map sqrt2 (map float_of_int (range 1 20));;



(****************************** Test Cases ***********************************)

sqrt 0.00000001 75.0;;
sqrt 0.00001 25.0;;

sqrt2 25.0;;
sqrt2 75.0;;

factorial1 4;;
factorial2 4;;
factorial3 4;;

fibonacci 3;;
fibonacci 44;;
fibonacci 150;;
(*Test your function by computing the 44th fibonacci number. 
What happens when you try to compute larger numbers? Why? 
Indicate the answer in a comment in your code.*)

map factorial1 [1;3;7];;
map fibonacci [1;3;7];;

map2 factorial1 [1;3;7];;
map2 fibonacci [1;3;7];;

range 2 5;;
range (-1) 5;;
range 10 2;;