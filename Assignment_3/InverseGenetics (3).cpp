/*
 * File: InverseGenetics.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Inverse Genetics problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include <fstream>
#include "set.h"
#include "map.h"
#include "console.h"
using namespace std;

/* Function: listAllRNAStrandsFor(string protein,
 *                                Map<char, Set<string> >& codons);
 * Usage: listAllRNAStrandsFor("PARTY", codons);
 * ==================================================================
 * Given a protein and a map from amino acid codes to the codons for
 * that code, lists all possible RNA strands that could generate
 * that protein
 */
void listAllRNAStrandsFor(string protein, Map<char, Set<string> >& codons);
void PrintingAllRNAS(string protein, Map<char, Set<string> >& codons, string result);

/* Function: loadCodonMap();
 * Usage: Map<char, Lexicon> codonMap = loadCodonMap();
 * ==================================================================
 * Loads the codon mapping table from a file.
 */
Map<char, Set<string> > loadCodonMap();

int main() {
    /* Load the codon map. */
    /* [TODO: Implement this!] */
    return 0;
}

/* You do not need to change this function. */
Map<char, Set<string> > loadCodonMap() {
    ifstream input("codons.txt");
    Map<char, Set<string> > result;

    /* The current codon / protein combination. */
    string codon;
    char protein;

    /* Continuously pull data from the file until all data has been
     * read.
     */
    while (input >> codon >> protein) {
        result[protein] += codon;
    }

    return result;
}

// For me to solve this probles, the easiest way is to call another function in listAllRNAStrandsFor 
void listAllRNAStrandsFor(string protein, Map<char, Set<string> >& codons){
	PrintingAllRNAS(protein, codons, "");
}

// The main function where we print all list of amino acid in nucleotides. Variable result is to remember current amino acid string in nucleotides
void PrintingAllRNAS(string protein, Map<char, Set<string> >& codons, string result){
	if(protein.length() == 0){ // Base case. If we check all letter in amino acid string
		cout << result << endl;  // Printing result
	} else {
		Set<string> out = codons.get(protein[0]); // We take set in map of the first character of the protein
		while(!out.isEmpty()){ // Checking all the elements in the set 
			string txt = out.first(); // Taking the element from the set
			out.remove(out.first()); // We remove it, because we do not need it any more
			PrintingAllRNAS(protein.substr(1), codons, string(result) + txt); // Use recursion and Go to the next step 
		}
	}
}
