/**********************************************************
 * File: HuffmanEncoding.cpp
 *
 * Implementation of the functions from HuffmanEncoding.h.
 * Most (if not all) of the code that you write for this
 * assignment will go into this file.
 */

#include "HuffmanEncoding.h"


/* Function: getFrequencyTable
 * Usage: Map<ext_char, int> freq = getFrequencyTable(file);
 * --------------------------------------------------------
 * Given an input stream containing text, calculates the
 * frequencies of each character within that text and stores
 * the result as a Map from ext_chars to the number of times
 * that the character appears.
 *
 * This function will also set the frequency of the PSEUDO_EOF
 * character to be 1, which ensures that any future encoding
 * tree built from these frequencies will have an encoding for
 * the PSEUDO_EOF character.
 */

/* Variable to remember encodingTree after compress operation */
//Node* treeStart; 


Map<ext_char, int> getFrequencyTable(istream& file) {
	Map<ext_char, int> result;
	filling_Map(result, file); // Filling the map
	result.put(PSEUDO_EOF, 1); // We also need EOF to be in our map
	return result;	
}


/* Function: buildEncodingTree
 * Usage: Node* tree = buildEncodingTree(frequency);
 * --------------------------------------------------------
 * Given a map from extended characters to frequencies,
 * constructs a Huffman encoding tree from those frequencies
 * and returns a pointer to the root.
 *
 * This function can assume that there is always at least one
 * entry in the map, since the PSEUDO_EOF character will always
 * be present.
 */
Node* buildEncodingTree(Map<ext_char, int>& frequencies) {
	PriorityQueue<Node*> que;
	filling_Que(que, frequencies); // Filling priority queue
	buildTree(que); // Building tree, where all path will be unique
	return que.peek(); // Returning que.peek, which is our tree's root
}

void buildTree(PriorityQueue<Node*>& que){
	while(que.size() != 1){

		/* getting Last two element if que has got else one */

		Node* first = que.dequeue();
		Node* second = NULL;
		if(que.size() >= 1){
			second = que.dequeue();
		}

		addNewRoot(que, first, second); // Adding new root
	}
}


/* Function: freeTree
 * Usage: freeTree(encodingTree);
 * --------------------------------------------------------
 * Deallocates all memory allocated for a given encoding
 * tree.
 */
void freeTree(Node* root) {
	deleteAll(root); // Deleting all elements of encodingTree
}

/* Function: encodeFile
 * Usage: encodeFile(source, encodingTree, output);
 * --------------------------------------------------------
 * Encodes the given file using the encoding specified by the
 * given encoding tree, then writes the result one bit at a
 * time to the specified output file.
 *
 * This function can assume the following:
 *
 *   - The encoding tree was constructed from the given file,
 *     so every character appears somewhere in the encoding
 *     tree.
 *
 *   - The output file already has the encoding table written
 *     to it, and the file cursor is at the end of the file.
 *     This means that you should just start writing the bits
 *     without seeking the file anywhere.
 */ 
void encodeFile(istream& infile, Node* encodingTree, obstream& outfile) { 
	char ch = 0;
	while(infile.get(ch)){
		conv_Char_ToBinary(encodingTree, ext_char(ch), outfile); // Converting char to 0s and 1s
	}
	/* Converting EOF to 0s and 1s for stoping in future after decoding file  */
	conv_Char_ToBinary(encodingTree, PSEUDO_EOF, outfile); 
}


/* Function: decodeFile
 * Usage: decodeFile(encodedFile, encodingTree, resultFile);
 * --------------------------------------------------------
 * Decodes a file that has previously been encoded using the
 * encodeFile function.  You can assume the following:
 *
 *   - The encoding table has already been read from the input
 *     file, and the encoding tree parameter was constructed from
 *     this encoding table.
 *
 *   - The output file is open and ready for writing.
 */
void decodeFile(ibstream& infile, Node* encodingTree, ostream& file) {
	ext_char bit = infile.readBit();
	ext_char ch = 0;
	while(true){
		/* Finding our character going through by 0s and 1s */
		ch = findDest(infile, bit, encodingTree, file); 

		if(ch == PSEUDO_EOF) break; // We reach EOF, so we have to stop here

		file.put(char(ch)); // putting our character in file 
	}
}

