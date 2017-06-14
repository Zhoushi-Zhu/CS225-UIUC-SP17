/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>
#include <iostream>

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
    ifstream wordsFile(filename);
    vector<string> Words;
    string temp;
    if (wordsFile.is_open()) {
    /* Reads a line from `wordsFile` into `word` until the file ends. */
    	while (getline(wordsFile, temp)) {
        		Words.push_back(temp);
        	//std::cout<<"!"<<std::endl;
    	}
	}

	for(auto & vecIt : Words){

	 auto find = dict.find(vecIt);

	 if(find == dict.end()){
	 	string Second = vecIt;
	 	std::sort(Second.begin(), Second.end());
	 	dict.insert(std::pair<string, string>(vecIt, Second));
	 }
	}

}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */
	for(auto & vecIt : words){

	 auto find = dict.find(vecIt);

	 if(find == dict.end()){
	 	string Second = vecIt;
	 	std::sort(Second.begin(), Second.end());
	 	dict.insert(std::pair<string, string>(vecIt, Second));
	 }
	}

}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
    vector<string> ret;
    auto find = dict.find(word);
    if(find == dict.end())
    	return vector<string>();
    else{
    	string temp = find->second;
    	for(auto & dictIt : dict){
    		if(dictIt.second == temp)
    			ret.push_back(dictIt.first);
    	}   
    }
    return ret;
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
	vector<vector<string>> ret;
	//vector<string> words;
	//<string> ana;

	/*for(auto & outer : dict){
		words.push_back(outer.first);
		//ana.push_back(outer.second);
	}*/


	for(auto & outer : dict){

		vector<string> A;

		//auto find = dict.find(word);
		string temp = outer.second;

		for(auto & inner : dict){
			if(inner.second == temp)
				A.push_back(inner.first);
			//std::cout<<"1"<<std::endl;
		}

		if(A.size() >= 2)
			ret.push_back(A);
	}


    return ret;
}
