/*************************************************************
 * File: pqueue-heap.cpp
 *
 * Implementation file for the HeapPriorityQueue
 * class.
 */
 
#include "pqueue-heap.h"
#include "error.h"

const int defaultLen = 16;
const int first = 0;

HeapPriorityQueue::HeapPriorityQueue() {
	currLen = 0;
	logLength = defaultLen;
	elems = new string[logLength];

}

/*Delete elements from queue and for this reason we should equal currLen to 0*/
HeapPriorityQueue::~HeapPriorityQueue() {
	currLen = 0;
	delete[] elems;
}

/*Return queue's size*/
int HeapPriorityQueue::size() {
	return currLen;
}

/*Tells if the queue is empty*/
bool HeapPriorityQueue::isEmpty() {
	return currLen == 0;
}

/*Adding element*/
void HeapPriorityQueue::enqueue(string value) {
	if(currLen == logLength){ //If massive is full we should resize the massive
		increase();
	}
	elems[currLen] = value;
	currLen ++;
	bubble_up();
}

/*Returning peek element*/
string HeapPriorityQueue::peek() {
	if(currLen == 0){
		error("You try to take a string from empty queue!");
	}
	return elems[0];
}

/*Returning peek element and removing it from queue*/
string HeapPriorityQueue::dequeueMin() {
	string result = peek();
	swapping();
	currLen --;
	bubble_down();
	return result;
}

/*Go from child to parents to sort massive*/
void HeapPriorityQueue::bubble_up(){
	for(int i = currLen; i > 1; i --){
		if(elems[i-1] <  elems[i/2-1]){
			string s = elems[i-1];
			elems[i-1] = elems[i/2-1];
			elems[i/2-1] = s;
		}
	}
}

/*After dequing we should sort our new massive*/
void HeapPriorityQueue::bubble_down(){
	int count = first+1;
	while(2*count <= currLen){
		int minAt = youngerChild(count); //Finding younger child
		string s = elems[count-1];
		if(s < elems[minAt]){
			break;
		}
		elems[count-1] = elems[minAt];
		elems[minAt] = s;
		count = minAt + 1;
	}
}

/*Finding younger child*/
int HeapPriorityQueue::youngerChild(int count){
	if(elems[2*count] == ""){
		return 2*count-1;
	} else {
		if(elems[2*count-1] < elems[2*count]){
			return 2*count-1;
		}
	}
	return 2*count;
}

/*Growing massive*/
void HeapPriorityQueue::increase(){
	logLength *= 2;
	string * tmp = new string[logLength];
	for(int i = 0; i < currLen; i++){
		tmp[i] = elems[i];
	}
	delete[] elems;
	elems = tmp;
}

/*Swapping last and first elements*/
void HeapPriorityQueue:: swapping(){
	elems[0] = elems[currLen-1];
	elems[currLen-1] = "";
}
