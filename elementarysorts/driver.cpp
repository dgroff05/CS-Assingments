/*
 In general, your program should be split up into different sections

 Section 0: Top Comment Block
   Always include the following:
   - First and last name
   - Last date of modification
   - Course + Section
   - Assignment Name
   - File Description

 Section 1: Includes (must be in the following order)
   1. C++ standard library includes (e.g. <algorithm>)
   2. C library includes (e.g. <math.h> or <cmath>)
   3. System library includes (<name.h> but are not part of the C or C++ standard)
   4. User includes (ones contained in quotes -- e.g. "Timer.hpp")

 Section 2: Preprocessor Definitions
   - Anything that starts with #define (or appropriate guards around it

 Section 3: Compile-time constants, type aliases, using directives, type definitions
   - constexpr Type name = value-expr;
   - using Type = type-expr;
   - using std::cout;
   - declarations of file-scoped struct/class/union

 Section 4: Global variables -- NOTE: use sparingly and ONLY if necessary

 Section 5: Forward declarations for non-template functions
   - A forward declaration is a function without a body.
   - Any default parameters MUST be specified in the forward declaration

 Section 6: Template function implementations
   - Any functions beginning with 'template <...>'

 Section 7: main() function implementation [[[entry point of program]]]
   - main must always have the following signature:
     int main (int argc, char* argv[])

 Section 8: Implementations of non-template functions
   - Must be listed in the SAME ORDER as the forward declarations above
   - REMINDER: whenever you update the parameter types/counts, update
     them in BOTH locations. Otherwise you can get a compiler error!
*/

// Author: Professor William Killian, Dylan Groff
// Date: 2/15/15
// Class: 362-01
// Assignment: Elementary Sorting Algorithms
// Description: This program calculates the number of comparisons and swaps needed to sort 
//              a vector of a size given by the user. The user can choose insertion, selection,
//              or optimized bubble sort and if the vector is in ascending, descending, or random
//              order. The vector is also compared with std::sort to make sure they are the same.



// Includes
////////////////////////////////////////////////////////////////////////////////

// TODO: add include you may use here

#include "sort.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <cstdlib>

// Forward declarations
////////////////////////////////////////////////////////////////////////////////

// -- for any helper functions you write

// Populates the vector based on the input number of elements and sequence type
template <typename T>
void
populateVector (std::vector<T>& v, const size_t& N, const char& type);

// Prints the statistics of the sorting algorithm
template <typename T>
void
printStatistics (const Statistics& stats, const std::vector<T>& copy, const std::vector<T>& sorted);

// Sorts the vector based on the algorithm given by the user
template <typename T>
void
sortVector (std::vector<T>& v, const std::string& algorithm, Statistics& stats);


// Compile-time constants, type aliases, using directives, type definitions 
////////////////////////////////////////////////////////////////////////////////
using std::cout;
using std::cin;
using std::vector;
using std::endl;


// Main
////////////////////////////////////////////////////////////////////////////////

int
main (int argc, char* argv[])
{
  Statistics stats;
  size_t numOfElements;
  std::string algorithm;
  char sequenceType;
  vector<int> ACopy;

  cout << "N         ==> ";
  cin >> numOfElements;
  cout << "Algorithm ==> ";
  cin >> algorithm;
  cout << "Type      ==> ";
  cin >> sequenceType;

  vector<int> A (numOfElements);

  populateVector (A, numOfElements, sequenceType);
  ACopy = A;

  sortVector (A, algorithm, stats);
  std::sort (ACopy.begin(), ACopy.end());

  printStatistics (stats, ACopy, A);

  return EXIT_SUCCESS;
}

// Function implementations
////////////////////////////////////////////////////////////////////////////////

// Populates the vector based on the input number of elements and sequence type
template <typename T>
void
populateVector (vector<T>& v, const size_t& N, const char& type)
{
  unsigned long seed;

  if (type == 'r')
  {
    cout << "Seed      ==> ";
    cin >> seed;

    // Initializes a generator random ints from 0 to 9,999 inclusive
    std::minstd_rand generator (seed);
    std::uniform_int_distribution<int> distribution (0, 9'999);

    // Adds random ints from the generator to the vector
    for (size_t i = 0;i < N;++i)
      v[i] = distribution (generator);
  }
  else if (type == 'a')
  {
    // Adds numbers to the vector in ascending order (1, 2, 3, ... , N)
    for (size_t i = 0;i < N;++i)
      v[i] = i + 1;
  }
  else if (type == 'd')
  {
    // Adds numbers to the vector in descending order (N-1, N-2, ... , 0)
    for (size_t i = 0;i < N;++i)
      v[i] = N - i;

  }
  else
    cout << "Type not recognized." << std::endl;
}


// Prints the statistics of the sorting algorithm
template <typename T>
void
printStatistics (const Statistics& stats, const vector<T>& copy, const vector<T>& sorted)
{
  cout << endl;
  cout << "# Compares: " << stats.numCompares << endl;
  cout << "# Swaps   : " << stats.numSwaps << endl;
  cout << "Sort ok?    ";
  if (sorted == copy)
    cout << "yes" << endl;
  else
    cout << "no" << endl;
}


// Sorts the vector based on the algorithm given by the user
template <typename T>
void
sortVector (vector<T>& v, const std::string& algorithm, Statistics& stats)
{
  if (algorithm == "bubble")
    bubbleSort (v, stats);
  else if (algorithm == "insertion")
    insertionSort (v, stats);
  else if (algorithm == "selection")
    selectionSort (v, stats);
  else
    cout << "Not an acceptable sorting algorithm." << endl;
}