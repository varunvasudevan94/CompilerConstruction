#include "parser.h"
#include "lexer.h"

void copy_node(node_t *root,node_t *root1);
void change_parent(node_t *root1,node_t *root);

void update_parent(node_t * root);
void prune(node_t *root);
	
	
void visit(node_t *root);
