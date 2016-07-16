/*
	Sanjay Reddy S -2013A7PS189P
	Varun Vasudevan-2013A7PS103P
	Batch No: 33
*/

#include "parserDef.h"
#include "lexerDef.h"

int tran[M][Nm];
int final[M]={0};
void commentless(char filename[]){
	FILE *fp=fopen(filename,"r+");
	if (!fp){
		printf("file could not be opened\n");
		return;
	}
	char ch;	
	while(!feof(fp)){
		fscanf(fp,"%c",&ch);
		if (ch=='%'){
			while (ch!='\n')
				fscanf(fp,"%c",&ch);
			
		}
		printf("%c",ch);

	}

	fclose(fp);

}


int get_token_index(int state,char lex[])
{
	int idy;
	switch(state){
		case 2:{idy=TK_PLUS;break;}
		case 3:{idy=TK_MINUS;break;}
		case 4:{idy=TK_MUL;break;}
		case 5:{idy=TK_DIV;break;}
		case 6:{idy=TK_NOT;break;}
		case 7:{idy=TK_SEM;break;}
		case 8:{idy=TK_DOT;break;}
		case 9:{idy=TK_SQR;break;}
		case 10:{idy=TK_SQL;break;}
		case 11:{idy=TK_CL;break;}
		case 12:{idy=TK_OP;break;}
		case 13:{idy=TK_COLON;break;}
		case 16:{idy=TK_AND;break;}
		case 19:{idy=TK_OR;break;}
		case 21:{idy=TK_NE;break;}
		case 23:{idy=TK_EQ;break;}
		case 24:{idy=TK_GT;break;}
		case 25:{idy=TK_GE;break;}
		case 26:{idy=TK_LT;break;}
		case 29:{idy=TK_ASSIGNOP;break;}
		case 30:{idy=TK_LE;break;}
		case 33:{idy=TK_RECORDID;break;}
		case 34:
		case 35:{idy=TK_NUM;break;}
		case 38:{idy=TK_RNUM;break;}
		case 43:{idy=TK_MAIN;break;}
		case 40:
		case 41:
		case 42:
		case 44:
		case 45:
		case 46:{idy=TK_FUNID;break;}
		case 49:
		case 50:
		case 51:{idy=TK_ID;break;}
		case 52:{idy=TK_COMMENT;break;}
		case 53:{idy=TK_COMMA;break;}
		case 48:
		case 54:
		case 55:{idy=TK_FIELDID;break;}
		default:
		idy=NO_TK;
		break;
	}
	if (idy==TK_FIELDID){
		if (!strcmp(lex,"parameter"))
			idy=TK_PARAMETER;
		else if (!strcmp(lex,"parameters"))
			idy=TK_PARAMETERS;
		else if (!strcmp(lex,"end"))
			idy=TK_END;
		else if (!strcmp(lex,"while"))
			idy=TK_WHILE;
		else if (!strcmp(lex,"int"))
			idy=TK_INT;
		else if (!strcmp(lex,"real"))
			idy=TK_REAL;
		else if (!strcmp(lex,"type"))
			idy=TK_TYPE;
		else if (!strcmp(lex,"global"))
			idy=TK_GLOBAL;
		else if (!strcmp(lex,"list"))
			idy=TK_LIST;
		else if (!strcmp(lex,"input"))
			idy=TK_INPUT;
		else if (!strcmp(lex,"output"))
			idy=TK_OUTPUT;
		else if (!strcmp(lex,"endwhile"))
			idy=TK_ENDWHILE;
		else if (!strcmp(lex,"call"))
			idy=TK_CALL;
		else if (!strcmp(lex,"record"))
			idy=TK_RECORD;
		else if (!strcmp(lex,"endrecord"))
			idy=TK_ENDRECORD;
		else if (!strcmp(lex,"if"))
			idy=TK_IF;
		else if (!strcmp(lex,"then"))
			idy=TK_THEN;
		else if (!strcmp(lex,"endif"))
			idy=TK_ENDIF;
		else if (!strcmp(lex,"else"))
			idy=TK_ELSE;
		else if (!strcmp(lex,"read"))
			idy=TK_READ;		
		else if (!strcmp(lex,"write"))
			idy=TK_WRITE;
		else if (!strcmp(lex,"return"))
			idy=TK_RETURN;
		else if (!strcmp(lex,"with"))
			idy=TK_WITH;
	

	}
	return idy;
}



