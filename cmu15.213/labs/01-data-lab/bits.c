/*
 * CS:APP Data Lab
 *
 * <Please put your name and userid here>
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
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 *
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce
 *      the correct answers.
 */


#endif
//1
/*
 * bitXor - x^y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  int A = ( (~x) & y ) ;
  int B = ( x & (~y));
  return  (~ ((~A) & (~B) )); // A or B = (~ ((~A) & (~B) ));
}
/*
 * tmin - return minimum two's complement integer
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  return 1 << 31;
}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
      // return ( ( (x + 1) & (1 << 31) ) >> 31) & (!( x >> 31 ));
      int xp1 = x + 1;  // x + 1
      int cx = (~x);

      // If x is TMAX, then xp1 should be equal to cx, so cx ^ xp1 = 0
      // But if x is -1(11...1), cx ^ xp1 = 0 also applied
      // so need to use !!(~x) to exclude this case
      return (!!(~x)) & (! (cx ^ xp1));
}
/*
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
    /*int allOdd = (x & (0xAA << 24))  + (x & (0xAA << 16)) + (x & (0xAA << 8)) + (x & 0xAA);*/  // this works but extends the limit of the operators
    int allOdd = x & ((0xAA << 24) | (0xAA << 16) | (0xAA << 8) | (x & 0xAA)); // clear all even bits
    int shift1 = allOdd >> 1; // propagate odd bit to its lower 1 even bit
    int allBitsSet = ( (allOdd) | (shift1) );  // if all odd bits set, the result should be 0xFFFFFFFF

    return (!( ~ allBitsSet ));  // if all odd bits set
}
/*
 * negate - return -x
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return (~x + 1);
}
//3
/*
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
     /*0...0 0011 0000*/
     /*0...0 0011 0001*/
     /*0...0 0011 0010*/
     /*0...0 0011 0011*/
     /*0...0 0011 0100*/
     /*0...0 0011 0101*/
     /*0...0 0011 0110*/
     /*0...0 0011 0111*/
     /*--------------------ABOVE bit3 is 0*/
     /*0...0 0011 1000*/
     /*0...0 0011 1001*/
     /*--------------------ABOVE bit123 is 100*/
     /*0...0 0011 1010*/
     /*0...0 0011 1011*/
     /*0...0 0011 1100*/
     /*0...0 0011 1101*/
     /*0...0 0011 1110*/
     /*0...0 0011 1111*/
     /*--------------------ABOVE bit123 is NOT 100*/
    int msgis0 = !(x & (~0x3F));   // msgis0 = 0 if any of the x's upper 26 bits not clear, which indicate it's not digitS, msgis0 = 1 otherwize
    int lsb4 = (x & 0xF); // least significant 4 bits
    int bit45is1 = (!((x >> 4) ^ 0x3));  // bit45is1 = 1 if bit45=11, bit45is1=0: otherwize
    int b3 = (!(lsb4 >> 3)); // b3=1 if bit3 is 0; b3=0: otherwize

    /*
     * Optimize this line with the following one to reduce 1 operator
    int b0_4valide = ((!(lsb4 ^ 0x8)) | (!(lsb4 ^ 0x9)) | b3); //1: if bit0_4 is between 0000-1001 (both inclusive)  or b3 is 0
    */
    //1: if bit0_4 is between 0000-1001 (both inclusive) or b3 is 0*/
    int b0_4valide = ((!((lsb4 >> 1) ^ 0x4)) | b3);  //

    // 1: msgis0=true and bit45is1=true and (bit3=0|bit0-4=[1000|1001])
    return (msgis0 & bit45is1 & b0_4valide);
}
/*
 * conditional - same as x ? y : z
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
    // return ( ((!x) ) * z ) | ((1 - (!x) ) * y);
    // return ( ((!x) ) * z ) + ((1 - (!x) ) * y);
    return z ^ ((y ^ z) & (~(!!x) + 1));  // -x = ~x + 1
}
/*
 * isLessOrEqual - if x <= y  then return 1, else return 0
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
    // Case 1: x < 0, y>=0 (y - x may overflow)
    // int b = (((((x >> 31) ^ 0) & 0x1)) & ((((y >> 31) ^ 1) & 0x1)));  // b = 1 when x < 0 and y >= 0, b = 0 otherwize
    int b = ((((x >> 31) ^ 0)  & ((y >> 31) ^ 1)) & 0x1);  // b = 1 when x < 0 and y >= 0, b = 0 otherwize

    // Case 2: y < 0, x>=0 (y - x may overflow)
    /*int c = ((((y >> 31) ^ 0) & 0x1) & ((((x >> 31) ^ 1) & 0x1)));  // c = 1 when y < 0 and x >= 0, c = 0 otherwize*/
    // x & y first,  then result & 0x1 to save 1 operator
    int c = ((((y >> 31) ^ 0)  & ((x >> 31) ^ 1)) & 0x1);  // c = 1 when y < 0 and x >= 0, c = 0 otherwize

    //Case 3: other cases
    // -x = ~x + 1
    //  y -x = y + (-x) = y + (~x + 1)
    int a = (((((y + (~x + 1) ) >> 31) ^ 1) & 0x1)); // a = 1 when (y-x) >= 0
    /*printf("x=%d, y=%d, b=%d, c=%d, a=%d, t=%d\n", x, y, b, c, a, ((y + (~x + 1) ) >> 31));*/

    // return (b | ((!b) & (!c)) | ((!b) & (c) & a));
    return (b | ((!b) & (!c) & (a)));
    /*return (b | ((!b)&(c)) | ((!b)&(!c)&(a)) );*/

}
//4
/*
 * logicalNeg - implement the ! operator, using all of
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int logicalNeg(int x) {
    /*
     * naive: BitOR all the bits to check if the final result is 1 or 0
    int y = (x & 0xFF) | ((x>>8) & 0xFF) | ((x>>16) & 0xFF) | ((x>>24) & 0xFF);  // y would be between 0 to 0xFF
    int z = (y & 0x0F) | ((y>>4) & 0x0F) ;  // z would be between 0 to 0x0F
    int w = (z & 0x03) | ((z>>2) & 0x03) ;  // z would be between 0 to 0x03
    int v = (w & 0x01) | ((w>>1) & 0x01) ;  // z would be between 0 to 0x01
    */

    // same idea with the naive implementation, but reduce useless computation
    int s = x | (x >> 16);   // ignore upper 16 bits, focus on least significant 16 bits
    int y = s | (s >> 8);   // ignore upper 24 bits, focus on least significant 8 bits, same idea for following computation
    int z = y | (y >> 4);
    int u = z | (z >> 2);
    int t = u | (u >> 1);
    int v = t & 0x01;   // mask out all the bits except the least significant one

    return (v^1);
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
// Method 1
/*int howManyBits(int x) {*/
    /*// The idea is to shrink the multi leading bits (1 or 0) to only 1 bit*/
    /*int y = (x >> 1);*/
    /*int w = (y ^ x); // indicate the adjacent 2 bits are same or not*/

    /*// Find the most significant 1 (right to left) of w, which means the ending of the continous of the leading 1 or 0 of x*/
    /*// counter count the number of 0 before the first 1 (most significant 1) found*/
    /*// the number of the bits (counter indicate) is redundant, can be substract from the original 32 bit*/
    /*int counter = 0;*/
    /*int b = 1;*/
    /*// skip the checking of the sign bit*/
    /*[>int b = (!((w>>31) & 0x1));  // b = 0 if bit is set (which will end up with all the following b assignment to 0), b = 1 otherwize<]*/
    /*[>counter += b;<]*/

    /*b = b & (!((w>>30) & 0x1));  // b = 0 if bit is set , b = 1 otherwize*/
    /*counter += b;*/

    /*b = b & (!((w>>29) & 0x1));  // b = 0 if bit is set , b = 1 otherwize*/
    /*counter += b;*/
    /*b = b & (!((w>>28) & 0x1));  // b = 0 if bit is set , b = 1 otherwize*/
    /*counter += b;*/
    /*b = b & (!((w>>27) & 0x1));  // b = 0 if bit is set , b = 1 otherwize*/
    /*counter += b;*/
    /*b = b & (!((w>>26) & 0x1));  // b = 0 if bit is set , b = 1 otherwize*/
    /*counter += b;*/
    /*b = b & (!((w>>25) & 0x1));  // b = 0 if bit is set , b = 1 otherwize*/
    /*counter += b;*/
    /*b = b & (!((w>>24) & 0x1));  // b = 0 if bit is set , b = 1 otherwize*/
    /*counter += b;*/
    /*b = b & (!((w>>23) & 0x1));  // b = 0 if bit is set , b = 1 otherwize*/
    /*counter += b;*/
    /*b = b & (!((w>>22) & 0x1));  // b = 0 if bit is set , b = 1 otherwize*/
    /*counter += b;*/
    /*b = b & (!((w>>21) & 0x1));  // b = 0 if bit is set , b = 1 otherwize*/
    /*counter += b;*/
    /*b = b & (!((w>>20) & 0x1));  // b = 0 if bit is set , b = 1 otherwize*/
    /*counter += b;*/

    /*b = b & (!((w>>19) & 0x1));  // b = 0 if bit is set , b = 1 otherwize*/
    /*counter += b;*/
    /*b = b & (!((w>>18) & 0x1));  // b = 0 if bit is set , b = 1 otherwize*/
    /*counter += b;*/
    /*b = b & (!((w>>17) & 0x1));  // b = 0 if bit is set , b = 1 otherwize*/
    /*counter += b;*/
    /*b = b & (!((w>>16) & 0x1));  // b = 0 if bit is set , b = 1 otherwize*/
    /*counter += b;*/
    /*b = b & (!((w>>15) & 0x1));  // b = 0 if bit is set , b = 1 otherwize*/
    /*counter += b;*/
    /*b = b & (!((w>>14) & 0x1));  // b = 0 if bit is set , b = 1 otherwize*/
    /*counter += b;*/
    /*b = b & (!((w>>13) & 0x1));  // b = 0 if bit is set , b = 1 otherwize*/
    /*counter += b;*/
    /*b = b & (!((w>>12) & 0x1));  // b = 0 if bit is set , b = 1 otherwize*/
    /*counter += b;*/
    /*b = b & (!((w>>11) & 0x1));  // b = 0 if bit is set , b = 1 otherwize*/
    /*counter += b;*/
    /*b = b & (!((w>>10) & 0x1));  // b = 0 if bit is set , b = 1 otherwize*/
    /*counter += b;*/

    /*b = b & (!((w>>9) & 0x1));  // b = 0 if bit is set , b = 1 otherwize*/
    /*counter += b;*/
    /*b = b & (!((w>>8) & 0x1));  // b = 0 if bit is set , b = 1 otherwize*/
    /*counter += b;*/
    /*b = b & (!((w>>7) & 0x1));  // b = 0 if bit is set , b = 1 otherwize*/
    /*counter += b;*/
    /*b = b & (!((w>>6) & 0x1));  // b = 0 if bit is set , b = 1 otherwize*/
    /*counter += b;*/
    /*b = b & (!((w>>5) & 0x1));  // b = 0 if bit is set , b = 1 otherwize*/
    /*counter += b;*/
    /*b = b & (!((w>>4) & 0x1));  // b = 0 if bit is set , b = 1 otherwize*/
    /*counter += b;*/
    /*b = b & (!((w>>3) & 0x1));  // b = 0 if bit is set , b = 1 otherwize*/
    /*counter += b;*/
    /*b = b & (!((w>>2) & 0x1));  // b = 0 if bit is set , b = 1 otherwize*/
    /*counter += b;*/
    /*b = b & (!((w>>1) & 0x1));  // b = 0 if bit is set , b = 1 otherwize*/
    /*counter += b;*/
    /*b = b & (!(w & 0x1));  // b = 0 if bit is set , b = 1 otherwize*/
    /*counter += b;*/

  /*return (32 + (~counter + 1));  // 31 - counter + 1(leading sign bit)*/
