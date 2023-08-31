/*
 * File: ConsecutiveHeads.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Consecutive Heads problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "Random.h"
using namespace std;

int main() {
    int count = 0; //counting all effort
	int heads = 0; // counting how much time we get head
	while(true){
		if(randomChance(1.0/2)){ //choosing ranomly with 50%
			cout << "head" <<endl; 
			heads ++;
		} else {
			cout << "tail" <<endl; // if we get tails we need heads be zero
			heads = 0;
		}
		count ++;
		if(heads == 3){ //if we get heads = 3 we should stop
			break;
		}
	}
	cout << "It took "<< count << " flips to get 3 consecutive heads" <<endl;
    return 0;
}
