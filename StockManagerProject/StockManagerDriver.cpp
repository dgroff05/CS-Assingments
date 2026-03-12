/* 
  File Name  : StockManagerDriver.cpp
  Author     : Dylan Groff
  Course     : N/A
  Date       : 
  Assignment : N/A
  Description: This program is designed to manage stock levels. It 
               tracks the current inventory of products and allows 
               users to add, delete and modify items in the inventory.
  Compile with 'g++ -std=c++23 -Wall StockManager.cpp -o StockManager'
*/


/************************************************************/
 // System Includes

#include <iostream>
#include <cstdlib>
//#include <print>
#include <string>
#include <vector>
#include <iterator>

/************************************************************/
// Local Includes
#include "StockManager.hpp"

/************************************************************/
// Using statements



/************************************************************/
//Function prototypes/global vars/type definitions

/************************************************************/

int 
main (int argc, char* argv[]) 
{
    std::vector<Product> inventory;
    printIntro ();
    std::string choice;

    while (true)
    {
        printDirections ();
        cin >> choice;
    
        if (choice == "a") addProduct (inventory);
        else if (choice == "d") deleteProduct (inventory);
        else if (choice == "u") updateProduct (inventory);
        else if (choice == "q") break;
        else cout << "Invalid choice." << endl;
    }
    
  return EXIT_SUCCESS;
}

/************************************************************/
