/* 
  File Name  : ROTH_IRACalculator.cpp
  Author     : Dylan Groff
  Course     : N/A
  Date       : 4/4/2025
  Assignment : N/A
  Description: This program calculates the total money accumulated by a Roth IRA
               from your current age to the retirement age of 65.
               Compile with 'g++ -std=c++23 -Wall ROTH_IRACalculator.cpp -o RCalc'
*/

/************************************************************/
// System Includes

#include <cstdlib>
#include <iostream>
#include <string>
#include <print>


/************************************************************/
// Local Includes


/************************************************************/
// Using statements

using std::cout;
using std::endl;
using std::cin;

/************************************************************/
//Function prototypes/global vars/type definitions

struct Portfolio
{
  double balance = 0.0;
  double annualContribution = 0.0;
  // Ranges from 5%-10%
  double interestRate = 0.05;
  int age;
};

// Gets inputs from the user;
Portfolio
promptForData (Portfolio p);

/************************************************************/

int
main (int agrc, char* argv[])
{
  // Welcome message
  cout << "\nWelcome! This program calculates the total money accumulated by a Roth IRA" << endl;
  cout << "            from your current age to the retirement age of 65." << endl;

  // Gets data from user
  Portfolio p = promptForData (p);

  // Calculates final balance;
  for (int i = 65; i > p.age; --i)
  {
    p.balance += (p.balance * p.interestRate);
    p.balance += p.annualContribution;
  }

  // Prints out the result
  std::locale::global (std::locale ("en_US.UTF-8"));
  std::println ("At age 65, you will have accumulated ${:.2Lf} using an interest rate of {:.2f}%.", p.balance, p.interestRate * 100);
  std::println ("");

  return EXIT_SUCCESS;
}

/************************************************************/
// Gets inputs from the user;
Portfolio
promptForData (Portfolio p)
{
  // Gets the balance
  cout << "\nEnter the initial balance of the Roth IRA: ";
  cin >> p.balance;
  // Gets the annual contribution
  cout << "\nEnter your annual contribution amount (At most $6,000 if you're under 50): ";
  cin >> p.annualContribution;
  // Gets the interest rate as a decimal value
  cout << "\nEnter the interest rate of your choice as a decimal value (between 0.05-0.10): ";
  cin >> p.interestRate;
  // Gets the age
  cout << "\nEnter your age: ";
  cin >> p.age;
  cout << endl;

  return p;
}