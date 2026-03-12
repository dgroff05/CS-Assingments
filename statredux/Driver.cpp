/***************************************************
 Name: Dylan Groff
 Course: 362-01
 Date: 2/5/25
 Assignment: Statician Redux
 Description: This program prompts for a n amount of numbers and then provides
              the sum, average, min, and max of the numbers.
 
 ***************************************************/

// Include Directives
// **************************************************
#include <iostream>
// TODO: other includes go here
#include <vector>
#include "Statistician.h"

// Using Statements
// **************************************************
using std::cout;
// TODO: any extra using statements would go here
using std::endl;
// Forward Declarations
// **************************************************

// TODO: any functions you implement AFTER main must be defined here


// Main
// **************************************************

int
main(int argc, char* argv[])
{
    int count;
    std::vector<float> nums;

    // Gets count value for number of values to be inserted into the vector
    cout << "Enter number of values ==> ";
    std::cin >> count;

    nums = populate (count);
    
    // Prints the statistics
    cout << "\nThe statistics of all " << count << " values are:" << endl;
    cout << "  Sum: " << sumOfValues (nums) << endl;
    cout << "  Avg: " << average (nums) << endl;
    cout << "  Min: " << minimum (nums) << endl;
    cout << "  Max: " << maximum (nums) << endl;

    return EXIT_SUCCESS;
}


// Function Implementations
// **************************************************

// TODO: any functions you call within main that are a part of this
// file must be implemented AFTER main
