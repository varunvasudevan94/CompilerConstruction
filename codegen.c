#include "codegen.h"


int record_flag=0;

int is_operator(int id){
	if (id==TK_PLUS ||id==TK_MINUS||id==TK_DIV ||id==TK_MUL)  
		return 1;
	return 0;
}
int l_count=0;
int uniq=0;

int parseword(char n1[]){
	int len=strlen(n1);
	int i,j;
	char field1[200];
	char field2[200];	
	for (i=0;i<len;i++){
		if (n1[i]=='.'){
			field1[i]='\0';
			break;
		}
		field1[i]=n1[i];		
	}
	i++;
	for (j=0;i<len;i++,j++){
		field2[j]=n1[i];
	}
	field2[j]='\0';

	char field[200];
	search_symbol_table(STable,field1,"_main",field);
	node_t *st[N];	
	int ct=0;	
	for (i=0;i<N;i++)
		st[i]=NULL;	
	getfields(field,STable,st);
	for (i=0;i<N;i++){
		if (!st[i])
			break;
		if (!strcmp(field2,st[i]->lex)){
			ct=i+1;	
			break;}
	}
	if (ct==0)
		return 0;
	int res=(ct-1)*4;
	strcpy(n1,field1);
	char tem[200];
	sprintf(tem,",%d",res);
	strcat(n1,tem);	
	
	/*printf("%s \n",field1);
	printf("%s \n",field2);	*/
	return 1;
}

void print_oper(char operator[],int l1,int l2,int rec,int r1,int r2){

if (!strcmp(operator,"+"))
	fprintf(printasm,"add");
else if (!strcmp(operator,"-"))
	fprintf(printasm,"sub");
else if (!strcmp(operator,"*"))
	fprintf(printasm,"mul");
else if (!strcmp(operator,"/"))
	fprintf(printasm,"div");	
if (rec==1){
	fprintf(printasm,"records");
}

else{
if (r1==0 && r2==0){
	if(!l1 && !l2)
		fprintf(printasm,"two");
	else if(l1 && !l2)
		fprintf(printasm,"one");
	if(!l1 && l2)
		fprintf(printasm,"one");
	else if (l1 && l2)
		fprintf(printasm,"zero");
}

else if (r1==0 && r2){
	if (l1|| l2)
		fprintf(printasm,"rn");
	else{
		fprintf(printasm,"ri");		
	}	
}
else if (r1 && r2==0){
	if (l1|| l2)
		fprintf(printasm,"rn");
	else{
		fprintf(printasm,"ri");		
	}	
}
else{
	fprintf(printasm,"rr");
}
}
}

//int record_flag=0;

