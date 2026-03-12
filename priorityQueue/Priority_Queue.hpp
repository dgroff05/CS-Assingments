/*
  Filename   : Priority_Queue.hpp
  Author     : Dylan Groff
  Description: Personal implementation of the priority queue class 
               using my own heap class.
*/

/************************************************************/
// Macro guard to prevent multiple inclusions

#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

/************************************************************/
// System includes

#include <functional>
#include <stdexcept>

/************************************************************/
// Local includes

#include "Heap.hpp"

/************************************************************/
// Using declarations


/************************************************************/

template <typename T, typename Compare = std::less<T>>
class Priority_Queue
{
public:
    // Using statements

    // Default constructor
    Priority_Queue ()
        : Heap ()
    {}

    // Custom comparator constructor
    explicitly Priority_Queue (const Compare& comparator)
        : Heap (comparator)
    {}

    // Heapify constructor; takes a vector and heapifies it (basically heap sort)
    Priority_Queue (const vector<t> elements, const Compare& cmp = Compare())
        : Heap (elements, cmp)
    {}

    // Copy Constructor
    Priority_Queue (const Priority_Queue& pq)
        : Heap (pq.heap)
    {}

    //  Destructor
    ~Priority_Queue ()
    {
        clear ();
    }

    // returns the size of the heap
    size_t
    size ()
    {
        return heap.size ();
    }

    // returns if the heap is empty
    bool
    empty ()
    {
        return size () == 0;
    }

    // Deletes all elements
    void 
    clear ()
    {
        heap.clear ();
    }

    // returns iterator pointing the begining
    iterator
    begin ()
    {
        return heap.begin ()
    }

    // const version of begin ()
    const_iterator
    begin () const
    {
        return heap.begin ();
    }

    // returns an iterator pointing to one past the last element
    iterator
    end ()
    {
        return heap.end ();
    }

    // const version of end ()
    const_iterator
    end () const
    {
        return heap.end ();
    }

    // Adds value to the heap
    void
    push (T& value)
    {
        heap.push (value);
    }

    // inserts a range of elements [begin, end)
    void
    push_range (iterator begin, iterator end)
    {
        for (auto i = begin; i != end; ++i)
            heap.push (*i);
    }

    // Removes the top element from the heap
    void
    pop ()
    {
        heap.pop ();
    }

    // Returns the top element
    T
    top ()
    {
        return heap.front ();
    }

  
private:
    
    Heap<T>  heap;

};
/************************************************************/

#endif