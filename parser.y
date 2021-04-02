%{
    #include <stdio.h>
    #include <stdlib.h>

    #include "ast.h"
    #include "hash.h"

    int yyerror();
    int getLineNumber(void);
%}

%union
{
    hash_node_t* symbol;
    ast_node_t* ast_node;
}

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
%token OPERATOR_NE
%token LEFT_ASSIGN
%token RIGHT_ASSIGN
%token<symbol> TK_IDENTIFIER

%token<symbol> LIT_INTEGER
%token<symbol> LIT_TRUE
%token<symbol> LIT_FALSE
%token<symbol> LIT_CHAR
%token<symbol> LIT_STRING

%type<ast_node> program;
%type<ast_node> declaration_list;
%type<ast_node> declaration;
%type<ast_node> type;
%type<ast_node> literal;
%type<ast_node> vector_initial_values;
%type<ast_node> function_definition_parameters;
%type<ast_node> function_definition_parameters_recursive;
%type<ast_node> command_block;
%type<ast_node> command_list;
%type<ast_node> command;
%type<ast_node> expression;
%type<ast_node> print_list;
%type<ast_node> print_list_recursive;
%type<ast_node> function_call_parameters;
%type<ast_node> function_call_parameters_recursive;
%type<ast_node> flux_control;

%token TOKEN_ERROR

%left '|' '&' 
%left '<' '>' OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_DIF 
%left '+' '-'  
%left '*' '/'
%left '~' '$' '#'

%%

program:
    declaration_list { $$ = $1; print_ast_tree($1); global_ast_node = $$; }
    ;

declaration_list:
    declaration declaration_list { $$ = create_ast_node(AST_DECLARATION_LIST, 0, $1, $2, 0, 0); }
    | { $$ = 0; }
    ;

declaration:
    type TK_IDENTIFIER ':' literal ';' { $$ = create_ast_node(AST_VARIABLE_DECLARATION, $2, $1, $4, 0, 0); }
    | type '[' LIT_INTEGER ']' TK_IDENTIFIER ';' { $$ = create_ast_node(AST_VECTOR_DECLARATION, $5, $1, create_ast_node(AST_VECTOR_SIZE, $3, 0, 0, 0, 0), 0, 0); }
    | type '[' LIT_INTEGER ']' TK_IDENTIFIER ':' vector_initial_values ';' { $$ = create_ast_node(AST_VECTOR_INIT_DECLARATION, $5, $1, create_ast_node(AST_VECTOR_SIZE, $3, 0, 0, 0, 0), $7, 0); }
    | type TK_IDENTIFIER '(' function_definition_parameters ')' command_block ';' { $$ = create_ast_node(AST_FUNCTION_DECLARATION, $2, $1, $4, $6, 0); }
    ;

type:
    KW_BOOL { $$ = create_ast_node(AST_BOOL, 0, 0, 0, 0, 0); }
    | KW_CHAR { $$ = create_ast_node(AST_CHAR, 0, 0, 0, 0, 0); }
    | KW_INT { $$ = create_ast_node(AST_INT, 0, 0, 0, 0, 0); }
    | KW_POINTER { $$ = create_ast_node(AST_POINTER, 0, 0, 0, 0, 0); }
    ;

literal:
    LIT_INTEGER { $$ = create_ast_node(AST_SYMBOL, $1, 0, 0, 0, 0); }
    | '-' LIT_INTEGER { $$ = create_ast_node(AST_SYMBOL, $2, 0, 0, 0, 0); }
    | LIT_TRUE { $$ = create_ast_node(AST_SYMBOL, $1, 0, 0, 0, 0); }
    | LIT_FALSE { $$ = create_ast_node(AST_SYMBOL, $1, 0, 0, 0, 0); }
    | LIT_CHAR { $$ = create_ast_node(AST_SYMBOL, $1, 0, 0, 0, 0); }
    ;

vector_initial_values:
    literal vector_initial_values { $$ = create_ast_node(AST_VECTOR_INITIAL_VALUES, 0, $1, $2, 0, 0); }
    | { $$ = 0; }
    ;

function_definition_parameters:
    type TK_IDENTIFIER function_definition_parameters_recursive { $$ = create_ast_node(AST_FUNCTION_DEFINITION_PARAMETERS, $2, $1, $3, 0, 0); }
    | { $$ = 0; }
    ;

function_definition_parameters_recursive:
    ',' type TK_IDENTIFIER function_definition_parameters_recursive { $$ = create_ast_node(AST_FUNCTION_DEFINITION_PARAMETERS_RECURSIVE, $3, $2, $4, 0, 0); }
    | { $$ = 0; }
    ;

command_block:
    '{' command_list '}' { $$ = create_ast_node(AST_COMMAND_BLOCK, 0, $2, 0, 0, 0); }
    ;

command_list:
    command ';' command_list { $$ = create_ast_node(AST_COMMAND_LIST, 0, $1, $3, 0, 0); }
    | { $$ = 0; }
    ;

