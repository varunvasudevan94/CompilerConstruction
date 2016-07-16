/*
	Sanjay Reddy S -2013A7PS189P
	Varun Vasudevan-2013A7PS103P
	Batch No: 33
*/

#include "stack.h"
#include "tree.h"
#include "parserDef.h"
#include <string.h>

tokenInfo tok[1000];
int size=0;
//int tok[500]={0};

int len=0;
int first[200][60]={0};
int follow[200][60]={0};
void insert(node **start,int id){
	node *newnode=(node *)malloc(sizeof(node));
	newnode->id=id;
	newnode->next=NULL;
	if (*start==NULL){
		*start=newnode;
		return;
	}

	node *temp=*start;
	while (temp->next){
		temp=temp->next;

	}	
	temp->next=newnode;

}


void print_node(node *start){
	while (start){
		printf("%d->",start->id);
		start=start->next;
	}
	printf("\n");	

}


int create_rules(node *rule[]){
	
	int i;
	for (i=0;i<100;i++){
		rule[i]=NULL;
	}
	int count=1;

	insert(&rule[count],program);
	insert(&rule[count],otherFunctions);
	insert(&rule[count],mainFunction);
	count++;

	insert(&rule[count],mainFunction);
	insert(&rule[count],TK_MAIN);
	insert(&rule[count],stmts);
	insert(&rule[count],TK_END);
	count++;

	insert(&rule[count],otherFunctions);
	insert(&rule[count],function);
	insert(&rule[count],otherFunctions);
	count++;

	insert(&rule[count],otherFunctions);
	insert(&rule[count],eps);
	count++;

	insert(&rule[count],function);
	insert(&rule[count],TK_FUNID);
	insert(&rule[count],input_par);
	insert(&rule[count],output_par);
	insert(&rule[count],TK_SEM);
	insert(&rule[count],stmts);
	insert(&rule[count],TK_END);
	count++;

	insert(&rule[count],input_par);
	insert(&rule[count],TK_INPUT);
	insert(&rule[count],TK_PARAMETER);
	insert(&rule[count],TK_LIST);
	insert(&rule[count],TK_SQL);
	insert(&rule[count],parameter_list);
	insert(&rule[count],TK_SQR);
	count++;

	insert(&rule[count],output_par);
	insert(&rule[count],TK_OUTPUT);
	insert(&rule[count],TK_PARAMETER);
	insert(&rule[count],TK_LIST);
	insert(&rule[count],TK_SQL);
	insert(&rule[count],parameter_list);
	insert(&rule[count],TK_SQR);
	count++;

	insert(&rule[count],output_par);
	insert(&rule[count],eps);
	count++;

	insert(&rule[count],parameter_list);
	insert(&rule[count],dataType);
	insert(&rule[count],TK_ID);
	insert(&rule[count],remaining_list);
	count++;

	insert(&rule[count],dataType);
	insert(&rule[count],primitiveDatatype);
	count++;

	insert(&rule[count],dataType);
	insert(&rule[count],constructedDatatype);
	count++;	

	insert(&rule[count],primitiveDatatype);
	insert(&rule[count],TK_INT);
	count++;

	insert(&rule[count],primitiveDatatype);
	insert(&rule[count],TK_REAL);
	count++;

	insert(&rule[count],constructedDatatype);
	insert(&rule[count],TK_RECORD);
	insert(&rule[count],TK_RECORDID);
	count++;

	insert(&rule[count],remaining_list);
	insert(&rule[count],TK_COMMA);
	insert(&rule[count],parameter_list);
	count++;

	insert(&rule[count],remaining_list);
	insert(&rule[count],eps);
	count++;

	insert(&rule[count],stmts);
	insert(&rule[count],typeDefinitions);
	insert(&rule[count],declarations);
	insert(&rule[count],otherStmts);
	insert(&rule[count],returnStmt);
	count++;	

	insert(&rule[count],typeDefinitions);
	insert(&rule[count],typeDefinition);
	insert(&rule[count],typeDefinitions);
	count++;

	insert(&rule[count],typeDefinitions);
	insert(&rule[count],eps);
	count++;

	insert(&rule[count],typeDefinition);
	insert(&rule[count],TK_RECORD);
	insert(&rule[count],TK_RECORDID);
	insert(&rule[count],fieldDefinitions);
	insert(&rule[count],TK_ENDRECORD);
	insert(&rule[count],TK_SEM);
	count++;

	insert(&rule[count],fieldDefinitions);
	insert(&rule[count],fieldDefinition);   
	insert(&rule[count],fieldDefinition);
	insert(&rule[count],moreFields);
	count++;

	insert(&rule[count],fieldDefinition);
	insert(&rule[count],TK_TYPE);
	insert(&rule[count],primitiveDatatype);
	insert(&rule[count],TK_COLON);
	insert(&rule[count],TK_FIELDID);
	insert(&rule[count],TK_SEM);
	count++;

	insert(&rule[count],moreFields);
	insert(&rule[count],fieldDefinition);
	insert(&rule[count],moreFields);
	count++;

	insert(&rule[count],moreFields);
	insert(&rule[count],eps);
	count++;

	insert(&rule[count],declarations);
	insert(&rule[count],declaration);
	insert(&rule[count],declarations);
	count++;

	insert(&rule[count],declarations);
	insert(&rule[count],eps);
	count++;

	insert(&rule[count],declaration);
	insert(&rule[count],TK_TYPE);
	insert(&rule[count],dataType);
	insert(&rule[count],TK_COLON);
	insert(&rule[count],TK_ID);
	insert(&rule[count],global_or_not);
	insert(&rule[count],TK_SEM);
	count++;

	insert(&rule[count],global_or_not);
	insert(&rule[count],TK_COLON);
	insert(&rule[count],TK_GLOBAL);
	count++;

	insert(&rule[count],global_or_not);
	insert(&rule[count],eps);
	count++;
	
	insert(&rule[count],otherStmts);
	insert(&rule[count],stmt);
	insert(&rule[count],otherStmts);
	count++;

	insert(&rule[count],otherStmts);
	insert(&rule[count],eps);
	count++;

	insert(&rule[count],stmt);
	insert(&rule[count],assignmentStmt);
	count++;

	insert(&rule[count],stmt);
	insert(&rule[count],iterativeStmt);
	count++;

	insert(&rule[count],stmt);
	insert(&rule[count],conditionalStmt);
	count++;

	insert(&rule[count],stmt);
	insert(&rule[count],ioStmt);
	count++;
		
	insert(&rule[count],stmt);
	insert(&rule[count],funCallStmt);
	count++;

	insert(&rule[count],assignmentStmt);
	insert(&rule[count],singleOrRecId);
	insert(&rule[count],TK_ASSIGNOP);
	insert(&rule[count],arithmeticExpression);
	insert(&rule[count],TK_SEM);
	count++;

	insert(&rule[count],singleOrRecId);
	insert(&rule[count],TK_ID);
	insert(&rule[count],new_24);
	count++;

	insert(&rule[count],new_24);
	insert(&rule[count],TK_DOT);
	insert(&rule[count],TK_FIELDID);
	count++;

	insert(&rule[count],new_24);
	insert(&rule[count],eps);
	count++;

	insert(&rule[count],funCallStmt);
	insert(&rule[count],outputParameters);
	insert(&rule[count],TK_CALL);
	insert(&rule[count],TK_FUNID);
	insert(&rule[count],TK_WITH);
	insert(&rule[count],TK_PARAMETERS);
	insert(&rule[count],inputParameters);
	insert(&rule[count],TK_SEM);
	count++;

	insert(&rule[count],outputParameters);
	insert(&rule[count],TK_SQL);
	insert(&rule[count],idList);
	insert(&rule[count],TK_SQR);
	insert(&rule[count],TK_ASSIGNOP);
	count++;

	insert(&rule[count],outputParameters);
	insert(&rule[count],eps);
	count++;

	insert(&rule[count],inputParameters);
	insert(&rule[count],TK_SQL);
	insert(&rule[count],idList);
	insert(&rule[count],TK_SQR);
	count++;

	insert(&rule[count],iterativeStmt);
	insert(&rule[count],TK_WHILE);
	insert(&rule[count],TK_OP);
	insert(&rule[count],booleanExpression);
	insert(&rule[count],TK_CL);
	insert(&rule[count],stmt);
	insert(&rule[count],otherStmts);
	insert(&rule[count],TK_ENDWHILE);
	count++;

	insert(&rule[count],conditionalStmt);
	insert(&rule[count],TK_IF);
	insert(&rule[count],TK_OP);
	insert(&rule[count],booleanExpression);
	insert(&rule[count],TK_CL);
	insert(&rule[count],TK_THEN);
	insert(&rule[count],stmt);
	insert(&rule[count],otherStmts);
	insert(&rule[count],elsePart);
	count++;

	insert(&rule[count],elsePart);
	insert(&rule[count],TK_ELSE);
	insert(&rule[count],stmt);
	insert(&rule[count],otherStmts);
	insert(&rule[count],TK_ENDIF);
	count++;

	insert(&rule[count],elsePart);
	insert(&rule[count],TK_ENDIF);
	count++;

	insert(&rule[count],ioStmt);
	insert(&rule[count],TK_READ);
	insert(&rule[count],TK_OP);
	insert(&rule[count],singleOrRecId);
	insert(&rule[count],TK_CL);
	insert(&rule[count],TK_SEM);
	count++;

	insert(&rule[count],ioStmt);
	insert(&rule[count],TK_WRITE);
	insert(&rule[count],TK_OP);
	insert(&rule[count],allVar);
	insert(&rule[count],TK_CL);
	insert(&rule[count],TK_SEM);
	count++;

	insert(&rule[count],allVar);
	insert(&rule[count],TK_ID);
	insert(&rule[count],new_32);
	count++;
	insert(&rule[count],new_32);
	insert(&rule[count],TK_DOT);
	insert(&rule[count],TK_FIELDID);
	count++;

	insert(&rule[count],new_32);
	insert(&rule[count],eps);
	count++;
	insert(&rule[count],allVar);
	insert(&rule[count],TK_NUM);
	count++;
	
	insert(&rule[count],allVar);
	insert(&rule[count],TK_RNUM);
	count++;

	insert(&rule[count],arithmeticExpression);
	insert(&rule[count],term);
	insert(&rule[count],expPrime);
	count++;	

	insert(&rule[count],expPrime);
	insert(&rule[count],lowPrecedenceOperators);
	insert(&rule[count],term);
	insert(&rule[count],expPrime);
	count++;

	insert(&rule[count],expPrime);
	insert(&rule[count],eps);
	count++;

	insert(&rule[count],term);
	insert(&rule[count],factor);
	insert(&rule[count],termPrime);
	count++;

	insert(&rule[count],termPrime);
	insert(&rule[count],highPrecedenceOperators);
	insert(&rule[count],factor);
	insert(&rule[count],termPrime);
	count++;

	insert(&rule[count],termPrime);
	insert(&rule[count],eps);
	count++;

	insert(&rule[count],factor);
	insert(&rule[count],TK_OP);
	insert(&rule[count],arithmeticExpression);
	insert(&rule[count],TK_CL);
	count++;

	insert(&rule[count],factor);
	insert(&rule[count],all);
	count++;
	
	insert(&rule[count],highPrecedenceOperators);
	insert(&rule[count],TK_MUL);
	count++;

	insert(&rule[count],highPrecedenceOperators);
	insert(&rule[count],TK_DIV);
	count++;

	insert(&rule[count],lowPrecedenceOperators);
	insert(&rule[count],TK_PLUS);
	count++;

	insert(&rule[count],lowPrecedenceOperators);
	insert(&rule[count],TK_MINUS);
	count++;

	insert(&rule[count],all);
	insert(&rule[count],TK_ID);
	insert(&rule[count],new_34);
	count++;

	insert(&rule[count],all);
	insert(&rule[count],TK_NUM);
	count++;

	insert(&rule[count],all);
	insert(&rule[count],TK_RNUM);
	count++;

	insert(&rule[count],new_34);
	insert(&rule[count],TK_DOT);
	insert(&rule[count],TK_FIELDID);
	count++;

	insert(&rule[count],new_34);
	insert(&rule[count],eps);
	count++;

	insert(&rule[count],booleanExpression);
	insert(&rule[count],TK_OP);
	insert(&rule[count],booleanExpression);
	insert(&rule[count],TK_CL);
	insert(&rule[count],logicalOp);
	insert(&rule[count],TK_OP);
	insert(&rule[count],booleanExpression);
	insert(&rule[count],TK_CL);
	count++;

	insert(&rule[count],booleanExpression);
	insert(&rule[count],var);
	insert(&rule[count],relationalOp);
	insert(&rule[count],var);
	count++;

	insert(&rule[count],booleanExpression);
	insert(&rule[count],TK_NOT);
	insert(&rule[count],TK_OP);
	insert(&rule[count],booleanExpression);
	insert(&rule[count],TK_CL);
	count++;

	insert(&rule[count],var);
	insert(&rule[count],TK_ID);
	count++;

	insert(&rule[count],var);
	insert(&rule[count],TK_NUM);
	count++;

	insert(&rule[count],var);
	insert(&rule[count],TK_RNUM);
	count++;

	insert(&rule[count],logicalOp);
	insert(&rule[count],TK_AND);
	count++;

	insert(&rule[count],logicalOp);
	insert(&rule[count],TK_OR);
	count++;

	insert(&rule[count],relationalOp);
	insert(&rule[count],TK_LT);
	count++;

	insert(&rule[count],relationalOp);
	insert(&rule[count],TK_LE);
	count++;

	insert(&rule[count],relationalOp);
	insert(&rule[count],TK_EQ);
	count++;

	insert(&rule[count],relationalOp);
	insert(&rule[count],TK_GT);
	count++;

	insert(&rule[count],relationalOp);
	insert(&rule[count],TK_GE);
	count++;

	insert(&rule[count],relationalOp);
	insert(&rule[count],TK_NE);
	count++;
	
	insert(&rule[count],returnStmt);
	insert(&rule[count],TK_RETURN);
	insert(&rule[count],optionalReturn);
	insert(&rule[count],TK_SEM);
	count++;

	insert(&rule[count],optionalReturn);
	insert(&rule[count],TK_SQL);
	insert(&rule[count],idList);
	insert(&rule[count],TK_SQR);
	count++;

	insert(&rule[count],optionalReturn);
	insert(&rule[count],eps);
	count++;

	insert(&rule[count],idList);
	insert(&rule[count],TK_ID);
	insert(&rule[count],more_ids);
	count++;

	insert(&rule[count],more_ids);
	insert(&rule[count],TK_COMMA);
	insert(&rule[count],idList);
	count++;

	insert(&rule[count],more_ids);
	insert(&rule[count],eps);
	count++;

	insert(&rule[count],11);
	insert(&rule[count],4);
	count++;

	return count;
}

