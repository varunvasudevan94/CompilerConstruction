/*
	Sanjay Reddy S -2013A7PS189P
	Varun Vasudevan-2013A7PS103P
	Batch No: 33
*/

#include "stack.h"
void insert_element(element **start,int id,int index){
	element *newnode=(element *)malloc(sizeof(element));
	newnode->next=NULL;
	newnode->id=id;
	newnode->index=index;
	if (*start==NULL){
		*start=newnode;
		return;
	}	
	newnode->next=*start;
	*start=newnode;

}

void delete_element(element **start){
	if(*start==NULL){
		printf("underflow\n");
		return;

	}
	element *temp=*start;
	*start=(*start)->next;
		


}

void init_stack(stack *S){
	(*S).start=NULL;
	

}

void push(stack *S,int id,int index){
	insert_element(&((*S).start),id,index);

}

void pop(stack *S){
	delete_element(&((*S).start));


}
int top(stack S){
	if (S.start==NULL)
		return -1;	//empty stack
	return (S.start)->id;

}
int top_index(stack S){
	if (S.start==NULL)
		return -1;
	return (S.start)->index;


}

void print_stack(stack S){
	element *start=S.start;

	while (start){
		printf("%d,%d   ",start->id,start->index);
		start=start->next;
	}
		printf("\n");
}

int empty(stack S){
	if (S.start==NULL)
		return 1;
	return 0;

}

/*
int main(){

stack s;
init_stack(&s);
int index=0;
push(&s,1,index++);
push(&s,3,index++);
push(&s,2,index++);
push(&s,4,index++);
print_stack(s);
pop(&s);
print_stack(s);
push(&s,5,index++);
print_stack(s);
pop(&s);
pop(&s);
pop(&s);
pop(&s);
pop(&s);
pop(&s);
print_stack(s);

	return 0;


}
*/
