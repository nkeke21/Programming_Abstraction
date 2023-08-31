/*
 * File: Combinations.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Combinations problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
using namespace std;

int comb(int n, int k); //counting combinations
int factorial(int q); //method counting factorial of number

int main() {
	cout <<	comb(2, 2) << endl;
    return 0;
}

int comb(int n, int k){
	int tot = factorial(k) * factorial(n - k);
	if(factorial(n)/tot == 1){ // if we reac 1 in triangle we should stop
		return 1;
	} else {
		return comb(n-1, k - 1) + comb(n-1, k); //sum of two numbers
	}
}

//method to count factorial
int factorial(int q){
	if(q == 0){
		return 1;
	} else {
		return q * factorial(q-1);
	}
}
