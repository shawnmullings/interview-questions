/** @file coin-combination.cpp
 *  @brief 
 *  
 *  Imagine you landed a new job as a cashier...
 *  Your quirky boss found out that you're a programmer and has a weird request about something they've been wondering for a long time.
 *  
 *  Write a function that, given:
 *  
 *  an amount of money
 *  a list of coin denominations
 *  computes the number of ways to make amount of money with coins of the available denominations.
 *  
 *  Example:  for amount= 4(4¢) and denominations= [1,2,3] (1¢, 2¢ and 3¢), your program would output 4—the number of ways to make 4¢ with those denominations:
 *  
 *  1. 1¢, 1¢, 1¢, 1¢
 *  2. 1¢, 1¢, 2¢
 *  3. 1¢, 3¢
 *  4. 2¢, 2¢
 *  
 *  @author Shawn Mullings (@shawnmullings)
 *  @bug No known bugs.
 */


/* -- Includes -- */

#include <iostream>
#include <vector>
#include <algorithm>

void coin_combination (int coins[], int coins_size, int counts[], int startIndex, int totalAmount){

	//firstly decide if we should proceed or not by track startIndex
	if(startIndex >= coins_size )//we have processed all coins
	{
		//format the print out as "amount=?*25 + ?*10+..."
		for(int i=0; i < coins_size; i++)
			std::cout << "" << counts[i] << " * " << coins[i] << " + ";
		//need a new line per case
		std::cout << "\n";
		return;
	}

	//other wise we need proceed
	//but notice if startIndex is the last one, we need check if it can be dividable by the smallest coin
	//if so, this is a good combination, otherwise, this is not possible combination thus discarded
	if(startIndex == coins_size-1)
	{
		if(totalAmount % coins[startIndex] == 0)//good combination
		{
			//set the counts of coins at start index
			counts[startIndex] = totalAmount / coins[startIndex];
			//proceed to recursive call
			coin_combination(coins, coins_size, counts, startIndex+1, 0);//notice startIndex+1 and remaining amount = 0
		}
	}
	else//we still have option to choose 0-N larger coins
	{
		for(int i=0; i <= totalAmount / coins[startIndex]; i++)
		{
			//for every cycle in a loop, we choose an arbitrary number of larger coins and proceed next
			counts[startIndex] = i;
			coin_combination(coins, coins_size, counts, startIndex+1, totalAmount-coins[startIndex]*i);
			//notice we need update the remaining amount
		}
	}
}

int main() {
	//set coins denomination
	int coins[] = {25,10,5,1};

	// Get size of coin array
	int coin_size( (sizeof(coins)/sizeof(int)) );

	//set the default counts array size to size of coins array
	int counts[coin_size];

	// Message
	std::cout << "All possible coin combinations of 25 cents are: " << std::endl;

	//Get combination of coins need for 50 cents
	coin_combination(coins, coin_size, counts, 0, 50);

	return 0;
}