/*
 * File: UniversalHealthCoverage.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the UniversalHealthCoverage problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */
#include <iostream>
#include <string>
#include "set.h"
#include "vector.h"
#include "simpio.h"
#include "console.h"
using namespace std;

/* Function: canOfferUniversalCoverage(Set<string>& cities,
 *                                     Vector< Set<string> >& locations,
 *                                     int numHospitals,
 *                                     Vector< Set<string> >& result);
 * Usage: if (canOfferUniversalCoverage(cities, locations, 4, result)
 * ==================================================================
 * Given a set of cities, a list of what cities various hospitals can
 * cover, and a number of hospitals, returns whether or not it's
 * possible to provide coverage to all cities with the given number of
 * hospitals.  If so, one specific way to do this is handed back in the
 * result parameter.
 */
bool canOfferUniversalCoverage(Set<string>& cities,
                               Vector< Set<string> >& locations,
                               int numHospitals,
                               Vector< Set<string> >& result);

void filling(Set<string>& cities, Vector< Set<string> >& locations,  int numHospitals, Vector< Set<string> > &vect, Vector< Vector< Set<string> > >& All, int startIndex);
bool possible(Vector< Set<string> >& result, Set<string>& cities);


int main() {
	Set<string> cities; cities.add("A"); cities.add("B"); cities.add("C"); cities.add("D"); cities.add("E"); cities.add("F"); cities.add("K");
	Set<string> loc3; loc3.add("B"); loc3.add("E"); 
	Set<string> loc1; loc1.add("A"); loc1.add("B"); loc1.add("C"); 
	Set<string> loc2; loc2.add("A"); loc2.add("C"); loc2.add("D");
	Set<string> loc5; loc5.add("V"); loc5.add("M"); loc5.add("S"); loc5.add("P");
	Set<string> loc4; loc4.add("C"); loc4.add("E"); loc4.add("F"); loc4.add("K");
	Vector<Set<string> > locations; locations += loc3;  locations += loc5;  locations += loc1;  locations += loc4; locations += loc2;
	int numHospitals = getInteger("Enter amount of hospitals: ");
	Vector< Set<string> > result;
	if(canOfferUniversalCoverage(cities, locations, numHospitals, result)){
		cout << "Yes, it is possible: " << result <<  endl;
	} else {
		cout  << "No, it is not possible " << endl;
	}
    return 0;
}

bool canOfferUniversalCoverage(Set<string>& cities, Vector< Set<string> >& locations,  int numHospitals, Vector< Set<string> >& result){
	Vector< Vector< Set<string> > > All; // Vector, where i save all list of hospitals that can cover the city 
	Vector< Set<string> > vect; // This is empy vector, which i need to remember list of hospitals that can cover the city
	filling(cities, locations, numHospitals, vect, All, 0); // Function to save list of hospitals covering the city
	
	int min = INT_MAX; // Now we need to detect which is the smallest list
	for(int i = 0; i < All.size(); i ++){
		if(All[i].size() < min){
			result = All[i];
			min = All[i].size();
		}
	}
	return All.size() > 0;
}

void filling(Set<string>& cities, Vector< Set<string> >& locations,  int numHospitals, Vector< Set<string> > &vect, Vector< Vector< Set<string> > >& All, int startIndex){
	if(possible(vect, cities)){
		All.add(vect); // Base case, if we find the list of hospitals covering the whole city, we should add it to the Vector(All) to remember it
	}
	if(numHospitals > 0 && startIndex < locations.size()){ 
		filling(cities, locations, numHospitals, vect, All, startIndex + 1); // Not adding first hospital
		vect.add(locations[startIndex]); 
		filling(cities, locations, numHospitals - 1, vect, All, startIndex + 1); // Adding first hospital
		vect.remove(vect.size() - 1); // This helps us to not to copy vect variable for many times, which means that we can use this variable by reference
	} 
}

bool possible(Vector< Set<string> >& result, Set<string>& cities){ // Function that return true if we find the list of hospitals covering the whole city
	Set<string> res; 
	for(int i = 0; i < result.size(); i ++){ // Uniting all sets in one set to detect if this list can coverage the whole city
		res += result[i];
	}
	Set<string> ss = cities - res;
	if(ss.size() == 0){ // Checking covering
		return true;
	} 
	return false;
}
