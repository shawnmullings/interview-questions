

/** @file reverse-words-in-string.cpp
 *  @brief 
 *
 *  You're working on a secret team solving coded transmissions.
 *  Your team is scrambling to decipher a recent message, worried it's a plot to break into a major European National Cake Vault. The message has been mostly deciphered, but all the words are backwards! Your colleagues have handed off the last step to you.
 *  
 *  Write a function reverse_words() that takes a string message and reverses the order of the words in-place.
 *  
 *  Since strings in Python are immutable ↴ , we'll first convert the string into a list of characters, do the in-place word reversal on that list, and re-join that list into a string before returning it. This isn't technically "in-place" and the list of characters will cost O(n) additional space, but it's a reasonable way to stay within the spirit of the challenge. If you're comfortable coding in a language with mutable strings, that'd be even better!
 *  
 *  For example:
 *  
 *  message = 'find you will pain only go you recordings security the into if'
 *  
 *  reverse_words(message)
 *  returns: 'if into the security recordings you go only pain will you find'
 *  
 *  When writing your function, assume the message contains only letters and spaces, and all words are separated by one space.
 *
 *  @author Shawn Mullings (@shawnmullings)
 *  @bug No known bugs.
 */


/* -- Includes -- */

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iterator>

std::string reverse_words(std::string &str);
void reverse_words_helper(std::string &str);
void string_split(const std::string &str, const char* delim, std::vector<std::string> &vec);

std::string reverse_words(std::string &str){

	// First reverse target string 
	reverse_words_helper(str);

	// Vector of words
	std::vector<std::string> str_tokenized;

	// Split target string on deliminator ' '
	char delim = ' ';
	string_split(str, &delim, str_tokenized);

	// Reverse each word in vector
	std::for_each(str_tokenized.begin(), str_tokenized.end(), reverse_words_helper);
	
	// Create out string stream
	std::ostringstream oss;

    // Convert vector of string to string via out string stream
    std::copy(str_tokenized.begin(), str_tokenized.end(), std::ostream_iterator<std::string>(oss, " "));

    // return string from out string stream
	return oss.str();
}

// Reverse string using standard library 'reverse' method  
void reverse_words_helper(std::string &str){ 
	std::reverse(str.begin(), str.end()); 
}

// Split target string on deliminator
void string_split(const std::string &str, const char* delim, std::vector<std::string> &vec){
  	// Create string stream from traget string 
  	std::stringstream str_stream(str);
  	// Split word
  	std::string str_token;
  
  	// loop trought target string using 'std::getline' to find words
	while(std::getline(str_stream, str_token, *delim)) {
		// Save word to vector
		vec.push_back(str_token);
	}
}

int main(int argc, char const *argv[])
{
	// Target string 
	std::string message ("find you will pain only go you recordings security the into if");
	
	// Output reversed words from target string 
	std::cout << reverse_words(message) << std::endl;

	return 0;
}
