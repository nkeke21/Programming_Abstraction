/*************************************************************
 * File: pqueue-doublylinkedlist.cpp
 *
 * Implementation file for the DoublyLinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-doublylinkedlist.h"
#include "error.h"

DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
	head = NULL;
	rem = NULL;
	len = 0;

}

/*Go across the queue and remove it's elements*/
DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
	Cell* tmp;
	while(head != NULL){
		tmp = head;
		head = head->next;
		delete tmp;
	}
}

/*Returning the queue's size*/
int DoublyLinkedListPriorityQueue::size() {
	return len;
}

/*Tells if queue is empty*/
bool DoublyLinkedListPriorityQueue::isEmpty() {
	return len == 0;
}


void DoublyLinkedListPriorityQueue::enqueue(string value) {
	Cell* newCell = new Cell;
	newCell->value = value;

	if(head == NULL){ //If we have empty queue
		newCell->next = NULL;
		newCell->last = NULL;
		head = newCell;
		rem = newCell;
	} else {
		Cell* curr = head; //Go across the queue and add the element in the last
		while(curr->next != NULL){
			curr = curr->next;
		}
		newCell->last = curr;
		newCell->next = NULL;
		curr->next = newCell;
	}

	len ++; 
}

/*Returning peek element*/
string DoublyLinkedListPriorityQueue::peek() {
	if(head == NULL){
		error("Queue is empty");
	} 
	string result = head->value; //Go across the queue and finding min element
	rem = head;
	for(Cell* ptr = head->next; ptr != NULL; ptr = ptr->next){
		if(result > ptr->value){
			result = ptr->value;
			rem = ptr;
		}
	}
	return result;
}

/*Finding where our peek element is and delete it from queue*/
string DoublyLinkedListPriorityQueue::dequeueMin() {
	string result = peek();
	Cell* tmp;
	mergeNewList(tmp); //Merging
	delete tmp;
	len --;
	return result;
}

void DoublyLinkedListPriorityQueue:: mergeNewList(Cell*& tmp){
	if(head == rem){
		atHead(tmp); //When dest element is in the head
		return ;
	}
	if(rem->next == NULL){//When the element is in the end
		atLast(tmp); 
		return;
	}
	inMid(tmp); //When the element is between head and end
}

//When dest element is in the head
void DoublyLinkedListPriorityQueue::atHead(Cell*& tmp){
	tmp = head;
	head = head->next;
	if(head != NULL){
		head->last = NULL;
	}
}

//When the element is in the end
void DoublyLinkedListPriorityQueue::atLast(Cell*& tmp){
	tmp = rem;
	Cell* previous = rem->last;
	if(previous != NULL){
		previous->next = NULL;
	}
}

//When the element is between head and end
void DoublyLinkedListPriorityQueue::inMid(Cell*& tmp){
	tmp = rem;
	Cell* next = tmp->next;
	Cell* previous = tmp->last;
	next->last = previous;
	previous->next = next;
}