void create_first(){
	int i;
	for (i=0;i<53;i++)
		first[i][i]=1;
	
	first[program][TK_MAIN]=1;
	first[program][TK_FUNID]=1;

	first[otherFunctions][eps]=1;
	first[otherFunctions][TK_FUNID]=1;

	first[mainFunction][TK_MAIN]=1;
	
	first[function][TK_FUNID]=1;

	first[input_par][TK_INPUT]=1;

	first[output_par][TK_OUTPUT]=1;
	first[output_par][eps]=1;
	
	
	first[parameter_list][TK_INT]=1;
	first[parameter_list][TK_RECORD]=1;
	first[parameter_list][TK_REAL]=1;
	
	first[dataType][TK_INT]=1;	
	first[dataType][TK_REAL]=1;
	first[dataType][TK_RECORD]=1;

	first[primitiveDatatype][TK_INT]=1;
	first[primitiveDatatype][TK_REAL]=1;

	first[constructedDatatype][TK_RECORD]=1;
	
	first[remaining_list][TK_COMMA]=1;
	first[remaining_list][eps]=1;
	
	first[typeDefinitions][TK_RECORD]=1;
	first[typeDefinitions][eps]=1;	


	first[declarations][TK_TYPE]=1;
	first[declarations][eps]=1;

	first[otherStmts][TK_ID]=1;
	first[otherStmts][TK_RECORDID]=1;
	first[otherStmts][TK_WHILE]=1;
	first[otherStmts][TK_IF]=1;
	first[otherStmts][TK_READ]=1;
	first[otherStmts][TK_WRITE]=1;
	first[otherStmts][TK_SQL]=1;
	first[otherStmts][TK_CALL]=1;
	first[otherStmts][eps]=1;

	first[returnStmt][TK_RETURN]=1;
	
	first[stmts][TK_RECORD]=1;
	first[stmts][TK_TYPE]=1;
	first[stmts][TK_ID]=1;
	first[stmts][TK_RECORDID]=1;
	first[stmts][TK_WHILE]=1;
	first[stmts][TK_IF]=1;
	first[stmts][TK_READ]=1;
	first[stmts][TK_WRITE]=1;
	first[stmts][TK_SQL]=1;
	first[stmts][TK_CALL]=1;
	first[stmts][TK_RETURN]=1;
	
	first[typeDefinitions][TK_RECORD]=1;	
	first[typeDefinitions][eps]=1;

	first[declaration][TK_TYPE]=1;

	first[typeDefinition][TK_RECORD]=1;
	
	first[fieldDefinitions][TK_TYPE]=1;
	first[fieldDefinitions][eps]=1;

	first[fieldDefinition][TK_TYPE]=1;
	
	first[moreFields][TK_TYPE]=1;
	first[moreFields][eps]=1;

	first[global_or_not][TK_COLON]=1;
	first[global_or_not][eps]=1;
	
	first[stmt][TK_ID]=1;
	first[stmt][TK_RECORDID]=1;
	first[stmt][TK_WHILE]=1;
	first[stmt][TK_IF]=1;
	first[stmt][TK_READ]=1;
	first[stmt][TK_WRITE]=1;
	first[stmt][TK_SQL]=1;
	first[stmt][TK_CALL]=1;
	
	first[assignmentStmt][TK_ID]=1;
	first[assignmentStmt][TK_RECORDID]=1;

	first[iterativeStmt][TK_WHILE]=1;

	first[conditionalStmt][TK_IF]=1;

	first[ioStmt][TK_READ]=1;
	first[ioStmt][TK_WRITE]=1;

	first[funCallStmt][TK_SQL]=1;
	first[funCallStmt][TK_CALL]=1;
	
	first[singleOrRecId][TK_ID]=1;

	first[new_24][TK_COLON]=1;
	first[new_24][eps]=1;
	
	first[funCallStmt][TK_SQL]=1;
	first[funCallStmt][TK_CALL]=1;

	first[outputParameters][TK_SQL]=1;
	first[outputParameters][eps]=1;
	
	first[inputParameters][TK_SQL]=1;

	first[elsePart][TK_ELSE]=1;
	first[elsePart][TK_ENDIF]=1;
	
	first[var][TK_NUM]=1;
	first[var][TK_RNUM]=1;
	first[var][TK_ID]=1;

	first[allVar][TK_NUM]=1;
	first[allVar][TK_RNUM]=1;
	first[allVar][TK_ID]=1;

	first[new_32][TK_DOT]=1;
	first[new_32][eps]=1;

	first[arithmeticExpression][TK_ID]=1;
	first[arithmeticExpression][TK_NUM]=1;
	first[arithmeticExpression][TK_RNUM]=1;
	first[arithmeticExpression][TK_OP]=1;
	
	first[term][TK_ID]=1;
	first[term][TK_NUM]=1;
	first[term][TK_RNUM]=1;
	first[term][TK_OP]=1;
	
	first[factor][TK_ID]=1;
	first[factor][TK_NUM]=1;
	first[factor][TK_RNUM]=1;
	first[factor][TK_OP]=1;
	
	first[lowPrecedenceOperators][TK_PLUS]=1;
	first[lowPrecedenceOperators][TK_MINUS]=1;
	
	first[expPrime][TK_PLUS]=1;
	first[expPrime][TK_MINUS]=1;
	first[expPrime][eps]=1;
	
	
	first[highPrecedenceOperators][TK_MUL]=1;
	first[highPrecedenceOperators][TK_DIV]=1;
	
	first[termPrime][TK_MUL]=1;
	first[termPrime][TK_DIV]=1;
	first[termPrime][eps]=1;
	
	first[all][TK_NUM]=1;
	first[all][TK_RNUM]=1;
	first[all][TK_ID]=1;
	
	first[new_34][eps]=1;
	first[new_34][TK_DOT]=1;
	
	first[booleanExpression][TK_OP]=1;
	first[booleanExpression][TK_NOT]=1;
	first[booleanExpression][TK_ID]=1;
	first[booleanExpression][TK_NUM]=1;
	first[booleanExpression][TK_RNUM]=1;
	
	first[logicalOp][TK_AND]=1;
	first[logicalOp][TK_OR]=1;
	
	first[relationalOp][TK_LT]=1;
	first[relationalOp][TK_LE]=1;
	first[relationalOp][TK_EQ]=1;
	first[relationalOp][TK_GT]=1;
	first[relationalOp][TK_GE]=1;
	first[relationalOp][TK_NE]=1;
	
	first[optionalReturn][eps]=1;
	first[optionalReturn][TK_SQL]=1;
	
	first[idList][TK_ID]=1;
	
	first[more_ids][TK_COMMA]=1;
	first[more_ids][eps]=1;
		
} 

