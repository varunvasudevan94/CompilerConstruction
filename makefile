all:
	gcc -g driver.c parser.c parser.h  stack.c stack.h tree.c tree.h parserDef.h lexer.c lexer.h lexerDef.h AST.h AST.c symbol_semantic.c  symbol_semantic.h codegen.c codegen.h -o toycompiler 
