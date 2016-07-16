#include "symbol_semantic.h"
#include <ctype.h>

extern int l_count;
extern int record_flag;
int is_operator(int id);


int parseword(char n1[]);
void print_oper(char operator[],int l1,int l2,int rec,int r1,int r2);


void icg_helper(node_t *root);
void search_icg_module(node_t *root,int id);

