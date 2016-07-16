/*
	Sanjay Reddy S -2013A7PS189P
	Varun Vasudevan-2013A7PS103P
	Batch No: 33
*/

#include "symbol_semantic.h"
symbol_table STable;

char record_list[20][100];
int record_count=0;
int t_size[200]={4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4};
int t_count=0;
int off[100]={0};
FILE *printasm=NULL;
int  semerr=0;
char err[50][50];
int node_count=0;
int err_count=0;


void add_child(childnode **head,node_t *child){
	childnode *newnode=(childnode *)sizeof(childnode);
	newnode->next=NULL;
	newnode->child=child;
	if ((*head)==NULL){
		*head=newnode;
		return;
	} 
	
}
	
node_t *create(int id,char lex[],int index,int token,int parentid,int line){
	node_t *newnode=(node_t *)malloc(sizeof(node_t));
	newnode->id=id;
	newnode->index=index;
	newnode->parentid=parentid;
	strcpy(newnode->lex,lex);
	newnode->parent=-1;
	newnode->token=token;
	newnode->line=line;
	newnode->type=-1;
	newnode->value=-999;
	newnode->dvalue=-999.99;
	newnode->offset=0;        //give some suitable value to find if uninitialized
	newnode->record=0;	
	int i;
	for (i=0;i<N;i++){
		newnode->child[i]=NULL;
	}
	
	newnode->child_head=NULL;
	newnode->no_of_child=0;

	return newnode;

}

int is_terminal(int S){
	if (S<54 || S==106)
		return 1;
	else
		return 0;

}



void dfs(node_t *root){
	if (!root)
		return;
	int i;
	
	for (i=0;i<N;i++){
		dfs(root->child[i]);
	}
	//printf("%s %s,%s\n",root->lex,m[root->id],m[root->parent]);
	char rnum[200];
		
	if (root->id==TK_RNUM || root->id==TK_NUM)	
		strcpy(rnum,root->lex);
	else
		strcpy(rnum,"---");	
	
	
	if (root->parentid!=-1){
	printf("%-25s %-10d %-25s %-10s %-25s %-10d %-20s\n",root->lex,root->line,m[root->id],rnum,m[root->parentid],is_terminal(root->id),m[root->token]);
		

	}
	else{
	char Root[]="ROOT";
	printf("%-25s %-10d %-25s %-10s %-25s %-10d %-20s\n",root->lex,root->line,m[root->id],rnum,Root,is_terminal(root->id),m[root->token]);
	}
}

node_t *find(node_t *root,int parent){
	
	if (!root)
		return NULL;
	if (root->index==parent)
		return root;
	int i;
	node_t *temp;
	for (i=0;i<N;i++){
		temp=find(root->child[i],parent);
		if (temp){

			//printf("I am the parent %d\n",parent);
			return temp;
		}	

	}
	return NULL;
	

}
int change(node_t **root,int parent,char lex[],int id,int line){
	if (*root==NULL){
		//return NULL;
		printf("invalid root_________________________________________");
		return 0;
	}
	if ((*root)->index==parent){
		strcpy((*root)->lex,lex);
		(*root)->id=id;
		(*root)->line=line;	
		//(*root)->id=id;
		return 1;	
	}
			
	int i;
	int temp;
	for (i=0;i<N;i++){
		if ((*root)->child[i]!=NULL)
		{
		
		temp=change(&((*root)->child[i]),parent,lex,id,line);
		if (temp)
			return 1;
		}
	}
	
}

void insert_t(node_t **root,int parent,int id,char lex[],int index,int token,int parentid,int line){
	node_t *newnode=create(id,lex,index,token,parentid,line);	
	if (*root==NULL){
		newnode->parent=-1;
		*root=newnode;
		return;

	}
	node_t *par=find(*root,parent);
	//printf("BAAAAAAAAAAAAAAAAAAAAAAAAP   %d %s\n",par->index,m[par->id]);
	if (!par){
		/*printf("My father was unknown %d\n",parent);*/
		//printf("Oops something went wrong!!!!No. of nodes in tree are not sufficient. Change value of N to something higher in tree.h file \n");

	}

	if (!par)
		return;
	newnode->parent=par->index;  //or id
	//now insert_t
	int i;
	
	
	for (i=0;i<N;i++){
		if (par->child[i]==NULL){
			par->child[i]=newnode;
			return;
		}
	}
	
	

}






