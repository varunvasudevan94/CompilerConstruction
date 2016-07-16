/*
	Sanjay Reddy S -2013A7PS189P
	Varun Vasudevan-2013A7PS103P
	Batch No: 33
*/

#include <stdio.h>
#include <stdlib.h>
#define N 20
#define L 100

extern char record_list[20][100];
extern int record_count; 
extern int t_size[200];
extern int t_count;
extern FILE *printasm;
extern int off[100];
extern int  semerr;
extern char err[50][50];
extern int err_count;
extern int node_count;

typedef struct Childnode{
	struct node_t *child;
	struct Childnode *next;


}childnode;


typedef struct node_t{
	int id;
	char lex[200];
	char field[200];
	int index;
	int parent;	//here it is id not index
	int token;
	int parentid;
	int line;
	int type;
	int value;
	float dvalue;
	int record;
	int offset;	

	struct node_t *child[N];
	childnode *child_head;     //not neeeded
	int no_of_child;		//not need	
	 

}node_t;

typedef struct addon{
	node_t *input[N];   //input list if function
	node_t *output[N];	//output list if function	
	node_t *field[N];	//field list if function


}addon;

typedef struct node_s{
	
	node_t s;
	char scope[1000];    //gice the lexof the enclosing function
	addon add;
	struct node_s *next;



}node_s;

typedef struct symbol{
	node_s *start[L];
	
}symbol;

typedef struct{
	   
	symbol ST[100];
	

} symbol_table;


extern  symbol_table STable;


typedef struct queue{

	node_t item;
	struct queue *next; 


}queue;


typedef struct header{
	queue *front;
	queue *rear;


}header;
void change_symbol(symbol *ST,symbol_table *STable);
void change_symbol_table(symbol_table *STable);
void change_symbol_line(node_s **temp,symbol_table *STable);


void add_child(childnode **head,node_t *child);

node_t *create(int id,char lex[],int index,int token,int parentid,int line);

void dfs(node_t *root);

node_t *find(node_t *root,int parent);
int change(node_t **root,int parent,char lex[],int id,int line);


void insert_t(node_t **root,int parent,int id,char lex[],int index,int token,int parentid,int line);


int is_terminal(int S);
queue *create_q(node_t item);

void enqueue(header *h,node_t item);


void dequeue(header *h);

int is_empty_q(header q);
void initialise_q(header *h);
void bfs(node_t *root,node_t **AST);
void BFS(node_t *root,FILE *);
void search_print(node_t *root);

typedef struct queue_p{

	node_t *item;
	struct queue_p *next; 


}queue_p;


typedef struct header_p{
	queue_p *front;
	queue_p *rear;


}header_p;



queue_p *create_q_p(node_t *item);

void print_symbol_line_asm(node_s *start);
void print_symbol_asm(symbol ST);
void print_symbol_table_asm(symbol_table STable);
void search_rid(symbol_table *STable,char lex[],char scope[],node_t *start[]);
void search_icg(node_t *root,int id);
void enqueue_p(header_p *h,node_t *item);
void dequeue_p(header_p *h);
int is_empty_q_p(header_p q);
void initialise_q_p(header_p *h);
void traverse_scope(node_t *root,int id,char scope[],symbol_table *STable);
void find_scope(node_t *root,symbol_table *STable,int);
void init_symbol_table(symbol_table *STable);
void print_symbol_table(symbol_table STable);
void print_in(node_t *root[]);
void get_fields(node_t *start[],node_t *root);
