/*
 * File: FleschKincaid.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Flesch-Kincaid problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include <fstream>
#include <string>
#include "simpio.h"
#include "tokenScanner.h"
#include "filelib.h"

using namespace std;

const double c0 = -15.59;
const double c1 = 0.39;
const double c2 = 11.8;

int syll(string  st);

struct statsT{
	double words; //created to save amount of words
	double sentences; //created to save amount of sentences
	double syllables; //created to save amount of syllables
	double score; //created to save amount of score
};

statsT filling(string fils);

int main() {
    ifstream file;
	string s = promptUserForFile(file, "Enter text file name: "); // asking user to enter string
	string fil(s);
	statsT result = filling(fil);
	cout << result.words <<endl;
	cout << result.sentences <<endl;
	cout << result.syllables<<endl;
	cout << result.score <<endl;
    return 0;
}

//methods to remember information about text file

statsT filling(string fils){
	statsT output;

	//variables for counting 
	output.words  = 0; output.score = 0; output.sentences = 0; output.syllables = 0;

	ifstream input(fils.c_str());
	string line;

	while(getline(input, line)){
		//using tokenscanner to get words
		TokenScanner scanner(line);
		scanner.addWordCharacters("'");
		scanner.ignoreWhitespace();

		while(scanner.hasMoreTokens()){
			string token = scanner.nextToken();
			if(scanner.getTokenType(token) == WORD && token != "'"){ //this is situation when token is string
				output.words ++;
				output.syllables += syll(token); //amount of syllables in word
				cout << token <<  " ----------> " << syll(token) << endl;
			}
			//counting sentences in text
			if(token == "." || token =="?" || token == "!"){
				output.sentences ++;
			}
		}
	}
	//we have got all the information. now we can count grade
	output.score = c0 + c1 * (output.words/output.sentences) + c2 * (output.syllables/output.words);
	return output;
}

int syll(string st){
	int cou = 0;
	string vowel = "aeiouAEIOUyy"; //string containint all vowels
	for(int i = 0; i < st.length() - 1; i ++){
	//if vowel contains st[i] and vowel does not contain st[i+1] this means that we should add 1 to cou
		if(vowel.find(st[i]) != std::string::npos && vowel.find(st[i+1]) == std::string::npos){
			cou ++;
		}
	}
	if(st[st.length() - 1] == 'e'){ //situation when last two chars are e
		if(st[st.length() - 2] == 'e'){
			cou ++;
		}
	} else if(st.length() >= 2){
		//situation for the last char when it is vowel and st[st.length - 2] is not 
		if(vowel.find(st[st.length()-1]) != std::string::npos && vowel.find(st[st.length() - 2]) == std::string::npos){
			cou ++;
		}
	}
	if(cou == 0){
		return 1;
	} else {
		return cou;
	}
}