/* 
  File Name  : CDInterest.cpp
  Author     : Dylan Groff
  Course     : CSCI 362-01
  Date       : 01/29/25
  Assignment : CD Interest
  Description: This program calculates the interest earned on a 
               certificate of deposit (CD) over a specified period.
  Compile with 'g++ -std=c++23 -Wall CDInterest.cpp -o CDInterest'
*/

/************************************************************/
 // System Includes

#include <iostream>
#include <cstdlib>
#include <print>

/************************************************************/
// Local Includes

/************************************************************/
// Using statements

using std::cout;
using std::cin;
using std::endl;
using std::println;

/************************************************************/
//Function prototypes/global vars/type definitions

// Holds all the data of the Certificate of Deposit
struct CD 
{
  double balance;
  double interestRate;
  int years;
};

// Inform user what program will do
void   
printIntro   ();

// Print the header followed by all the rows.
void   
printTable   (int numRows, double balance, double rate);

// Print one row of table. "interest" is a dollar amount,
//   not a rate.
void   
printRow     (int rowNum, double balance, double interest);

// Calculate interest given a balance and percentage rate (like 7.2%)
// Divide rate by 100 before multiplying.
double 
calcInterest (double balance, double rate);

// Calculates the new balance by adding the old balance with interest
double 
calcFinalBalance (double balance, double interest);

// Prompts the user for balance, interest rate, and years, and then 
// assigns the data to variables
CD   
getData ();

/************************************************************/

int 
main (int argc, char* argv[]) 
{
  printIntro ();
  CD cd = getData ();
  printTable (cd.years, cd.balance, cd.interestRate);
  return EXIT_SUCCESS;
}

/************************************************************/

// Inform user what program will do
void
printIntro () 
{
  println ("This program will calculate the interest earned");
  println ("  on a CD over a period of several years.\n");
}

/************************************************************/

// Print the header followed by all the rows.
void
printTable (int numRows, double balance, double rate) 
{
  println ("Year     Balance     Interest     New Balance");
  println ("----     -------     --------     -----------");
  for (size_t i = 1;i <= numRows;++i) 
  {
    printRow (i, balance, calcInterest (balance, rate));
    balance += calcInterest (balance, rate);
  }
}

/************************************************************/

// Print one row of table. "interest" is a dollar amount,
//   not a rate.
void
printRow (int rowNum, double balance, double interest) 
{
  std::locale::global (std::locale ("en_US.UTF-8"));
  println ("{:<4d}{:>12.2Lf}{:>13.2Lf}{:>16.2Lf}", rowNum, balance, interest, balance + interest);
}

/************************************************************/

// Calculate interest given a balance and percentage rate (like 7.2%)
// Divide rate by 100 before multiplying.
double
calcInterest (double balance, double rate) 
{
  return balance * (rate / 100);
}

/************************************************************/

// Calculates the new balance by adding the old balance with interest.
double
calcFinalBalance (double balance, double interest) 
{
  return balance + interest;
}

/************************************************************/

// Prompts user for data and then returns a struct containing the data.
CD 
getData () 
{
  CD cd;
  cout << "Please enter the initial balance: ";
  cin >> cd.balance;
  cout << "Please enter the interest rate  : ";
  cin >> cd.interestRate;
  cout << "Please enter the number of years: ";
  cin >> cd.years;
  cout << endl; 
  return cd;
}

/************************************************************/