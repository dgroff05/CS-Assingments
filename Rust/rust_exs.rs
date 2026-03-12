/* This file is full of sample Rust code for CSMC 330 Presentation / Paper 
 * Author: Dylan Groff
 * File name: rust_exs.rs
 * Compile with: rustc rust_exs.rs
*/

// Use statements


// Shows readability
fn sum (x: f64, y: f64) -> f64
{
    return x + y;
}

// Shows readability and pattern matching
fn pattern ()
{
    let triple = (1, 4, 8);
    match triple
    {
        (1,..) => println! ("First num is 1."),
        (..,5) => println! ("Last num is 5."),
        (2, .., 6) => println! ("First num is 2 and the last num is 6."),
        (x, _, _) => println! ("Destructuring with pattern matching. x = {}", x),
        _ => println! ("Doesn't matter what's in triple."),
    }
}


fn main () 
{
    // Uses type inferencing
    let sum = sum (10_000.0, 14e3);
    println! ("The sum is {}.", sum);

    // writiability issue
    let mut arr: [i32; 5] = [1, 2, 3, 4, 5];

    // Ownership and casting
    /*
    let s = String::from ('5');
    // Ownership is transferred to t
    let t = s; 
    println! ("{}",s); 
    // Results in an error because s does not have ownership
    // Possible solution: use s.clone() to create a copy of the value */

    // Restrictive aliasing
    /* 
    let word = String::from("hello");

    let w1 = &s;
    /* Causes error because w2 is trying to 
     * mutable borrow while there is an active immutable borrow */
    let w2 = &mut s; */

    // type conversions
    let x = 5_i32;
    let y = x as f64;

    // Conditional assignment
    let z = if x > 0 { 
        "Positive"
        } else {
        "Negative"
    };

}