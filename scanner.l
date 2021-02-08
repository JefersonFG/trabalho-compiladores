%{
#include "tokens.h"
int is_running = 1;
%}

%%

char return KW_CHAR; /* Palavras reservadas */
int return KW_INT;
bool return KW_BOOL;
pointer return KW_POINTER;

if return KW_IF; /* Palavras reservadas */
then return KW_THEN;
else return KW_ELSE;
while return KW_WHILE;
read return KW_READ;
print return KW_PRINT;
return return KW_RETURN;

"," return yytext[0]; /* Caracteres especiais */
";" return yytext[0];
":" return yytext[0];
"(" return yytext[0];
")" return yytext[0];
"[" return yytext[0];
"]" return yytext[0];
"{" return yytext[0];
"}" return yytext[0];
"+" return yytext[0];
"-" return yytext[0];
"*" return yytext[0];
"/" return yytext[0];
"<" return yytext[0];
">" return yytext[0];
"|" return yytext[0];
"&" return yytext[0];
"~" return yytext[0];
"$" return yytext[0];
"#" return yytext[0];

"<=" return OPERATOR_LE; /* Operadores compostos */
">=" return OPERATOR_GE;
"==" return OPERATOR_EQ;
"!=" return OPERATOR_DIF;
"<-" return LEFT_ASSIGN;
"->" return RIGHT_ASSIGN;

[0-9]+ return LIT_INTEGER; /* Literais */
'\\?.' return LIT_CHAR;
\"(\\.|[^"\\])*\" return LIT_STRING;
true return LIT_TRUE;
false return LIT_FALSE;

[a-z|A-Z|_][a-z|A-Z|0-9|_]* return TK_IDENTIFIER;

. return TOKEN_ERROR;

%%

int yywrap(void) {
    is_running = 0;
    return 1;
}

int isRunning() {
    return is_running;
}
