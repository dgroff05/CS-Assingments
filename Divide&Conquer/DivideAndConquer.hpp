/*
  File       : DivideAndConquer.hpp
  Author     : Gary Zoppetti, Will Killian, Chad Hogg, and Dylan Groff
  Course     : CSCI 362-s25
  Date       : 4/15/25
  Assignment : Sorting Part 1 (sorts1)
  Description: This file includes the implementation of quicksort, mergesort,
               and quickselect.
*/
#ifndef DIVIDE_AND_CONQUER_HPP_
#define DIVIDE_AND_CONQUER_HPP_

#include <iterator>
#include <utility>
#include <vector>
// For std::copy only
#include <algorithm>

// NOTE: you are forbidden from using anything from <algorithm> for this assignment
//       EXCEPT for std::copy

namespace SortUtils
{

// [9]
// Given a RandomAccessRange [first, last), determine where the "midpoint"
// would be and perform the following steps:
// order *first, *mid, *std::prev(last) in such a way such that
//   *first <= *mid <= *std::prev(last)
//
// returns the median value (NOT an iterator)
//
template<std::random_access_iterator Iter>
std::iter_value_t<Iter>
median3 (Iter first, Iter last)
{
  // Finds the midpoint and makes an iterator pointing to it
  auto mid = std::next (first, std::distance (first, last) / 2);

  // Moves last forward so it is no longer a nullptr
  last = std::prev(last);

  // Orders the first, median, and last values
  if (*first > *mid)
  {
    std::iter_swap (first, mid);
  }
  if (*first > *last)
  {
    std::iter_swap (first, last);
  }
  if (*mid > *last)
  {
    std::iter_swap (mid, last);
  }

  return *mid;
}

// [10]
// Takes two sorted ranges [first1, last1) and [first2, last2)
// and "merges" them by copying values into the iterator starting
// at "out". Uses operator< for comparing values
//
// Returns the iterator of one-past-the-last where we wrote to out
//
template<typename Iter1, typename Iter2, typename OIter>
OIter
merge (Iter1 first1, Iter1 last1, Iter2 first2, Iter2 last2, OIter out)
{
  // Adds the smaller element of the halves to the output iterator
  while (first1 != last1 && first2 != last2)
  {
    if (*first1 <= *first2)
    {
      *out = *first1;
      ++first1;
      ++out;
    }
    else
    {
      *out = *first2;
      ++first2;
      ++out;
    }
  }

  // Adds the rest of the first half when second half is depleted
  while (first1 != last1 && first2 == last2)
  {
    *out = *first1;
    ++first1;
    ++out;
  }
  // Adds the rest of the second half when first half is depleted
  while (first2 != last2 && first1 == last1)
  {
    *out = *first2;
    ++first2;
    ++out;
  }

  return out;
}

// [15]
// Takes a RandomAccessRange [first, last) and partitions the data into
// three groups -- this should be accomplished in a SINGLE PASS Big-O: O(N)
//
// Group 1: all values in [first, last) < pivot
// Group 2: all values in [first, last) == pivot
// Group 3: all values in [first, last) > pivot
//
// [ ... Group 1 ... | ... Group 2 ... | ... Group 3 ... ]
//                   ^                 ^
//                   p1                p2
//
// Returns a pair of iterators pointing to "p1" and "p2" above
//
// Hint: See separate Three Way Partition explanation in handout.
//
template<typename Iter, typename Value>
std::pair<Iter, Iter>
partition (Iter first, Iter last, Value const& pivot)
{
  // Keeps track of smaller values
  auto lo = first;
  // Keeps track of equal values
  auto eq = first;
  // Keeps track of bigger values
  auto hi = last;

  // eq walks through elements until it reaches hi
  while (eq != hi)
  {
    // Swaps wiith lo if element is less than pivot and advances lo
    if (*eq < pivot)
    {
      std::iter_swap (lo, eq);
      ++lo;
      ++eq;
    }
    // Swaps with hi if element is greater than pivot and advances hi
    else if (*eq > pivot)
    {
      --hi;
      std::iter_swap (eq, hi);
    }
    // Advances eq when the element is equal to the pivot
    else
      ++eq;
  }

  return std::make_pair (lo, hi);
}

// [10]
// Given a RandomAccessRange, recursively call partition on either the
// left half or right half until you have found the nth largest element
//
// A call to nth_element (v.begin(), v.end(), 0) will return the min
// A call to nth_element (v.begin(), v.end(), v.size() - 1) will return the max
// A call to nth_element (v.begin(), v.end(), v.size() / 2) will return the median
//
// Precondition:
//   std::distance (begin, end) > n
//
// Hints:
//  - n will change if you need to recurse on the right half
//  - No recursion happens if "index of" n is between "index of" p1 and p2
//    remember: p1 and p2 are the return values to partition.
//  - call median3 to get a pivot value
//
template<typename Iter>
Iter
nth_element (Iter first, Iter last, size_t n)
{
  if (std::distance (first, last) < 1) return last;

  auto [p1, p2] = SortUtils::partition (first, last, SortUtils::median3 (first, last));

  // Calculates "index of" p1
  size_t leftSide = std::distance (first, p1);
  // Calculates "index of" p2
  size_t rightSide = std::distance (p1, p2) + leftSide;

  // Recurses left side
  if (n < leftSide) return nth_element (first, p1, n);
  // Recurses right side
  else if (n >= rightSide) return nth_element (p2, last, n - rightSide);
  // Returns if n is between p1 and p2 and finds where n is 
  else return std::next (p1, n - leftSide);
}

// [10]
// Given a RandomAccessRange, sort using merge sort
//
// Precondition:
//   std::distance (begin, end) > 0
//
// Hints:
//   - You will need a vector to act as a temporary buffer.
//   - The merge function will expect that vector to already be big enough
//     to hold all of the elements.
//
template<typename Iter>
void
merge_sort (Iter first, Iter last)
{
  // T is the type of data we are sorting
  using T = std::iter_value_t<Iter>;

  if (std::distance (first, last) <= 1) return;

  // Finds the midpoint and makes an iterator that points to it
  Iter mid = std::next (first, std::distance (first, last) / 2);

  // Sorts first half
  merge_sort (first, mid);
  // Sorts second half
  merge_sort (mid, last);
  
  // Creates a temporary vector to store the merged sorted sides
  std::vector<T> v (std::distance (first, last));
  SortUtils::merge (first, mid, mid, last, v.begin ());

  // Copies over the sorted elements from the vector
  std::copy (v.begin (), v.end (), first);
}

// Provided for you -- no need to change.
template<typename Iter>
void
insertion_sort (Iter first, Iter last)
{
  for (Iter i = first; i != last; ++i)
  {
    for (Iter j = i; j != first; --j)
    {
      if (*(j - 1) > *j)
      {
        std::iter_swap (j - 1, j);
      }
      else
      {
        break;
      }
    }
  }
}


// [10]
// Given a RandomAccessRange, sort using quick sort
//
// Precondition:
//   std::distance (begin, end) > 0
//
// Hints:
//   - median3 will be called to find the pivot
//   - partition should be called
//   - if there are fewer than 16 elements, use the provided insertion sort instead
//
template<typename Iter>
void
quick_sort (Iter first, Iter last)
{
  // T is the type of data we are sorting
  //using T = std::iter_value_t<Iter>;

  if (std::distance (first, last) <= 1) return;

  // Calls insertion sort if there are too few elements
  if (std::distance (first, last) < 16)
    SortUtils::insertion_sort (first, last);

  auto [p1, p2] = SortUtils::partition (first, last, SortUtils::median3 (first, last));

  // Sorts first part
  quick_sort (first, p1);
  // Sorts second part
  quick_sort (p2, last);
}

} // end namespace util

#endif
