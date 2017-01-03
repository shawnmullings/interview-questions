
/** @file palindrome-string.cpp
 *  @brief 
 *
 *  Write an efficient function that checks, in-place, whether a string input such as "aabbcbbaa" is a palindrome.
 *  
 *  A palindrome is a word, phrase, or sequence that reads the same backward as forward.
 *  
 *  For example:
 *  
 *  "aabbcbbaa" should return true
 *  "abcda" should return false
 *
 *  @author Shawn Mullings (@shawnmullings)
 *  @bug No known bugs.
 */


/* -- Includes -- */

#include <iostream>
#include <string>


/* Evalute 'str' as a palindrome */
bool isPalindrome(std::string &str)
{
    /*  return the results of 'std::equal()' evaluation of the first half of 'str' with second half of 'str' via reverse begin iterator 'rbegin()'.
        Reverse iterator 'rbegin()' starts at the 'reverse of the begining of a container' (the end) iterates backwards 
        towards the beginning of the container. */
    return (std::equal( str.begin(), str.begin() + str.size()/2, str.rbegin() ));
}
 
int main(int argc, char const *argv[])
{
    // Target string 
    std::string target_string("aabbcbbaa");

    // Output 'isPalindrome' results to console
    std::cout << "Is " << target_string << " a palindrome: " << (isPalindrome(target_string) ? "true" : "false") << std::endl;
 
    return 0;
}