
/** @file random-number.cpp
 *  @brief 
 *  
 *  You have a function rand7() that generates a random integer from 1 to 7. Use it to write a function rand5() that generates a random integer from 1 to 5.
 *  
 *  rand7() returns each integer with equal probability. rand5() must also return each integer with equal probability.
 *  
 *  @author Shawn Mullings (@shawnmullings)
 *  @bug No known bugs.
 */

/* -- Includes -- */

#include <iostream>
#include <random>
#include <ctime>
#include <math.h>

/*
*
*	Generates a random integer from 1 to 7
*
*	return integer from 1 - 7
*/
int rand7(){

	/* Uniformly-distributed integer random number generator that produces non-deterministic random numbers */
    std::random_device rd;

    /* Mersenne Twister pseudo-random generator of 32-bit numbers */
    std::mt19937 gen(rd());

    /* Produce random integer value uniformly distributed on the interval 1 - 7 */
    std::uniform_int_distribution<> dis(1, 7);

    return dis(gen);
}

/*
*
*	Generates a random integer from 1 to 5
*
*	return integer from 1 - 5
*/
int rand5(){
	/* 5 / 7 = 0.71428571. Use to squeeze range 1 - 7 into range 1 - 5 */
	float tUnits = 0.71428571;

	/* 5 / 7 = 0.71428571 */
	return ( std::ceil(tUnits * rand7()) );
}

int main(int argc, char const *argv[])
{
	/* Generate rand5() using rand7() ouput */
	std::cout << "Generate random integer from 1 to 5" << std::endl;
	std::cout << "Random integer: " << rand5() << std::endl;

	return 0;
}