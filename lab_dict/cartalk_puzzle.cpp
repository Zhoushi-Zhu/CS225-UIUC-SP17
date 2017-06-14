/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>
#include <iostream>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of "StringTriples" (a typedef'd std::tuple, see top of
 * cartalk_puzzle.h). Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<StringTriple> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    /* Your code goes here! */
    vector<StringTriple> ret;
    vector<string> word5;
    ifstream wordsFile(word_list_fname);

    string word;
	if (wordsFile.is_open()) {
    /* Reads a line from `wordsFile` into `word` until the file ends. */
    	while (getline(wordsFile, word)) {
        	if(word.size() == 5)
        		word5.push_back(word);
        	//std::cout<<"!"<<std::endl;
    	}
	}

	for(auto & wordIt : word5){

		string orig = wordIt;
		string first = orig;
		string second = orig;

		first.erase(0, 1);
		second.erase(1, 1);

		/*std::cout<<"@"<<std::endl;
		std::cout<<orig<<std::endl;
		std::cout<<first<<std::endl;
		std::cout<<second<<std::endl;*/

		if(d.homophones(orig, first) && d.homophones(orig, second)){
			//std::cout<<"?"<<std::endl;
			StringTriple temp;
			get<0>(temp) = orig;
			get<1>(temp) = first;
			get<2>(temp) = second;
			ret.push_back(temp);
		}

	}
	


    return ret;
}
