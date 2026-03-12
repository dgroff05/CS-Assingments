/*
  Filename   : Heap.hpp
  Author     : Dylan Groff
  Description: Personal implementation of the heap class
*/

/************************************************************/
// Macro guard to prevent multiple inclusions

#ifndef HEAP_H
#define HEAP_H

/************************************************************/
// System includes

#include <vector>
#include <iterator>
#include <functional>
#include <stdexcept>

/************************************************************/
// Local includes

/************************************************************/
// Using declarations
using std::vector;

/************************************************************/

template <typename T, typename Compare = std::less<T>>
class Heap
{
public:
    // Using statements

    // Default constructor
    Heap ()
        : heap (), 
        comp (Compare ())
    {}

    // Custom comparator constructor
    explicitly Heap (const Compare& comparator)
        : heap (), 
        comp (comparator)
    {}

    // Heapify constructor; takes a vector and heapifies it (basically heap sort)
    Heap (const vector<t> elements, const Compare& cmp = Compare())
        : heap (elements), 
        comp (cmp)
    {
        // Heapifies the vector
        for (size_t i = heap.size() / 2 - 1; i >= 0; --i) 
            downHeap (i);
    }

    // Copy Constructor
    Heap (const Heap& h)
        : Heap (h.heap), 
        comp (h.comp)
    {}

    //  Destructor
    ~Heap ()
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

    // Clears all elements
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
        heap.push_back (value);
        upHeap (size () - 1);
    }

    // inserts a range of elements [begin, end)
    void
    push_range (iterator begin, iterator end)
    {
        for (auto i = begin; i != end; ++i)
            push (*i);
    }

    // Removes the top element from the heap
    void
    pop ()
    {
        heap.front () = heap.back ();
        heap.pop_back ();
        heap.downHeap (0);
    }

    // Returns the top element
    T
    top ()
    {
        return heap.front ();
    }

  
private:
    // Down Heap method; Moves element down the heap until it is in the right position
    void 
    downHeap (size_t pos)
    {
        size_t i, maxChild;
        T val = heap[pos];
        for (i = pos; (maxChild = leftChild (i)) < heap.size (); i = maxChild)
        {
            if (maxChild + 1 < heap.size () && comp (heap[maxChild], heap[maxChild + 1]))
                ++maxChild;
            if (comp (val, heap[maxChild]))
                heap[i] = heap[maxChild];
            else break;
        }
        // Find where to place it
        heap[] = val;
    }

    // Up heap method; Moves element up the heap until it is in the right position
    void
    upHeap (size_t pos)
    {
        T item = heap[pos];

        size_t i;
        for (i = pos; i != 0 && comp (item, v[p(i)]); i = p(i))
            heap[i] = v[p(i)];

        heap[i] = item;
    }

    // Gets the left child of the current node and returns its index
    size_t
    leftChild (size_t pos)
    {
        return 2 * pos + 1;
    }

    // Gets the right child of the current node and returns its index
    size_t
    rightChild (size_t pos)
    {
        return 2 * pos + 2;
    }

    // Gets the parent of the current node and returns its index
    size_t
    parent (size_t pos)
    {
        return (pos - 1) / 2
    }

    vector<T> heap;
    Compare comp;

};
/************************************************************/

#endif