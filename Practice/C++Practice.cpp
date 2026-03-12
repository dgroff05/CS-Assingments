/* 
  Filename   : C++Practice.cpp
  Author     : Dylan Groff
  Description: Random C++ practice
*/

/**************************************/
 // Includes
#include <iostream>


/**************************************/
// Using statements
using std::cout;
using std::endl;

/**************************************/
//Forward Declarations
bool 
arrayEq (int array1[], int array2[], int size);

/**************************************/

int 
main (int argc, char* argv[]) {
  int array1[] = {3,6,9};
  int array2[] = {3,4,9};
  cout << arrayEq(array1, array2, 3) << endl;

  return 0;
}

bool 
arrayEq (int array1[], int array2[], int size) {
  for (int i = 0;i < size;i++) 
    if (array1[i] != array2[i]) return false;
  return true;
}