queue *create_q(node_t item){
	queue *newnode=(queue *)malloc(sizeof(queue));
	newnode->next=NULL;
	newnode->item=item;

	return newnode;


}

void enqueue(header *h,node_t item){
	queue *newnode=create_q(item);

	if ((*h).front==NULL){
		((*h).front)=newnode;
		((*h).rear)=newnode;
	}
	else{
		
		((*h).rear)->next=newnode;
		(*h).rear=newnode;

	}
		


}


void dequeue(header *h){
	if ((*h).front==NULL){
		printf("underflow !!!!!!!!!!!!!");
		return;

	}
	
	if ((*h).front==(*h).rear){
		queue *temp=(*h).front;
		(*h).front=NULL;
		(*h).rear=NULL;
		free(temp);	
		return;

	}

	queue *temp=(*h).front;
	(*h).front=((*h).front)->next;
	free(temp);	
}

int is_empty_q(header q){
	if (q.front==NULL)
		return 1;
	return 0;


}

void initialise_q(header *h){
	(*h).front=NULL;
	(*h).rear=NULL;

}


void refine(node_t *start[]){
	int i;	
	for (i=0;i<N;i++){
		if (!start[i])
			break;
		start[i]->type=start[i]->id;

	}

}	

int booltypecheck(node_t *top,char scope[],symbol_table STable){
	node_t *root=top->child[0];   //this is my bollean expression
	if (!root)
		return -1;   //no root is there
	if (root->child[0] && root->child[0]->id==TK_NOT){
		int type=booltypecheck(top->child[0],scope,STable);
		if(type==2)
			return type;		
		root->type=type;
		return type;

	}
	else if (root->child[0] && root->child[0]->id==TK_ID){
		char field[N];// you will get this back if it is record	
		int t1=search_symbol_table(STable,root->child[0]->lex,"global",field);
		if (t1==0){
			t1=search_symbol_table(STable,root->child[0]->lex,scope,field);
		}


		int t2=0;
			if (root->child[1])
				t2=search_symbol_table(STable,root->child[1]->lex,"global",field);
			if (t2==0){
				t2=search_symbol_table(STable,root->child[1]->lex,scope,field);
			}

		//printf("cheetah  %s \n",m[t1]);
		if (t1==t2 || (t1==TK_INT || t1==TK_REAL))
			root->type=boolean;

		else {
				
			root->type=0;
			if (root->type!=-3){ //error code for id and recordid
			printf("ERROR at line %d : type not matching in the boolean expression\n",top->child[0]->line);
			char word[200];
			sprintf(word,"ERROR at line %d : type not matching in the boolean expression\n",top->child[0]->line);			
			strcpy(err[err_count++],word);
			semerr=1;
			}
			return 2;

		}
		return boolean;

	}

	//add here for nested boolean expressions		
	
	return -1;

}
void getlist(node_t *root,int id,node_t *start[]){
	if (root==NULL)
		return;
	int k=0;
	int i;
	for (i=0;i<N;i++)
		start[i]=NULL;

	
	node_t *stop=(node_t *)malloc(sizeof(node_t));
	
	stop->id=-1;
	header_p h;
	initialise_q_p(&h);
	enqueue_p(&h,root);
	enqueue_p(&h,stop);
	int flag=0;
	node_t *top=NULL;
	while (!is_empty_q_p(h)){
	
		top=((h.front)->item);	
		dequeue_p(&h);
		if ((*top).id==-1){
			continue;
		}
		if ((*top).id==id){

			if(id==TK_ID){
			start[k++]=top;							
			flag=1;}

			else if (id==TK_ASSIGNOP){
			start[k++]=top->child[0];

			}
			else if (id==TK_READ){
			start[k++]=top->child[1];
			
			}
				
		}
		int i;	
		for (i=0;i<N;i++){
			if ((*top).child[i]==NULL)
				break;
			enqueue_p(&h,(((*top).child[i])));

		
		if (i>0)
		enqueue_p(&h,stop);
	
	}
	
    }


	
}

