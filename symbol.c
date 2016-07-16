#include "codegen.h"





void print_symbol_line_asm(node_s *start){
	while (start){	
		if (start->s.type==TK_RECORDID){
			fprintf(printasm,"%s resb %d\n",(start->s).lex,20);
		}
		else
			if (strcmp(start->s.lex,"---") && start->s.type!=fieldDefinitions && start->s.id!=TK_FUNID)
				fprintf(printasm,"%s resb %d\n",(start->s).lex,4);
		/*if (start->s.id==TK_FUNID){
			printf("input:");
			print_in((start->add).input);
			printf("output:");
			print_in((start->add).output);}
		if (start->s.id==TK_RECORDID){
			print_in((start->add).field);
		}*/
		start=start->next;
	}
}

void print_symbol_asm(symbol ST){
	int i;
	for (i=0;i<L;i++){
		if (ST.start[i]==NULL)
			continue;
		print_symbol_line_asm(ST.start[i]);			
	}
}

void print_symbol_table_asm(symbol_table STable){
	int i;
	for (i=0;i<100;i++){
		print_symbol_asm(STable.ST[i]);
	}
}

int check_record(char name[]){
	int i;
	for (i=0;i<record_count;i++){
		if (!strcmp(name,record_list[i]))
			return 1;
	}
	return 0;
}

void getfields(char lex[],symbol_table STable,node_t *st[]){
	int key=hash_key_symbol("global");
	int key1=hash_key_symbol(lex);
	symbol s=STable.ST[key];
	int i;
	node_s *start=s.start[key1];
	while (start){
		if (!strcmp(start->s.lex,lex)){
			addon add=start->add;
			for (i=0;i<N;i++){
				if (!add.field[i])
					break;
				st[i]=add.field[i];
			}
		}
		start=start->next;
	}		
}

void change_symbol_line(node_s **temp,symbol_table *STable){
	node_s *start=*temp;	
	while (start){	
		int i;
		if (start->s.type==TK_RECORDID){
			strcpy(record_list[record_count++],start->s.lex);
			char field[200];
			search_symbol_table(*STable,start->s.lex,"_main",field);
			//printf("%s\n",field);
			int type=search_symbol_table(*STable,field,"global",field);
			node_t *st[N];
			
			for (i=0;i<N;i++)
				st[i]=NULL;	
			getfields(field,*STable,st);
			//print_in(st);
			addon add;
			int i;
			//printf("track\n");
			for (i=0;i<N;i++){
				if (!st[i])
					break;
			
			char field1[200];
			
			strcpy(field1,start->s.lex);	
			strcat(field1,".");
			strcat(field1,st[i]->lex);
			char temp[200];
			strcpy(temp,st[i]->lex);
			//printf("acc:field %s\n",start->s.lex);
			if (temp[0]!='#')
			strcpy(st[i]->lex,field1);
			
			//insert_symbol_table(STable,*st[i],add,"_main");
			strcpy(st[i]->lex,temp);
			}
		}	
		start=start->next;
	}
}


void change_symbol(symbol *ST,symbol_table *STable){
	int i;
	for (i=0;i<L;i++){
		if ((*ST).start[i]==NULL)
			continue;
		
		change_symbol_line(&((*ST).start[i]),STable);		
	}
}

void change_symbol_table(symbol_table *STable){
	int i;
	for (i=0;i<100;i++){
		//printf("%d\n",i);
		change_symbol(&((*STable).ST[i]),STable);
		//printf("\n");
	}
}

int is_rel(int id){
	if (id==TK_LT || id==TK_LE || id==TK_GT || id==TK_GE || TK_EQ)
		return 1;

	return 0;
}

