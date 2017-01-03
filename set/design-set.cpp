
/** @file design-set.cpp
 *  @brief 
 *
 *  Design a data structure that supports insert, delete, search and getRandom in constant time
 *  
 *  insert(x): Inserts an item x to the data structure if not already present.
 *  
 *  remove(x): Removes an item x from the data structure if present.
 *  
 *  search(x): Searches an item x in the data structure.
 *  
 *  getRandom(): Returns a random element from current set of elements
 *  
 *  @author Shawn Mullings (@shawnmullings)
 *  @bug No known bugs.
 */


/* -- Includes -- */

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <ctime>
#include <random>

struct DesignSet
{
  private:
    // A value container
    std::vector<int> vec;

    // A hash where keys are vector elements and values are location of element with the vector
    std::map<int, int> hash;

  public:
    DesignSet(){}

    // Returns a random element
    int getRandom()
      { 
        srand(time(NULL));
        std::size_t rNum = rand() % vec.size();

        print_to_console("getrandom: " + std::to_string(rNum)); 

        return rNum;
      };

    // Add an element to container
    void insert(int val)
      { 
        print_to_console("inserting: " + std::to_string(val)); 

        if (hash.find(val) != hash.end())
          return;

        std::size_t sz = vec.size();
        vec.push_back(val);
        hash[val] = sz;

      };

    // Delete an element to container
    void remove(int val)
      { 
        print_to_console("remove: " + std::to_string(val));  

        if (hash.find(val) == hash.end())
          return;

        int loc = hash[val];
        hash.erase(val);

        hash[vec.back()] = loc;

        hash.find(val)->second = vec.back();
        vec.pop_back();
      };

    // Returns index of element if element is present, otherwise null
    int search(int val)
      { 
        print_to_console("search: " + std::to_string(val)); 

        return hash.find(val)->second;;
      };
    void print_to_console(std::string val){ std::cout << val << std::endl; }
};


int main(){

  DesignSet ds; 
  ds.insert(1000);
  ds.insert(900);
  ds.insert(800);
  ds.insert(700);
  ds.insert(600);
  ds.insert(500);
  ds.insert(400);
  ds.insert(300);
  ds.insert(200);
  ds.insert(100);
  ds.insert(50);

  std::cout << ds.search(600) << std::endl;
  
  ds.remove(200);
  ds.insert(1100);

  std::cout << ds.search(1100) << std::endl;
  std::cout << ds.getRandom() << std::endl;

  return 0;
}
