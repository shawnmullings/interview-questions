
/** @file permutation-is-palindrome.cpp
 *  @brief 
 *  
 *  Write an efficient function that checks whether any permutation of an input string is a palindrome.
 *  
 *  Permutation is a way, especially one of several possible variations, in which a set or number of things can be ordered or arranged.
 *  
 *  Palindrome is a word, phrase, or sequence that reads the same backward as forward.
 *  
 *  method "permutationIsPalindrome(string)" should return true if palindrome is found.
 *  
 *  For example:
 *  
 *  "civic" should return true
 *  "ivicc" should return true
 *  "civil" should return false
 *  "livci" should return false
 *  
 *  @author Shawn Mullings (@shawnmullings)
 *  @bug No known bugs.
 */


/* -- Includes -- */


#include <iostream>
#include <string>

/* Function to evalute 'str' as a palindrome */
bool isPalindrome(std::string &str)
{
    return (std::equal( str.begin(), str.begin() + str.size()/2, str.rbegin() ));
}

/* Function to evalute all permutations 'str' as a palindrome */
bool permutationIsPalindrome(std::string &str){
    // Found palindrome flag
    bool foundPermutationAsPalindrome = false;

    // loop to find permutations of 'str' and evaluate each as palindrome
    do{
        if( isPalindrome(str) ){
            //std::cout << str << std::endl;
            foundPermutationAsPalindrome = true;
        }

    }while( std::next_permutation(str.begin(), str.end() ) && foundPermutationAsPalindrome == false);

    // return palindrome flag
    return foundPermutationAsPalindrome;
}

 
int main(int argc, char const *argv[])
{
    // Target string 
    std::string target_string("aabbcc");

    // Output 'permutationIsPalindrome' results to console
    std::cout << "Permutation of " << target_string << " is a palindrome: " << ( permutationIsPalindrome(target_string) ? "true" : "false" ) << std::endl;
 
    return 0;
}

