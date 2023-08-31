/*
 * File: WordLadder.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Word Ladder problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "Lexicon.h"
#include "queue.h"
#include "simpio.h"
#include "stack.h"
#include "set.h"
#include <time.h>

using namespace std;

void addInQue(Lexicon& lex, Lexicon& used, string& temp, string& res, Queue<string>& everySeq){
	if(lex.contains(temp)){ //if changed word exist in lexicon
		if(!used.contains(temp)){ // if we have not used this word yet
			everySeq.enqueue(string(res) + " -> " + temp); // we should add new sequence in the queue
			used.add(temp); // adding used word in lexicon
		}
	}
}

//method, returning right sequence
string create(string& st, string& fl, Lexicon& lex){
	Queue< string > everySeq; // queue where we save sequences
	
	/** adding first word to the queue */
	string res = st;
	everySeq.enqueue(res);
	
	/**lexicon where we save used words */
	Lexicon used;
	used.add(st);

	while(!everySeq.isEmpty()){
		
		res = everySeq.dequeue();
		string temp = res.substr(res.size() - st.size(), st.size()); // last word in last string

		//if last word of last string equals final string we should stop and return exact sequence
		if(temp == fl){
			return res;
		} else {
			string copy = temp; 
			for(int j = 0; j < temp.length(); j++){
				for(char i = 'a'; i <= 'z'; i ++){
					temp[j] = i; //changing one symbol in word
					addInQue(lex, used, temp , res, everySeq); //adding new word in queue
					temp[j] = copy[j]; 
				}
			}
		}
	}
	return ""; //return empty string
}

int main() {

	//we ask consumer to enter two words
	while(true){	
		string str1 = getLine("Enter the start word (or nothing to quit): ");
		
		if(str1.length() == 0) {
			cout << "Goodbye! "<< endl;
			break;
		}

		string str2 = getLine("Enter the ending word: ");

		Lexicon words("EnglishWords.dat"); //lexicon of english words
		cout << "Processing..." << endl;
		
		string res = create(str1, str2, words); //this is the main methods which return the right sequence
		
		/** if res size equals 0 (we have not got right sequence), we should print no ladder found
		* else we need to print the right sequence*/
		if(res.size()  == 0){
			cout << "No ladder found" << endl;
		} else {
			cout << "Ladder found: " << res << endl;
		}
		cout << "" << endl;
	}
    return 0;
}