int checklist(node_t *explist[],node_t *list[]){
	int i,j;
	for (i=0;i<N;i++){
			
		if (!explist[i])
			return 0;
		node_t *ele=explist[i];
		for (j=0;j<N;j++){
			if (!list[j])
				break;
			//printf("drac:%s %s\n",explist[i]->lex,list[j]->lex);
			if (!strcmp(explist[i]->lex,list[j]->lex))
				return 1;

		}


	}


	int count1=0,count2=0;
	for (i=0;i<N;i++){
		if (explist[i])
			count1++;
		if (list[i])
			count2++;

	}
	//printf("yoghurt %d %d %d\n",N,count1,count2);
	return 0;
}
void append(node_t *list1[],node_t *list2[]){
	int i,j;
	for (i=0;i<N;i++){
		if (!list1[i])
			break;
	}
	for (j=0;i+j<N;j++){
		list1[j+i]=list2[j];
	}

}

void checkwhile(node_t *top,char scope[],symbol_table STable){
	node_t *explist[N];
	node_t *list1[N],*list2[N],*list3[N],*list4[N];


	int i;
	for (i=0;i<N;i++){
		explist[i]=NULL;
		list1[i]=NULL;
		list2[i]=NULL;
		list3[i]=NULL;
		list4[i]=NULL;

	}
	getlist(top->child[0],TK_ID,explist);
	getlist(top->child[1],TK_ASSIGNOP,list1);
	getlist(top->child[1],TK_READ,list3);
	
	if (top->child[2]){
		getlist(top->child[2],TK_ASSIGNOP,list2);
		getlist(top->child[2],TK_READ,list4);
	}	
	//printf("hey it is me swappy\n");
	//print_in(explist);
	//print_in(list2);
        append(list1,list2);
	append(list1,list3);
	append(list1,list4);
	int flag=checklist(explist,list1);   //check if there is an element in explist which is there in list1	
	if (!flag){
		printf("ERROR at line %d : There is no variable in check condition of while loop changing inside\n",top->child[0]->line);
		semerr=1;
		char word[200];
		sprintf(word,"ERROR at line %d : There is no variable in check condition of while loop changing inside\n",top->child[0]->line);
		strcpy(err[err_count++],word);	
		semerr=1;	
	}

}
void traverse_scope(node_t *root,int id,char scope[],symbol_table *STable){
	if (root==NULL)
		return;

	node_t *stop=(node_t *)malloc(sizeof(node_t));
	
	stop->id=-1;
	//FILE *fp =fopen("reddy.txt","w+");
	
	//printf("BFSIININNG11111\n\n");
	header_p h;
	initialise_q_p(&h);
	enqueue_p(&h,root);
	enqueue_p(&h,stop);
	int flag=0;
	node_t *top=NULL;
	while (!is_empty_q_p(h)){
	
		top=((h.front)->item);	
		dequeue_p(&h);
		if ((*top).id==-1){
			//fprintf(fp,"\n\n");
			continue;
		}
		if ((*top).id==id){
			//switch cases
				
			flag=1;
			node_t temp=*(top->child[0]);
			temp.type=(top->child[0]->child[0]->id);
				
			addon add;
			int i;
			for (i=0;i<N;i++){	
			add.input[i]=NULL;
			add.output[i]=NULL;
			add.field[i]=NULL;}
			if (id==typeDefinitions){
				//add field list
				
				get_fields(add.field,top->child[0]);
				refine(add.field);
				//printf("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF%s\n",top->child[0]->lex);
				//print_in(add.field);
				char field[200];
				if(!search_symbol_table(*STable,temp.lex,"global",field)){			
					insert_symbol_table(STable,temp,add,"global");
					

				}	
				else{
					printf("ERROR: %s redeclared in line no. %d\n",temp.lex,temp.line);   //printf previous declaration or first			
					char word[200];
					sprintf(word,"ERROR: %s redeclared in line no. %d\n",temp.lex,temp.line);			
					strcpy(err[err_count++],word);
					semerr=1;
				}

			}
			else if (id==iterativeStmt){
				//printf("@@@@@@@@@@@@@@@@@@@@@@@@   %s %s %d \n",(top->child[0]->lex),scope,top->child[0]->line);
				//do checking for while thing

				int type=booltypecheck(top,scope,*STable);
				if (type==2)
					return;
				checkwhile(top,scope,*STable);

			}
			
			else{
				char field[200];
				if(!search_symbol_table(*STable,temp.lex,scope,field)  && !search_symbol_table(*STable,temp.lex,"global",field)){
					if (top->child[0]->child[1]  && top->child[0]->child[1]->id==TK_GLOBAL)			
							insert_symbol_table(STable,temp,add,"global");
					else{
							/*if (temp.type==TK_RECORDID){
								printf("chitnis %s\n",temp.lex);
								node_t *start[N];
								search_rid(*STable,temp.lex,"global",start);


							}*/

								
							insert_symbol_table(STable,temp,add,scope);


							if (temp.type==TK_RECORDID){
																	
								//printf("jingul %d\n",search_symbol_table(*STable,"#book","global",field));
								//printf("%s  drinks \n ",m[search_symbol_table(*STable,field,"global",field)]);
																
								//search_symbol_table(*STable,field,"global",field);

									
							}							
							

					}
					//printf("lol i m feeling positive %s\n\n\n",m[top->child[0]->child[1]->id]);

				}	
				else{
					printf("\nERROR: %s redeclared in line no. %d\n",temp.lex,temp.line);   //printf previous declaration or first			
					char word[200];
					sprintf(word,"\nERROR: %s redeclared in line no. %d\n",temp.lex,temp.line);			
					strcpy(err[err_count++],word);
					semerr=1;	
				}

			}
			//BFS(top,fp);  instead of this insert scope
			//insert_scope(top,STable);
			//fprintf(fp,"\n\n######################################################\n\n");	
				
		}
		//if (flag)
		//fprintf(fp,"\nparent %s-%s-%d\nchildren ",m[(*top).id],(*top).lex,(*top).index);
		int i;	
		for (i=0;i<N;i++){
			if ((*top).child[i]==NULL)
				break;
			enqueue_p(&h,(((*top).child[i])));

		
		if (i>0)
		enqueue_p(&h,stop);
	
	}
	
}


	
}