void create_follow(){
	follow[program][dollar]=1;

	follow[mainFunction][dollar]=1;

	follow[typeDefinitions][TK_TYPE]=1;
	follow[typeDefinitions][TK_ID]=1;
	follow[typeDefinitions][TK_RECORDID]=1;
	follow[typeDefinitions][TK_WHILE]=1;
	follow[typeDefinitions][TK_IF]=1;
	follow[typeDefinitions][TK_READ]=1;
	follow[typeDefinitions][TK_WRITE]=1;
	follow[typeDefinitions][TK_SQL]=1;
	follow[typeDefinitions][TK_CALL]=1;
	follow[typeDefinitions][TK_RETURN]=1;

	follow[declarations][TK_ID]=1;
	follow[declarations][TK_RECORDID]=1;
	follow[declarations][TK_WHILE]=1;
	follow[declarations][TK_IF]=1;
	follow[declarations][TK_READ]=1;
	follow[declarations][TK_WRITE]=1;
	follow[declarations][TK_SQL]=1;
	follow[declarations][TK_CALL]=1;
	follow[declarations][TK_RETURN]=1;

	follow[otherStmts][TK_RETURN]=1;
	follow[otherStmts][TK_ENDWHILE]=1;	
	follow[otherStmts][TK_ELSE]=1;	
	follow[otherStmts][TK_ENDIF]=1;	
	
	follow[otherFunctions][TK_MAIN]=1;
	
	follow[output_par][TK_SEM]=1;
	
	follow[remaining_list][TK_SQR]=1;
	
	follow[moreFields][TK_ENDRECORD]=1;
	
	follow[global_or_not][TK_SEM]=1;
	
	follow[otherStmts][TK_RETURN]=1;
	
	follow[new_24][TK_ASSIGNOP]=1;
	follow[new_24][TK_CL]=1;		

	follow[outputParameters][TK_CALL]=1;
	follow[singleOrRecId][TK_CL]=1;		
	follow[new_32][TK_CL]=1;
	
	follow[expPrime][TK_SEM]=1;
	follow[expPrime][TK_CL]=1;             
	follow[termPrime][TK_PLUS]=1;
	follow[termPrime][TK_MINUS]=1;
	follow[termPrime][TK_SEM]=1;
	follow[termPrime][TK_CL]=1;            
	follow[new_34][TK_PLUS]=1;
	follow[new_34][TK_MINUS]=1;
	follow[new_34][TK_SEM]=1;
	follow[new_34][TK_MUL]=1;
	follow[new_34][TK_DIV]=1;
	follow[new_34][TK_CL]=1;          
	follow[optionalReturn][TK_SEM]=1;
	
	follow[more_ids][TK_SQR]=1;
	
}

