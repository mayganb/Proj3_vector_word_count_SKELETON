/**
 * array_function.cpp
 * Author: Maygan Brewer
 */

#include "../includes/array_functions.h"
#include "../includes/utilities.h"
#include "../includes/constants.h"
#include <algorithm>


using namespace std;
using namespace constants;

namespace KP {
	bool ascendComp(const entry &firstEntry, const entry &secondEntry);
	bool descendComp(const entry &firstEntry, const entry &secondEntry);
	bool numOfTimes(const entry &firstEntry, const entry &secondEntry);

	//remove all elements from vector that tracks words and their occurrences
	void clear(vector<entry>  &entries){
		entries.clear();
	}

	//return how many unique words are in the vector
	int getSize(vector<entry> &entries){
		return entries.size();
	}

	//get word at location i iff i<size(see above function), otherwise return the last word
	//(this is lazy, should throw an exception instead)
	string getWordAt(vector<entry> &entries, int i){
		return entries.at(i).word;
	}

	//get number_occurences at location i iff i<size(see above function), otherwise return the last number_occurences
	//(this is lazy, should throw an exception instead)
	int getNumbOccurAt(vector<entry>  &entries,int i){
		if (entries.size() == 0){
			return FAIL;
		}
		return entries.at(i).number_occurences;
	}

	/*loop through the entire file, one line at a time
		 * call processLine on each line from the file
		 * returns false: myfstream is not open
		 *         true: otherwise*/
	bool processFile(vector<entry>  &entries,fstream &myfstream){
		if(!myfstream){
			return false;
		}
		string line1;
		while (getline(myfstream, line1)) {
			processLine(entries, line1);
		}
		return true;
	}

	/*take 1 line and extract all the tokens from it
		feed each token to processToken for recording*/
	void processLine(vector<constants::entry>  &entries,string &myLine){
		string tokenTemp;
		stringstream myStr(myLine);
		while (getline(myStr, tokenTemp, CHAR_TO_SEARCH_FOR)){
			processToken(entries, tokenTemp);
		}
	}

	/*NOTE: first call strip_unwanted_chars from utilities to get rid of rubbish chars in the token
		 * if the token is an empty string after this then return since we are not tracking empty strings
		 *
		 * Keep track of how many times each token seen, in other words look thru the entries vector that
		 * holds entry structs to see if there is a struct that has entry.word==token,
		 * if so increment entry.number_occurences, otherwise create a new entry struct for the token,
		 * set entry.number_occurences=1 and add it to the entries vector*/
	void processToken(vector<constants::entry>  &entries,string &token){
		if(strip_unwanted_chars(token) == false){
			return;
		}
		string nToken = token;
		toUpper(nToken);
		int num1 = -1;
		for (unsigned int i = 0; i < entries.size(); i++){
			string user = entries[i].word_uppercase;
			if (user == nToken){
				num1 = i;
				break;
			}

		}
		if (num1 != -1){
			entries[num1].number_occurences++;
		}
		else{
			entry newEntry {token, nToken, 1};
			entries.push_back(newEntry);
		}
	}
	/*
	 * Sort entries based on so enum value.
	 * Please provide a solution that sorts according to the enum
	 * The presence of the enum implies a switch statement based on its value
	 * See the course lectures and demo projects for how to sort a vector of structs
	 */
	void sort(vector<constants::entry>  &entries, sortOrder so){
		if(so == NONE) {
			return;
		}
		if (so == ASCENDING) {
			sort(entries.begin(), entries.end(), ascendComp);
		}
		if (so == DESCENDING) {
			sort(entries.begin(), entries.end(), descendComp);
		}
		if (so == NUMBER_OCCURRENCES) {
			sort(entries.begin(), entries.end(), numOfTimes);
		}
	}
	bool ascendComp(const entry &firstEntry, const entry &secondEntry){
		return firstEntry.word_uppercase < secondEntry.word_uppercase;
	}
	bool descendComp(const entry &firstEntry, const entry &secondEntry){
		return firstEntry.word_uppercase > secondEntry.word_uppercase;
	}
	bool numOfTimes(const entry &firstEntry, const entry &secondEntry){
		return firstEntry.number_occurences > secondEntry.number_occurences;
	}


}