/*}*/

// Method 2, more compact, but number of operators beyond the limit
int howManyBits(int x) {
    // most significant bit
    int msb = (x>>31);
    // propagation msg bit to every bit for xor operation
    int prg = msb | msb << 1;
    prg = prg | prg << 2;
    prg = prg | prg << 4;
    prg = prg | prg << 8;
    prg = prg | prg << 16;

    int target = x ^ prg;
    // The idea is to find the first 1(right to left) of the target
    // The leading 0s before 1 could be shrink to only one
    // The number of the least bits is 32 - number_of_leading_0 + 1

    int numLeading0 =
        (!(((x << 1) >> 1) ^ x)) +
        (!(((x << 2) >> 2) ^ x)) +
        (!(((x << 3) >> 3) ^ x)) +
        (!(((x << 4) >> 4) ^ x)) +
        (!(((x << 5) >> 5) ^ x)) +
        (!(((x << 6) >> 6) ^ x)) +
        (!(((x << 7) >> 7) ^ x)) +
        (!(((x << 8) >> 8) ^ x)) +
        (!(((x << 9) >> 9) ^ x)) +
        (!(((x << 10) >> 10) ^ x)) +
        (!(((x << 11) >> 11) ^ x)) +
        (!(((x << 12) >> 12) ^ x)) +
        (!(((x << 13) >> 13) ^ x)) +
        (!(((x << 14) >> 14) ^ x)) +
        (!(((x << 15) >> 15) ^ x)) +
        (!(((x << 16) >> 16) ^ x)) +
        (!(((x << 17) >> 17) ^ x)) +
        (!(((x << 18) >> 18) ^ x)) +
        (!(((x << 19) >> 19) ^ x)) +
        (!(((x << 20) >> 20) ^ x)) +
        (!(((x << 21) >> 21) ^ x)) +
        (!(((x << 22) >> 22) ^ x)) +
        (!(((x << 23) >> 23) ^ x)) +
        (!(((x << 24) >> 24) ^ x)) +
        (!(((x << 25) >> 25) ^ x)) +
        (!(((x << 26) >> 26) ^ x)) +
        (!(((x << 27) >> 27) ^ x)) +
        (!(((x << 28) >> 28) ^ x)) +
        (!(((x << 29) >> 29) ^ x)) +
        (!(((x << 30) >> 30) ^ x)) +
        (!(((x << 31) >> 31) ^ x)) ;

    return (32 + (~numLeading0 + 1));
}
//float
/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
    int E1 = !(((uf >> 23) ^ 0xFF) & 0xFF);  // E1=1 if Exp=0xFF only, E1=0 otherwize
    int M1 = !!((uf | (uf >> 8) | ((uf >> 16) & 0x7F))  & 0xFF); // M1=1 if mantissa != 000...0

    // Case1: NaN, Exp = 0xFF, Mantissa != 000...0
    if ( E1 && M1 ) {
        return uf;
    }

    int mantissa = (uf & 0x7FFFFF);

    int sign = (uf>>31);
    // scale 2 means keep the mantissa not change but increase the exp by 1
    // need to check if exp overflow(oxFF) happen after scaling, if yes, set frac to 000...0(infinity)
    int exp = (uf >> 23) & 0xFF;

    if (exp == 0) {
        // Case2: Denormalized value
        if (mantissa & 0x400000) {
            // Test the most significant bit of the Mantissa
            // (if 1 then need to transform  to Normalized format after scaling)
            exp = 1;
        }
        mantissa = (mantissa << 1) ; // scaling by 2, includeing the case the argument is 0
        mantissa = mantissa & 0x7FFFFF; // clear carry bit if there is (omit by Normalized format)
    } else {
        // Case3: Normalized value

        // Case3-1: overflow before or after scale
        // Two cases should set the value to infinity when
        // exp = 0xFF
        // exp = 0xFE: will overflow after scale by 2
        if ((exp & 0xFE) == 0xFE) {
            // infinity's representation
            exp = 0xFF;
            mantissa = 0;
        } else {
            exp += 1; // scale by 2
        }
    }

    int ret = (sign << 31) + (exp << 23) + mantissa;

    /*printf("argument=%d, sign:%d, exp=%d, mantissa=%d, ret=%d\n", uf, sign, exp, mantissa, ret);*/

    return ret;
}
/*
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
    int E1 = !(((uf >> 23) ^ 0xFF) & 0xFF);  // E1=1 if Exp=0xFF only, E1=0 otherwize

    // Case 1: NaN or infinity
    if (E1) {
        return 0x80000000u;
    }

    int mantissa = (uf & 0x7FFFFF);
    int sign = ((uf>>31) & 0x1)? -1:1;
    int exp = (uf >> 23) & 0xFF;

    if (exp == 0) {
        /*printf("exp==0\n");*/
        // Case2: Denormalized value
        return 0;

    } else {
        /*printf("exp==0\n");*/
        // Case3: Normalized value
        // Handle difference cases per  E to [-126, -2], [-1], [0, 31], [32, 127]
        // Accordint to E = Exp - Bias(2^(k-1) -1)
        // That means per Exp to [-1, 125], [126] , [127, 158], [159, 254]
        if (exp > 125) {
            // the value represented by uf should be larger than 1.0 x 2^(-1)
            /*printf("exp>125\n");*/
            if ( exp > 158) {
                // overflow for int
                return 0x80000000u;
            } else {
                if (exp == 126) {
                    return 0u;   // 1.???? * 2^(-1) round to 0, this condition branch could be merge to upper branch
                } else {
                    /*printf("exp>126: exp=%d ,frac=%d\n", exp, mantissa);*/
                    int shiftN = exp - 127 - 23;
                    if (shiftN  > 0) {
                        return (sign  /*sign*/) * (
                            (mantissa << (shiftN/*shift the fraction part*/))
                            | (1 << (exp - 127)/*add mantissa's leading 1 back*/));

                    } else {
                        return (sign /*sign*/) * (
                        (mantissa >> (-shiftN/*shift the fraction part*/))
                        | (1 << (exp - 127)/*add mantissa's leading 1 back*/));
                    }
                }
            }
        } else {
                // Exp: [-1, 125], E[-126, -2]
                /*printf("exp<=126\n");*/
                return 0u;  // all value thess than 1.??? * 2^(-2) round to 0
        }
    }
}
/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatPower2(int x) {
    int sign = 0x0;
    int exp = 0x0;
    int mantissa = 0x0;

    if (x > 127) {
        // Case 1: if x too large, return +INF
        exp = 0xFF;
        mantissa = 0x0;
    } else {
        if (x < -(126 + 23)) {
            // Case 2: if x too small, return 0
            // 0
            exp = 0x0;
            mantissa = 0x0;
        } else {
            // Case 2: TODO
            if (x < -126) {
                // Denormalized
                exp = 0x0;
                mantissa = (1 << (23 + (x + 126)));
            } else {
                // Normalized
                // E = Exp - Bias
                exp = x + 127;
            }
        }
    }

    int ret = (sign << 31) + (exp << 23) + mantissa;

    /*printf("argument=%d, sign:%d, exp=%d, mantissa=%d, ret=%d\n", x, sign, exp, mantissa, ret);*/

    return ret;
}
