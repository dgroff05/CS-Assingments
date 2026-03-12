////////////////////////////////////////////////////////////////////////////////
// Name: Dylan Groff
// Course: 362-s25
// Date: 3/9/25
// Assignment: Josephus
// Description: This program simulates the Josephus problem where N people
//              are in a circle and every kth person is killed until there 
//              is one person left. That person is then declared the survivor.
//
////////////////////////////////////////////////////////////////////////////////

#include <list>
// TODO: add additional includes
#include <iterator>
#include <iostream>

#include "Josephus.h"

/* Simulate the Josephus problem modeled as a std::list.
 * This function will modify the passed list with only a
 * single survivor remaining.
 *
 * @param circle -- the linked list of people
 * @param k -- skip amount. NOTE: k > 0
 *
 * @return a list of those who are executed in chronological order
 *
 * T(N,k) = (N - 1) * (k + 1)
 * I have derived this from calculating the while loop will iterate N - 1 times,
 * the for loop will iterate k times, and the erase function will require one additional traversal
 * backwards. I then multiplied (N - 1) * (k + 1) to get the function because (k + 1) traversals 
 * happens (N - 1) times. T(5,3) = 16 while the counter in the code shows 16 traversals. I have tested it
 * with several other cases, all of which had the counter equal to the equation. 
*/
template <typename T>
std::list<T>
execute (std::list<T>& circle, int k)
{
  std::list<T> killed;
  // TODO :)
  std::list<int>::iterator li = circle.end ();
  
  size_t traversals = 0;
  
  // N - 1 iterations
  while (circle.size () > 1)
  {
    // Advances the list iterator
    for (int i = k; i > 0; --i)
    {
      if (next (li, 1) == circle.end () || li == circle.end ())
        li = circle.begin ();
      else
        ++li;
    }
    // k iterations which means k traversals
    traversals += k;

    // Adds the value killed to the killed list and erases it from the circle list
    killed.push_back (*li);
    li = circle.erase (li);

    // Checks if iterator equals begin () so it doesn't decrement it but instead makes it equal to end ()
    // + 1 traversal
    if (li == circle.begin ())
      li = circle.end ();
    else
      --li;
    ++traversals;

    // Prints the number of traversals
    //std::cout << "(" << traversals << ") ";
  }

  return killed;
}

/* entry point to the Josephus problem from the autograder / main
 *
 * @param n -- number of people in the circle
 * @param k -- skip amount. NOTE: k > 0
 */
int
josephus (int n, int k)
{
  // 1. make a list
  std::list<int> circle;
  // 2. populate it with values [1, 2, 3, ... , N]
  for (int i = 1; i <= n; ++i)
    circle.push_back (i);
  // 3. call execute
  execute (circle, k);
  // 4. return the lone survivor
  return circle.front ();
  // HINT: While working on this lab, you may also find
  //       it useful to print out the "kill" order.
}
