%{
    #include <stdio.h>
    #include <stdlib.h>
    int yyerror();
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
%token KW_FOR
%token KW_BREAK
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

%nonassoc IFX
%nonassoc KW_ELSE

%left '|' '&' 
%left '<' '>' OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_DIF 
%left '+' '-'  
%left '*' '/'
%nonassoc UMINUS

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
    | type TK_IDENTIFIER '(' function_definition_parameters ')' command_block
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
    | '-' LIT_INTEGER %prec UMINUS
    | LIT_FLOAT
    | '-' LIT_FLOAT %prec UMINUS
    | LIT_TRUE
    | LIT_FALSE
    | LIT_BYTE
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
    | expression '+' expression
    | expression '-' expression
    | expression '*' expression
    | expression '/' expression
    | expression '<' expression
    | expression '>' expression
    | expression '|' expression
    | expression '&' expression
    | expression 'v' expression
    | expression OPERATOR_LE expression
    | expression OPERATOR_GE expression
    | expression OPERATOR_EQ expression
    | expression OPERATOR_DIF expression
    | '~' expression
    | '(' expression ')'
    | TK_IDENTIFIER '(' function_call_parameters ')'
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

function_call_parameters:
    expression function_call_parameters_recursive
    |
    ;

function_call_parameters_recursive:
    ',' expression function_call_parameters_recursive
    |
    ;

flux_control:
    KW_IF '(' expression ')' KW_THEN command %prec IFX
    | KW_IF '(' expression ')' KW_THEN command KW_ELSE command
    | KW_WHILE '(' expression ')' command
    | KW_FOR '(' TK_IDENTIFIER ':' expression ',' expression ',' expression ')' command
    | KW_BREAK
    ;

%%

int yyerror() {
    fprintf(stderr, "Syntax error at line: %d\n", getLineNumber());
    exit(3);
}
