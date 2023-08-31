/*
 * File: NumericConversions.cpp
 * ---------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Numeric Conversions problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
using namespace std;

/* Function prototypes */

string intToString(int n); //converts int to string
int stringToInt(string str); //converts string to int

/* Main program */

int main() {
	cout << intToString(-15)<< endl;
	cout << stringToInt("-15")<<endl;
    return 0;
}

string intToString(int n){
	if(n < 0){
		n = -n; //if input is negative we should add '-' in the first position
		return "-" +  intToString(n);
	} else if(n < 1) {
		return ""; //when input is less than 1, we should stop
	} else {
		char ch = char('0') + n % 10; //converts int to char
		if(n > 0){
			return intToString(n/10) + ch; 
		}
	}
}

int stringToInt(string str){
	if(str.length() == 0){ //if length is 0, we should stop
		return 0;
	} else if(str.length() == 1 && str[0] == '-'){ 
		return 0;
	} else {
		if(str[0] == '-'){ //situation when the number is negative
			return (stringToInt(str.substr(1, str.length() - 2))) * (-10) - (str[str.length()-1]-'0');
		} else { //situation when number is positive
			return stringToInt(str.substr(0, str.length() - 1)) * 10 + (str[str.length()-1] - '0');
		}
	}
}