void initialise(){ //set the transitions corresponding to all states as 0:dead state and later change	

	memset(tran, 0, sizeof(tran[0][0]) * M * Nm);

}

int decide_ch_acc(char ch)
{
	int i=(int)ch;
	if((i>=65&&i<=90)||(i>=97&&i<=122)||(i>=48&&i<=57))
	{return 1;}
	return -1;

}

int unknownsymbol(char symbol){//For Error recognition an unknown symbol is used 1:legal symbol | 0:unknown symbol
	int flag=0;
	if (symbol>='a' && symbol<='z')
		flag=1;
	else if (symbol>='A' && symbol<='Z')
		flag=1;
	else if (symbol>='0' && symbol<='9')
		flag=1;
	switch(symbol){
		case '%':{flag=1;break;}
		case '+':{flag=1;break;}
		case '-':{flag=1;break;}
		case '*':{flag=1;break;}
		case '_':{flag=1;break;}
		case '[':{flag=1;break;}
		case ']':{flag=1;break;}
		case '<':{flag=1;break;}
		case '>':{flag=1;break;}
		case '(':{flag=1;break;}
		case ')':{flag=1;break;}
		case '=':{flag=1;break;}
		case '#':{flag=1;break;}
		case '@':{flag=1;break;}
		case '&':{flag=1;break;}
		case ';':{flag=1;break;}
		case ':':{flag=1;break;}
		case '.':{flag=1;break;}
		case '/':{flag=1;break;}
		case '~':{flag=1;break;}
		case '!':{flag=1;break;}
		case '$':{flag=1;break;}
		


	}
	int i=symbol;
	 if((i>=123&&i<=126)||(i==91||i==93||i==95)||(i>=58&&i<=62)||(i==64)||(i>=40&&i<=46)||(i==38||i==37||i==35||i==33||i==32)||(i==0))
	{return 1;}
	else if((i==13)||(i==9)||(i==10))
	{return 1;}
	
	

	return flag;
}

void insert_dfa(int initial_state,char symbol,int final_state){
	
	tran[initial_state][symbol]=final_state;


}

void construct_table(){//The table is populated here by following the transitions in the DFA
	char ch;
	int i;
	
	insert_dfa(1,'+',2);    
	insert_dfa(1,'-',3);
	insert_dfa(1,'*',4);
	insert_dfa(1,'/',5);
	insert_dfa(1,'~',6);
	insert_dfa(1,';',7);
	insert_dfa(1,'.',8);
	insert_dfa(1,']',9);
	insert_dfa(1,'[',10);
	insert_dfa(1,')',11);
	insert_dfa(1,'(',12);
	insert_dfa(1,':',13);
	insert_dfa(1,'%',52);
	insert_dfa(1,',',53);

	insert_dfa(1,'&',14);insert_dfa(14,'&',15);insert_dfa(15,'&',16);
	insert_dfa(1,'@',17);insert_dfa(17,'@',18);insert_dfa(18,'@',19);
	insert_dfa(1,'!',20);insert_dfa(20,'=',21);
	insert_dfa(1,'=',22);insert_dfa(22,'=',23);
	insert_dfa(1,'>',24);insert_dfa(24,'=',25);
	insert_dfa(1,'<',26);insert_dfa(26,'-',27);insert_dfa(27,'-',28);insert_dfa(28,'-',29);insert_dfa(26,'=',30);
	
	insert_dfa(1,'#',31);//for TK_RECORDID
	for(i=97;i<=122;i++)
	{
		ch=(char)i;
		//insert_dfa(1,ch,31);
		insert_dfa(31,ch,32);
		insert_dfa(32,ch,33);
		insert_dfa(33,ch,33);
	}

	insert_dfa(34,'.',36);
	insert_dfa(35,'.',36);//for TK_INT && TK_RNUM
	for(i=48;i<=57;i++)
	{
		ch=(char)i;
		insert_dfa(1,ch,34);
		insert_dfa(34,ch,35);
		insert_dfa(35,ch,35);
		insert_dfa(36,ch,37);
		insert_dfa(37,ch,38);
	}
	
	insert_dfa(1,'_',39);insert_dfa(39,'m',40);insert_dfa(40,'a',41);insert_dfa(41,'i',42);insert_dfa(42,'n',43);//for TK_MAIN && TK_FUNID
	for(i=65;i<=90;i++)
	{
		ch=(char)i;
		insert_dfa(39,ch,44);
		insert_dfa(44,ch,45);
		insert_dfa(45,ch,45);
		ch=(char)(i+32);
		insert_dfa(44,ch,45);
		insert_dfa(45,ch,45);
		if(ch!='m')
		{
		insert_dfa(39,ch,44);
		}
	}
	for(i=48;i<=57;i++)
	{
		ch=(char)i;
		insert_dfa(44,ch,46);
		insert_dfa(45,ch,46);
		insert_dfa(46,ch,46);
	}
	
	insert_dfa(1,'\0',47);//47 corresponds to \0 and \n and ' '
	insert_dfa(1,' ',47);
	insert_dfa(1,'\n',47);
	insert_dfa(1,'\t',47);
	insert_dfa(1,13,47);
	//insert_dfa(1,'$',101);
	//insert_dfa(1,'b',48);
	for(i=50;i<=55;i++)//for TK_ID
	{
		ch=(char)i;
		insert_dfa(48,ch,49);
		insert_dfa(50,ch,51);
		insert_dfa(49,ch,51);
		insert_dfa(51,ch,51);
	}
	for(i=98;i<=100;i++)
	{
		ch=(char)i;
		insert_dfa(1,ch,48);
		insert_dfa(49,ch,50);
		insert_dfa(50,ch,50);
	}
	
	
	for(i=97;i<=122;i++)//for TK_FIELDID
	{
		ch=(char)i;
		insert_dfa(54,ch,55);
		insert_dfa(55,ch,55);
		insert_dfa(48,ch,54);
		if(i<98||i>100)
		{insert_dfa(1,ch,54);}
	}	
	
	int arr[43]={1,2,3,4,5,6,7,8,9,10,11,12,13,16,19,21,23,24,25,26,29,30,33,35,38,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,34,101};
	for(i=0;i<43;i++){
		final[arr[i]]=1;
	}		
	
	
}


