/* 
  File Name  : Queue.hpp
  Author     : Dylan Groff
  Course     : N/A
  Date       : 4/4/25
  Assignment : N/A
  Description: This is my own queue class implemented using a deque.
*/

/************************************************************/
// Macro guard to prevent multiple inclusions

#ifndef QUEUE_H
#define QUEUE_H
/************************************************************/
// System includes
#include <deque>

/************************************************************/
// Local includes


/************************************************************/
// Using declarations


/************************************************************/

template <typename T>
class Queue 
{
    private:

    // Data members
    deque<T> d;

    public:

    // Default ctor
    Queue () 
    : d ()
    {

    }

    // Returns the size of the queue
    size_t
    size ()
    {
        return d.size ();
    }

    // Returns if the queue is empty
    bool
    empty ()
    {
        d.empty ();
    }

    // Returns the front of the queue
    T&
    front () 
    {
        return d.front ();
    }

    // Const version of front ()
    T&
    front () 
    {
        return d.front ();
    }

    // Returns the back of the queue
    T&
    back () 
    {
        return d.back ();
    }

    // Const version of back ()
    T&
    back () const
    {
        return d.back ();
    }

    // Adds element to the back of the queue
    void
    push (const T& value)
    {
        d.push_back (value);
    }

    // Deletes element at the front of the queue
    void
    pop ()
    {
        d.pop_front ();
    }


};