void bfs(node_t *root,node_t **Ast){
	if (root==NULL)
		return;
	node_t *AST=*Ast;
	node_t stop;
	stop.id=-1;

	//FILE * fp;
	//fp=fopen("output1.txt","w+");


	//printf("BFSIININNG\n\n");
	header h;
	initialise_q(&h);
	enqueue(&h,*root);
	enqueue(&h,stop);
	AST=NULL;
	int index=0;
	insert_t(&AST,-1,program,"---",index++,root->token,-1,0);
	while (!is_empty_q(h)){
		
	
		node_t top=((h.front)->item);	
		dequeue(&h);
		
		if (top.id==-1){
			//printf("\n");
			continue;
		}
		
		if (top.id!=DEL){
			//insert_t(&AST,top.parent,top.id,top.lex,top.index,top.token,top.parentid,top.line);	
			if(top.child[0]!=NULL)
				;//printf("parent:%s %s %d\nchildren:\n",m[top.id],top.lex,top.index);
			int i;
			for(i=0;i<N;i++){
				node_t *temp=top.child[i];
				if (!temp){
					if(i!=0)	
					;//printf("\n\n");
					break;
				}
				int t=temp->id;
				if (temp->id!=DEL)
					;//printf("  %s: %s: %d    ",m[temp->id],temp->lex,temp->index);
			}
			

		}
		//printf("%s ",m[top.id]);
		int i;	
		for (i=0;i<N;i++){
			if (top.child[i]==NULL)
				break;

			enqueue(&h,(*(top.child[i])));
			node_t *temp=top.child[i];
			if ((top.child[i])->id!=DEL){
				insert_t(&AST,temp->parent,temp->id,temp->lex,temp->index,temp->token,temp->parentid,temp->line);

			}

		}
		if (i>0)
		enqueue(&h,stop);
	
	}
	//fclose(fp);
	

	/*
	fp=fopen("reddy1.txt","w+");
	search_print(AST,fp,TK_ID);
	//BFS(AST,fp);	
	fclose(fp);*/
	//traverse_scope(AST,TK_FUNID,"---");
	//return AST;
	*Ast=AST;

}



