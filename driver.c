/*
	Sanjay Reddy S -2013A7PS189P
	Varun Vasudevan-2013A7PS103P
	Batch No: 33
*/

#include "AST.h"
node_t * stage1(char *argv[]);



void main_of_asm(node_t *AST){
	char ch='%';
	fprintf(printasm,"; nasm -f elf64 -l main1.lst  main1.asm\n");
	fprintf(printasm,"; gcc -o main1 main1.o\n");
	fprintf(printasm,"; ./main1\n\n\n");

	fprintf(printasm,"%c",ch);
	fprintf(printasm,"include 'function.asm'\n\n");
	
	fprintf(printasm,"section .data\n");
	fprintf(printasm,"msg: db \"For debugging: \",10,0\n");
	fprintf(printasm,"prompt: db \"Please enter the value: \",10,0\n");
	fprintf(printasm,"fmt_in:db \"%c",ch);
	fprintf(printasm,"d\",0\n");
	fprintf(printasm,"fmt_out: db \"output=%c",ch);
	fprintf(printasm,"d\",10,0\n");
	//fprintf(printasm,"msg1: db \"Enter the value of b2: \",10,0\n");
	//fprintf(printasm,"msg2: db \"Enter the value of d2: \",10,0\n\n");
	fprintf(printasm,"section .text\n");
	fprintf(printasm,"global main\n");
	fprintf(printasm,"extern printf,scanf\n\n");
	fprintf(printasm,"\nmain:\n\n");
			
	if (AST->child[1] && AST->child[1]->id==mainFunction)
		search_icg(AST->child[1],TK_ASSIGNOP);
	else if (AST->child[0] && AST->child[0]->id==mainFunction)
		search_icg(AST->child[0],TK_ASSIGNOP);	
	
	fprintf(printasm,"\nret\n\n");
	

}

void bss_of_asm(){

	fprintf(printasm,"\nsection .bss\n\n");
	int i;	
	for ( i=1;i<=t_count;i++)
		fprintf(printasm,"t%d resb %d\n",i,t_size[i]);	
	
	print_symbol_table_asm(STable);	

}



int main(int argc,char *argv[]){

	if (argc==1){
		printf("input and output file missing\n");
		return 0;
	}
	
	if (argc==2){
		printf(".asm file missing\n");
		return 0;
	}
	
	node_t * root=stage1(argv);


	return 0;
}


