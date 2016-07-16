/*
	Sanjay Reddy S -2013A7PS189P
	Varun Vasudevan-2013A7PS103P
	Batch No: 33
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct E{
	int id;
	int index;
	struct E *next;
	
}element;


typedef struct{
	element *start;
	//add top if needed
}stack;



void insert_element(element **start,int id,int index);
void delete_element(element **start);
void init_stack(stack *S);
void push(stack *S,int id,int index);
void pop(stack *S);
void print_stack(stack S);
int top(stack S);
int empty(stack S);
int top_index(stack S);