int parseerr=0;

void print_arr(int arr[],int size){
	int i;
	for (i=0;i<size;i++){
		if (arr[i])
			printf("%d ",i);



	}
	printf("\n");


}
void comb(int A[],int B[]){
	int i;
	for (i=0;i<60;i++)
	{
		A[i]=A[i]||B[i];
	
	}


}

void first_comp(node *rule,int ans[]){
	node *temp=rule->next;	
	while (temp){
		int val=temp->id;
		comb(ans,first[val]);
		if (!first[val][eps])
			break;
		temp=temp->next;

	}		
	if (ans[eps])
		comb(ans,follow[rule->id]);
	
	
}

int id=0;

tokenInfo getNext(){
	if (size<len)
		return tok[size++];
	tokenInfo tem;
	tem.token=-1;
	return tem;

}

int parse[200][100]={0};

void createParseTable(node *rule[],int count){
	int i,j;
	for (i=1;i<count;i++){
		
		int ans[60]={0};
		first_comp(rule[i],ans);
		for (j=0;j<60;j++){
			if (ans[j]){
				parse[rule[i]->id][j]=i;
			}
		}
	}
	for (i=0;i<200;i++)
	{
		for(j=0;j<60;j++)
		{
			if(follow[i][j]==1 && parse[i][j]==0)
			{parse[i][j]=-1;}//-1 for denoting Synchronising set 
		}
	}
}