node_t * stage1(char *argv[]){

	init_map();	
	initialise();
	construct_table();
	int i;
	for (i=0;i<500;i++){
		tok[i].token=0;
		tok[i].line=0;
		strcpy(tok[i].lex,"");

	}
	char buffer[100]="";
	char next_token[100]="";
	
	

	FILE *fp=fopen(argv[1],"r+");
	if (!fp){
		printf("file not found!!!!");
		return 0;

	}


	getStream(fp,buffer,BUFFER_SIZE);
	int n;
	while (1)
	{	
		n=getNextToken(fp,buffer,next_token);
	
		//printf("buffer:%s\n",buffer);
		if (n==-1)
		{
			if (buffer_empty){
				
				//printf("report success:\n");
				break;
			}
		else{
			printf("error at line %d:%s\n",line,next_token);
			error=1;
			char temp[200];
			sprintf(temp,"error at line %d:%s\n",line,next_token);			
			strcpy(err[err_count++],temp);
							
		}
	

	}
	
	int tk=get_token_index(n,next_token);
	if (strlen(next_token)>20 && tk==TK_ID){
		printf("error  at line %d:too long field:%s\n",line,next_token);
		char temp[200];
		sprintf(temp,"error  at line %d:too long field:%s\n",line,next_token);			
		strcpy(err[err_count++],temp);
	}

	if (tk!=NO_TK){
		//printf("%s\n",m[tk]);
		tok[len].token=tk;
		strcpy(tok[len].lex,next_token);
		tok[len].line=line;
		len++;
		
		//printf("token=%s tokenid=%d line=%d\n",next_token,tk,line);

	}	
	}


	if (tok[len-1].token!=TK_END){
		tok[len++].token=TK_END;
	strcpy(tok[len-1].lex,"end");
	tok[len-1].line=line;

	}	
	tok[len++].token=dollar;
	strcpy(tok[len-1].lex,"dollar");
	tok[len-1].line=-1;
	
	/*if (error){
	printf("lex anal false\n");

	}

	else
		printf("lex anal prevails\n");*/
	fclose(fp);
	
	int q;/*
	for(q=0;q<len-1;q++)
	{
		if(tok[q].token!=TK_COMMENT&&tok[q].token!=TK_OP && tok[q].token!=TK_CL && tok[q].token==tok[q+1].token)
		{	printf("error at line %d:Unrecognized Pattern!! %s\n",tok[q].line,tok[q+1].lex);
			error=1;
		}
		if((tok[q].token==TK_NUM && tok[q+1].token==TK_DOT)||(tok[q].token==TK_LT && strcmp(tok[q].lex,"<--")==0)||(tok[q].token==TK_RNUM && tok[q+1].token==TK_NUM))
		{printf("error at line %d:Unrecognized Pattern!! %s\n",tok[q].line,tok[q+1].lex);
		error=1;			
		}
	}
	*/
	
	stack s1;
	init_stack(&s1);
	int f=0;
	for (q=0;q<len-1;q++){
		
		if ((tok[q].token==TK_FUNID && tok[q+1].token==TK_INPUT)||(tok[q].token==TK_MAIN)){
			push(&s1,q,tok[q].line);
			//printf("**%s %d\n",tok[q].lex,tok[q].line);
			

		}
		else if (tok[q].token==TK_END){

			if (empty(s1)){
				error=1;
				f=1;
				break;
			}
			pop(&s1);

		}


	}
	if (!empty(s1)){
		//pop(&s1);
		f=1;
		error=1;
	}
	if (f){

		while(!empty(s1)){
		
		printf("error at line %d: missing end of function %s\n",top_index(s1),tok[top(s1)].lex);
		char temp[200];
		sprintf(temp,"error at line %d: missing end of function %s\n",top_index(s1),tok[top(s1)].lex);			
		strcpy(err[err_count++],temp);
		pop(&s1);

		}
	}

	
	init_map();
	node *rule[100];
	
	for (i=0;i<100;i++){
		rule[i]=NULL;
	}

	int count=create_rules(rule);
	create_first();
	create_follow();
	int choice;
	int lexerror=error;
	int parseerror=0;
	int semerror=0;
	createParseTable(rule,count);
	node_t *root=NULL;
	if (!lexerror)	
		root=parseInputSourceCode(rule,count);
	if (root==NULL && !lexerror) 
		parseerror=1;
		//printf("\n");
	//node_t *root1;
	visit(root);
	node_t *AST=NULL,*AST1=NULL;
	if (!parseerror){	
			
			bfs(root,&AST);
			bfs(AST,&AST1);
						
			
			
			
						
			init_symbol_table(&STable);	
			find_scope(AST,&STable,0);
			find_scope(AST,&STable,1);
			find_scope(AST,&STable,2);
			semerror=semerr;
	}
	else
		semerror=1;

	printf("Both Lexical and Syntactical Analysis modules are done...\n");
	printf("Some Rudimentary Error handling attempted...\n");
	printf("Semantic and Typechecking Done...\n");

	do{
	printf("\n***********************************************************************************************************\n");
	printf("1 :  For printing the token list (on the console) generated by the lexer\n"); 
        printf("2 :  For parsing to verify the syntactic correctness of the input source code\n");           
        printf("3 :  For printing AST\n"); 
        printf("4 :  For compression percentage\n");
	printf("5 :  For printing symboltable\n");
	printf("6 :  For semantic and typechecking analysis\n");
	printf("7 :  For assembly code\n");
	printf("8:   For exiting");
	printf("\n***********************************************************************************************************\n");
	
	printf("enter your choice\n");
		
	scanf("%d",&choice);
			
	switch(choice){
		case 1:{
			int i;
			for (i=0;i<len-1;i++){
				printf("%-30s %-30s %-30d\n",m[tok[i].token],tok[i].lex,tok[i].line);

			}	
			break;
			}
		case 2:{

			if (error){
				printf("Source code lexically incorrect\n");
				break;
			}
			
			if (error){
				printf("Source code lexically incorrect\n");
				lexerror=error;	
				break;
				
			}	
			if (flag*(!error)){
			printf("Input source code is syntactically correct!!\n");
			printf("%-50s\n","SYNTAX TREE");	
			printParseTree(root);
			}
			else
			printf("Syntactically incorrect\n");
			break;

			}
		case 3:{
			printf("%-50s\n","AST");	
			printParseTree(AST1);
			break;
			}
		case 4:{
				
			//dfs(root,fp1);
			if (!semerror){
			node_count=0;
			search_print(AST1);
			int ast_count=node_count;
			node_count=0;
			search_print(root);
			int root_count=node_count;
			double per=(root_count-ast_count+0.00)/root_count;
			per*=100;
			printf("compression percentage...(No. of nodes) %d  %d  %f%c\n",ast_count,node_count,per,'%');
			int sz=sizeof(node_t);
			printf("memory\nAST        :%f kb\nSYNTAX TREE:%f kb",sz*ast_count/1000.0,sz*node_count/1000.0);
			}
			else{
			printf("There seems to be some errors in your code. Please correct them first");		
			}
			//printf("Parse tree printed in %s\n",argv[2]);
			//char field[200];
			
			//printf("%s\n\n",m[search_symbol_table(STable,"d3","_main")]);
			//printf("%s", m[search_symbol_table(STable,"b5c6","_main")]);
			//printf("%s", m[search_symbol_table(STable,"b5c6","_main")]);
			//printf("%s", m[search_symbol_table(STable,"b5c6","_main")]);
			//addon add;
			//add.input[0]=NULL;			
			//search_get_add(STable,"_readMarks","global");
			//print_list(STable,"_readMarks","global");	
			break;
			}
		case 5:{ if (!parseerror && !lexerror){
			printf("%-50s\n","SYMBOL TABLE");		
			printf("%-25s %-25s %-10s %-10s\n","LEX","TYPE","SCOPE","OFFSET");
			printf("***********************************************************************************************************\n");	
			find_scope(AST,&STable,3);
			}
			else{
				printf("please first correct the errors!!!\n");
				
			}
			 break;}
		case 6:{ printf("semantics and typechecking...\n");
			 if (semerror){
				printf("semantically incorrect check the below errors\n");
				int i;
				for (i=0;i<err_count;i++){
					printf("%s",err[i]);
				}

			  }
			 else{
				printf("semantically correct\n");

			}
			

			break;}	
		case 7:{ 

			if (!semerror){

			printasm=fopen(argv[2],"w+");
			
			main_of_asm(AST);
			bss_of_asm();
			fclose(printasm);

			printf("printed .asm file in %s\n",argv[2]);
			printf("\nPlease follow the instruction to run the .asm \n\n");
			printf("$ nasm -f elf64 -l main1.lst  main1.asm\n");
			printf("$ gcc -o main1 main1.o\n");
			printf("$ ./main1\n\n\n");	
			}
			else{
				printf("please check the errors\n");
			}	
			break;}	
		case 8:{ printf("exiting...\n");break;}
		default:printf("you have entered an incorrect option\n");
					
		
	}
	}while (choice!=8);

	return root;
}

