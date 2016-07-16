#include "tree.h"
#include "parserDef.h"

#include <string.h>

void insert_symbol(node_s **start,node_t s,addon add,char scope[]);
int hash_key_symbol(char lex[]);
void insert_ht_symbol(symbol *ST,node_t s,addon add,char scope[]);
void print_symbol_line(node_s *start);
void print_symbol(symbol ST);
void init_ht_symbol(symbol *ST);
void insert_symbol_table(symbol_table *STable,node_t s,addon add,char scope[]);
void print_symbol_table(symbol_table STable);
void init_symbol_table(symbol_table *STable);
int getfieldtype(symbol_table STable,char scope[],char lex[],char fieldtype[]);
int typecheck(node_t *root,char scope[],symbol_table STable);
int search_symbol_table(symbol_table STable,char lex[],char scope[],char field[]);
int compare_args(node_t *ar1[],node_t *ar2[],char call_scope[],symbol_table STable,int io);
void search_get_add(symbol_table STable,char lex[],char scope[],node_t *input[],node_t *output[],int flag);
int search_symbol_table_line(symbol_table STable,char lex[],char scope[],char field[]);
void getfields(char lex[],symbol_table STable,node_t *st[]);
int check_record(char name[]);

