#include "AST.h"

void copy_node(node_t *root,node_t *root1){
	 root->id=root1->id;
	 strcpy(root->lex,root1->lex);
	 root->index=root1->index;
	 root->parent=root1->parent;	//here it is id not index
	 root->token=root1->token;
	 root->parentid=root1->parentid;
	 root->line=root1->line;
}	 

void change_parent(node_t *root1,node_t *root){
	root1->parent=root->index;
	root1->parentid=root->id;
}

void update_parent(node_t * root){
	int i;
	for (i=0;i<N;i++){
		node_t *temp=root->child[i];
		if (!temp)
			break;
		change_parent(temp,root);
	}
}


void remove_eps(node_t *root){
	int count=0,i,flag=0;
	for (i=0;i<N;i++){
		node_t *temp=root->child[i];	
		if (!temp)
			break;
		
		if (temp->id==DEL)
			continue;
		else if (temp->id==eps){
			temp->id=DEL;
			flag++;
		}
		count++;	
	}

	if (flag==count && count!=0){
		root->id=eps;
	}		
}

void prune(node_t *root){
	if (!root)
		return;
	int id=root->id;
	if (id==TK_SEM){
		root->id=DEL;
		return;
	}
	switch(id){	
		node_t *temp;	
		case mainFunction:{		
			temp=root->child[2];  //TK_END
			temp->id=DEL;
			temp=root->child[0];  //TK_MAIN
			temp->id=DEL;
			break;
		}
		case otherFunctions:
		//case output_par:
		//case remaining_list:
		case typeDefinitions:
		case moreFields:
		case declarations:
		//case global_or_not:
		case otherStmts:
		//case new_24:
		//case outputParameters:
		//case new_32:
		//case expPrime:
		//case termPrime:
		//case new_34:
		//case optionalReturn:
		//case more_ids:
		{
			temp=root->child[0];
			if (temp->id==eps)
				root->id=eps; 
			break; 
		}
		case function:{
			//printf("BEFORE %s %s\n",m[root->id],root->lex);		
			copy_node(root,root->child[0]);	     //replace for copying individaul fields
			update_parent(root);				
			//printf("AFTER %s %s\n",m[root->id],root->lex);	
			(root->child[0])->id=DEL;
			(root->child[5])->id=DEL;
			//printf("AFTER1 %s %s\n",m[root->id],root->lex);
			break;
		}
		case input_par:{
			//copy_node(root,root->child[4]);
			update_parent(root);
			(root->child[0])->id=DEL;
			(root->child[1])->id=DEL;
			(root->child[2])->id=DEL;
			(root->child[3])->id=DEL;
			//(root->child[4])->id=DEL;
			(root->child[5])->id=DEL;
			break;
		}
		case output_par:{
			if ((root->child[0])->id==TK_OUTPUT){
				//copy_node(root,root->child[4]);
				 update_parent(root);
				(root->child[0])->id=DEL;
				(root->child[1])->id=DEL;
				(root->child[2])->id=DEL;
				(root->child[3])->id=DEL;
				//(root->child[4])->id=DEL;
				(root->child[5])->id=DEL;
			}
			else
			{
				temp=root->child[0];
				if (temp->id==eps)
				root->id=eps; 
			}
			break; 
		}
		case parameter_list:
		{
			copy_node(root,root->child[1]);
			update_parent(root);
			root->type=root->child[0]->id;	
			//printf("%s\n\n\n",m[root->type]);
			(root->child[1])->id=DEL;
			break;
		}
		case dataType:
		{
			copy_node(root,root->child[0]);
			update_parent(root);
			root->type=root->id;
			//printf("%s",m[root->id]);
			(root->child[0])->id=DEL;
			break;
		}
		case primitiveDatatype:
		{
			copy_node(root,root->child[0]);
			update_parent(root);
			root->type=root->id;
			(root->child[0])->id=DEL;
			break;
		}
		case constructedDatatype:
		{
			copy_node(root,root->child[1]);
			update_parent(root);
			(root->child[0])->id=DEL;
			(root->child[1])->id=DEL;
			break;
		}
		case remaining_list:
		{
			if((root->child[0])->id==TK_COMMA)
			{
				copy_node(root,root->child[1]);
				update_parent(root);
				(root->child[0])->id=DEL;
				//(root->child[1])->id=DEL;
			}
			else
			{
				temp=root->child[0];
				if (temp->id==eps)
				root->id=eps;
			}
			break;
		}
		case typeDefinition:
		{
			copy_node(root,root->child[1]);
			update_parent(root);
			(root->child[0])->id=DEL;
			(root->child[1])->id=DEL;
			(root->child[3])->id=DEL;
			(root->child[4])->id=DEL;
			break;
		}
		case declaration:
		{
			copy_node(root,root->child[3]);
			update_parent(root);
			(root->child[0])->id=DEL;
			(root->child[2])->id=DEL;
			(root->child[3])->id=DEL;
			(root->child[5])->id=DEL;
			break;
		}
		case global_or_not:
		{
			if(root->child[0] && (root->child[0])->id==TK_COLON)
			{
				copy_node(root,root->child[1]);
				update_parent(root);
				(root->child[0])->id=DEL;
				(root->child[1])->id=DEL;
			}
			else
			{
				temp=root->child[0];
				if (temp && temp->id==eps)
				root->id=eps;
			}
			break;
		}
		case stmt:
		{
			//copy_node(root,root->child[0]);
			//update_parent(root);
			//root=root->child[0];
			//(root->child[0])->id=DEL;
			break;
		}
		case assignmentStmt:
		{
			copy_node(root,root->child[1]);
			update_parent(root);
			//printf("%s\n",m[root->child[2]->id]);
			(root->child[1])->id=DEL; //  deleting here
			(root->child[3])->id=DEL;
			break;
		}
		case singleOrRecId:
		{
			copy_node(root,root->child[0]);
			update_parent(root);
			//root=root->child[0];
			//printf("\n%s %s\n",m[(root)->id]
			//,m[(root->child[0])->id]);
			//(root->child[0])->id=DEL;
			break;
		}
		case new_24:
		{
			if((root->child[0])->id==TK_DOT)
			{
				copy_node(root,root->child[1]);
				update_parent(root);
				(root->child[0])->id=DEL;
				(root->child[1])->id=DEL;
			}
			else
			{
				temp=root->child[0];
				if (temp->id==eps)
				root->id=eps;
			}
			break;
		}
		case funCallStmt:
		{
			copy_node(root,root->child[2]);
			update_parent(root);
			//(root->child[1])->id=DEL;
			(root->child[2])->id=DEL;
			(root->child[3])->id=DEL;
			(root->child[4])->id=DEL;
			(root->child[6])->id=DEL;
			break;
		}
		case outputParameters:
		{
			if((root->child[0])->id==TK_SQL)
			{
				copy_node(root,root->child[1]);
				update_parent(root);
				(root->child[0])->id=DEL;
				(root->child[1])->id=DEL;
				(root->child[2])->id=DEL;
				(root->child[3])->id=DEL;
			}
			else
			{
				temp=root->child[0];
				if (temp->id==eps)
				root->id=eps;
			}
			break;
		}
		case inputParameters:
		{
			copy_node(root,root->child[1]);
			update_parent(root);
			(root->child[1])->id=DEL;
			(root->child[2])->id=DEL;
			(root->child[0])->id=DEL;
			break;
		}
		case iterativeStmt:
		{
			(root->child[0])->id=DEL;
			(root->child[1])->id=DEL;
			(root->child[3])->id=DEL;
			(root->child[6])->id=DEL;
			break;
		}
		case conditionalStmt:
		{
			(root->child[0])->id=DEL;
			(root->child[1])->id=DEL;
			(root->child[3])->id=DEL;
			(root->child[4])->id=DEL;
			break;
		}
		case elsePart:
		{
			if((root->child[0])->id==TK_ELSE){
			(root->child[0])->id=DEL;
			(root->child[3])->id=DEL;
			}
			break;    //Added the elsePart

		}
		case ioStmt:
		{
			copy_node(root,root->child[0]);
			
			update_parent(root);
			//nprintf("IOSTMT %s %s\n",root->child[2]->lex,m[root->id]);
			strcpy(root->lex,root->child[2]->lex);	
			//printf("%s\n",root->child[0]->lex);	
			//(root->child[0])->id=DEL;
			(root->child[1])->id=DEL;
			(root->child[3])->id=DEL;
			(root->child[4])->id=DEL;
			//printf("IOSTMT %s %s\n",root->lex,m[root->id]);
		/*	for (int i=0;i<N;i++){
				node_t *temp=root->child[i];
				if (temp==NULL)
					break;
				printf("%s\n",m[temp->id]);	
			}
			printf("\n\n");

		*/
			break;
		}
		case allVar:
		{
			copy_node(root,root->child[0]);
			update_parent(root);
			(root->child[0])->id=DEL;
			break;
		}
		case new_32:
		{
			if((root->child[0])->id==TK_DOT)
			{
				copy_node(root,root->child[1]);
				update_parent(root);
				(root->child[0])->id=DEL;
				(root->child[1])->id=DEL;
			}
			else
			{
				temp=root->child[0];
				if (temp->id==eps)
				root->id=eps;
			}
			break;
		}
		/*case arithmeticExpression:{
			copy_node(root,root->child[1]);
			update_parent(root);
			(root->child[1])->id=DEL;
				

			break;
		}	
		*/
		case factor:{
			
			temp=root->child[0];
			if (temp->id==TK_OP){
				(root->child[0])->id=DEL;
				(root->child[2])->id=DEL;
				copy_node(root,root->child[1]);	
				//root=root->child[0];
				int i;
				for (i=0;i<N;i++){
					root->child[i]=(root->child[1])->child[i];
				}
				update_parent(root);	
			}
			else{
					copy_node(root,root->child[0]);
					update_parent(root);
					temp->id=DEL;
					//printf("%s\n\n",m[root->child[0]->id]);	
					//root=root->child[0];	//possibie error 
			}
			break;
		}
		case expPrime:{	
			temp=root->child[0];
			if (temp->id==eps ){
				//printf("\n\n\n");
				root->id=DEL;
			}
			else{
				copy_node(root,temp);
				update_parent(root);
				temp->id=DEL;
			}	
			break;
		}
		case arithmeticExpression:{
			//printf("%s %s\n",m[root->child[0]->id],m[root->child[1]->id]);			
			break;
		}	
		case term:{
				//printf("%s",root->child[0]->lex);
		
				if (root->child[1]->id==eps){
					//printf("%s\n",m[root->id]);
					//printf("deleting \n\n\n\n");
				}
				break;
		}
		case termPrime:{
			temp=root->child[0];
			if (temp->id==eps){
				//printf("\n\n\n");
				root->id=DEL;
			}
			else{
				copy_node(root,temp);
				update_parent(root);
				temp->id=DEL;
			}	
			break;
		}
		/*case expPrime:{
			temp=root->child[0];
			if (temp->id==eps)
				root->id=eps;
			else{
				copy_node(root,temp);
				update_parent(root);
				temp->id=DEL;				
		
			}
				
			break;
		}*/
		case highPrecedenceOperators:
		case lowPrecedenceOperators:
		{
			copy_node(root,root->child[0]);
			update_parent(root);
			(root->child[0])->id=DEL;
			break;
		}
		case all:
		{
			if (root->child[0]->id==TK_ID){
				//printf("%s\n",root->child[0]->lex);
				copy_node(root,root->child[0]);
				//(root->child[0])->id=DEL;
				//root=root->child[0];				
				update_parent(root);
			}
			else{
			copy_node(root,root->child[0]);
			update_parent(root);
			(root->child[0])->id=DEL;
			}
			break;
		}
		case new_34:
		{
			if((root->child[0])->id==TK_DOT)
			{
				copy_node(root,root->child[1]);
				//printf("%s",root->child[1]->lex);
				update_parent(root);
				(root->child[0])->id=DEL;
				(root->child[1])->id=DEL;
			}
			else
			{
				temp=root->child[0];
				if (temp->id==eps){
					root->id=DEL;
				}
			}
			break;
		}
		case booleanExpression:
		{
			if((root->child[0])->id==TK_OP)
			{
				copy_node(root,root->child[3]);
				update_parent(root);	
				(root->child[0])->id=DEL;
				(root->child[2])->id=DEL;
				(root->child[3])->id=DEL;
				(root->child[4])->id=DEL;
				(root->child[6])->id=DEL;
			}
			else if((root->child[0])->id==TK_ID)
			{
				copy_node(root,root->child[1]);
				update_parent(root);
				//printf("%s\n",root->lex);
				(root->child[1])->id=DEL;
			}
			else if((root->child[0])->id==TK_NOT)
			{
				copy_node(root,root->child[0]);
				update_parent(root);
				(root->child[0])->id=DEL;
				(root->child[1])->id=DEL;
				(root->child[3])->id=DEL;
			}
			break;
		}
		case var:
		case logicalOp:
		case relationalOp:
		{
			copy_node(root,root->child[0]);
			update_parent(root);
			(root->child[0])->id=DEL;
			break;
		}
		case returnStmt:{
			//(root->child[0])->id=DEL;
			(root->child[2])->id=DEL;
			break;
		}
		case optionalReturn:
		{
			if((root->child[0])->id==TK_SQL)
			{
				//copy_node(root,root->child[1]);
				//update_parent(root);
				(root->child[0])->id=DEL;
				//(root->child[1])->id=DEL;
				(root->child[2])->id=DEL;
				root=root->child[1];
			}
			else
			{
				temp=root->child[0];
				if (temp->id==eps)
				root->id=eps;
			}
			break;
		}
		case idList:
		{
			//copy_node(root,root->child[0]);
			//update_parent(root);
			//root=root->child[0];
			if((root->child[1])->id==eps){
				root=root->child[0];
			}
			//(root->child[0])->id=DEL;
			break;
		}
		case more_ids:
		{
			if((root->child[0])->id==TK_COMMA)
			{
				//copy_node(root,root->child[1]);
				update_parent(root);		
				(root->child[0])->id=DEL;
				//(root->child[1])->id=DEL;
			}
			else
			{
				temp=root->child[0];
				if (temp->id==eps)
				root->id=DEL;
			}

			update_parent(root);
			break;
		}
		case TK_ID:{
			node_t *temp=root->child[0];
			if (temp){
				root->type=temp->id;
				//printf("%s",m[root->type]);
			}
			break;
		}
		/*
		case otherFunctions:{
			temp=root->child[0];
			if (temp->id==eps)
				root->id=eps; 
			break; 

		}
		case declarations:{
			temp=root->child[0];
			if (temp->id==eps)
				root->id=eps;  
			break;
	
		} 
		case typeDefinitions:{
			temp=root->child[0];
			if (temp->id==eps)
				root->id=eps;  
			break;

		}
		case optionalReturn:{
			temp=root->child[0];
			if (temp->id==eps)
				root->id=eps;  
			break;			
			
		}
		case otherStmts:{
			temp=root->child[0];
			if (temp->id==eps)
				root->id=eps;  
			break;

		}
		
		case stmts:{
			temp=root->child[0];
			if (temp->id==eps)
				root->id=eps;  
			break;			
		} 
		*/
	}
}

void visit(node_t *root){
	
	
	if (!root)
		return;


	int i;	
	for (i=0;i<N;i++){
		node_t * temp=root->child[i];
		if (!temp)
			break;			
		visit(temp);
	}
	prune(root);
	update_parent(root);	
	remove_eps(root);
	update_parent(root);
}
