/*************************************************************
 * File: pqueue-linkedlist.cpp
 *
 * Implementation file for the LinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-linkedlist.h"
#include "error.h"

LinkedListPriorityQueue::LinkedListPriorityQueue() {
	head = NULL;
	len = 0; 
}

/*Go across along the linked list and delete it's elements*/
LinkedListPriorityQueue::~LinkedListPriorityQueue() {
	Cell* tmp;
	while(head != NULL){
		tmp = head;
		head = head->next;
		delete tmp;
	}
}

/*Returning the queue's size*/
int LinkedListPriorityQueue::size() {
	return len; 
}

/*Tells if the queue is empty*/
bool LinkedListPriorityQueue::isEmpty() {
	return len == 0;
}

void LinkedListPriorityQueue::enqueue(string value) {
	/*Creating new cell to save new value*/
	Cell* newCell = new Cell;
	newCell->word = value;
	
	if(head == NULL){ //If there is no element in queue
		newCell->next = NULL;
		head = newCell;
	} else {
		if(value < head->word){
			addAtFirst(newCell); 
		} else {
			sortedPutting(newCell); 
		}
	}
	len++;
}
/*If we addElement in the head*/
void LinkedListPriorityQueue:: addAtFirst(Cell*& newCel){
	Cell* tmp = head;
	newCel->next = tmp;
	head = newCel;
}

void LinkedListPriorityQueue:: sortedPutting(Cell*& newCel){
	for(Cell* ptr = head; ptr != NULL; ptr = ptr->next){
		if(ptr->next == NULL){//Adding in the end
			newCel->next = NULL;
			ptr->next = newCel;
			break;
		} else { //Adding between first and last element
			Cell* tm = ptr->next;
			if(newCel->word >= ptr->word && newCel->word <= tm->word){
				newCel->next = tm;
				ptr->next = newCel;
				break;
			}
		}
	}
}

/*Returning peek element*/
string LinkedListPriorityQueue::peek() {
	if(head == NULL){
		error("Queue is empty");
	} 
	return head->word;
}

/*Returning peek element and removing it from queue*/
string LinkedListPriorityQueue::dequeueMin() {
	string result = peek();
	Cell* tmp = head;
	head = head->next;
	delete tmp;
	len --;
	return result;
}