void icg_helper(node_t *root){
	//root is  assignop initialise add condition for that too
		if (!root)
			return ;
		int i;
		for (i=0;i<N;i++){
			if (!root->child[i])
				break;
			icg_helper(root->child[i]);
		}
		if (root->id==TK_READ){
			if (strcmp(root->lex,"read") ){
					int ct=-1;
					int is_record=check_record(root->lex);
					char name[200];
					//strcpy(name,root->lex);
					if(root->child[1] && root->child[1]->child[1] && root->child[1]->child[1]->id==TK_FIELDID){
						/*strcat(name,".");
						
						strcat(name,root->child[1]->child[1]->lex);*/
						strcpy(name,root->child[1]->child[1]->lex);
						char field[200];
						search_symbol_table(STable,root->lex,"_main",field);
				
						node_t *st[N];		
						for (i=0;i<N;i++)
							st[i]=NULL;	
				
						
						getfields(field,STable,st);
						for (i=0;i<N;i++){
							if (!st[i])
								break;
							if (!strcmp(name,st[i]->lex)){
								ct=i+1;	
								break;}
						}

						for (i=0;i<N;i++){
							if (!st[i])
								break;
				
						}

						if (ct!=-1){
						
							fprintf(printasm,"readrecord fmt_in,%s,%d,t%d,prompt\n",root->lex,ct,++t_count);
							t_size[t_count]=4;
						}
						else{
					
							fprintf(printasm,"read fmt_in,%s,prompt\n",root->lex);
						}
								


					}
					else if (is_record){
						
							printf("ERROR at line %d : You can't read a record\n",root->line);
							char temp[200];
							sprintf(temp,"ERROR at line %d : You can't read a record\n",root->line);			
							strcpy(err[err_count++],temp);
							semerr=1;
					}
					else
					fprintf(printasm,"read fmt_in,%s,prompt\n",root->lex);
			}
			return;
		}
		if (root->id==TK_WRITE){
			if (strcmp(root->lex,"write")){
					char name[200];
					strcpy(name,root->lex);
					if(root->child[1] && root->child[1]->child[0] && root->child[1]->child[0]->id==TK_FIELDID){
						strcat(name,".");
						strcat(name,root->child[1]->child[0]->lex);
					}
			if (check_record(name)){
				char field[200];
				search_symbol_table(STable,name,"_main",field);
				int type=search_symbol_table(STable,field,"global",field);
				node_t *st[N];
			
				for (i=0;i<N;i++)
					st[i]=NULL;	
				getfields(field,STable,st);
				for (i=0;i<N;i++){
					if (!st[i])
						break;
				  //i for all the, total fields
				}
				
				fprintf(printasm,"writerecord %s,fmt_out,t%d,t%d,%d,%d,%d\n",name,++t_count,++t_count,i,++uniq,++uniq);
				t_size[t_count]=4;
				t_size[t_count-1]=4;

			}
			else
			fprintf(printasm,"write fmt_out,%s\n",name);
			}
			return;
		}
		if (root->id==TK_ASSIGNOP){
			/*if (root->child[1]->id==complex){
				char field[200];
				search_symbol_table(STable,root->child[1]->child[0]->lex,"_main",field);
				
				node_t *st[N];		
				for (i=0;i<N;i++)
					st[i]=NULL;	
				

				getfields(field,STable,st);
					

				char str[200];
				strcpy(str,root->child[1]->lex);
				char s[2]=",";
				char *token;
				token=strtok(str,s);
				i=0;
				while (token!=NULL){
					printf("mov %s.%s %s\n",root->child[0]->lex,st[i++]->lex,token);
					token=strtok(NULL,s);
				}
			}*///String tokenising code
			if  (root->child[1]->record==1){
				char field[200];
				search_symbol_table(STable,root->child[0]->lex,"_main",field);
				int type=search_symbol_table(STable,field,"global",field);
				node_t *st[N];
			
				for (i=0;i<N;i++)
					st[i]=NULL;	
				getfields(field,STable,st);
				for (i=0;i<N;i++){
					if (!st[i])
						break;
				  //i for total fields
				}
				fprintf(printasm,"assignrecords %s,%s,t%d,%d,%d,%d\n",root->child[0]->lex,root->child[1]->lex,++t_count,i,++uniq,++uniq);
				t_size[t_count]=4;
			
			}
			else{
				char n1[200],n2[200];
				strcpy(n1,root->child[0]->lex);	
				strcpy(n2,root->child[1]->lex);		
				int f1=parseword(n1);
				int f2=parseword(n2);	
			 	int isnum=isdigit(n2[0]);
				if (!f1 && isnum)
					fprintf(printasm,"store %s,%s\n",n1,n2);
				else if(f1 && isnum)
					fprintf(printasm,"storerecord %s,%s\n",n1,n2);
				else if (!f1 && !f2)
					 fprintf(printasm,"assigntwo %s,%s\n",n1,n2);
				else if(!f1)
					fprintf(printasm,"assignfield %s,%s\n",n1,n2);
					
				else if (f1 && !f2)
					fprintf(printasm,"assignrecord %s,%s\n",n1,n2);

				else if (f1 && f2)
					fprintf(printasm,"assignfields %s,%s\n",n1,n2);
				else	
			 		fprintf(printasm,"assigntwo %s,%s\n",n1,n2);

			}		
		}	
	
		if (!root->child[0]){
			return;
		}
		if (root->id==TK_MUL || root->id==TK_DIV){
			return;
		}	
		if (root->id==TK_ID){
			if (root->child[1] && root->child[1]->id==TK_FIELDID){
				char field[200];
				strcpy(field,root->lex);
				strcat(field,".");
				strcat(field,root->child[1]->lex);
				strcpy(root->lex,field);
				root->record=2;
			}		
			return;
		}
		if (root->id==TK_NUM)
			return;	
		if (is_operator(root->id) && !root->child[1]){
			//printf("%s\n",root->child[0]->lex);
			return; 
		}	
		if (is_operator(root->id) && is_operator(root->child[1]->id)){
				//printf(" %s %s %s\n",root->child[0]->lex,op1,root->child[1]->child[0]->lex);
				char op1[200];
				node_t op;
			        strcpy(op.lex,op1);
				op.id=root->child[0]->id;
				strcpy(op1,root->child[0]->lex);
				int rec=0;
				int r1=0,r2=0;
				
				if (root->child[0]->record==2 ){
						r1=1;
					}	             
					 if (root->child[1]->child[0]->record==2){
						r2=1;
					}

				if (check_record(op1)||check_record(root->child[1]->child[0]->lex)||root->child[0]->record||root->child[1]->child[0]->record ){				

					if (root->child[0]->record==2 || root->child[1]->child[0]->record==2)
					{
					root->child[0]->record=2;
					root->child[1]->child[0]->record=2;
					root->record=2;}
					
					else{
						root->child[0]->record=1;
					root->child[1]->child[0]->record=1;
					root->record=1;
					}
					rec=1;
				}
				char name[200];
				t_count++;	
				sprintf(name,"%s%d","t",t_count);

				strcpy(root->child[0]->lex,name);
				char n1[200],n2[200];
				strcpy(n1,op1);
				strcpy(n2,root->child[1]->child[0]->lex);
				
				int f1=parseword(n1);
				int f2=parseword(n2);
				
				if (root->record==1)
					rec=1;
				else if (root->record==2)
					rec=2;

				if (rec==1)
					t_size[t_count]=20;
				int l1=0;
				int l2=0;
				if (isdigit(n1[0]))
					l1=1;
				if (isdigit(n2[0]))
					l2=1;	
				//printf("debug 1:%s\n",root->lex);
				print_oper(root->lex,l1,l2,rec,f1,f2);
				if (rec==1){
					char field[200];
					search_symbol_table(STable,n2,"_main",field);
					node_t *st[N];	
						
					for (i=0;i<N;i++)
						st[i]=NULL;	
					getfields(field,STable,st);
					for (i=0;i<N;i++){
						if (!st[i])
							break;
				
					}
					if (i==0){
						search_symbol_table(STable,n1,"_main",field);
					node_t *st[N];	
						
					for (i=0;i<N;i++)
						st[i]=NULL;	
					getfields(field,STable,st);
					for (i=0;i<N;i++){
						if (!st[i])
							break;
				
						}


					}

					//printf("\n");	
					if (isdigit(n1[0]))
						fprintf(printasm,"one %s,%s,%s,t%d,%d,%d,%d\n",name,n2,n1,++t_count,i,++uniq,++uniq);
					else if (isdigit(n2[0]))
						fprintf(printasm,"one %s,%s,%s,t%d,%d,%d,%d\n",name,n1,n2,++t_count,i,++uniq,++uniq);
					else if (check_record(n1))
						fprintf(printasm,"two %s,%s,%s,t%d,%d,%d,%d\n",name,n1,n2,++t_count,i,++uniq,++uniq);
					else if (check_record(n2))
						fprintf(printasm,"two %s,%s,%s,t%d,%d,%d,%d\n",name,n2,n1,++t_count,i,++uniq,++uniq);
					else
						fprintf(printasm," %s,%s,%s,t%d,%d,%d,%d\n",name,n2,n1,++t_count,i,++uniq,++uniq);
	
				}
				else if (l1 && !l2)
					fprintf(printasm," %s,%s,%s\n",root->child[0]->lex,n2,n1);
				
				else{
					if(f1 && !f2)	
						fprintf(printasm," %s,%s,%s\n",root->child[0]->lex,n1,n2);
					else if (!f1 && f2)					
						fprintf(printasm," %s,%s,%s\n",root->child[0]->lex,n2,n1);
					else
						fprintf(printasm," %s,%s,%s\n",root->child[0]->lex,n1,n2);
				}
				root->child[1]=NULL;			
				return; 
		}
		if (root->id==term || root->id==arithmeticExpression){
			if (!root->child[1]){
				//only one child exist pull up
				//printf("%s %s\n",root->lex,root->child[0]->lex);	
				strcpy(root->lex,root->child[0]->lex);   
				root->record=root->child[0]->record;
				root->child[0]=NULL;
				//root->child[1]=NULL;
				return; 
			}
			else{
				//only one child exist pull up	
				int r1=0,r2=0;
				char name[200];
				//printf("%d---\n",t_count++);
				t_count++;	
				int rec=0;
				sprintf(name,"%s%d","t",t_count);
					if (root->child[1]->child[0]->record==2){
						r1=1;
					}
					if (root->child[0]->record==2){
						r2=1;
					}

				if (check_record(root->child[1]->child[0]->lex) || check_record(root->child[0]->lex)||root->child[1]->child[0]->record || root->child[0]->record){
					
					
					if(root->child[1]->child[0]->record==2 || root->child[0]->record==2){
					root->child[0]->record=2;
					root->child[1]->child[0]->record=2;
					root->record=2;
					}
					else{
						root->child[0]->record=1;
					root->child[1]->child[0]->record=1;
					root->record=1;

					}	
					rec=1;
				}
				char n1[200],n2[200];
				int l1=0;
				int l2=0;
				strcpy(n1,root->child[0]->lex);
				strcpy(n2,root->child[1]->child[0]->lex);

				int f1=parseword(n1);
				int f2=parseword(n2);
				
				if (isdigit(n1[0]))
					l1=1;
				if (isdigit(n2[0]))
					l2=1;	
				if (root->record==1)
					rec=1;
				else if (root->record==2)
					rec=2;
				
				//printf("debug 1:%s\n",root->lex);	
				if (rec==1)
					t_size[t_count]=20;	
				print_oper(root->child[1]->lex,l1,l2,rec,f1,f2);
					
				strcpy(root->lex,name); 
				//printf("%d\n",root->child[1]->record);
				if (rec==1){
					char field[200];
					search_symbol_table(STable,n2,"_main",field);
					node_t *st[N];	
						
					for (i=0;i<N;i++)
						st[i]=NULL;	
					getfields(field,STable,st);
					for (i=0;i<N;i++){
						if (!st[i])
							break;
					}
					if (i==0){
						search_symbol_table(STable,n1,"_main",field);
					node_t *st[N];	
						
					for (i=0;i<N;i++)
						st[i]=NULL;	
					getfields(field,STable,st);
					for (i=0;i<N;i++){
						if (!st[i])
							break;
						}
					}
					//printf("\n");
					if (isdigit(n1[0])){
						fprintf(printasm,"one %s,%s,%s,t%d,%d,%d,%d\n",name,n2,n1,++t_count,i,++uniq,++uniq);
					}
					else if (isdigit(n2[0]))
						fprintf(printasm,"one %s,%s,%s,t%d,%d,%d,%d\n",name,n1,n2,++t_count,i,++uniq,++uniq);
					else if (check_record(n1))
						fprintf(printasm,"two %s,%s,%s,t%d,%d,%d,%d\n",name,n1,n2,++t_count,i,++uniq,++uniq);
					else if (check_record(n2))
						fprintf(printasm,"two %s,%s,%s,t%d,%d,%d,%d\n",name,n2,n1,++t_count,i,++uniq,++uniq);
					else
					fprintf(printasm," %s,%s,%s,t%d,%d,%d,%d\n",name,n2,n1,++t_count,i,++uniq,++uniq);
				}
				else if (l1 && !l2)
					fprintf(printasm," %s,%s,%s\n",root->lex,n2,n1);
				else{
					if (f1 && !f2)
						fprintf(printasm," %s,%s,%s\n",root->lex,n1,n2);
					else if (!f1 && f2)
						fprintf(printasm," %s,%s,%s\n	",root->lex,n2,n1);
					else
						fprintf(printasm," %s,%s,%s\n",root->lex,n1,n2);	
				}		 //different cases
				root->child[0]=NULL;
				root->child[1]=NULL;
				return; 
			}	
		}
}

void search_icg_module(node_t *root,int id){
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
		if ((*top).id==id){
			if (id==stmt){
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

