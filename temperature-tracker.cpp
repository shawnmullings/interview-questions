
/** @file temperature-tracker.cpp
 *  @brief 
 *  You decide to test if your oddly-mathematical heating company is fulfilling its All-Time Max, Min, Mean and Mode Temperature Guarantee™.
 *  
 *  Write a class TempTracker with these methods:
 *  
 *  insert()—records a new temperature
 *  get_max()—returns the highest temp we've seen so far
 *  get_min()—returns the lowest temp we've seen so far
 *  get_mean()—returns the mean ↴ of all temps we've seen so far
 *  get_mode()—returns a mode ↴ of all temps we've seen so far
 *  
 *  Optimize for space and time. Favor speeding up the getter functions (get_max(), get_min(), get_mean(), and get_mode()) over speeding up the insert() function.
 *  
 *  get_mean() should return a float, but the rest of the getter functions can return integers. Temperatures will all be inserted as integers. 
 *  We'll record our temperatures in Fahrenheit, so we can assume they'll all be in the range 0..110.
 *  
 *  If there is more than one mode, return any of the modes. 
 *  
 *  @author Shawn Mullings (@shawnmullings)
 *  @bug No known bugs.
 */

/* -- Includes -- */

#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <string>
#include <map>

class TempTracker{
	public:

		/* Contructor */
		TempTracker(){
			this->_max_temp = 0;
			this->_min_temp = 110;
		}

		/* Destructor */
		~TempTracker(){}

		/* Add temperature to container method and initiate max, min, mean, and mode calculations */
		void insert(int value){
			//if (value == NULL)
			//	return;

			this->_temps.push_back(value);

			get_max_helper(value);
			get_min_helper(value);
			get_mean_helper();
			get_mode_helper();
		}

		/* Calculate maximum temperature method  */
		int get_max(){ return this->_max_temp; }

		/* Calculate minimum temperature method  */
		int get_min(){ return this->_min_temp; }

		/* Calculate mean method  */
		float get_mean(){ return this->_mean_temp; }

		/* Calculate mode method  */
		int get_mode(){ return this->_mode_temp; }

		/* Output temperature to console */
		void trace(){

			/* use string stream to convert vector items to string for "cout" */
			std::stringstream result;
			std::copy(this->_temps.begin(), this->_temps.end(), std::ostream_iterator<int>(result, " "));
			std::cout << result.str() << std::endl;
		}


	private:

		std::vector<int> _temps; 	/* Temperature container */
		int _max_temp;				/* Maximum temperature variable */
		int _min_temp;				/* Minimum temperature variable */
		float _mean_temp; 			/* Average temperature variable */
		float _mode_temp; 			/* Most instances temperature variable */

		/* get max helper method */
		void get_max_helper(int value){ 
			_max_temp =  (value > _max_temp) ? value : _max_temp;
		}

		/* get min helper method */
		void get_min_helper(int value){ 
			_min_temp =  (value < _min_temp) ? value : _min_temp;
		}

		/* get average (mean) helper method */
		void get_mean_helper(){ 

			int sum_of_elems = 0;
			for (std::vector<int>::iterator it = _temps.begin(); it != _temps.end(); it++)
    			sum_of_elems += (*it);

			_mean_temp = (float)(sum_of_elems/_temps.size()); 
		}
		
		/* get most instances (max) helper method */
		void get_mode_helper(){ 
			int max; 
			max = 0;
			
			int most_common;
			most_common = -1;
			
			std::map<int,int> m;

			for (std::vector<int>::iterator vi = this->_temps.begin(); vi != this->_temps.end(); vi++) {
				m[*vi]++;
			  	if (m[*vi] > max) {
			    	max = m[*vi]; 
			    	this->_mode_temp = *vi;
			  	}
			} 
		}
};

int main(int argc, char const *argv[])
{
	/* Initailize TempTracker object */
	TempTracker tt;

	/* Add  some temperatures */
	tt.insert(45);
	tt.insert(50);
	tt.insert(74);
	tt.insert(82);
	tt.insert(98);
	tt.insert(32);
	tt.insert(17);
	tt.insert(101);
	tt.insert(101);
	tt.insert(105);
	tt.insert(63);
	tt.insert(98);
	tt.insert(45);
	tt.insert(45);

	tt.trace();

	/* Output max, min, mean, and mode to console */
	std::cout << "Max: " << tt.get_max() << std::endl;
	std::cout << "Min: " << tt.get_min() << std::endl;
	std::cout << "Mean: " << tt.get_mean() << std::endl;
	std::cout << "Mode: " << tt.get_mode() << std::endl;

	return 0;
}