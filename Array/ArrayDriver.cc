/*
  Filename   : ArrayDriver.cc
  Author     : Gary M. Zoppetti, Dylan Groff
  Course     : CSCI 362-01
  Assignment : Array
  Description: Test some, but NOT ALL, methods of the Array class.
               Compile with: g++ -Wall ArrayDriver.cc -o ArrayDriver
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

#include "Array.hpp"

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
  Array<int> A;

  // For holding the actual result
  ostringstream output;
  // Put the actual result into the output stream
  output << A;
  printTestResult ("no-arg ctor", "[ ]", output);

  // Must clear the output stream each time
  output.str ("");
  output << A.empty ();
  // "1" for true, "0" for false
  printTestResult ("empty", "1", output);
  
  A.push_back (5);
  A.push_back (10);
  A.push_back (15);

  output.str ("");
  output << A;
  printTestResult ("push_back", "[ 5 10 15 ]", output);

  output.str ("");
  output << A.size ();
  printTestResult ("size", "3", output);
  
  std::cout << A << std::endl;
  A.pop_back ();
  std::cout << A << std::endl;
  A.pop_back ();
  std::cout << A << std::endl;

  output.str ("");
  output << A;
  printTestResult ("pop_back", "[ 5 ]", output);

  /************************************************************/
  // Convert the following tests to use printTestResult
  /************************************************************/
  
  for (int i = 0; i < 10; ++i)
    A.insert (A.begin (), i);

  output.str ("");
  output << A;
  printTestResult ("Inserted 9 8 ... 0 at beginning", "[ 9 8 7 6 5 4 3 2 1 0 5 ]", output);
  
  for (Array<int>::iterator i = A.begin (); i != A.end (); )
    i = A.erase (i);

  output.str ("");
  output << A;
  printTestResult ("Erased all elements of A", "[ ]", output);

  // Size ctor, with a fill value. 
  Array<int> B (3, 9);
  
  output.str ("");
  output << B;
  printTestResult ("B (3, 9): 3 9's", "[ 9 9 9 ]", output);

  // Range ctor. 
  Array<int> C (B.begin (), B.begin () + 2);
  
  output.str ("");
  output << C;
  printTestResult ("C (B.begin (), B.begin () + 2): 9 9", "[ 9 9 ]", output);

  // Assignment operator. 
  B = A;

  output.str ("");
  output << B;
  printTestResult ("B = A: empty", "[ ]", output);
  

  cout << "Inserting 0, 1, 2, 3, 4 at beginning of B\n";
  for (int i = 0; i < 5; ++i)
    B.insert (B.begin (), i);
  
  output.str ("");
  output << B;
  printTestResult ("Inserting 0, 1, 2, 3, 4 at beginning of B", "[ 4 3 2 1 0 ]", output);

  /************************************************************/
  // START WRITING YOUR TESTS HERE
  /************************************************************/

  // Test range ctor (a different case than I test above)

  // Test copy ctor

  // Test capacity

  // Test Resize
  Array<int> D (6, 8);
  D.resize (3);

  output.str ("");
  output << D;
  printTestResult ("Resizing D to 3", "[ 8 8 8 ]", output);

  Array<int> E (6, 8);
  E.resize (12);

  output.str ("");
  output << E;
  printTestResult ("Resizing E to 12", "[ 8 8 8 8 8 8 0 0 0 0 0 0 ]", output);
  
  // Test assignment operator
  E = D;

  output.str ("");
  output << E;
  printTestResult ("Assigning D to E", "[ 8 8 8 ]", output);

  E = B;

  output.str ("");
  output << E;
  printTestResult ("Assigning B to E", "[ 4 3 2 1 0 ]", output);
  
  // Insert test
  E.insert (E.begin () + 2, 9);

  output.str ("");
  output << E;
  printTestResult ("Inserting 9 to E at pos 2", "[ 4 3 9 2 1 0 ]", output);

   for (int i = 0; i < 10; ++i)
    A.insert (A.begin (), i);

  A.reserve (A.size () + 3);

  A.insert (A.begin () + 5, 23);

  output.str ("");
  output << A;
  printTestResult ("Inserting 23 in middle of A", "[ 9 8 7 6 5 23 4 3 2 1 0 ]", output);

  // Erase test
  E.erase (E.begin () + 1);

  output.str ("");
  output << E;
  printTestResult ("Erasing 3 from E", "[ 4 9 2 1 0 ]", output);
  
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
