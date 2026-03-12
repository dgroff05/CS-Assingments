(* Author:      Dylan Groff
 * Instructor:  Dr. Zoppetti
 * Date:        10/14/25
 * Assignment:  Lab 3 - Tuples and Higher-Order Functions
 * Description: Implement several higher-order and tuple functions in OCaml.
 *)

(* CSCI 330: OCaml Lab 3
 * misc3.ml
 *)

(* ***** DOCUMENT ALL FUNCTIONS YOU WRITE OR COMPLETE ***** *)

(* int * string * (string * int) list -> int
 * Finds the first key that equals k in the list of key-pairs l and returns the
 * value. If the key is not found, the default value d is returned.
 *)
let rec assoc (d,k,l) = 
  match l with
  | [] -> d
  | (key,value)::t -> 
  if (key = k) then
    value
  else
    assoc (d,k,t) 
;;

(* int list -> int list
 * Removes the duplicates from a given list.
 *)
(* fill in the code wherever it says : failwith "to be written" *)
let removeDuplicates l = 
  let rec helper (seen,rest) = 
      match rest with 
        [] -> seen
      | h::t -> 
        let seen' = if (List.mem h seen) then seen else h::seen in
        let rest' = t in 
	  helper (seen',rest') 
  in
      List.rev (helper ([],l))
;;

(* (int -> int * bool) * int -> int
 * Runs the given function f while the condition returned is true.
 *)
(* Small hint: see how ffor is implemented below *)
let rec wwhile (f,b) = 
  let (result,bool) = f b in
  if bool then wwhile (f,result) else result
;;

(* (int -> int) * int -> int
 * Repeatedly updates b with f(b) until b = f(b) and then returns b.
 *)
(* fill in the code wherever it says : failwith "to be written" *)
let fixpoint (f,b) = wwhile ((fun x -> (f x,x != f x)),b)


(* ffor: int * int * (int -> unit) -> unit
   Applies the function f to all the integers between low and high
   inclusive; the results get thrown away.
 *)
let rec ffor (low,high,f) = 
  if low>high 
  then () 
  else let _ = f low in ffor (low+1,high,f)
;;

(****************************** Test Cases ***********************************)
assoc (-1,"jeff", [("sorin",85);("jeff",23);("moose",44)]);; (*int = 23*)
assoc (-1,"bob",[("mary",77);("bob",33);("bob",44)]);; (*int = 33*)
assoc (1337,"alice",[("bob",1);("charlie",2)]);; (*int = 1337*)

removeDuplicates [1;6;2;4;12;2;13;6;9];; (* int list = [1;6;2;4;12;13;9] *)

let f x =
  let xx = x * x * x
  in (xx, xx < 100);;

wwhile (f, 2);; (* int = 512 *)

let g x = truncate (1e6 *. cos (1e-6 *. float x));;
let h x = x * x;;
fixpoint (g,0);;  (* int = 739085 *)
fixpoint (h, 0);; (* int = 0 *)
fixpoint (h, 1);; (* int = 1 *)