void boolean_evaluate(node_t *root){
	if (!root)
		return;
	int i;
	for (i=0;i<N;i++){
		if (!root->child[i])
			break;
		boolean_evaluate(root->child[i]);
	}
	if (root->id==TK_ID){
		return;
	}
	if (root->id==TK_NUM){
		return;
	}

	if (root->id==TK_NOT){
		if (root->child[0]){
				char name[200];
				t_count++;	
				sprintf(name,"%s%d","t",t_count);
				t_size[t_count]=4;
				char op[200];
				strcpy(op,root->child[0]->lex);
				if (isdigit(op[0]))	
					fprintf(printasm,"notone %s,%s\n",name,root->child[0]->lex);
				else
					fprintf(printasm,"nottwo %s,%s\n",name,root->child[0]->lex);	
		strcpy(root->lex,name);
		}
		return;
	}
	
	if (is_rel(root->id)){
		
		if (root->child[0] && root->child[1]){
			char name[200];
			t_count++;	
			sprintf(name,"%s%d","t",t_count);
			t_size[t_count]=4;
			char op2[200];
			strcpy(op2,root->child[1]->lex);
			if(isdigit(op2[0])){
				if (!strcmp(root->lex,"&&&"))	
					fprintf(printasm,"andone %s,%s,%s\n",name,root->child[0]->lex,root->child[1]->lex);
				else if (!strcmp(root->lex,"@@@"))	
					fprintf(printasm,"orone %s,%s,%s\n",name,root->child[0]->lex,root->child[1]->lex);
				else if (!strcmp(root->lex,"<"))	
					fprintf(printasm,"lessthanone %s,%s,%s\n",name,root->child[0]->lex,root->child[1]->lex);
				else if (!strcmp(root->lex,"<="))	
					fprintf(printasm,"lessthanequalone %s,%s,%s\n",name,root->child[0]->lex,root->child[1]->lex);
				else if (!strcmp(root->lex,">"))	
					fprintf(printasm,"greatthanone %s,%s,%s\n",name,root->child[0]->lex,root->child[1]->lex);
				else if (!strcmp(root->lex,">="))	
					fprintf(printasm,"greatthanequalone %s,%s,%s\n",name,root->child[0]->lex,root->child[1]->lex);
				else if (!strcmp(root->lex,"=="))	
					fprintf(printasm,"equalone %s,%s,%s\n",name,root->child[0]->lex,root->child[1]->lex);
				else if (!strcmp(root->lex,"!="))	
					fprintf(printasm,"notequalone %s,%s,%s\n",name,root->child[0]->lex,root->child[1]->lex);
			}
			else{
				if (!strcmp(root->lex,"&&&"))	
					fprintf(printasm,"andtwo %s,%s,%s\n",name,root->child[0]->lex,root->child[1]->lex);
				else if (!strcmp(root->lex,"@@@"))	
					fprintf(printasm,"ortwo %s,%s,%s\n",name,root->child[0]->lex,root->child[1]->lex);
				else if (!strcmp(root->lex,"<"))	
					fprintf(printasm,"lessthantwo %s,%s,%s\n",name,root->child[0]->lex,root->child[1]->lex);
				else if (!strcmp(root->lex,"<="))	
					fprintf(printasm,"lessthanequaltwo %s,%s,%s\n",name,root->child[0]->lex,root->child[1]->lex);
				else if (!strcmp(root->lex,">"))	
					fprintf(printasm,"greatthantwo %s,%s,%s\n",name,root->child[0]->lex,root->child[1]->lex);
				else if (!strcmp(root->lex,">="))	
					fprintf(printasm,"greatthanequaltwo %s,%s,%s\n",name,root->child[0]->lex,root->child[1]->lex);
				else if (!strcmp(root->lex,"=="))	
					fprintf(printasm,"equaltwo %s,%s,%s\n",name,root->child[0]->lex,root->child[1]->lex);
				else if (!strcmp(root->lex,"!="))	
					fprintf(printasm,"notequaltwo %s,%s,%s\n",name,root->child[0]->lex,root->child[1]->lex);

			//printf("%s %s %s %s\n",root->lex,name,root->child[0]->lex,root->child[1]->lex);

			}		
		strcpy(root->lex,name);
		}	
		return;
	}
}