/* Function: writeFileHeader
 * Usage: writeFileHeader(output, frequencies);
 * --------------------------------------------------------
 * Writes a table to the front of the specified output file
 * that contains information about the frequencies of all of
 * the letters in the input text.  This information can then
 * be used to decompress input files once they've been
 * compressed.
 *
 * This function is provided for you.  You are free to modify
 * it if you see fit, but if you do you must also update the
 * readFileHeader function defined below this one so that it
 * can properly read the data back.
 */
void writeFileHeader(obstream& outfile, Map<ext_char, int>& frequencies) {
	/* The format we will use is the following:
	 *
	 * First number: Total number of characters whose frequency is being
	 *               encoded.
	 * An appropriate number of pairs of the form [char][frequency][space],
	 * encoding the number of occurrences.
	 *
	 * No information about PSEUDO_EOF is written, since the frequency is
	 * always 1.
	 */
	 
	/* Verify that we have PSEUDO_EOF somewhere in this mapping. */
	if (!frequencies.containsKey(PSEUDO_EOF)) {
		error("No PSEUDO_EOF defined.");
	}
	
	/* Write how many encodings we're going to have.  Note the space after
	 * this number to ensure that we can read it back correctly.
	 */
	outfile << frequencies.size() - 1 << ' ';
	
	/* Now, write the letter/frequency pairs. */
	foreach (ext_char ch in frequencies) {
		/* Skip PSEUDO_EOF if we see it. */
		if (ch == PSEUDO_EOF) continue;
		
		/* Write out the letter and its frequency. */
		outfile << char(ch) << frequencies[ch] << ' ';
	}
}

/* Function: readFileHeader
 * Usage: Map<ext_char, int> freq = writeFileHeader(input);
 * --------------------------------------------------------
 * Reads a table to the front of the specified input file
 * that contains information about the frequencies of all of
 * the letters in the input text.  This information can then
 * be used to reconstruct the encoding tree for that file.
 *
 * This function is provided for you.  You are free to modify
 * it if you see fit, but if you do you must also update the
 * writeFileHeader function defined before this one so that it
 * can properly write the data.
 */
Map<ext_char, int> readFileHeader(ibstream& infile) {
	/* This function inverts the mapping we wrote out in the
	 * writeFileHeader function before.  If you make any
	 * changes to that function, be sure to change this one
	 * too!
	 */
	Map<ext_char, int> result;
	
	/* Read how many values we're going to read in. */
	int numValues;
	infile >> numValues;
	
	/* Skip trailing whitespace. */
	infile.get();
	
	/* Read those values in. */
	for (int i = 0; i < numValues; i++) {
		/* Get the character we're going to read. */
		ext_char ch = infile.get();
		
		/* Get the frequency. */
		int frequency;
		infile >> frequency;
		
		/* Skip the space character. */
		infile.get();
		
		/* Add this to the encoding table. */
		result[ch] = frequency;
	}
	
	/* Add in 1 for PSEUDO_EOF. */
	result[PSEUDO_EOF] = 1;
	return result;
}

/* Function: compress
 * Usage: compress(infile, outfile);
 * --------------------------------------------------------
 * Main entry point for the Huffman compressor.  Compresses
 * the file whose contents are specified by the input
 * ibstream, then writes the result to outfile.  Your final
 * task in this assignment will be to combine all of the
 * previous functions together to implement this function,
 * which should not require much logic of its own and should
 * primarily be glue code.
 */
void compress(ibstream& infile, obstream& outfile) {
	Map<ext_char, int> frequencyMap = getFrequencyTable(infile); // Filling map
	writeFileHeader(outfile, frequencyMap);
	infile.rewind(); // Go to the infile's start
	Node* root = buildEncodingTree(frequencyMap);

	/* Filling encodingTree and Remembering it for the decompress */

	encodeFile(infile, root , outfile);
	freeTree(root);
}

