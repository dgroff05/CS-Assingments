/* 
  File Name  : StockManager.cpp
  Author     : Dylan Groff
  Course     : N/A
  Date       : 
  Assignment : N/A
  Description: This header file is designed to manage stock levels. It 
               tracks the current inventory of products and allows 
               users to add, delete and modify items in the inventory.

*/
/************************************************************/
// Macro guard to prevent multiple inclusions

#ifndef STOCKMANAGER_H
#define STOCKMANAGER_H
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

/************************************************************/
// Using statements

using std::cout;
using std::cin;
using std::endl;
//using std::println;
using std::string;
using std::vector;

/************************************************************/
//Function prototypes/global vars/type definitions

// Holds all the data about each product.
struct Product
{
    int id;
    string name;
    int quantity;
    double price;
};

// Prints the intro explaining this program.
void 
printIntro ();

// Prints the directions on how to run each function.
void 
printDirections ();

// Adds a product to the inventory vector.
void 
addProduct (vector<Product>& inventory);

// Deletes a product from the inventory vector.
void
deleteProduct (vector<Product>& inventory);

// Updates a product in the inventory vector.
void 
updateProduct (vector<Product>& inventory);

// Searches for a product given by the user and then prints the product's data.
void 
searchForProduct (const vector<Product>& inventory);

// Prints out all the products and thier data from the inventory.
void
printInventory (const vector<Product>& inventory);

// Prints the data from a product
void
printProduct (const Product stock);

// Prompts for the data of a product
Product
promptForProductData ();

/************************************************************/

// Prints the intro explaining this program.
void 
printIntro ()
{
    cout << "Welcome! This program is designed to manage stock levels." << endl;
    cout << "It tracks the current inventory of products and allows users \nto add, delete, and modify items in the inventory.\n" << endl;
}

/************************************************************/

// Searches for a product given by the user and then prints the product's data.
void 
searchForProduct (const vector<Product>& inventory)
{
    if (inventory.size() == 0)
    {
        cout << "Can not search for a product when the inventory is empty.\n" << endl;
        return;
    }

    string nameOfProduct;
    cout << "Please enter the name of the product to search for: ";
    cin >> nameOfProduct;

    for (size_t i = 0;i < inventory.size();++i) 
    {
        if (inventory[i].name == nameOfProduct)
        {
            printProduct (inventory[i]);
            return;
        }
    }

    cout << "Product not found in inventory.\n" << endl;
}

/************************************************************/

// Prints the data from a product
void
printProduct (const Product stock)
{
    cout << stock.name << endl;
    cout << "ID: " << stock.id << endl;
    cout << "Quantity: " << stock.quantity << endl;
    cout << "Price: $" << stock.price << endl;
}

/************************************************************/

// Prints out all the products and thier data from the inventory.
void
printInventory (const vector<Product>& inventory)
{
    size_t productCounter = 1;
    for (Product p : inventory)
    {
        cout << productCounter << "." << endl;
        printProduct (p);
        ++productCounter;
    }
}

/************************************************************/

// Prints the directions on how to run each function.
void 
printDirections ()
{
    cout << "Enter 'a' to add a product." << endl;
    cout << "Enter 'd' to delete a product." << endl;
    cout << "Enter 'u' to update a product." << endl;
    cout << "Enter 'q' to quit." << endl;
}

/************************************************************/

// Adds a product to the inventory vector.
void 
addProduct (vector<Product>& inventory) 
{
    Product stock = promptForProductData ();
    inventory.push_back(stock);
}

/************************************************************/

// Deletes a product from the inventory vector.
void
deleteProduct (vector<Product>& inventory)
{
    // Checks inventory size and returns if vector is empty
    if (inventory.size() == 0) 
    {
        cout << "Can not delete a product from an empty inventory." << endl;
        return;
    }

    // Gets the name of the product from the user
    string nameOfProduct;
    cout << "Please enter the name of the product to update: ";
    cin >> nameOfProduct;

    // Finds the position of the element in the list and erases it
    for (size_t i = 0;i < inventory.size();++i) 
    {
        if (inventory[i].name == nameOfProduct)
        {
            inventory.erase (inventory.begin () + i);
        }
    }

    // Prints if product is not in the vector
    cout << "Product not found in inventory." << endl;
}

/************************************************************/

// Updates a product in the inventory vector.
void 
updateProduct (vector<Product>& inventory) 
{
    if (inventory.size() == 0)
    {
        cout << "Must add a product to the inventory before updating.\n" << endl;
        return;
    }

    string nameOfProduct;
    cout << "Please enter the name of the product to update: ";
    cin >> nameOfProduct;

    for (size_t i = 0;i < inventory.size();++i) 
    {
        if (inventory[i].name == nameOfProduct)
        {
            inventory[i] = promptForProductData ();
            return;
        }
    }

    cout << "Product not found in inventory.\n" << endl;
}

/************************************************************/

// Prompts for the data of a product
Product
promptForProductData () 
{
    Product stock;

    cout << "Please enter product ID number: ";
    cin >> stock.id;
    cout << "Please enter product name: ";
    cin >> stock.name;
    cout << "Please enter product quantity: ";
    cin >> stock.quantity;
    cout << "Please enter product price: ";
    cin >> stock.price;

    return stock;
}

/************************************************************/

#endif