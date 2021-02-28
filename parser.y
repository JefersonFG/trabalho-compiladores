%{
    #include <stdio.h>
    #include <stdlib.h>
    int yyerror();
    #define YYDEBUG 1
%}

%token KW_BOOL
%token KW_BYTE
%token KW_INT
%token KW_LONG
%token KW_FLOAT

%token KW_IF
%token KW_THEN
%token KW_ELSE
%token KW_WHILE
%token KW_READ
%token KW_PRINT
%token KW_RETURN

%token OPERATOR_LE
%token OPERATOR_GE
%token OPERATOR_EQ
%token OPERATOR_DIF
%token LEFT_ASSIGN
%token RIGHT_ASSIGN
%token TK_IDENTIFIER

%token LIT_INTEGER
%token LIT_FLOAT
%token LIT_TRUE
%token LIT_FALSE
%token LIT_BYTE
%token LIT_STRING

%token TOKEN_ERROR

%left '|' '&' 
%left '<' '>' OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_DIF 
%left '+' '-'  
%left '*' '/'

%%

program:
    declaration_list
    ;

declaration_list:
    declaration declaration_list
    |
    ;

declaration:
    type TK_IDENTIFIER ':' literal ';'
    | type TK_IDENTIFIER '[' LIT_INTEGER ']' ';'
    | type TK_IDENTIFIER '[' LIT_INTEGER ']' ':' vector_initial_values ';'
    | type TK_IDENTIFIER '(' function_parameters ')' command_block
    ;

type:
    KW_BOOL
    | KW_BYTE
    | KW_INT
    | KW_LONG
    | KW_FLOAT
    ;

literal:
    LIT_INTEGER
    | '-' LIT_INTEGER
    | LIT_FLOAT
    | '-' LIT_FLOAT
    | LIT_TRUE
    | LIT_FALSE
    | LIT_BYTE
    ;

vector_initial_values:
    literal vector_initial_values
    |
    ;

function_parameters:
    type TK_IDENTIFIER function_parameters
    ',' type TK_IDENTIFIER function_parameters
    |
    ;

command_block:
    '{' command_list '}'
    ;

command_list:
    command ';' command_list
    |
    ;

command:
    TK_IDENTIFIER ':' expression
    | TK_IDENTIFIER '[' expression ']' ':' expression
    | KW_READ TK_IDENTIFIER
    | KW_PRINT print_list
    | KW_RETURN expression
    | flux_control
    | command_block
    |
    ;

expression:
    TK_IDENTIFIER
    | TK_IDENTIFIER '[' expression ']'
    | literal
    ;

print_list:
    LIT_STRING print_list_recursive
    | expression print_list_recursive
    ;

print_list_recursive:
    LIT_STRING print_list_recursive
    | expression print_list_recursive
    |
    ;

flux_control:
    ;

%%

int yyerror() {
    fprintf(stderr, "Syntax error at line: %d\n", getLineNumber());
    exit(3);
}
