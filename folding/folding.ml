(* CSCI 330: Programming Assignment 5
 * misc5.ml
 * Name: Dylan Groff
 * Date: 11/23/25
 * Course: CSCI 330 - Programming Languages
 * Assignment: folding
 * Description: Implement several functions using list folding.
 *)
(* For this assignment, you may use the following library functions:

   List.map
   List.fold_left
   List.fold_right
   List.split
   List.combine
   List.length
   List.append
   List.rev

   See http://caml.inria.fr/pub/docs/manual-ocaml/libref/List.html for
   documentation.
*)



(* Do not change the skeleton code! The point of this assignment is to figure
 * out how the functions can be written this way (using fold). You may only
 * replace the   failwith "to be implemented"   part. *)



(*****************************************************************)
(******************* 1. Warm Up   ********************************)
(*****************************************************************)

(* succeeded tests *)
(* int list -> int *)
let sqsum xs = 
  (* squares x and adds it to the accumulator *)
  let f a x = (x * x) + a in
  let base = 0 in
    List.fold_left f base xs

(* tests succeeded *)
(* ('a -> 'a) list -> 'a -> 'a *)
let pipe fs s = 
  (* runs the function x on the previous function output a *)
  let f a x = x a in
  let base = s in
    List.fold_left f base fs

(* tests succeeded *)
(* ('a -> 'a) list -> ('a -> 'a) *)
let pipec fs = 
  (* runs function x on function a that returns the base value to ensure a function is returned *)
  let f a x = fun b ->  x (a b) in
  (* base is a function that returns itself, needs to be a 
     function in order for pipec to return a function. *)
  let base = fun b -> b in
    List.fold_left f base fs

(* tests succeeded *)
(* string -> string list -> string *)
let rec sepConcat sep sl = match sl with 
  | [] -> ""
  | h :: t -> 
      (* concatenates seperator between previous values and the next value *)
      let f a x = a ^ sep ^ x in
      (* sets base to the first element in the list *)
      let base = h in
      let l = t in
        List.fold_left f base l

(* tests succeeded *)
(* ('a -> string) -> 'a list -> string *)
(* calls sepConcat to seperate each element with "; " and then concats that 
   result with brackets to make it into the full list format. *)
let stringOfList f l = "[" ^ sepConcat "; " (List.map f l) ^ "]"

(* tests succeeded *)
(* int list -> int list -> int list *)
let prodLists l1 l2 =
  (* Multiplies each pair of elements from the lists together and appends it to the accumulator.
     Append is needed in order to preserve the order of the list. *)
  let f a x = a @ [(fst x) * (snd x)] in
  (* sets base to an empty list to store the new values *)
  let base = [] in
  let args = List.combine l1 l2 in
    List.fold_left f base args

(*****************************************************************)
(******************* 2. Big Numbers ******************************)
(*****************************************************************)

(* clone : 'a -> int -> 'a list 

clone takes as input x and an integer n. The result is a list of length n, where each element is x. 
If n is 0 or negative, clone will return the empty list. 

# clone 3 5;;
- : int list = [3; 3; 3; 3; 3] 
# clone "foo" 2;;
- : string list = ["foo"; "foo"]
# clone clone (-3);;
- : ('_a -> int -> '_a list) list = [])
*)
let rec clone x n = if (n <= 0) then [] else x::(clone x (n - 1))

(*
padZero : int list -> int list -> int list * int list 

padZero takes two lists: [x1,...,xn] [y1,...,ym] and adds zeros in front to make the lists equal in length. 

# padZero [9;9] [1;0;0;2];;
- : int list * int list = ([0;0;9;9],[1;0;0;2]) 
# padZero [1;0;0;2] [9;9];;
- : int list * int list = ([1;0;0;2],[0;0;9;9]) 
*)
let rec padZero l1 l2 = 
   let l1len = List.length l1 in
   let l2len = List.length l2 in
    ((clone 0 (l2len-l1len)@l1), (clone 0 (l1len-l2len)@l2))

(*
removeZero : int list -> int list 

removeZero takes a list and removes a prefix of trailing zeros. 

# removeZero [0;0;0;1;0;0;2];;
- : int list = [1;0;0;2] 
# removeZero [9;9];;
- : int list = [9;9] 
# removeZero [0;0;0;0];;
- : int list = [] 
*)

let rec removeZero l = 
  match l with
  | 0::t -> removeZero t
  | _ -> l

