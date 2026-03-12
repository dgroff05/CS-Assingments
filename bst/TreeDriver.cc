/*
  Filename   : TreeDriver.cc
  Author     : Gary M. Zoppetti, Dylan Groff
  Course     : CSCI 362-01
  Assignment : n/a
  Description: Test some, but NOT ALL, methods of the BST class.
               Compile with: g++ -g -Wall TreeDriver.cc -o TreeDriver
*/   

/************************************************************/
// System includes

#include <cstdlib>
#include <iostream>
#include <string>
#include <iterator>
#include <sstream>
#include <cassert>

/************************************************************/
// Local includes

#include "SearchTree.hpp"

/************************************************************/
// Using declarations

using std::cin;
using std::cout;
using std::endl;
using std::ostream_iterator;
using std::string;
using std::ostringstream;

/************************************************************/
// Function prototypes/global vars/typedefs

void
printTestResult (const string& test,
		 const string& expected,
		 const ostringstream& actual);

/************************************************************/

int      
main (int argc, char* argv[]) 
{
  // For holding the actual result
  ostringstream output;

  SearchTree<int> A;
  for (size_t i = 1; i < 5; ++i)
  {
    auto pair = A.insert (i);
    if (!pair.second) std::cout << "Insert Unsuccessful" << std::endl;
  }
  output << A;
  printTestResult ("Inserting", "[ 1 2 3 4 ]", output);


  // Copy Constructor
  SearchTree<int> B (A);
  output.str ("");
  output << B;
  printTestResult ("Copy Constructor of A to B", "[ 1 2 3 4 ]", output);
  cout << *B.end () << endl;


  return EXIT_SUCCESS;
}


/************************************************************/

void
printTestResult (const string& test,
		 const string& expected,
		 const ostringstream& actual)
{
  cout << "Test: " << test << endl;
  cout << "==========================" << endl;
  cout << "Expected: " << expected << endl;
  cout << "Actual  : " << actual.str () << endl;
  cout << "==========================" << endl << endl;

  // Ensure the two results are the same
  assert (expected == actual.str ());
}
/************************************************************/
