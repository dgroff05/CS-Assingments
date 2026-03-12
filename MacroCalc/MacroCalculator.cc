/* 
  File Name  : MacroCalculator.cc
  Author     : Dylan Groff
  Course     : N/A
  Date       : 12/14/15
  Assignment : N/A
  Description: This program is designed to calculate the amount of
               calories, protein, fats, and carbs needed for someone
               based on theur activity level and body weight (pounds).
  Compile with 'g++ -std=c++23 -Wall MacroCalculator.cc -o Mcalc'
*/


/************************************************************/
 // System Includes

#include <iostream>
#include <cstdlib>

/************************************************************/
// Local Includes

/************************************************************/
// Using statements



/************************************************************/
//Function prototypes/global vars/type definitions
// Calculates the number of calories burned per day
int calories (double bodyWeight, double activityLevel, double height, bool sex, int age);

// Calculates the number of grams of protein needed per day
int protein (double bodyWeight, double activityLevel, int age);

/************************************************************/

int 
main (int argc, char* argv[]) 
{
    // print intro
    std::cout << "Welcome to the Macro Calculator! This program calculates the amount of " <<
    "calories, protein, fats, and carbs needed for someone based on theur activity level(scale of 0-10), " <<
    "height (inches), age, sex, body weight (pounds)." << std::endl;

    // Declares variables to store information 
    double bodyWeight;
    double height;
    bool sex;
    int age;
    double activityLevel;

    // start attaining necessary information
    std::cout << "Please enter your body weight (pounds): " << std::endl;
    std::cin >> bodyWeight;
    std::cout << "Please enter your height (inches): " << std::endl;
    std::cin >> height;
    std::cout << "Please enter your sex (1 for male, 0 for female): " << std::endl;
    std::cin >> sex;
    std::cout << "Please enter your age: " << std::endl;
    std::cin >> age;
    std::cout << "Please enter your activity level on a sacle of 0-10 with 0 being sedentary and 10 being extremely active: " << std::endl;
    std::cin >> activityLevel;

    // Prints out calculated data
    int caloriesBurnedDaily = calories (bodyWeight, activityLevel, height, sex, age);
    int dailyProtein = protein (bodyWeight, activityLevel, age);
    // 20% of total calories
    int lowerFats = caloriesBurnedDaily * 0.20;
    // 35% of total calories
    int upperFats = caloriesBurnedDaily * 0.35; 
    // upper range of carbs
    int lowerCarbs = caloriesBurnedDaily - (dailyProtein * 4) - lowerFats;
    // lower range of carbs
    int upperCarbs = caloriesBurnedDaily - (dailyProtein * 4) - upperFats;

    std::cout << "\nTotal dailiy calories burned: " << caloriesBurnedDaily << " calories" << std::endl;
    std::cout << "Recommended protein intake: " << dailyProtein << "g (" << dailyProtein * 4 << " calories)" << std::endl;
    std::cout << "Recommended intake range of fats: " << lowerFats / 9 << "-" << upperFats / 9 << "g (" << lowerFats << "-" << upperFats << " calories)" << std::endl;
    std::cout << "Fill the rest of the calories with carbohydrates: " << lowerCarbs / 4 << "-" << upperFats / 4 << "g (" << lowerCarbs << "-" << upperCarbs << " calories)\n" << std::endl; 

    return EXIT_SUCCESS;
}

/************************************************************/

// Calculates the number of calories burned per day
int calories (double bodyWeight, double activityLevel, double height, bool sex, int age)
{
    // calculates basal metabolic rate using Mifflin-St Jeor formula; 1 is for male, 0 for female
    double BasalMetabolicRate = (sex) ? (10 * bodyWeight / 2.2) + (6.25 * height * 2.54) - (5 * age) + 5: 
    (10 * bodyWeight / 2.2) + (6.25 * height * 2.54) - (5 * age) - 161;

    // Creates a formula factor based on activity level
    activityLevel = (activityLevel * 0.07) + 1.2;

    // calculates total calories burned in a day and returns it
    return (int) (activityLevel * BasalMetabolicRate);
}

// Calculates the number of grams of protein needed per day
int protein (double bodyWeight, double activityLevel, int age)
{
    // creates a factor for the formula based on activity level
    activityLevel = (activityLevel * 0.14) + 0.8;

    // returns calculated grams of protein needed; if age >= 65, a constant rate is used
    return (age >= 65) ? bodyWeight / 2.2 * 1.2: bodyWeight / 2.2 * activityLevel;
}