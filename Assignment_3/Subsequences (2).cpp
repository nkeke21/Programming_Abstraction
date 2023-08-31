/*
 * File: Subsequences.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Subsequences problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
using namespace std;

/* Given two strings, returns whether the second string is a
 * subsequence of the first string.
 */
bool isSubsequence(string text, string subsequence);

int main() {
    // [TODO: fill with your code]
    return 0;
}


bool isSubsequence(string text, string subsequence){
	if(subsequence.length() == 0){
		return true; //base case, where we check if we check all letters in subsequence
	} else if(text.length() >= 1){ 
		if(text[0] == subsequence[0]) return isSubsequence(text.substr(1), subsequence.substr(1)); //if first letters of strings match to each other we go to the next step
		if(text[0] != subsequence[0]) return isSubsequence(text.substr(1), subsequence); //if first letters do not match to each other we make text string shorter and go to the next step
	} 
	return false;
}
