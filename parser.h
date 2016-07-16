/*
	Sanjay Reddy S -2013A7PS189P
	Varun Vasudevan-2013A7PS103P
	Batch No: 33
*/

#include "stack.h"
#include "tree.h"
#include "parserDef.h"
#include <string.h>


extern int size;
extern tokenInfo tok[N];
extern int len;
extern int flag;

extern int first[200][60];
extern int follow[200][60];
//extern int synch[200][60];
void insert(node **start,int id);


void print_node(node *start);//To print the production rule in a particular line
int create_rules(node *rule[]);//For creating the production rules

void create_first();//Creating the first sets

void create_follow();//For the follow sets
//void create_synch();
void print_arr(int arr[],int size);//For printing the array arr
void comb(int A[],int B[]);//Union operation used in parsing table creation
void first_comp(node *rule,int ans[]);//To compute the first sets used in parsing table

tokenInfo getNext();//Get the next Token from the token Stream

extern int parse[200][100];
void createParseTable(node *rule[],int count);

int terminal(int S);//To check if its a terminal or not
node_t *parseInputSourceCode(node *rule[],int count);
void init_map();//Used to link the token_ids with the actual names of the tokens
void printParseTree(node_t *root);//Print Parse Tree in the file
