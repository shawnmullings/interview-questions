
/** @file find-first-consecutive-char.cpp
 *  @brief 
 *
 *  Given a string find the first consectutive character.
 *  
 *  input: "infinity"
 *  output: "i"
 *
 *  @author Shawn Mullings (@shawnmullings)
 *  @bug No known bugs.
 */


/* -- Includes -- */

#include <iostream>
#include <map>
#include <unordered_map>
#include <string>

char first_consectutive_char (std::string &s){

  std::map<char, int> charStore;

  for(int it = 0;  it != s.length(); it++){
    charStore[ s[it] ]++;
    std::cout << charStore[ s[it] ] << std::endl;
    if (charStore[ s[it] ] > 1){
      return charStore[ s[it] ];
    }
  }

  return ' ';
}


int main ()
{
  std::string s("hello");
  std::cout << first_consectutive_char(s) << std::endl;

  return 0;
}