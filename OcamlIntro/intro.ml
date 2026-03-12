(* Author:      Dylan Groff
 * Instructor:  Dr. Zoppetti
 * Date:        9/15/25
 * Assignment:  Lab 1 - Introduction to OCaml
 * Description: Implement several functions in OCaml.
 *)

(* BEGIN PROVIDED FUNCTIONS *)

(* explode : string -> char list
 * (explode s) is the list of characters in the string s in the order in
 *   which they appear
 * e.g.  (explode "Hello") is ['H';'e';'l';'l';'o']
 *)
let explode s =
        let rec _exp i =
                if i >= String.length s then [] else (s.[i])::(_exp (i+1)) in _exp 0;;

(* END PROVIDED FUNCTIONS *)


(* For ALL of the following method stubs (those with failwith "to be written"),
   add documentation comments including expected behavior *)


(* sumList: int list -> int
 * Sums all ints in a list and returns the sum.
 *)
let rec sumList l = 
        if l = [] then
                0
        else
                List.hd l + sumList (List.tl l)
;;

(*  digitsOfInt: int -> int list
 *  Puts each digit of a number into a list in the order it was given.
 *  Only accepts ints > 0. 
 *)
let rec digitsOfInt n = 
        if n < 10 then
                [n]
        else
                digitsOfInt (n/10) @ [n mod 10]
;;

(*  additivePersistence: int -> int
 *  Adds up all the digits in a given int. Returns the number of additions it
 *  takes to have a single digit remaining.
 *)
let rec additivePersistence n = 
        if n < 10 then
                0
        else 
                1 + additivePersistence (sumList (digitsOfInt n))
;;

(*  digitalRoot: int -> int
 *  Adds up all the digits in a given int until there is a single digit left. 
 *  This number is then returned.
 *)
let rec digitalRoot n = 
        if n < 10 then 
                n
        else
               digitalRoot (sumList (digitsOfInt n))

;;

(*  listReverse: 'a list -> 'a list
 *  Takes a list and puts it in reverse order.
 *)
let rec listReverse l = 
        if l = [] then
                l
        else
                listReverse (List.tl l) @ [List.hd l]
;;

(*  palindrome: string -> bool
 *  Checks to see if a given string is the same word forwards as it is 
 *  backwards.
 *)
let palindrome w = 
        let word = explode w in
        let reverse = listReverse word in

        if word = reverse then
                true
        else
                false
;;



(* BEGIN PROVIDED FUNCTIONS *)

(* digits : int -> int list
 * (digits n) is the list of digits of n in the order in which they appear
 * in n
 * e.g. (digits 31243) is [3,1,2,4,3]
 *      (digits (-23422) is [2,3,4,2,2]
 *)
let digits n = digitsOfInt (abs n);;

(* END PROVIDED FUNCTIONS *)

(************** Add Testing Code Here ***************)

sumList [1;2;3;4;5];; (*int = 15*)
sumList [1;3;-2;5];;  (*int = 7*)

digitsOfInt 6782384;; (*int list = [6; 7; 8; 2; 3; 8; 4]*)
digitsOfInt 2345;;    (*int list = [2; 3; 4; 5]*)

additivePersistence 9876;;  (*int = 2*)
additivePersistence 13456;; (*int = 3*)

digitalRoot 9876;;  (*int = 3*)
digitalRoot 13456;; (*int = 1*)

listReverse [1;2;3;4];;              (*int list = [4; 3; 2; 1]*)
listReverse ["h";"e";"l";"l";"o"];;  (*string list = ["o"; "l"; "l"; "e"; "h"]*)

palindrome "tacocat";;   (*bool = true*)
palindrome "sandwich";;  (*bool = false*)