command:
    TK_IDENTIFIER LEFT_ASSIGN expression { $$ = create_ast_node(AST_ASSIGNMENT, $1, $3, 0, 0, 0); }
    | expression RIGHT_ASSIGN TK_IDENTIFIER { $$ = create_ast_node(AST_REVERSE_ASSIGNMENT, $3, $1, 0, 0, 0); }
    | TK_IDENTIFIER '[' expression ']' LEFT_ASSIGN expression { $$ = create_ast_node(AST_VECTOR_ASSIGNMENT, $1, $3, $6, 0, 0); }
    | expression RIGHT_ASSIGN TK_IDENTIFIER '[' expression ']' { $$ = create_ast_node(AST_REVERSE_VECTOR_ASSIGNMENT, $3, $1, $5, 0, 0); }
    | KW_READ TK_IDENTIFIER { $$ = create_ast_node(AST_READ, $2, 0, 0, 0, 0); }
    | KW_PRINT print_list { $$ = create_ast_node(AST_PRINT, 0, $2, 0, 0, 0); }
    | KW_RETURN expression { $$ = create_ast_node(AST_RETURN, 0, $2, 0, 0, 0); }
    | flux_control { $$ = $1; }
    | command_block { $$ = $1; }
    | { $$ = 0; }
    ;

expression:
    TK_IDENTIFIER { $$ = create_ast_node(AST_SYMBOL, $1, 0, 0, 0, 0); }
    | TK_IDENTIFIER '[' expression ']' { $$ = create_ast_node(AST_VECTOR, $1, $3, 0, 0, 0); }
    | literal { $$ = $1; }
    | expression '+' expression { $$ = create_ast_node(AST_ADD, 0, $1, $3, 0, 0); }
    | expression '-' expression { $$ = create_ast_node(AST_SUB, 0, $1, $3, 0, 0); }
    | expression '*' expression { $$ = create_ast_node(AST_MULT, 0, $1, $3, 0, 0); }
    | expression '/' expression { $$ = create_ast_node(AST_DIV, 0, $1, $3, 0, 0); }
    | expression '<' expression { $$ = create_ast_node(AST_LESSER, 0, $1, $3, 0, 0); }
    | expression '>' expression { $$ = create_ast_node(AST_GREATER, 0, $1, $3, 0, 0); }
    | expression '|' expression { $$ = create_ast_node(AST_OR, 0, $1, $3, 0, 0); }
    | expression '&' expression { $$ = create_ast_node(AST_AND, 0, $1, $3, 0, 0); }
    | expression OPERATOR_LE expression { $$ = create_ast_node(AST_LESSER_EQUAL, 0, $1, $3, 0, 0); }
    | expression OPERATOR_GE expression { $$ = create_ast_node(AST_GREATER_EQUAL, 0, $1, $3, 0, 0); }
    | expression OPERATOR_EQ expression { $$ = create_ast_node(AST_EQUAL, 0, $1, $3, 0, 0); }
    | expression OPERATOR_NE expression { $$ = create_ast_node(AST_NOT_EQUAL, 0, $1, $3, 0, 0); }
    | '~' expression { $$ = create_ast_node(AST_NOT, 0, $2, 0, 0, 0); }
    | '$' expression { $$ = create_ast_node(AST_ADDRESS, 0, $2, 0, 0, 0); }
    | '#' expression { $$ = create_ast_node(AST_DEREFERENCE, 0, $2, 0, 0, 0); }
    | '(' expression ')' { $$ = create_ast_node(AST_PARENTHESIS, 0, $2, 0, 0, 0); }
    | TK_IDENTIFIER '(' function_call_parameters ')' { $$ = create_ast_node(AST_FUNCTION_CALL, $1, $3, 0, 0, 0); }
    ;

print_list:
    LIT_STRING print_list_recursive { $$ = create_ast_node(AST_PRINT_LIST, 0, create_ast_node(AST_SYMBOL, $1, 0, 0, 0, 0), $2, 0, 0); }
    | expression print_list_recursive { $$ = create_ast_node(AST_PRINT_LIST, 0, $1, $2, 0, 0); }
    ;

print_list_recursive:
    ',' LIT_STRING print_list_recursive { $$ = create_ast_node(AST_PRINT_LIST_RECURSIVE, 0, create_ast_node(AST_SYMBOL, $2, 0, 0, 0, 0), $3, 0, 0); }
    | ',' expression print_list_recursive { $$ = create_ast_node(AST_PRINT_LIST_RECURSIVE, 0, $2, $3, 0, 0); }
    | { $$ = 0; }
    ;

function_call_parameters:
    expression function_call_parameters_recursive { $$ = create_ast_node(AST_FUNCTION_CALL_PARAMETERS, 0, $1, $2, 0, 0); }
    | { $$ = 0; }
    ;

function_call_parameters_recursive:
    ',' expression function_call_parameters_recursive { $$ = create_ast_node(AST_FUNCTION_CALL_PARAMETERS_RECURSIVE, 0, $2, $3, 0, 0); }
    | { $$ = 0; }
    ;

flux_control:
    KW_IF '(' expression ')' KW_THEN command { $$ = create_ast_node(AST_IF, 0, $3, $6, 0, 0); }
    | KW_IF '(' expression ')' KW_THEN command KW_ELSE command { $$ = create_ast_node(AST_IF_ELSE, 0, $3, $6, $8, 0); }
    | KW_WHILE '(' expression ')' command { $$ = create_ast_node(AST_WHILE, 0, $3, $5, 0, 0); }
    ;

%%

int yyerror() {
    fprintf(stderr, "Syntax error at line: %d\n", getLineNumber());
    exit(3);
}
