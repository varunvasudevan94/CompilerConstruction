/*
	Sanjay Reddy S -2013A7PS189P
	Varun Vasudevan-2013A7PS103P
	Batch No: 33
*/

#include "lexerDef.h"


int get_token_index(int state,char lex[]);//Returns token_identity based on current state and lex[].Also includes lookup for keywords
void initialise();//Creates the table with initially all pointing to trap state
void insert_dfa(int initial_state,char symbol,int final_state);//Creates the transition in the table (used by construct_table)
void construct_table();//The table is populated here by following the transitions in the DFA
int decide_ch_acc(char ch);//Returns 1 if 'ch' is a number or a letter. Else -1
int unknownsymbol(char symbol);//returns 1 if its a legal character. Else 0 (Used in error analysis)
int getnextstate(int current_state,char symbol);//For given symbol on the current state it gives the final state
int getStream(FILE *fp,char buffer[],int size);//Interacts with the file stores size no. of characters in the buffer
int getNextToken(FILE *fp,char buffer[],char next_token[]);//Searches for tokens in buffer & returns them
void commentless(char filename[]);//for printing commentless code onto the console