(* tests succeeded *)
(* int list -> int list -> int list *) (* (fst a,[fst x + snd x + snd a]) *)
let bigAdd l1 l2 = 
  let add (l1, l2) = 
    (* Sets the tens digit of the sum of the pair + prev carry to the carry. Cons the ones 
       digit to the list of the rest of the numbers. *)
    let f a x = ((fst x + snd x + fst a) / 10,(fst a + fst x + snd x) mod 10 :: snd a) in
    (* sets the starting carry to 0 and starting list to empty list *)
    let base = (0, []) in
    (* reverses the combined list so we start from the ones digit *)
    let args = List.rev (List.combine l1 l2) in
    let (carry, res) = List.fold_left f base args in
      carry::res
  in 
    removeZero (add (padZero l1 l2))

(* EXTRA CREDIT BELOW *)
(* tests succeeded *)
(* int -> int list -> int list *)
let rec mulByDigit i l =
  let mult (l1, l2) = 
    (* sets the carry to tens digit and up of the product + prev carry. 
       Cons the ones digit of the product + prev pair to the rest of the numbers. *)
    let f a x = ((fst x * snd x + fst a) / 10, (fst x * snd x + fst a) mod 10 :: snd a) in
    (* sets the starting carry to 0 and starting list to empty list *)
    let base = (0, []) in
    (* reverses the list so we start with the ones digit *)
    let args = List.rev (List.combine l1 l2) in
    let (carry, res) = List.fold_left f base args in
      carry::res
  in 
    (* Creates an list of equal size filled with the digit we are multiplying by.
       Also removes any unneccessary 0s. *)
    removeZero (mult ((clone i (List.length l)), l))

(* tests succeeded *)
(* int list -> int list -> int list *)
let bigMul l1 l2 = 
  (* Uses fst a to hold the offset. The offset is used to shift the product over to the correct digits place
     before adding the product and the prev product. This done by creating a list of 0s with the offset being
     the length. I used mulByDigit to get the product for each digit of the multiplicand. Then used bigAdd to
     sum the products each time with the offset included. The offset is incremented by 1 after each time. *)
  let f a x = ((fst a) + 1, bigAdd ((mulByDigit x l2) @ (clone 0 (fst a))) (snd a)) in
  (* the offset starts at 0 and the list of the product starts as an empty list *)
  let base = (0, []) in 
  (* reverses the list of multipliers so the least significant digit is first in the list. *)
  let args = List.rev l1 in  
  let (_, res) = List.fold_left f base args in
    res
;;

(* Test Cases *)

sqsum [];;
(* int = 0 *)
sqsum [1;2;3;4] ;;
(* int = 30 *)
sqsum [-1;-2;-3;-4] ;;
(* int = 30 *)

pipe [] 3;;
(* int = 3 *)
pipe [(fun x-> 2*x);(fun x -> x + 3)] 3;;
(* int = 9 *)
pipe [(fun x -> x + 3);(fun x-> 2*x)] 3;;
(* int = 12 *)

pipec [] 3;;
(* int = 3 *)
pipec [(fun x-> 2*x);(fun x -> x + 3)] 3;;
(* int = 9 *)
pipec [(fun x -> x + 3);(fun x-> 2*x)] 3;;
(* int = 12 *)

sepConcat ", " ["foo";"bar";"baz"];;
(* string = "foo, bar, baz" *)
sepConcat "---" [];;
(* string = "" *)
sepConcat "," ["hello"];;
(* string = "hello" *)
sepConcat "" ["a";"b";"c"];;
(* string = "abc" *)

stringOfList string_of_int [1;2;3;4;5;6];;
(* string = "[1; 2; 3; 4; 5; 6]" *)
stringOfList (fun x -> x) ["foo"];;
(* string = "[foo]" *)
stringOfList (stringOfList string_of_int) [[1;2;3];[4;5];[6];[]];;
(* string = "[[1; 2; 3]; [4; 5]; [6]; []]" *)

prodLists [] [];;
(* int list = [] *)
prodLists [3] [4];;
(* int list = [12] *)
prodLists [10; 20; 30] [5; 5; 5];;
(* int list = [50; 100; 150] *)

bigAdd [9;9] [1;0;0;2];;
(* int list = [1;1;0;1] *)
bigAdd [9;9;9;9] [9;9;9];;
(* int list = [1;0;9;9;8] *)

mulByDigit 9 [9;9;9;9];;
(* int list = [8;9;9;9;1] *)
mulByDigit 4 [5;6;3;2;7];;
(* int list = [2;2;5;3;0;8] *)
mulByDigit 0 [1;3;4;5];;
(* int list = []*)

bigMul [1;2] [1;2];;
(* int list = [1;4;4] *)
bigMul [0] [1;2;3;4];;
(* int list = [] *)
bigMul [9;9;9;9] [9;9;9;9];;
(* int list = [9;9;9;8;0;0;0;1] *)
bigMul [9;9;9;9;9] [9;9;9;9;9];;
(* int list = [9;9;9;9;8;0;0;0;0;1] *)