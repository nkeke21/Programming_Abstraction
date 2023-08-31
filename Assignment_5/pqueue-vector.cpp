/*************************************************************
 * File: pqueue-vector.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 */
 
#include "pqueue-vector.h"
#include "error.h"

/*Because we have got vector, we need not to fill this method. prgoram will work btw*/
VectorPriorityQueue::VectorPriorityQueue() {
	// TODO: Fill this in!
}


VectorPriorityQueue::~VectorPriorityQueue() {
	/*Cleaning queue*/
	vect.clear();
}

int VectorPriorityQueue::size() {
	/*Returning queue's size*/
	return vect.size();
}

bool VectorPriorityQueue::isEmpty() {
	/*Tells if queue is empty*/
	return vect.size() == 0;
}

void VectorPriorityQueue::enqueue(string value) {
	// TODO: Fill this in!
	vect.add(value);
}

string VectorPriorityQueue::peek() {
	/*Finding peek element in queue*/
	string result = "";
	if(vect.size() == 0){
		error("Queue is empty");
	} 

	result = vect[0]; minAt = 0;
	for(int i = 1; i < vect.size(); i ++){
		if(vect[i] < result){
			result = vect[i];
			minAt = i;
		}
	}
	return result;
}

string VectorPriorityQueue::dequeueMin() {
	//Finding peek element and delete it from queue.
	string s = peek();
	vect.remove(minAt);
	return s;
}