void BFS(node_t *root,FILE *fp){
	if (root==NULL)
		return;

	node_t stop;
	stop.id=-1;
	//FILE *fp =fopen("reddy.txt","w+");
	if (!fp){
		//printf("jingalala");
		return;

	}
	//printf("BFSIININNG\n\n");
	header h;
	initialise_q(&h);
	enqueue(&h,*root);
	enqueue(&h,stop);
	while (!is_empty_q(h)){
	
		node_t top=((h.front)->item);	
		dequeue(&h);
		if (top.id==-1){
			fprintf(fp,"\n\n");
			continue;
		}
		/*if (top.id==declarations || top.id==typeDefinitions){
				continue;
		}*/
		
		fprintf(fp,"\nparent %s-%s-%d\nchildren ",m[top.id],top.lex,top.index);
		int i;	
		for (i=0;i<N;i++){
			if (top.child[i]==NULL)
				break;
			fprintf(fp,"%s-%s-%d(%d)	",m[(top.child[i])->id],(top.child[i])->lex,(top.child[i])->index,i);
			enqueue(&h,(*(top.child[i])));

		}
		if (i>0)
		enqueue(&h,stop);
	
	}
//fclose(fp);
}

queue_p *create_q_p(node_t *item){
	queue_p *newnode=(queue_p *)malloc(sizeof(queue_p));
	newnode->next=NULL;
	newnode->item=item;

	return newnode;


}

void enqueue_p(header_p *h,node_t *item){
	queue_p *newnode=create_q_p(item);

	if ((*h).front==NULL){
		((*h).front)=newnode;
		((*h).rear)=newnode;
	}
	else{
		
		((*h).rear)->next=newnode;
		(*h).rear=newnode;

	}
		


}


void dequeue_p(header_p *h){
	if ((*h).front==NULL){
		printf("underflow !!!!!!!!!!!!!");
		return;

	}
	
	if ((*h).front==(*h).rear){
		queue_p *temp=(*h).front;
		(*h).front=NULL;
		(*h).rear=NULL;
		free(temp);	
		return;

	}

	queue_p *temp=(*h).front;
	(*h).front=((*h).front)->next;
	free(temp);	
}

int is_empty_q_p(header_p q){
	if (q.front==NULL)
		return 1;
	return 0;


}

void initialise_q_p(header_p *h){
	(*h).front=NULL;
	(*h).rear=NULL;

}

void insert_inout(node_t **start,node_t *root){
	node_t *newnode=(node_t *)malloc(sizeof(node_t));


		newnode->type=root->id;
		
		strcpy(newnode->lex,root->lex);
		
		//add whatever

	
	node_t *temp=*start;
	if (temp==NULL){
		*start=newnode;
		return;	
	}
	while (temp->child[0]){

		temp=temp->child[0];
	}	
	temp->child[0]=newnode;


}



void get_fields(node_t *start[],node_t *root){
	node_t *temp=root->child[0];   //root was tk_recordid
	int k=0;
	//now root is field definition
	if (root){
		if (temp->id==fieldDefinitions){
			//fielddef fielddef moreFields
			root=root->child[0];
			/*printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
			for (int i=0; i<N;i++){
				temp=root->child[i];
				if(!temp){printf("\n\n\n");break;}	
				
				printf("%s\n",m[temp->id]);
			}	*/

			temp=root->child[0];	
			if (!temp)
				return;
			temp->id=temp->child[1]->id;
			strcpy(temp->lex,temp->child[3]->lex);
			//do the same for lex
			start[k++]=temp;
		
			temp=root->child[1];
			if (!temp)
				return;
			temp->id=temp->child[1]->id;     //make this record later
			strcpy(temp->lex,temp->child[3]->lex);
			start[k++]=temp;
			root=root->child[2];
			
			while (root){
				temp=root->child[0];
				if (!temp)
					return;
				
				temp->id=temp->child[1]->id;
				strcpy(temp->lex,temp->child[3]->lex);
			//do the same for lex
				start[k++]=temp;
				root=root->child[1];

				
			}
	


		}
		else
			return;

	}
		
	
	

}

