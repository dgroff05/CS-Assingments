/*
  Filename   : ListDriver.cc
  Authors    : Gary M. Zoppetti, William Killian
  Course     : CSCI 362-01
  Assignment : N/A
  Description: Test some, but NOT ALL, methods of the List class.
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

#include "List.hpp"

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
  List<int> A;
 
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
  
  
  A.pop_back ();
  A.pop_back ();

  output.str ("");
  output << A;
  printTestResult ("pop_back", "[ 5 ]", output);
  
  /************************************************************/
  // Convert the following tests to use printTestResult
  /************************************************************/
  // Inserting several elements
  for (int i = 0; i < 10; ++i)
    A.insert (A.begin (), i);
  std::cout << "A size: " << A.size () << std::endl << std::endl;
  output.str ("");
  output << A;
  printTestResult ("Inserted 9 8 ... 0 at beginning", "[ 9 8 7 6 5 4 3 2 1 0 5 ]", output);

  // Erasing all elements
  for (List<int>::iterator i = A.begin (); i != A.end (); )
    i = A.erase (i);

  std::cout << "A size: " << A.size () << std::endl << std::endl;
  output.str ("");
  output << A;
  printTestResult ("Erased all elements of A", "[ ]", output);

  // Size ctor, with a fill value. 
  List<int> B (3, 9);
  std::cout << " B size: " << B.size () << std::endl << std::endl;
  output.str ("");
  output << B;
  printTestResult ("B (3, 9)", "[ 9 9 9 ]", output);

  // Range ctor.
  List<int> C (B.begin (), std::next(B.begin (), 2));
  std::cout << "C size: " << C.size () << std::endl << std::endl;
  output.str ("");
  output << C;
  printTestResult ("C (B.begin (), B.begin () + 2): 9 9", "[ 9 9 ]", output);


  // Assignment operator. 
  B = A;
  std::cout << "A size: " << A.size () << " B size: " << B.size () << std::endl << std::endl;
  output.str ("");
  output << B;
  printTestResult ("B = A", "[ ]", output);
  

  // Inserting several elements
  for (int i = 0; i < 5; ++i)
    B.insert (B.begin (), i);

  std::cout << " B size: " << B.size () << std::endl << std::endl;
  output.str ("");
  output << B;
  printTestResult ("Inserting 0, 1, 2, 3, 4 at beginning of B", "[ 4 3 2 1 0 ]", output);

  /************************************************************/
  // START WRITING YOUR TESTS HERE
  /************************************************************/

  // Test range ctor (a different case than I test above)

  // Test copy ctor
  List<int> D (B);
  std::cout << "D size: " << D.size () << std::endl << std::endl;
  output.str ("");
  output << D;
  printTestResult ("Copy ctor of B to D", "[ 4 3 2 1 0 ]", output);

  // Test capacity

  // ...

  // Assignment Operator
  A = B;
  std::cout << "A size: " << A.size () << " B size: " << B.size () << std::endl << std::endl;
  output.str ("");
  output << A;
  printTestResult ("Assigning B to A", "[ 4 3 2 1 0 ]", output);
  
  // Erase
  A.erase (std::next (A.begin (), 2));
  std::cout << "A size: " << A.size () << std::endl << std::endl;
  output.str ("");
  output << A;
  printTestResult ("Erasing 2 in A", "[ 4 3 1 0 ]", output);

  // Insert
  A.insert (std::next (A.begin (), 2), 8);
  std::cout << "A size: " << A.size () << std::endl << std::endl;
  output.str ("");
  output << A;
  printTestResult ("Inserting 8 in A before 3rd element", "[ 4 3 8 1 0 ]", output);

  // Transfer
  /*
  List<int>::transfer (std::next (B.begin (), 2), C.begin (), C.end ());

  output.str ("");
  output << B;
  printTestResult ("Transfering C to B", "[ 4 3 9 9 2 1 0 ]", output);

  List<int>::transfer (std::next (B.begin (), 2), std::next (A.begin (), 2), std::next (A.begin (), 3));

  output.str ("");
  output << B;
  printTestResult ("Transfering C to B", "[ 4 3 8 9 9 2 1 0 ]", output);
  */
  // Resize
  std::cout << B.size () << std::endl;
  B.resize (3, 8);
  std::cout << " B size: " << B.size () << std::endl << std::endl;
  output.str ("");
  output << B;
  printTestResult ("Resize B to 3", "[ 4 3 2 ]", output);

  B.resize (8, 8);
  std::cout << " B size: " << B.size () << std::endl << std::endl;
  output.str ("");
  output << B;
  printTestResult ("Resize B to 8", "[ 4 3 2 8 8 8 8 8 ]", output);

  // Erase range
  B.erase (B.begin (), std::next (B.begin (), 3));
  std::cout << " B size: " << B.size () << std::endl << std::endl;
  output.str ("");
  output << B;
  printTestResult ("Erase range in B", "[ 8 8 8 8 8 ]", output);

  
  // Reverse
  A.reverse ();

  output.str ("");
  output << A;
  printTestResult ("Reversing A", "[ 0 1 8 3 4 ]", output);
  
  // Pop front
  A.pop_front ();
  A.pop_front ();
  std::cout << "A size: " << A.size () << std::endl << std::endl;
  output.str ("");
  output << A;
  printTestResult ("Popping front in A", "[ 8 3 4 ]", output);


  // clear ()
  A.clear ();
  std::cout << "A size: " << A.size () << std::endl << std::endl;
  output.str ("");
  output << A;
  printTestResult ("Clearing all elements in A", "[ ]", output);

  
  
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
