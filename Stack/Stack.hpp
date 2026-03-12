/*
  Filename   : Stack.hpp
  Author     : Dylan Groff
  Description: Personal implementation of the stack class
*/

/************************************************************/
// Macro guard to prevent multiple inclusions

#ifndef STACK_H
#define STACK_H

/************************************************************/
// System includes

#include <vector>

/************************************************************/
// Local includes

/************************************************************/
// Using declarations
using std::vector;

/************************************************************/

template <typename T>
class Stack
{
public:
    // Using statments

    // Default constructor
    Stack ()
        : stack ();
    {}

    // Copy constructor
    Stack (const Stack& s)
        : stack (s.stack)
    {}

    // Destructor
    ~Stack ()
    {
        clear ();
    }

    // Returns the size of the stack
    size_t
    size ()
    {
        return stack.size ();
    }

    // Returns if the stack is empty
    bool
    empty ()
    {
        return size () == 0;
    }

    // Clears all elements in the stack
    void
    clear ()
    {
        stack.clear ();
    }

    // Adds element to the stack
    void
    push (const T& value)
    {
        stack.push_back (value);
    }

    // Pops the top element
    void
    pop ()
    {
        stack.pop_back ();
    }

    // returns the top element
    T
    top ()
    {
        return stack.back ();
    }

private:
    vector<T> stack;
}

/************************************************************/

#endif