/* Function: decompress
 * Usage: decompress(infile, outfile);
 * --------------------------------------------------------
 * Main entry point for the Huffman decompressor.
 * Decompresses the file whose contents are specified by the
 * input ibstream, then writes the decompressed version of
 * the file to the stream specified by outfile.  Your final
 * task in this assignment will be to combine all of the
 * previous functions together to implement this function,
 * which should not require much logic of its own and should
 * primarily be glue code.
 */
void decompress(ibstream& infile, ostream& outfile) {
	Map<ext_char, int> frequencyMap = readFileHeader(infile);
	Node* root = buildEncodingTree(frequencyMap);
	decodeFile(infile, root, outfile);

	freeTree(root); // Clearing tree
}


/* Reading information and saving it in the map */

void filling_Map(Map<ext_char, int>& result, istream& file){
	char ch = 0;
	while(file.get(ch)){
 
		if(!result.containsKey(ch)){ // New element in the map
			result.put(ch, 1);
			continue;
		}

		result.put(ch, result.get(ch) + 1); // We have already got this element in the map
	}
}

/* Reading map and saving info in priority Queue */

void filling_Que(PriorityQueue<Node*>& que, Map<ext_char, int>& frequencies){
	foreach(ext_char ch in frequencies){

		/* Creating new node and adding it to the queue */
		
		Node* tmp = new Node;
		tmp->character = ch;
		tmp->one = NULL;
		tmp->zero = NULL;
		tmp->weight = frequencies.get(ch);
		que.enqueue(tmp, tmp->weight);
	}
}

/* Adding new root to the queue while we have not
*  got one element left. New root merge last two 
*  element of the queue if it has got, else stop
*/

void addNewRoot(PriorityQueue<Node*>& que, Node*& first, Node*& second){

	/* Creating root and adding it to the queue */
	
	Node* root = new Node;
	root->character = NOT_A_CHAR;
	root->one = first;
	root->zero = second;
	root->weight = first->weight + second->weight;
	que.enqueue(root, root->weight);
}

/* Going through the tree and delete it's elements */

void deleteAll(Node* root){
	if(root!= NULL){
		deleteAll(root->one);
		deleteAll(root->zero);
		delete root;
	}
}

/* After reading character from the text, we 
* should convert it to 0 s and 1 s */

void conv_Char_ToBinary(Node*& encodingTree, ext_char ch, obstream& outfile){
	string str = "";
	find(str, encodingTree, "", ext_char(ch));
	fillingFile(str, outfile);
}

/* Finding the string which consist only 0s and 1s and it 
*  matches our character. Every string is unique */

void find(string& result, Node* encodingTree, string curr, ext_char ch){
	if(encodingTree->character == NOT_A_CHAR){
		if(found(result, encodingTree, curr, ch)){
			return;
		}
	}
	if(encodingTree->one != NULL)
		find(result, encodingTree->one, curr + '1', ch);
	
	if(encodingTree->zero != NULL)
		find(result, encodingTree->zero, curr + '0', ch);
}

/* If we found our character, we should stop here */

bool found(string& result, Node*& encodingTree, string& curr, ext_char& ch){
	if(encodingTree->one->character == ch){
		result = curr + '1';
		return true;
	}
	if(encodingTree->zero->character == ch){
		result = curr + '0';
		return true;
	}
	return false;
}

/* We already have got string and now we need it to be 
*  writen in the outfile file */

void fillingFile(string str, obstream& outfile){
	if(str.size() > 0){
		outfile.writeBit(str[0]-'0');
		fillingFile(str.substr(1), outfile);
	}
}

/* We go through the 0s and 1s until we find our 
*  destination ext_char */

ext_char findDest(ibstream& infile, ext_char& bit, Node* encodingTree, ostream& file){
	if(encodingTree->character != NOT_A_CHAR){
		return encodingTree->character;
	}
	ext_char x = bit;
	bit = infile.readBit();
	if(x == 0){
		 return findDest(infile, bit, encodingTree->zero, file);
	} else {
		 return findDest(infile, bit, encodingTree->one, file);
	}
	return NULL;
}
