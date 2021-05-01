#include <stdio.h>

#include "ast.h"

#pragma once

typedef struct semantic_error_node_s {
    char* error_message;
    struct semantic_error_node_s* next_error;
} semantic_error_node_t;

extern semantic_error_node_t* global_semantic_error_list;

// Traverses de ast looking for variables that were already declared
void check_redeclared_variables(ast_node_t* node);

// Shows all the semantic errors to the user
void print_semantic_error_list(semantic_error_node_t* semantic_error_list);

// Frees memory associated with the semantic error list
void free_semantic_error_list(semantic_error_node_t* semantic_error_list);