void get_inout(node_t *	start[],node_t *root){
	root=root->child[0];
	//
	int k=0;	
	//printf("$$$$$$$$$$$$$$$$$$$%s\n",root->lex);
	char name[200];
	strcpy(name,root->lex);	
	//printf("%d ",root->id);
	start[k++]=root;
	start[k-1]->type=root->child[0]->id;
	//printf("$$$$$$$$$$$$$$$$$$$%s\n",m[root->child[0]->id]);
		
	strcpy(start[k-1]->lex,name);	
	root=root->child[1];
	
	while(root){
		
		//	
		node_t *temp=root->child[1];
		//printf("%d ",temp->id);
	//	printf("$$$$$$$$$$$$$$$$$$$111%s\n",m[temp->id]);
		char name[200];
		strcpy(name,root->lex);
		
		start[k++]=temp;
		
	//printf("$$$$$$$$$$$$$$$$$$$%s\n",m[start[k-1]->type]);
		start[k-1]->type=temp->id;
		strcpy(start[k-1]->lex,name);
		root=root->child[2];

	}	
	//printf("\n");

}
void print_in(node_t *root[]){
	
	int i;		
	for (i=0;i<N;i++){
		if (!root[i])
			break;
		printf("%s-%s	",m[root[i]->type],root[i]->lex);

	}	
	printf("\n");
}

void get_inout_call(node_t *root,node_t *start[],char call_scope[],symbol_table STable){
	//root hasidlist
	int k=0;
	int i;
	for (i=0;i<N;i++){
		start[i]=NULL;

	}			
	char field[200];
	while (root->child[1]){//more id is there

		node_t * temp=root->child[0];
		int t1=0,t2=0;	
		//printf("\nkjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj\n");	
		t1=search_symbol_table(STable,temp->lex,call_scope,field);
		t2=search_symbol_table(STable,temp->lex,call_scope,field);
		if (t1==0 && t2==0){
			printf("ERROR %s NOT DECLARED line  %d \n",temp->lex,temp->line);
			char word[200];
			sprintf(word,"ERROR %s NOT DECLARED line  %d \n",temp->lex,temp->line);			
			semerr=1;
			//pop(&s1);

		}			
		temp->type=t1>t2?t1:t2;
		start[k++]=temp;
		root=root->child[1];
		root=root->child[0];



	}
	node_t *temp=root->child[0];
	int t1=0,t2=0;
	//if((temp->type=search_symbol_table(STable,temp->lex,call_scope,field))==0 )
	t1=search_symbol_table(STable,temp->lex,call_scope,field);
	t2=search_symbol_table(STable,temp->lex,"global",field);
	if (t1==0 && t2==0){		
			printf("ERROR %s NOT DECLARED line no %d \n",temp->lex,temp->line);
			char word[200];
			sprintf(word,"ERROR %s NOT DECLARED line no %d \n",temp->lex,temp->line);			
			strcpy(err[err_count++],word);
			semerr=1;
	}	
	temp->type=t1>t2?t1:t2;
	start[k++]=temp;
		//printf("symolize########################%s %s\n\n",start[k-1]->lex,call_scope);
		
}

void check_output_par(node_t *root,node_t *return_output[],char scope[],symbol_table STable,int id){
	if (root==NULL)
		return;

	node_t *stop=(node_t *)malloc(sizeof(node_t));
	
	stop->id=-1;
	
	header_p h;
	initialise_q_p(&h);
	enqueue_p(&h,root);
	enqueue_p(&h,stop);
	
	node_t *top=NULL;
	while (!is_empty_q_p(h)){
	
		top=((h.front)->item);	
		dequeue_p(&h);
		if ((*top).id==-1){
			//fprintf(fp,"\n\n");
			continue;
		}
		if ((*top).id==id){
			if (id==optionalReturn){
				get_inout_call(top->child[0],return_output,scope,STable);
				
			
			}
			if (id==TK_ASSIGNOP){
				int type=typecheck(top,scope,STable);
				if (type==0){
					//printf("DILMAH TEA\n\n\n");
					printf("ERROR at line %d: types not matching\n",top->line);
					char word[200];
					sprintf(word,"ERROR at line %d: types not matching\n",top->line);			
					strcpy(err[err_count++],word);
					semerr=1;
				}
			}
	
		}
		int i;	
		for (i=0;i<N;i++){
			if ((*top).child[i]==NULL)
				break;
			enqueue_p(&h,(((*top).child[i])));

		
		if (i>0)
		enqueue_p(&h,stop);
	
	}
	
    }


}


