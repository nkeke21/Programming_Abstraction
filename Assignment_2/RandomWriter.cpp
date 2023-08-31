/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Random Writer problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "simpio.h"
#include <fstream>
#include <string>
#include "random.h"
#include "filelib.h"
#include <time.h>
#include "map.h"
using namespace std;

// struct for saving information
struct statsT{
	string max;
	Map<string, Vector<char> > map;
};

//this method fill map and save the most important information
void fill(char c, Map<string, Vector<char> >& map, int k, string& text){
	if(text.length() >= k){
		map[text.substr(text.length()-k, k)].add(c);
	}
	text += c;	
}

//this method returns most frequent string in the text
string sort(Map<string, Vector<char> >& map){
	string result = "";
	int maxLen = INT_MIN;
	
	// we are searching string which has got the most longest vector in the value
	foreach(string st in map){
		if(map.get(st).size() > maxLen){
			maxLen = map.get(st).size();
			result = st;
		}
	}

	return result;
}

//method which returns character
char extra(string& last, statsT& inf, int& k){
	Vector<char> vect = inf.map.get(last); // vector of last string 
	if(vect.size() >= 1){ // if the string has got vector with the length more than 1, this means that something follow it in the text
		int x = randomInteger(0, vect.size() - 1);
		return vect[x];
	}
	return ' '; 
}

//method for printing
void printing(statsT& info,  int& k){
	string result = "";  //creating empty string
	result = string(result) + info.max; //adding most frequent string

	if(result.length() >= k){ // if k is more than result, this means that consumer enter k which is more than text, so we should return empty string
		while(result.length() < 2000){ 
			
			string last = result.substr(result.length() -k, k); //last string 
			if(info.map.get(last).size() == 0){ //if nothing follow the current last string we should stop
				break;
			} else{
				result += extra(last, info, k); //adding extra character
			}

		}
	}

	cout << result << endl;
}

void output(string st, int& k){
	statsT info;  //struct where i save information
	
	/**In the next lines we read file and save information */
	string file(st);
	ifstream input(file.c_str());
	string text;
	
	char c = 0;
	while(input.get(c)){
		fill(c, info.map , k, text);
	
	}

	input.close();
	info.max = sort(info.map); //this method return the string with the length of k which we meet mostly in the text 
	printing(info, k); // printing information
}

int main() {
	/**First of all, we should make consumer enter filename and k. If file name does not exist we should 
	/* make consumer to enter file name again or if a consumer enter k less than 1 or more than 10 we should make it to enter k again */ 
	ifstream file;
	string s = promptUserForFile(file, "Enter file name:  ");
	int k = getInteger("Enter the Maskow order [1-10]: ");
	while(k < 1 || k > 10){
		k = getInteger("Enter the Maskow order [1-10]: ");
	}
	cout << "Processing file..." << endl;

	output(s, k); //main method which will print result

	return 0;
}
