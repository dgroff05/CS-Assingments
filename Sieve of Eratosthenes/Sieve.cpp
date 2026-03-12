/* 
  File Name  : Sieve.cc
  Author     : Dylan Groff
  Course     : CSCI 362-01
  Date       : 4/5/25
  Assignment : Sieve of Eratosthenes
  Description: This program implements the Sieve of Eratosthenes which finds all
               prime numbers from 2 to N. This can be run either using a set or a vector.
               The program will show how long it takes given N and which method to use. It
               will also show the number of prime numbers in that range.
               Compile with 'g++ -O3 -Wall Sieve.cpp -o Sieve' to run and 
               'g++ -g -Wall Sieve.cpp -o Sieve' for testing the file.
               Run with ./Sieve (set/vector) (# of elements)   
*/

/************************************************************/
// System Includes

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <cmath>
#include <iterator>


/************************************************************/
// Local Includes

#include "Timer.hpp"

/************************************************************/
// Using statements

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::set;

/************************************************************/
//Function prototypes/global vars/type definitions

// Return the set of primes between 2 and N.
// Use a set to implement the sieve.
set<unsigned>
sieveSet (unsigned N);

// Return the set of primes between 2 and N.
// Use a vector to implement the sieve.
// After filtering out the composites, put the primes in a set
//   to return to the caller. 
set<unsigned>
sieveVector (unsigned N);

// Prints out the set of prime numbers
void
printSet (set<unsigned> primeNums);

/************************************************************/

int 
main (int argc, char* argv[]) 
{ 
    // Makes sure file is ran with all required arguments
    if (argc != 3) 
    {
        std::cerr << "Usage: " << argv[0] << " <set/vector> <# of elements>" << endl;
        exit (EXIT_FAILURE);
    }

    string method (argv[1]);
    unsigned numElements = std::stoul (argv[2]);

    Timer<> t;
    set<unsigned> primeNums;
    
    if (method == "set")
    {
        t.start ();
        primeNums = sieveSet (numElements);
        t.stop ();

        // Prints results
        cout << "Pi[" << numElements << "] = " << primeNums.size () << " (using a set)" << endl;
        cout << "Time: " << std::round (t.getElapsedMs () * 100) / 100 << " ms" << endl;

        //printSet (primeNums);
    }
    else if (method == "vector")
    {
        t.start ();
        primeNums = sieveVector (numElements);
        t.stop ();

        // Prints results
        cout << "Pi[" << numElements << "] = " << primeNums.size () << " (using a vector)" << endl;
        cout << "Time: " << std::round (t.getElapsedMs () * 100) / 100 << " ms" << endl;

        //printSet (primeNums);
    }
    // For when command line arguments are not what they should be
    else
    {
        std::cerr << "Usage: " << argv[0] << " <set/vector> <# of elements>" << endl;
        exit (EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

/************************************************************/

// Return the set of primes between 2 and N.
// Use a set to implement the sieve.
set<unsigned>
sieveSet (unsigned N)
{
    set<unsigned> nums;
    // Adds numbers from 2 - N
    for (unsigned i = 2; i <= N; ++i)
        nums.insert (i);
    
    for (auto m = nums.begin (); m != nums.end () && *m <= sqrt (N); ++m)
    {
        // Erases all m * k, k + 1, k + 2, ... <= N
        for (unsigned k = *m; *m * k <= N; ++k)
            nums.erase (*m * k);
    }
    
    return nums;
}

/************************************************************/

// Return the set of primes between 2 and N.
// Use a vector to implement the sieve.
// After filtering out the composites, put the primes in a set
//   to return to the caller. 
set<unsigned>
sieveVector (unsigned N)
{
    // Declares set to hold results
    set<unsigned> primeNums;

    // Fills vector with N true booleans
    vector<bool> nums (N + 1, true);

    unsigned m = 2;
    for (unsigned i = 0; i < sqrt (N); ++i)
    {
        // Sets all m * k, k + 1, k + 2, ... <= N to false
        for (unsigned k = m; m * k <= N; ++k)
            nums[m * k] = false;
    
        // Does one increment on m
        ++m;
        // Keeps incrementing m if it's a composite number
        while (!nums[m])
            ++m;
    }

    // Adds all prime numbers from 2 to N to a set
    for (unsigned i = 2; i < nums.size (); ++i)
        if (nums[i]) primeNums.insert (i);

    return primeNums;
}

/************************************************************/

// Prints out the set of prime numbers
void
printSet (set<unsigned> primeNums)
{
    cout << "[ ";
    for (unsigned p : primeNums)
        cout << p << " ";
    cout << "]" << endl;
}

/************************************************************/
/*
N       10,000,000    20,000,000   40,000,000
=============================================
Pi[N] (s)   664579       1270607      2433654
Pi[N] (v)   664579       1270607      2433654


N       10,000,000    20,000,000   40,000,000
=============================================
set     13537.04ms    29208.24ms   62497.48ms
vector    225.41ms      455.95ms     964.27ms

DISCUSS FINDINGS HERE.
When first creating the set of numbers, it takes O(NlogN) to insert all elements
into the set. Set uses an underlying red-black tree so it will always be balanced.
This means each erase operation is always O(logN). At the end of the function, there 
is no need to construct a new set to return the numbers. The original one is returned 
instead.

For vector, it takes O(N) to create the vector of bools which is better than set. However 
vector at the end of the function must insert all elements into a set to be returned
which takes about O(N) to go through the vector and then do Pi[N] inserts of O(logN)
complexity. The vector method offers constant time subscripting which is very good when we 
use that to "erase" our values. This by far makes up for having to add all the elements to 
a set at the end of the function.

Overall, set and vector take about the same time complexity for creating their respective 
containers and returning sets, but the main difference comes in erasing elements. While the
complexity to run set is still good, it doesn't come near to the efficiency of the O(1) "erase" 
when using a vector. The size of N has no impact on vector's "erase," but it has a substantial 
impact on set's erase. Constant time will always take the same amount of steps which is why it 
works so well here. When we have such a large input size, the difference in run time between 
constant and logarithmic really shows. This is why there's no surprise that the vector method 
is faster.
*/