void scope_helper(node_t *top,char scope[],symbol_table STable){
	if(!strcmp(scope,"---")){
		strcpy(scope,"_main");

	}	

	if ((top->id)==TK_FUNID){
			
				if ((top->child[1]) && top->child[1]->id==TK_CALL){	
					//printf("hello my friend %s %s %s\n\n\n",m[(top->child[1])->id],top->lex,scope);
					//	match_parameters(top,scope);
					node_t *input[N];
					node_t *output[N];
					//printf("hijabbbuddin %s %s   \n\n",scope,top->lex);
					if (!strcmp(scope,top->lex)){
						printf("ERROR at line no %d : recursive calls not permitted!!!!!\n",top->line);
						char word[200];
						sprintf(word,"ERROR at line no %d : recursive calls not permitted!!!!!\n",top->line);			
						strcpy(err[err_count++],word);
						semerr=1;							

					}	
					get_inout_call(top->child[0],output,scope,STable);
					
					get_inout_call(top->child[2],input,scope,STable);
					//printf("nice darling jeeeeeeee %d\n",top->line);
					char field[200];
					int call_line=top->line;
					int scope_line=search_symbol_table_line(STable,top->lex,"global",field);
					//printf("burrrrrrrrrrrrrrrrrrrrrrrrrrrrrah %d %d\n\n",call_line,scope_line);
					if (call_line<=scope_line){
						printf("ERROR at line %d : function not defined\n",top->line);
						char word[200];
						sprintf(word,"ERROR at line %d : function not defined\n",top->line);			
						strcpy(err[err_count++],word);
						semerr=1;	

					}
					//printf("jinxxxxxxxxxxxxxxxxxxx********************************************************* \n\n");
					
					//printf("jinxxxxxxxxxxxxxxxxxxx 1\n");
					//print_in(output);
					search_get_add(STable,top->lex,"global",input,output,1);	

				}
				if (top->child[0] && top->child[0]->id==input_par){
					node_t *return_output[N];
					
					check_output_par(top,return_output,scope,STable,optionalReturn);
					search_get_add(STable,top->lex,"global",return_output,return_output,0);
					//printf("draft!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
					//print_in(return_output);

				}

	}
	
	//cover all the cases here I'll break your leg if you touch anything else


}

void check_scope(node_t * root,symbol_table STable){

	//printf("scope:  %s\n",root->lex);
	char scope[200];
	strcpy(scope,root->lex);
	
		if (root==NULL)
		return;

	node_t *stop=(node_t *)malloc(sizeof(node_t));
	
	stop->id=-1;
	
	header_p h;
	initialise_q_p(&h);
	enqueue_p(&h,root);
	enqueue_p(&h,stop);
	int flag=0;
	node_t *top=NULL;
	while (!is_empty_q_p(h)){
	
		top=((h.front)->item);	
		dequeue_p(&h);
		if ((*top).id==-1){
			
			continue;
		}


		scope_helper(top,scope,STable);				

		int i;	
		for (i=0;i<N;i++){
			if ((*top).child[i]==NULL)
				break;
			enqueue_p(&h,(((*top).child[i])));

		
		if (i>0)
		enqueue_p(&h,stop);
	
	}
	
}




	

}

