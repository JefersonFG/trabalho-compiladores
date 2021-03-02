%{
    #include <stdio.h>
    #include <stdlib.h>
    int yyerror();
%}

%token KW_BOOL
%token KW_CHAR
%token KW_INT
%token KW_POINTER

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
%token LIT_TRUE
%token LIT_FALSE
%token LIT_CHAR
%token LIT_STRING

%token TOKEN_ERROR

%left '|' '&' 
%left '<' '>' OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_DIF 
%left '+' '-'  
%left '*' '/'
%left '~' '$' '#'

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
    | type '[' LIT_INTEGER ']' TK_IDENTIFIER ';'
    | type '[' LIT_INTEGER ']' TK_IDENTIFIER ':' vector_initial_values ';'
    | type TK_IDENTIFIER '(' function_definition_parameters ')' command_block ';'
    ;

type:
    KW_BOOL
    | KW_CHAR
    | KW_INT
    | KW_POINTER
    ;

literal:
    LIT_INTEGER
    | '-' LIT_INTEGER
    | LIT_TRUE
    | LIT_FALSE
    | LIT_CHAR
    ;

vector_initial_values:
    literal vector_initial_values
    |
    ;

function_definition_parameters:
    type TK_IDENTIFIER function_definition_parameters_recursive
    |
    ;

function_definition_parameters_recursive:
    ',' type TK_IDENTIFIER function_definition_parameters_recursive
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
    TK_IDENTIFIER LEFT_ASSIGN expression
    | expression RIGHT_ASSIGN TK_IDENTIFIER
    | TK_IDENTIFIER '[' expression ']' LEFT_ASSIGN expression
    | expression RIGHT_ASSIGN TK_IDENTIFIER '[' expression ']'
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
    | expression '+' expression
    | expression '-' expression
    | expression '*' expression
    | expression '/' expression
    | expression '<' expression
    | expression '>' expression
    | expression '|' expression
    | expression '&' expression
    | expression OPERATOR_LE expression
    | expression OPERATOR_GE expression
    | expression OPERATOR_EQ expression
    | expression OPERATOR_DIF expression
    | '~' expression
    | '$' expression
    | '#' expression
    | '(' expression ')'
    | TK_IDENTIFIER '(' function_call_parameters ')'
    ;

print_list:
    LIT_STRING print_list_recursive
    | expression print_list_recursive
    ;

print_list_recursive:
    ',' LIT_STRING print_list_recursive
    | ',' expression print_list_recursive
    |
    ;

function_call_parameters:
    expression function_call_parameters_recursive
    |
    ;

function_call_parameters_recursive:
    ',' expression function_call_parameters_recursive
    |
    ;

flux_control:
    KW_IF '(' expression ')' KW_THEN command
    | KW_IF '(' expression ')' KW_THEN command KW_ELSE command
    | KW_WHILE '(' expression ')' command
    ;

%%

int yyerror() {
    fprintf(stderr, "Syntax error at line: %d\n", getLineNumber());
    exit(3);
}