int terminal(int S){
	if (S<54 || S==106)
		return 1;
	else
		return 0;

}
int flag=0;



node_t *parseInputSourceCode(node *rule[],int count){
node_t *root=NULL;
int ind=0;


stack s;
init_stack(&s);

push(&s,dollar,-1);
push(&s,program,ind++);

tokenInfo next=getNext();
insert_t(&root,-1,program,"---",0,next.token,-1,0);
char Next[200];

//int flag=0;
while (1){

	if (empty(s) && next.token==-1){
		
	        flag=1;
	 	break;  
	}
	if (empty(s)){

		break;
	}
	if (next.token==-1)		{
		break;

		}


	if (terminal(top(s))){
		if (top(s)==next.token){
			change(&root,top_index(s),next.lex,next.token,next.line);	
			next=getNext();
			//node_t *temp=(root,top_index(s));
				
			pop(&s);
			continue;

		}
		else{
			parseerr=1;
			printf("error at line %d:unexpected token \" %s \" which is %s expected %s \n",next.line,next.lex,m[next.token],m[top(s)]);			
			break;	
			}
	}
	else{
		int rule_no=parse[top(s)][next.token];
		int parent=top_index(s);    //unique index for parent

		
			
		int p=top(s);
		pop(&s);


		if (rule_no<=0){
			parseerr=1;
			printf("error at line %d:unexpected token \" %s \" which is %s \n",next.line,next.lex,m[next.token]);			
			
			break;
		}	


		node *start=rule[rule_no]->next;
		stack temp;
		init_stack(&temp);
		while (start){
			
			push(&temp,start->id,ind);
			insert_t(&root,parent,start->id,"---",ind,next.token,p,0);
			ind++ ;	
			start=start->next;
			
		}
		while (!empty(temp)){
			if (top(temp)!=eps){
			//printf("indexingggg %d\n",top_index(temp));	
			push(&s,top(temp),top_index(temp));
			}
			pop(&temp);


		}		


	}
	


}
  if (parseerr)
	return NULL;		
  return root;	
}