void find_scope(node_t *root,symbol_table *STable,int f){
	if (f==3){
		print_symbol_table(*STable);
		return;
	}

	if (root==NULL)
		return;
	node_t *stop=(node_t *)malloc(sizeof(node_t));
	
	stop->id=-1;
	//FILE *fp =fopen("reddy.txt","w+");
	
	//printf("BFSIININNG11111\n\n");
	header_p h;
	initialise_q_p(&h);
	enqueue_p(&h,root);
	enqueue_p(&h,stop);
	int flag=0;
	node_t *top=NULL;
	while (!is_empty_q_p(h)){
	
		top=((h.front)->item);	
		dequeue_p(&h);
		if ((*top).id==-1){
			//fprintf(fp,"\n\n");
			continue;
		}

				
		if ((*top).id==TK_FUNID ||(*top).id==mainFunction){
			/*if ((*top).child[1] && (*top).child[1]->id==TK_CALL){
				printf("hey there %s\n\n\n",top->lex);
					traverse_scope(top,TK_FUNID,top->lex,STable);
			}*/
		
			if ((*top).child[0]->id==input_par ||(*top).id==mainFunction){
			addon add;

			if (f==1)	
				check_scope(top,*STable);
			else if (f==2){
				node_t *return_dummy[N];
				if (top->id==mainFunction)
					check_output_par(top,return_dummy,"_main",*STable,TK_ASSIGNOP);
				else
					check_output_par(top,return_dummy,top->lex,*STable,TK_ASSIGNOP);
				
				
			}
				

			else{
				int i;
				for (i=0;i<N;i++){
				add.input[i]=NULL;   //give input parameter
				add.output[i]=NULL;  //give output parameter
				add.field[i]=NULL;   //give field list  not needed here
				}
				node_t temp=*top;
			
				if ((*top).id!=mainFunction){
					get_inout(add.input,(*top).child[0]);
					int i;
					for (i=0;i<N;i++){
						if (!add.input[i])
							break;
						
						insert_symbol_table(STable,*(add.input[i]),add,(*top).lex);
					}	
		
					//refine(add.input);
					
					
					get_inout(add.output,(*top).child[1]);
					for (i=0;i<N;i++){
						if (!add.output[i])
							break;
					
						insert_symbol_table(STable,*(add.output[i]),add,(*top).lex);
					}
					//printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
					//print_in(add.output);
					//refine(add.output);			
				//printf("???????????????????????????????????????????\n");
				//	print_in(add.input);
				//printf("???????????????????????????????????????????\n");
				//	print_in(add.output);

								
			
					//printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n\n");
				}
				char field[200];
				if(!search_symbol_table(*STable,temp.lex,"global",field)){			
						insert_symbol_table(STable,temp,add,"global");
					
				}
				else{
						printf("ERROR: %s redeclared in line no. %d\n",temp.lex,temp.line);   //printf previous declaration or first
						char word[200];
						sprintf(word,"ERROR: %s redeclared in line no. %d\n",temp.lex,temp.line);			
						strcpy(err[err_count++],word);
						semerr=1;
				}

						//insert_symbol_table(STable,temp,add,"_global");
	
			
			flag=1;
				if ((*top).id==mainFunction){
					traverse_scope(top,declarations,"_main",STable);
					traverse_scope(top,typeDefinitions,"_main",STable);
					traverse_scope(top,iterativeStmt,"_main",STable);
					

				}
				else{
						
					traverse_scope(top,declarations,top->lex,STable);
					traverse_scope(top,typeDefinitions,top->lex,STable);// Remove if not Required
					traverse_scope(top,iterativeStmt,top->lex,STable);
					
   
					
				}
			//BFS(top,fp);  instead of this insert scope
			//insert_scope(top,STable);
			//fprintf(fp,"\n\n######################################################\n\n");	
		}		
		}
	}
		//if (flag)
		//fprintf(fp,"\nparent %s-%s-%d\nchildren ",m[(*top).id],(*top).lex,(*top).index);
		int i;	
		for (i=0;i<N;i++){
			if ((*top).child[i]==NULL)
				break;
			enqueue_p(&h,(((*top).child[i])));

		
		if (i>0)
		enqueue_p(&h,stop);
	
	}
	
}

if (f==2){
change_symbol_table(STable);
//print_symbol_table(*STable);
//printf("done with\n");

//printf("trrrrrrrrrrrrrringgggggggggggggggggg\n");
//print_symbol_table(*STable);
}
	
}


void search_print(node_t *root){
	if (root==NULL)
		return;

	
	
	header_p h;
	initialise_q_p(&h);
	enqueue_p(&h,root);
	
	int flag=0;
	node_t *top=NULL;
	while (!is_empty_q_p(h)){
		node_count++;
		top=((h.front)->item);	
		dequeue_p(&h);
		int i;	
		for (i=0;i<N;i++){
			if ((*top).child[i]==NULL)
				break;
		enqueue_p(&h,(((*top).child[i])));

		
		
	
	}
//fclose(fp);
	
}


	
}


void insert_scope(node_t *root,symbol_table *STable){
	
	
	/*
	insert_symbol_table(&STable,"varun",1,"main");  //for inserting  into the hashtable
	search_symbol_table(STable,"jing","main");     //search the symbol into the hashtable
	*/	




}


