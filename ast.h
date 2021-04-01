#include <stdio.h>

#include "hash.h"

#pragma once

#define NUM_SONS 4

// Base ast symbol
#define AST_SYMBOL 1

// Types
#define AST_BOOL 2
#define AST_CHAR 3
#define AST_INT 4
#define AST_POINTER 5

// Commands
#define AST_IF 6
#define AST_IF_ELSE 7
#define AST_WHILE 8
#define AST_READ 9
#define AST_PRINT 10
#define AST_RETURN 11

// Operators
#define AST_ADD 12
#define AST_SUB 13
#define AST_MULT 14
#define AST_DIV 15
#define AST_LESSER 16
#define AST_GREATER 17
#define AST_OR 18
#define AST_AND 19
#define AST_LESSER_EQUAL 20
#define AST_GREATER_EQUAL 21
#define AST_EQUAL 22
#define AST_NOT_EQUAL 23
#define AST_NOT 24
#define AST_LEFT_ASSIGN 25
#define AST_RIGHT_ASSIGN 26
#define AST_ADDRESS 27
#define AST_DEREFERENCE 28

// Parser rules
#define AST_DECLARATION_LIST 29
#define AST_VARIABLE_DECLARATION 30
#define AST_VECTOR_DECLARATION 31
#define AST_VECTOR_INIT_DECLARATION 32
#define AST_FUNCTION_DECLARATION 33
#define AST_VECTOR_INITIAL_VALUES 34
#define AST_FUNCTION_DEFINITION_PARAMETERS 35
#define AST_FUNCTION_DEFINITION_PARAMETERS_RECURSIVE 36
#define AST_COMMAND_BLOCK 37
#define AST_COMMAND_LIST 38
#define AST_PRINT_LIST 39
#define AST_PRINT_LIST_RECURSIVE 40
#define AST_FUNCTION_CALL_PARAMETERS 41
#define AST_FUNCTION_CALL_PARAMETERS_RECURSIVE 42

// Expression specific
#define AST_ASSIGNMENT 43
#define AST_REVERSE_ASSIGNMENT 44
#define AST_VECTOR_ASSIGNMENT 45
#define AST_REVERSE_VECTOR_ASSIGNMENT 46
#define AST_VECTOR 47
#define AST_PARENTHESIS 48
#define AST_FUNCTION_CALL 49

typedef struct ast_node_s {
    int type;
    hash_node_t* symbol;
    struct ast_node_s* sons[NUM_SONS];
} ast_node_t;

// Global ast node to be used as the root of the generated tree
extern ast_node_t* global_ast_node;

// Creates a new AST node to be added to the final tree
ast_node_t* create_ast_node(int type, hash_node_t* symbol, ast_node_t* son0, ast_node_t* son1, ast_node_t* son2, ast_node_t* son3);

// Prints the complete table starting from the root node passed
void print_ast_tree(ast_node_t* root);
