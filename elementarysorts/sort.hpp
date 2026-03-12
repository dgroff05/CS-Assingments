// Author: Professor William Killian, Dylan Groff
// Date: 2/15/25
// Class: 362-01
// Assignment: Elementary Sorting Algoritms
//
// Description:
//
// Header file for templated sorting algorithms, specifically
// bubble sort (optimized), insertion sort, and selection sort.
// Includes a 'Statistics' datatype for aggregating counts for
// swaps and comparisons.

#ifndef SORTING_ALGORITHMS_HPP_
#define SORTING_ALGORITHMS_HPP_

#include <vector>

struct Statistics {
  // default constructs swaps and compares to zero
  std::size_t numSwaps { 0 };
  std::size_t numCompares { 0 };
};

template <typename T>
void
bubbleSort (std::vector<T>& v, Statistics& s)
{
  s.numCompares = 0;
  s.numSwaps = 0;

  for (size_t i = v.size () - 1; i >= 1 ;--i)
  {
    bool didSwap = false;
    for (size_t j = 0; j < i; ++j) 
    {
      ++s.numCompares;
      if (v[j] > v[j + 1]) 
      {
        std::swap (v[j], v[j + 1]);
        ++s.numSwaps;
        didSwap = true;
      }
    }
    if (!didSwap) 
      break;
  }
}

template <typename T>
void
insertionSort (std::vector<T>& v, Statistics& s)
{
  s.numCompares = 0;
  s.numSwaps = 0;

  for (size_t i = 1; i < v.size (); ++i)
  {
    T e = v[i];
    size_t j = i;
    while (j >= 1 && e < v[j - 1]) 
    {
      ++s.numCompares;
      v[j] = v[j - 1];
      --j;
    }
    
    // Additional compare for when while loop ends because e < v[j - 1] is false
    if (j >= 1 && !(e < v[j - 1]))
      ++s.numCompares;

    v[j] = e;
  }
}

template <typename T>
void
selectionSort (std::vector<T>& v, Statistics& s)
{
  s.numCompares = 0;
  s.numSwaps = 0;

  for (size_t i = 0;i < v.size () - 1;++i)
  {
    size_t min = i;
    for (size_t j = i + 1;j < v.size ();++j)
    {
      if (v[j] < v[min])
        min = j;
      ++s.numCompares;
    }
    std::swap (v[i], v[min]);
    ++s.numSwaps;
  }
}

#endif
