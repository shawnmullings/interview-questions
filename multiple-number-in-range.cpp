/** @file multiple-number-in-range.cpp
 *  @brief 
 *  
 *  I have a list where every number in the range 1...n appears once except for one number which appears twice.
 *  Write a function for finding the number that appears twice.
 *  
 *  @author Shawn Mullings (@shawnmullings)
 *  @bug No known bugs.
 */


/* -- Includes -- */

#include <iostream>
#include <vector>

int multiple_times(std::vector<int> vec){

	// Iterator that will contain duplicate int value
	std::vector<int>::iterator ret;

	// Sort container to get duplicate value sid-by-side
  	std::sort(vec.begin(),vec.end());

  	// Find first instance of same adjacent value
	ret = std::adjacent_find (vec.begin(), vec.end());

	// Return duplicate value (in sorted array this will be the first instance of same adjacent value)
	return (*ret);
}


int main(int argc, char const *argv[])
{
	// Array of target values
	int myints[] = {5,30,8,30,72,20,10,14,24};
	// Array size variable
	int arrSize;

	// Set target array size variable
	arrSize = (sizeof(myints)/sizeof(*myints));

	// Add array values to vector (not the most efficient way of doing the allocation)
	std::vector<int> vec(myints, myints+arrSize);

	// Get duplicate value
	std::cout << "This number appears twice: " << multiple_times(vec) << std::endl;

	return 0;
}