/*
 * File: Boggle.cpp
 * ----------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the main starter file for Assignment #4, Boggle.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "gboggle.h"
#include "grid.h"
#include "gwindow.h"
#include "lexicon.h"
#include "random.h"
#include "simpio.h"
using namespace std;

/* Constants */

const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;

const string STANDARD_CUBES[16]  = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};
 
const string BIG_BOGGLE_CUBES[25]  = {
    "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
    "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
    "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
    "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
    "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

const int B_SIZE = 4;
const int MIN_SIZE = 4;
const int strSize = 16;

/* Function prototypes */

void welcome();
void giveInstructions();

bool instruct();
void playGame();

bool wantFill();
void customFill(Grid<char> &grd);
bool valid(string str);
void labbing(string s, Grid<char> &grd);

void fillingCubes(Grid<char> &grd);
void swap(int i, int x, Vector<string> &stCubes);
void labCubes(Vector<string> stCubes, Grid<char> &grd);

void guessing(Grid<char> &grd, Lexicon lex);

void playerPart(Grid<char> &grd, Lexicon lex, Set<string> &gamer);
bool find(string dest, Grid<char> grd, Lexicon lex);
bool finding(string dest, Grid<char> &grd, Lexicon lex, string curr, int r, int c);
void unLight(Grid<char> &grd);

void computerPart(Grid<char> &grd, Lexicon lex, Set<string> gamer, Set<string> &computer);
void compFind(Grid<char> &grd, Lexicon lex, string str, int r, int c, Set<string> gamer, Set<string> &computer);

bool GO_ON();

/* Main program */

int main() {
    GWindow gw(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
    initGBoggle(gw);
    welcome();
	if(instruct()) giveInstructions(); //Asking player if he needs instructions
	playGame(); //Main part of the code
    return 0;
}

//This is the main part because there is the most significant code for this game
void playGame(){
	Lexicon lex("EnglishWords.dat"); 

	//While loop for playing again and again if a costumer wants to continue game
	while(true){
		//In the next lines we draw board and make character grid to save information 
		drawBoard(B_SIZE, B_SIZE);
		Grid<char> grd (B_SIZE, B_SIZE);
		
		//Asking customers if they want to fill the board
		cout << "I'll give you a chance to set up the board to your specification, which makes it easier to confirm your boggle program is working. "<< endl;
		if(wantFill()) {
			customFill(grd); //Costumer fills the board
		} else {
			fillingCubes(grd); //Computer fills the board
		}
		//Everything is okay, because board is filled, and now we want to guess the words
		guessing(grd, lex);
		if(!GO_ON()) break; // asking customers if they want to continue game
	}
}

/*Asking player if he needs instructions */
bool instruct(){
	while(true){
		string s = getLine("Do you need instruction? ");
		if(toLowerCase(s) == "yes") return true;
		if(toLowerCase(s) == "no") return false;
		cout << "Please answer yes or no." << endl;
	}
	return false;
}

/*Asking customers if they want to fill the board */
bool wantFill(){
	while(true){
		string s = getLine("Do you want to force the board configuration? ");
		if(toLowerCase(s) == "yes") return true;
		if(toLowerCase(s) == "no") return false;
		cout << "Please answer yes or no." << endl;
	}
	return false;
}

/*Costumer fills the board */
void customFill(Grid<char> &grd){
	string s = "";

	//We should ask a customer to enter valid string while he/her does not enter it.
	while(true){
		s = getLine("Enter valid string: "); s = toUpperCase(s);
		if(s.size() == grd.nCols * grd.nRows && valid(s)){
			break;
		} else{
			cout << "Please enter valid string. " << endl;
		}
	}
	labbing(s, grd); //Saving info in the grid and fill the board
}

/*Check if all characters are the letters*/
bool valid(string str){
	for(int i = 0; i < str.size(); i ++) {
		if(str[i] < 'A' || str[i] > 'Z') return false;
	}
	return true;
}

/*Saving info in the grid and fill the board*/
void labbing(string s, Grid<char> &grd){
	for(int r = 0; r < grd.nRows; r ++){
		for(int c = 0; c < grd.nCols; c ++){
			int index = r * B_SIZE + c;
			grd[r][c] = s[index];
			labelCube(r, c, grd[r][c]);
		}
	}
}

/* Computer fills the board */
void fillingCubes(Grid<char> &grd){
	Vector<string> stCubes;
	for(int i = 0; i < strSize; i ++){
		stCubes += STANDARD_CUBES[i]; //Adding words to the vector.
	}
	for(int i = 0; i < stCubes.size(); i ++){
		int x = randomInteger(i, stCubes.size()-1); //Putting them randomly in the vector.
		swap(i, x, stCubes);
	}

	labCubes(stCubes, grd);
}

void swap(int i, int x, Vector<string> &stCubes){
	string s = stCubes[x];
	stCubes[x] = stCubes[i];
	stCubes[i] = s;
}

/*Taking characters from the strings of the specific vector and filling the board and grid with them*/
void labCubes(Vector<string> stCubes, Grid<char> &grd){
	for(int r = 0; r < B_SIZE; r ++){
		for(int c = 0; c < B_SIZE; c ++){
			int index = r * B_SIZE + c; //Index for the vector.
			string str = stCubes[index];
			int rand = randomInteger(0, str.size() - 1);
			grd[r][c] = str[rand]; //Filling the grid.
			labelCube(r, c, grd[r][c]); //Filling the board.
		}
	}
}

/*Guessing part*/
void guessing(Grid<char> &grd, Lexicon lex){
	Set<string> gamer; Set<string> computer; //Sets for the player and computer to save information.
	playerPart(grd, lex, gamer); //Player starts the game.
	computerPart(grd, lex, gamer, computer); 
}

/*Player guessing the words*/
void playerPart(Grid<char> &grd, Lexicon lex, Set<string> &gamer){
	/*While loop that makes a player enter the words while he/her wants*/
	while(true){
		string s = getLine("Enter a word: ");
		if(s.length() == 0) break; //Stop the while loop when a player enter the empty string.
		if(!gamer.contains(toLowerCase(s))){ //If entered word is not in the already guessed word.
			if(s.size() >= MIN_SIZE){ //Word is not valid if its lengths is less than four.
				if(lex.contains(s)){
					if(find(toUpperCase(s), grd, lex) && valid(toUpperCase(s))){ //Checking if word satisfy the rules of the game.
						recordWordForPlayer(s, HUMAN);
						pause(300);
						unLight(grd); //"Unlighting" the cubes.
						gamer.add(toLowerCase(s));
					} else {
						cout << "You can not make that word!"<< endl;
					}
				} else {
					cout << "That is not a word!" << endl;
				}
			} else {
				cout << "I'm sorry, but we have our standards." << endl;
				cout << "That word doesn't meet the minimum word length." <<endl;
			}
		} else {
			cout << "You already entered this word!" << endl;
		}
	}
}

/*Going through the board and check all the words(whose sizes equals destionation word size)*/
bool find(string dest, Grid<char> grd, Lexicon lex){
	for(int r = 0; r < grd.nRows; r ++){
		for(int c = 0; c < grd.nCols; c ++){
			char ch = grd[r][c]; 
			grd[r][c] = '0'; 
			if(finding(dest, grd, lex, string("") + ch, r, c)) {
				highlightCube(r, c, true);
				return true;
			}
			grd[r][c] = ch; //Backtracking.
 		} 
	}
	return false;
}

/*Main part in finding the destination word*/
bool finding(string dest, Grid<char> &grd, Lexicon lex, string curr, int r, int c){
	if(curr == dest){  //Base case.
		return true;
	}else if(curr.size() < dest.size() && lex.containsPrefix(curr)){ 
		/*In the next lines we check the cubes aroung the current cube*/
		for(int i = r - 1; i <= r + 1; i ++){ 
			for(int j = c - 1; j <= c + 1; j ++){
				if(i >= 0 && i < grd.nRows){
					if(j >= 0 && j < grd.nCols){
						if(grd[i][j] != '0'){ //If we already checked this cube we do not check it again.
							char ch = grd[i][j];
							grd[i][j] = '0';
							if(finding(dest, grd, lex , string(curr) + ch, i , j)) {
								highlightCube(i, j, true);
								return true;
							}
							grd[i][j] = ch; //Backtracking.
						}
					}
				}
			}
		}
	}
	return false;
}

/*"Unlighting the cubes"*/
void unLight(Grid<char> &grd){
	for(int r = 0; r < grd.nRows; r ++){
		for(int c = 0; c < grd.nCols; c ++){
			highlightCube(r, c, false);
		}
	}
}

/*Computer guessing the words.*/
void computerPart(Grid<char> &grd, Lexicon lex, Set<string> gamer, Set<string> &computer){
	for(int r = 0; r < grd.nRows; r ++){
		for(int c = 0; c < grd.nCols; c ++){
			char ch = grd[r][c];
			grd[r][c] = '0';
			compFind(grd, lex, string("") + ch, r, c, gamer, computer);
			grd[r][c] = ch; //Backtracking. 
 		} 
	}
}

/*
* Tactic of guessing the words is almost the same as finding the 
* destination word, but now we do not have to check size of the current word.
*/
void compFind(Grid<char> &grd, Lexicon lex, string str, int r, int c, Set<string> gamer, Set<string> &computer){
	if(lex.contains(str) && str.size()>= 4 && !gamer.contains(toLowerCase(str))){
		if(!computer.contains(str)) { //If guessed word is not in the already guessed word of computer.
			computer.add(str);
			recordWordForPlayer(str, COMPUTER);
		}
	}
	if(lex.containsPrefix(str)){
		for(int i = r - 1; i <= r + 1; i ++){
			for(int j = c - 1; j <= c + 1; j ++){
				if(i >= 0 && i < grd.nRows){
					if(j >= 0 && j < grd.nCols){
						if(grd[i][j] != '0'){
							char ch = grd[i][j];
							grd[i][j] = '0';
							compFind(grd, lex ,str + ch, i , j ,gamer, computer);
							grd[i][j] = ch; //Backtracking.
						}
					}
				}
			}
		}
	}
}

/*Asking customers if they want to continue game */
bool GO_ON(){
	while(true){
		string s = getLine("Do you want to play again? ");
		if(toLowerCase(s) == "yes") return true;
		if(toLowerCase(s) == "no") return false;
		cout << "Please enter yes or no."<< endl;
	}
	return false;
}


/*
 * Function: welcome
 * Usage: welcome();
 * -----------------
 * Print out a cheery welcome message.
 */

void welcome() {
    cout << "Welcome!  You're about to play an intense game ";
    cout << "of mind-numbing Boggle.  The good news is that ";
    cout << "you might improve your vocabulary a bit.  The ";
    cout << "bad news is that you're probably going to lose ";
    cout << "miserably to this little dictionary-toting hunk ";
    cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

/*
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Print out the instructions for the user.
 */

void giveInstructions() {
    cout << endl;
    cout << "The boggle board is a grid onto which I ";
    cout << "I will randomly distribute cubes. These ";
    cout << "6-sided cubes have letters rather than ";
    cout << "numbers on the faces, creating a grid of ";
    cout << "letters on which you try to form words. ";
    cout << "You go first, entering all the words you can ";
    cout << "find that are formed by tracing adjoining ";
    cout << "letters. Two letters adjoin if they are next ";
    cout << "to each other horizontally, vertically, or ";
    cout << "diagonally. A letter can only be used once ";
    cout << "in each word. Words must be at least four ";
    cout << "letters long and can be counted only once. ";
    cout << "You score points based on word length: a ";
    cout << "4-letter word is worth 1 point, 5-letters ";
    cout << "earn 2 points, and so on. After your puny ";
    cout << "brain is exhausted, I, the supercomputer, ";
    cout << "will find all the remaining words and double ";
    cout << "or triple your paltry score." << endl << endl;
    cout << "Hit return when you're ready...";
    getLine();
}

// [TODO: Fill in the rest of the code]