int getnextstate(int current_state,char symbol){

	return tran[current_state][symbol];

}

int state=1;
int current=0,next=0;
int prev_acc=0;
int ans=0;
int token_index=0;
int buffer_empty=0;
int line=1;
int error=0;


int getStream(FILE *fp,char buffer[],int size){
//Stores 'size' number of characters from the file into the buffer
	strcpy(buffer,"");
	if (feof(fp)){
		//printf("empty buffer\n");
		//end_of_file=1;
		buffer_empty=1;
		return -1;
	}
	int i=0;
	while (!feof(fp)){
		if (i>=size)
			break;
		char ch;
		fscanf(fp,"%c",&ch);
		
		if (ch=='%'){
			while (ch!='\n'){
				fscanf(fp,"%c",&ch);
			}
			//line++;
		}

		if (!unknownsymbol(ch)){
			printf("unknown character:%c\n",ch);
			ch=' ';
			error=1;


		}
		
		buffer[i++]=ch;
	}
	//buffer[i]='\0';
	//printf("apl:%s\n",buffer);  //for debugging purposes only
	if (feof(fp)){
		//printf("empty buffer\n");
		//end_of_file=1;
		buffer_empty=1;
		return -1;
	}
	return i;	

}

int getNextToken(FILE *fp,char buffer[],char next_token[]){

while (1){
	if (next==BUFFER_SIZE){
		next=0;
		int buffer_curr=getStream(fp,buffer,BUFFER_SIZE);
		if (buffer_curr==-1 || buffer_curr==0){
			
			return -1;
		}
	}

	state=getnextstate(state,buffer[next]);

	if (final[state]){
		prev_acc=1;
		ans=state;	
	}
	
	if (prev_acc==1 && state==0){

		next_token[token_index]='\0';

		if (!strcmp(next_token,"\n"))
			line++;	
		token_index=0;
		current=next;
		state=1;
		prev_acc=0;

		break;
		
	}	
	else if (state==0 ){
		next_token[token_index++]=buffer[next++];
				
		next_token[token_index]='\0';
		state=1;
		prev_acc=0;
		current=next;
		token_index=0;

		return -1;
	}
	 

	next_token[token_index++]=buffer[next];
	next++;
	}

return ans;



}




