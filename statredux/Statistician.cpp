/***************************************************
 Name: Dylan Groff
 Course: 362-01
 Date: 2/5/25
 Assignment: Statician Redux
 Description: This is the implementation file for the Statistician header file.
 
 ***************************************************/

// TODO: other includes go here

#include "Statistician.h"
#include <algorithm>
#include <numeric>
#include <iostream>

// Function Implementations
// **************************************************

// Finds the largest value in the passed vector
// Assumes nums is not empty
float
maximum (const std::vector<float>& nums)
{
	// TODO
	return *std::max_element (nums.begin(), nums.end());
}


// Finds the smallest value in the passed vector
// Assumes nums is not empty
float
minimum (const std::vector<float>& nums)
{
	// TODO
	return *std::min_element (nums.begin(), nums.end());
}


// Finds the sum of values from the passed vector
// Should return zero if the vector is empty
float
sumOfValues (const std::vector<float>& nums)
{
	// TODO
	return std::accumulate (nums.begin(), nums.end(), 0.0f);
}


// Finds the average of all values from the passed vector
// assumes nums is not empty
float
average (const std::vector<float>& nums)
{
	// TODO
	return sumOfValues (nums) / nums.size ();
}

// Creates and returns a new vector. Reads in count number
// of values from the user by prompting for each one
// should return an empty vector if count <= 0
std::vector<float>
populate (int count)
{
	std::vector<float> result;
	// TODO
	if (count <= 0) 
		return result;

	for (size_t i = 0;i < count;++i)
	{
		float value;
		std::cout << "Enter value ==> ";
		std::cin >> value;
		result.push_back (value);
	}

	return result;
}