void init_map(){
int i;
for ( i=0;i<200;i++)
	strcpy(m[i],"");

strcpy(m[TK_ASSIGNOP],"TK_ASSIGNOP");
strcpy(m[TK_COMMENT],"TK_COMMENT");
strcpy(m[TK_FIELDID],"TK_FIELDID");
strcpy(m[TK_ID],"TK_ID");
strcpy(m[TK_NUM],"TK_NUM");
strcpy(m[TK_RNUM],"TK_RNUM");
strcpy(m[TK_FUNID],"TK_FUNID");
strcpy(m[TK_RECORDID],"TK_RECORDID");
strcpy(m[TK_WITH],"TK_WITH");
strcpy(m[TK_PARAMETERS],"TK_PARAMETERS");
strcpy(m[TK_END],"TK_END");
strcpy(m[TK_WHILE],"TK_WHILE");
strcpy(m[TK_INT],"TK_INT");
strcpy(m[TK_REAL],"TK_REAL");
strcpy(m[TK_TYPE],"TK_TYPE");
strcpy(m[TK_MAIN],"TK_MAIN");
strcpy(m[TK_GLOBAL],"TK_GLOBAL");
strcpy(m[TK_PARAMETER],"TK_PARAMETER");
strcpy(m[TK_LIST],"TK_LIST");
strcpy(m[TK_SQL],"TK_SQL");
strcpy(m[TK_SQR],"TK_SQR");
strcpy(m[TK_INPUT],"TK_INPUT");
strcpy(m[TK_OUTPUT],"TK_OUTPUT");
strcpy(m[TK_SEM],"TK_SEM");
strcpy(m[TK_COLON],"TK_COLON");
strcpy(m[TK_DOT],"TK_DOT");
strcpy(m[TK_ENDWHILE],"TK_ENDWHILE");
strcpy(m[TK_OP],"TK_OP");
strcpy(m[TK_CL],"TK_CL");
strcpy(m[TK_IF],"TK_IF");
strcpy(m[TK_THEN],"TK_THEN");
strcpy(m[TK_ENDIF],"TK_ENDIF");
strcpy(m[TK_READ],"TK_READ");
strcpy(m[TK_WRITE],"TK_WRITE");
strcpy(m[TK_RETURN],"TK_RETURN");
strcpy(m[TK_PLUS],"TK_PLUS");
strcpy(m[TK_MINUS],"TK_MINUS");
strcpy(m[TK_MUL],"TK_MUL");
strcpy(m[TK_DIV],"TK_DIV");
strcpy(m[TK_CALL],"TK_CALL");
strcpy(m[TK_RECORD],"TK_RECORD");
strcpy(m[TK_ENDRECORD],"TK_ENDRECORD");
strcpy(m[TK_ELSE],"TK_ELSE");
strcpy(m[TK_AND],"TK_AND");
strcpy(m[TK_OR],"TK_OR");
strcpy(m[TK_NOT],"TK_NOT");
strcpy(m[TK_LT],"TK_LT");
strcpy(m[TK_LE],"TK_LE");
strcpy(m[TK_EQ],"TK_EQ");
strcpy(m[TK_GT],"TK_GT");
strcpy(m[TK_GE],"TK_GE");
strcpy(m[TK_NE],"TK_NE");
strcpy(m[TK_COMMA],"TK_COMMA");
strcpy(m[NO_TK],"NO_TK");
strcpy(m[program],"program");
strcpy(m[otherFunctions],"otherFunctions");
strcpy(m[mainFunction],"mainFunction");
strcpy(m[stmts],"stmts");
strcpy(m[function],"function");
strcpy(m[input_par],"input_par");
strcpy(m[output_par],"output_par");
strcpy(m[parameter_list],"parameter_list");
strcpy(m[dataType],"dataType");
strcpy(m[remaining_list],"remaining_list");
strcpy(m[primitiveDatatype],"primitiveDatatype");
strcpy(m[constructedDatatype],"constructedDatatype");
strcpy(m[typeDefinitions],"typeDefinitions");
strcpy(m[declarations],"declarations");
strcpy(m[otherStmts],"otherStmts");
strcpy(m[returnStmt],"returnStmt");
strcpy(m[typeDefinition],"typeDefinition");
strcpy(m[fieldDefinitions],"fieldDefinitions");
strcpy(m[fieldDefinition],"fieldDefinition");
strcpy(m[moreFields],"moreFields");
strcpy(m[declaration],"declaration");
strcpy(m[global_or_not],"global_or_not");
strcpy(m[stmt],"stmt");
strcpy(m[assignmentStmt],"assignmentStmt");
strcpy(m[iterativeStmt],"iterativeStmt");
strcpy(m[conditionalStmt],"conditionalStmt");
strcpy(m[ioStmt],"ioStmt");
strcpy(m[funCallStmt],"funCallStmt");
strcpy(m[singleOrRecId],"singleOrRecId");
strcpy(m[new_24],"new_24");
strcpy(m[arithmeticExpression],"arithmeticExpression");
strcpy(m[outputParameters],"outputParameters");
strcpy(m[idList],"idList");
strcpy(m[inputParameters],"inputParameters");
strcpy(m[booleanExpression],"booleanExpression");
strcpy(m[elsePart],"elsePart");
strcpy(m[allVar],"allVar");
strcpy(m[var],"var");
strcpy(m[all],"all");
strcpy(m[lowPrecedenceOperators],"lowPrecedenceOperators");
strcpy(m[term],"term");
strcpy(m[highPrecedenceOperators],"highPrecedenceOperators");
strcpy(m[factor],"factor");
strcpy(m[expPrime],"expPrime");
strcpy(m[termPrime],"termPrime");
strcpy(m[logicalOp],"logicalOp");
strcpy(m[relationalOp],"relationalOp");
strcpy(m[optionalReturn],"optionalReturn");
strcpy(m[more_ids],"more_ids");
strcpy(m[eps],"eps");
strcpy(m[new_32],"new_32");
strcpy(m[new_34],"new_34");
strcpy(m[dollar],"dollar");
strcpy(m[DEL],"DEL");

}

void printParseTree(node_t *root){

			printf("DFS-POST ORDER TRAVERSAL\n");
			printf("Line No. 0 indicates non-terminal\n");
			printf("%-25s %-10s %-25s %-10s %-25s %-10s %-20s\n","lexemeCurrNode","lineNo","token","value","parentNode","leaf?","nodeSymbol");
printf("********************************************************************************************************************************************\n");				
			
			dfs(root);
	
			


}
