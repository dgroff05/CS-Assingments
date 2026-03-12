/*
 * CS:APP Data Lab
 * Author:      Dylan Groff
 * Instructor:  Dr. Zoppetti
 * Date:        10/12/25
 * Assignment:  Data Lab
 * Description: Implement several bit-wise functions using limited operations.
 * 
 * Dylan Groff     dylangroff19
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code
  must conform to the following style:

  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>

  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.


  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 *
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use btest to verify that your solutions produce
 *      the correct answers.
 */


#endif
/* Copyright (C) 1991-2025 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses Unicode 10.0.0.  Version 10.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2017, fifth edition, plus
   the following additions from Amendment 1 to the fifth edition:
   - 56 emoji characters
   - 285 hentaigana
   - 3 additional Zanabazar Square characters */
// 1
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) { /* Test succeeded 9 ops */
  /* Checks to see if x is TMax by checking to see if x will wrap around to 
  itself. Also checks to make sure x is not -1. Uses !! to make sure result
  is only 1 or 0. */
  return !(x ^ ~(x + 1)) & !!(x ^ ~0) ;
}
/*
 * isTmin - returns 1 if x is the minimum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmin(int x) { /* Test succeeded 9 ops */
  /* Checks to see if x is TMin by seeing if x - 1 is TMax so I can 
  avoid any overflow issues with trying to compute the inverse of TMin and 
  comparing that to TMin. Also checks to make sure x is not 0. Uses !! to 
  make sure result is only 1 or 0. */
  int y = x + ~0;
  return !(y ^ ~(y + 1)) & !!x;
}
/*
 * isZero - returns 1 if x == 0, and 0 otherwise 
 *   Examples: isZero(5) = 0, isZero(0) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int isZero(int x) { /* Test succeeded 2 ops*/
  /* Checks to see if there is any bit that is equal to 1. Returns
  1 if x is all 0s. */
  return !(x | 0);
}
/* 
 * TMax - return maximum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmax(void) { /* Test succeeded 2 ops*/
  /* Creates a bit pattern of 011...1*/
  return ~(1 << 31);
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) { /* Test succeeded 1 op */
  /* Creates a bit pattern of 100...0 */
  return (1 << 31);
}
/* 
 * minusOne - return a value of -1 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int minusOne(void) { /* Test succeeded 1 op */
  /* Flips all of the bits of 0. */
  return ~0;
}
/* 
 * fitsShort - return 1 if x can be represented as a 
 *   16-bit, two's complement integer.
 *   Examples: fitsShort(33000) = 0, fitsShort(-32768) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int fitsShort(int x) { /* Test succeeded 4 ops */
  /* Shakes off leading 16 bits. Right shifts 16 bits back to preserve the 
  sign and return bits to original position. Then checks if the modifed number
  and the original are the same. */
  int y = x << 16;
  y = y >> 16;
  return !(x ^ y);
}
/* 
 * thirdBits - return word with every third bit (starting from the LSB) set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int thirdBits(void) { /* Test succeeded 8 ops */
  /* Target bit pattern: 0100 1001 0010 0100 1001 0010 0100 1001 */
  /* Creates the pattern, slides it down, and unions with previous version to
  double itself. */
  int x = (1 << 3) | 1; 
  x = (x << 6) | x;
  x = (x << 12) | x;
  x =  (x << 24) | x;
  return x;
}
/* 
 * specialBits - return bit pattern 0xffca3fff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 3
 *   Rating: 1
 */
int specialBits(void) { /* Test succeeded 2 ops */
    /* Target bit pattern in binary: 1111 1111 1100 1010 0011 1111 1111 1111
    Create the complement of the ca3 part, shift it down to the correct position, and
    then return the compliment of the whole thing. */
    int x = 215 << 14;
    return ~x;
}
/* 
 * upperBits - pads n upper bits with 1's
 *  You may assume 0 <= n <= 32
 *  Example: upperBits(4) = 0xF0000000
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 10
 *  Rating: 1
 */
int upperBits(int n) { /* Test succeeded 6 ops */
  /* Creates a pattern of 10...0 to be able to shift the 1 (n-1) times to the
  right. It is (n-1) times because there is already a 1 there. If n == 0, the
  !! helps to keep the pattern equal to all 0s. */
  int x = (!!n << 31);
  return x >> (n + ~0);
}
// 2
// int
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) { /* Test succeeded 2 ops */
  /* Flips all of the bits and then adds 1. */
  return ~x + 1;
}
/* 
 * dividePower2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: dividePower2(15,1) = 7, dividePower2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int dividePower2(int x, int n) { /* Test succeeded 7 ops */
    /* First obtains the sign of the integer. Then it calculates the bias and
    bitwise ands it with the sign so that the bias will be 0 for positive 
    numbers and 2^n - 1 for negative numbers. Finally, the bias is added to x
    and is right shifted n places (divided by 2^n). */
    int sign = x >> 31;
    int bias = ((1 << n) + ~0) & sign;
    return (x + bias) >> n;
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) { /* Test succeeded 10 ops */
  /* Shifts x left to shake off (32 - n) bits. Then shifts right (32 - n) bits
  to preserve the sign and return the bits to their original position. Then we
  check this modified value against the original. */
  int y = x << (32 + (~n + 1));
  y = y >> (32 + (~n + 1));
  return !(x ^ y);
}
// float
/* 
 * floatAbsVal - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned floatAbsVal(unsigned uf) { /* Test succeeded 9 ops */
  /* Breaks the float dpwn into its respective parts. First checks for
  NaN and returns uf if it is. Otherwise the function returns the positive
  version of uf. */
  unsigned frac = uf << 9;
  unsigned exp = (uf >> 23) & 0xff;
  if (exp == 0xff && frac > 0) return uf;
  return (uf & ~(1 << 31));
}
/* 
 * floatNegate - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned floatNegate(unsigned uf) { /* Test succeeded 8 ops */
  /* Breaks the float dpwn into its respective parts. First checks for
  NaN and returns uf if it is. Otherwise the function returns the negated
  version of uf. */
  unsigned frac = uf << 9;
  unsigned exp = (uf >> 23) & 0xff;
  if (exp == 0xff && frac > 0) return uf; /*just make sure > 1111 1111?*/
  return (uf ^ 1 << 31);
}
