%{
#include "tokens.h"
#include "hash.h"

int is_running = 1;
int line_number = 1;

%}

%x COMMENT

%%

"\n" line_number++; /* Contagem de linhas */

[ \t] /* Ignora whitespace */

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

[0-9]+ {insert_hash_value(global_hash_table, yytext, LIT_INTEGER); return LIT_INTEGER;} /* Literais */
'\\?.' {insert_hash_value(global_hash_table, yytext, LIT_CHAR); return LIT_CHAR;}
\"(\\.|[^"\\])*\" {insert_hash_value(global_hash_table, yytext, LIT_STRING); return LIT_STRING;}
true return LIT_TRUE;
false return LIT_FALSE;

[a-z|A-Z|_][a-z|A-Z|0-9|_]* {insert_hash_value(global_hash_table, yytext, TK_IDENTIFIER); return TK_IDENTIFIER;}

"//".* /* Comentários de uma linha */
"/*" BEGIN(COMMENT); /* Comentários de várias linhas */
<COMMENT>.
<COMMENT>"\n" line_number++;
<COMMENT>"*/" BEGIN(INITIAL);

. return TOKEN_ERROR;

%%

void initMe(void) {
    int hash_size = 20;
    global_hash_table = create_hash_table(hash_size);
}

int yywrap(void) {
    is_running = 0;
    return 1;
}

int isRunning(void) {
    return is_running;
}

int getLineNumber(void) {
    return line_number;
}