void search_icg(node_t *root,int id){
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
		if((*top).id==stmt){
			if (top->child[0]->id==iterativeStmt){
				int label1=0,label2=0;   //names for goto statements
				label1=++l_count;
				label2=++l_count;
			
				fprintf(printasm,"l%d:\n",label1);
			
				boolean_evaluate(top->child[0]->child[0]);
				fprintf(printasm,"mov eax,[%s]\n",top->child[0]->child[0]->lex);
				fprintf(printasm,"cmp eax,1\n");
				fprintf(printasm,"jne l%d\n",label2);
				
				search_icg(top->child[0],stmt);
				fprintf(printasm,"jmp l%d\n\n",label1);
				fprintf(printasm,"l%d:\n",label2);
					
				continue;}
			else if (top->child[0]->id==conditionalStmt){
				int label1=0,label2=0,label3=0;
				label1=++l_count;
				label2=++l_count;
				if (top->child[0]->child[2]->child[0]->id!=TK_ENDIF)
					label3=++l_count;
				else if (top->child[0]->child[3] && top->child[0]->child[3]->child[0]->id!=TK_ENDIF)
					label3=++l_count;
				//printf("label:%d %d %d\n",label1,label2,label3);
				boolean_evaluate(top->child[0]->child[0]);
				fprintf(printasm,"mov eax,[%s]\n",top->child[0]->child[0]->lex);
				fprintf(printasm,"cmp eax,1\n");
				
				fprintf(printasm,"jne l%d\n",label2);
				
				//printf("check %s\n",top->child[0]->child[0]->lex);

				fprintf(printasm,"l%d:\n",label1);
					  
				icg_helper(top->child[0]->child[1]);

				
				if (top->child[0]->child[2]->id==otherStmts){
					if (!top->child[0]->child[3]){
						//printf("\n");
						if (!label3)
							fprintf(printasm,"jmp l%d\n",label2);
						else
							fprintf(printasm,"jmp l%d\n",label3);
						fprintf(printasm,"l%d:\n",label2);	
						if (top->child[0]->child[2]->child[0]->id!=TK_ENDIF){
						search_icg(top->child[0]->child[2],stmt);	
						}
					}	
					else{	
					search_icg(top->child[0]->child[2],stmt);
						if (top->child[0]->child[3]->child[0]->id!=TK_ENDIF)	
							fprintf(printasm,"jmp l%d\n",label3);
						fprintf(printasm,"l%d:\n",label2);	
					//printf("\n");
					if (top->child[0]->child[3]->child[0]->id!=TK_ENDIF){	
					//printf("\n");			
					search_icg(top->child[0]->child[3],stmt);	
					//printf("\n");
					fprintf(printasm,"l%d:\n",label3);	
					}
					}	
				}
				else{//printf("\n");
					if (top->child[0]->child[2]->child[0]->id!=TK_ENDIF)	
							fprintf(printasm,"jmp l%d\n",label3);
						fprintf(printasm,"l%d:\n",label2);
					if (top->child[0]->child[2]->child[0]->id!=TK_ENDIF){
					search_icg(top->child[0]->child[2],stmt);
					fprintf(printasm,"l%d:\n",label3);}
					//printf("\n");
				}
				//printf("%d\n",label3);
				continue;}
			else if (top->child[0]->id==TK_READ){
				icg_helper(top->child[0]);
				continue;}
			else if (top->child[0]->id==TK_WRITE){
				icg_helper(top->child[0]);
				continue;}

		}
		if((*top).id==stmt){
			icg_helper(top->child[0]);
			continue;
		}
		if ((*top).id==id){
			if (id==TK_ASSIGNOP){
				icg_helper(top);
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


void insert_symbol(node_s **start,node_t s,addon add,char scope[]){		//insertion of node at the end of the list
	node_s *newnode=(node_s *)malloc(sizeof(node_s));
	//newnode->line_no=line_no;
	//strcpy(newnode->lex,lex);
	int id1=hash_key_symbol(scope);
	
	int tp=off[id1];
	if (s.type==TK_RECORDID){
		strcpy(s.field,s.child[0]->lex);
		off[id1]+=12;	
	}
	else{
		off[id1]+=4;	
	}
	s.offset=tp;	
	newnode->s=s;
	newnode->add=add;
	strcpy(newnode->scope,scope);
	newnode->next=NULL;
				
	if (*start==NULL){
		*start=newnode;
		return;
	}
	node_s *temp=*start;
	while(temp->next){
		temp=temp->next;
	}

	temp->next=newnode;

}

int hash_key_symbol(char lex[]){
	int i;
	int key=0;
	for (i=0;lex[i]!='\0';i++){
		key+=lex[i];

	}

	return key%L;
}

void insert_ht_symbol(symbol *ST,node_t s,addon add,char scope[]){
	int key=hash_key_symbol(s.lex);
	insert_symbol(&(ST->start[key]),s,add,scope);
		
} 

void print_symbol_line(node_s *start){
	while (start){	
		//lexeme type scope offset
		if (start->s.id!=TK_FUNID && strcmp(start->s.lex,"---")){
			if (start->s.type==TK_RECORDID){			
				printf("%-25s %-25s %-10s %-10d\n",(start->s).lex,start->s.field,start->scope,start->s.offset);
			}
			else{
				if (start->s.type==fieldDefinitions)
				printf("%-25s %-25s %-10s %-10d\n",(start->s).lex,"RECORD",start->scope,start->s.offset);				
				else 
				printf("%-25s %-25s %-10s %-10d\n",(start->s).lex,m[(start->s).type],start->scope,start->s.offset);
			}	
		}
		/*
		if (start->s.id==TK_FUNID){
			printf("input:");
			print_in((start->add).input);
			printf("output:");
			print_in((start->add).output);}
		if (start->s.id==TK_RECORDID){
			print_in((start->add).field);
		}*/	
		start=start->next;
	}


}


void print_symbol(symbol ST){
	int i;
	for (i=0;i<L;i++){
		if (ST.start[i]==NULL)
			continue;
		//printf("%d:",i);
		print_symbol_line(ST.start[i]);	
		//printf("\n");
	}


}


void init_ht_symbol(symbol *ST){
	int i;
	for (i=0;i<L;i++){
		ST->start[i]=NULL;
	}

}


void insert_symbol_table(symbol_table *STable,node_t s,addon add,char scope[]){		//insertion of node at the end of the list
	int key=hash_key_symbol(scope);
	insert_ht_symbol(&(STable->ST[key]),s,add,scope);		

}


void print_symbol_table(symbol_table STable){
	int i;
	for (i=0;i<100;i++){
		//printf("%d\n",i);
		print_symbol(STable.ST[i]);
		//printf("\n");
	}

}
void init_symbol_table(symbol_table *STable){
	int i;
	for (i=0;i<L;i++){
		init_ht_symbol(&(STable->ST[i]));
	}
}

int getfieldtype(symbol_table STable,char scope[],char lex[],char fieldtype[]){
	int key1=hash_key_symbol(scope);
	int key=hash_key_symbol(lex);
        symbol temp=STable.ST[key1];
	node_s *start=temp.start[key];
	
	while(start){
		if (!strcmp((start->s).lex,lex)){
			addon add=start->add;
			//add.field- list of fields
			int i;
			for (i=0;i<N;i++){
				if (!add.field[i])
					break;

				if (!strcmp(fieldtype,add.field[i]->lex)){   //match the fields 
					return add.field[i]->type;

				}
			}
		}
		start=start->next;
	}
	return 0;
}

int typecheck(node_t *root,char scope[],symbol_table STable){ //assignment stm should be the root    
	if (!root)
		return -1;		//for an empty case type is always right
	//base cases
	if (root->id==TK_NUM){
		root->type=TK_INT;
		return TK_INT;
	}
	else if (root->id==TK_RNUM){
		root->type=TK_REAL;
		return TK_REAL;

	}
	else if (root->id==TK_ID){
		char field[200];
		int type=search_symbol_table(STable,root->lex,scope,field);
		int type1=search_symbol_table(STable,root->lex,"global",field);
		if (type==0)
			type=type1;	
		if (type==TK_RECORDID){
			if (root->child[1]){
				char fieldtype[N];
				strcpy(fieldtype,root->child[1]->lex);   //field
				type=getfieldtype(STable,"global",field,fieldtype);	
				//printf("%s \n",m[type]);			
				//printf("%s %s\n",field,root->child[1]->lex);		
			}

		}

		//printf("type from the table %s\n",m[type]);

		if (type==0){	
			
							
			printf("ERROR at line %d :%s not declared in the scope\n",root->line,root->lex);
			char temp[200];
			sprintf(temp,"ERROR at line %d :%s not declared in the scope\n",root->line,root->lex);			
			strcpy(err[err_count++],temp);
			semerr=1;
			return 0;	

		}

		root->type=type;
		return type;

	}

	//else if for record field
	
	int ans1=typecheck(root->child[0],scope,STable);
		
	int ans2=typecheck(root->child[1],scope,STable);
		
	if (ans1==ans2 || ans2==-1){
		root->type=root->child[0]->type;
		return root->type;	

	}
	else if (ans1==TK_INT && ans2==TK_RECORDID){
		return root->type==-3;
	
	}
	
	else{
		root->type=0;

		
	}
	//now collapse the type of root
	
	return 0;

}


int search_symbol_table(symbol_table STable,char lex[],char scope[],char field[]){
	int key1=hash_key_symbol(scope);
	int key=hash_key_symbol(lex);
        symbol temp=STable.ST[key1];
	node_s *start=temp.start[key];
	
	while(start){
		if (!strcmp((start->s).lex,lex)){
			int type=(start->s).type;
			if (type==TK_RECORDID){
				strcpy(field,(start->s).field);
					
			}
			
				
			return type;
		}
		start=start->next;
	}

	return 0;
}


int search_symbol_table_line(symbol_table STable,char lex[],char scope[],char field[]){
	int key1=hash_key_symbol(scope);
	int key=hash_key_symbol(lex);
        symbol temp=STable.ST[key1];
	node_s *start=temp.start[key];
	
	while(start){
		if (!strcmp((start->s).lex,lex)){
			int line=(start->s).line;
			
			return line;
		}
		start=start->next;
	}

	return 0;
}


int compare_args(node_t *ar1[],node_t *ar2[],char call_scope[],symbol_table STable,int io){
	int i;	
	//print_in(ar1);
	//print_in(ar2);

	int line=0;
	int flag=0;
	int type=0;
	for (i=0;i<N;i++){	
		if (!ar1[i] && !ar2[i]){
			//return 0;
			flag=0;
			break;
		}	
		if (!ar1[i]){
			flag=-1;
			line=ar2[i]->line;
			break;	
		}
		if (!ar2[i]){
			flag=1;
			line=ar1[i]->line;
			break;
		}
		//printf("type checking---%s: %s\n\n",m[ar1[i]->type],m[ar2[i]->type]);
		if (ar1[i]->type!=ar2[i]->type){
			line=ar1[i]->line;
			type=ar1[i]->type;
			if (type==TK_ID)
				break;	
			flag=2;
			break;
		}
	}

	int t1=3,t2=3;  //some value other than error codes
	if (io){			//0 is input 1 is output
		t2=flag;

	}
	else{
		t1=flag;

	}	
				if (flag!=0){
					printf("ERROR at line %d ",line);
					char temp[200];
					sprintf(temp,"ERROR at line %d ",line);			
					strcpy(err[err_count++],temp);	
					semerr=1;
				}
				if (io==2){

					if (t2==1)
						printf("LESS OUTPUT ARGUEMENTS in function definition \n");
					else if (t2==-1)
						printf("MORE OUTPUT ARGUEMENTS in function definition \n");
					else if (t2==2)
						printf("OUTPUT ARGUEMENTS DON'T MATCH required type in function definition %s\n",m[type]);	

				}
				else{					
					if (t1==1)
						printf("LESS INPUT ARGUEMENTS\n");
					else if (t1==-1)
						printf("MORE INPUT ARGUEMENTS\n");
					else if (t1==2)
						printf("INPUT ARGUEMENTS DON'T MATCH required type %s\n",m[type]);
					if (t2==1)
						printf("LESS OUTPUT ARGUEMENTS\n");
					else if (t2==-1)
						printf("MORE OUTPUT ARGUEMENTS\n");
					else if (t2==2)
						printf("OUTPUT ARGUEMENTS DON'T MATCH required type %s\n",m[type]);
				}

	return flag;

}

void search_get_add(symbol_table STable,char lex[],char scope[],node_t *input[],node_t *output[],int flag){
	int key1=hash_key_symbol(scope);
	int key=hash_key_symbol(lex);
        symbol temp=STable.ST[key1];
	node_s *start=temp.start[key];
	
	while(start){
		if (!strcmp((start->s).lex,lex)){
			//return (start->add);
			
			addon ad=start->add;

			if (flag){
				int t1=compare_args(ad.input,input,lex,STable,0);    //0 means success -1 means less arguements 1 means more arguements 2 means arg types not match
			//0-input &&& 1-output
				
				//printf("\n\n");
				int t2=compare_args(ad.output,output,lex,STable,1);    //lex is call scope
				//printf("%d %d\n",t1,t2);
				if (!t1 && !t2)
					;//printf("CORRECT MATCH\n\n\n");
				else{
					/*if (t1==1)
						printf("LESS INPUT ARGUEMENTS\n");
					else if (t1==-1)
						printf("MORE INPUT ARGUEMENTS\n");
					else if (t1==2)
						printf("INPUT ARGUEMENTS DON'T MATCH\n");
						if (t2==1)
					printf("LESS OUTPUT ARGUEMENTS\n");
						else if (t2==-1)
					printf("MORE OUTPUT ARGUEMENTS\n");
					else if (t2==2)
						printf("OUTPUT ARGUEMENTS DON'T MATCH\n");*/
	
				}	
				//printf("input here........................\n");	
				//print_in(ad.output);
			}
			else{
				int t2=compare_args(ad.output,output,lex,STable,2);	
				
			}

			return;
		}
		start=start->next;
	}
	
}

