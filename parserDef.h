/*
	Sanjay Reddy S -2013A7PS189P
	Varun Vasudevan-2013A7PS103P
	Batch No: 33
*/

typedef struct Node{
	int id;
	struct Node *next;



}node;

typedef struct{
	int id;
	int token;
	char lex[200];
	int line;

}tokenInfo; 

char m[200][200];

typedef enum{
TK_ASSIGNOP=0,
TK_COMMENT,
TK_FIELDID,
TK_ID,
TK_NUM,
TK_RNUM=5,
TK_FUNID,
TK_RECORDID,
TK_WITH,
TK_PARAMETERS,
TK_END=10,
TK_WHILE,
TK_INT,
TK_REAL,
TK_TYPE,
TK_MAIN=15,
TK_GLOBAL,
TK_PARAMETER,
TK_LIST,
TK_SQL,
TK_SQR=20,
TK_INPUT,
TK_OUTPUT,
TK_SEM,
TK_COLON,
TK_DOT=25,
TK_ENDWHILE,
TK_OP,
TK_CL,
TK_IF,
TK_THEN=30,
TK_ENDIF,
TK_READ,
TK_WRITE,
TK_RETURN,
TK_PLUS=35,
TK_MINUS,
TK_MUL,
TK_DIV,
TK_CALL,
TK_RECORD=40,
TK_ENDRECORD,
TK_ELSE,
TK_AND,
TK_OR,
TK_NOT=45,
TK_LT,
TK_LE,
TK_EQ,
TK_GT,
TK_GE=50,
TK_NE,
TK_COMMA,
NO_TK=53,

program,
otherFunctions=55,
mainFunction,
stmts,
function,
input_par,
output_par=60,
parameter_list,
dataType,
remaining_list,
primitiveDatatype,
constructedDatatype=65,
typeDefinitions,
declarations,
otherStmts,
returnStmt,
typeDefinition=70,
fieldDefinitions,
fieldDefinition,
moreFields,
declaration,
global_or_not=75,
stmt,
assignmentStmt,
iterativeStmt,
conditionalStmt,
ioStmt=80,
funCallStmt,
singleOrRecId,
new_24,
arithmeticExpression,
outputParameters=85,
idList,
inputParameters,
booleanExpression,
elsePart,
allVar=90,
var,
all,
new_34,
lowPrecedenceOperators,
term=95,
highPrecedenceOperators,
factor,
expPrime,
termPrime,
logicalOp=100,
relationalOp,
optionalReturn,
more_ids,
eps,
new_32=105,
dollar=106,
DEL=199,
boolean,
complex
}tokens;

