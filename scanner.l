%{
#include "y.tab.h"
#include "hash.h"

int is_running = 1;
int line_number = 1;

%}

%x COMMENT

%%

"\n" line_number++; /* Contagem de linhas */

[ \t] /* Ignora whitespace */

bool return KW_BOOL; /* Palavras reservadas */
byte return KW_BYTE;
int return KW_INT;
long return KW_LONG;
float return KW_FLOAT;

if return KW_IF; /* Palavras reservadas */
then return KW_THEN;
else return KW_ELSE;
while return KW_WHILE;
for return KW_FOR;
break return KW_BREAK;
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

"v" return yytext[0]; /* TODO: Esse é o operador lógico OR dessa linguagem? */

"<=" return OPERATOR_LE; /* Operadores compostos */
">=" return OPERATOR_GE;
"==" return OPERATOR_EQ;
"!=" return OPERATOR_DIF;
"<-" return LEFT_ASSIGN;
"->" return RIGHT_ASSIGN;

[0-9]+ {insert_hash_value(global_hash_table, yytext, LIT_INTEGER); return LIT_INTEGER;} /* Literais */
[0-9]+\.[0-9]+ {insert_hash_value(global_hash_table, yytext, LIT_FLOAT); return LIT_FLOAT;}
'\\?.' {insert_hash_value(global_hash_table, yytext, LIT_BYTE); return LIT_BYTE;}
\"(\\.|[^"\\])*\" {insert_hash_value(global_hash_table, yytext, LIT_STRING); return LIT_STRING;}
true|TRUE return LIT_TRUE;
false|FALSE return LIT_FALSE;

[a-z|A-Z|_][a-z|A-Z|0-9|_]* {insert_hash_value(global_hash_table, yytext, TK_IDENTIFIER); return TK_IDENTIFIER;}

"//".* /* Comentários de uma linha */
"/*" BEGIN(COMMENT); /* Comentários de várias linhas */
<COMMENT>.
<COMMENT>"\n" line_number++;
<COMMENT>"*/" BEGIN(INITIAL);

. return TOKEN_ERROR;

%%

void initMe(void) {
    int hash_size = 1000;
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
