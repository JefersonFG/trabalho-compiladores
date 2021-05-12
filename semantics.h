#include <stdio.h>

#include "ast.h"

#pragma once

typedef struct semantic_error_node_s {
    char* error_message;
    struct semantic_error_node_s* next_error;
} semantic_error_node_t;

extern semantic_error_node_t* global_semantic_error_list;

// Traverses the ast tree starting on the passed node looking for semantic errors in the declarations
void verify_declarations(ast_node_t* node);

// Shows all the semantic errors to the user
void print_semantic_error_list(semantic_error_node_t* semantic_error_list);

// Frees memory associated with the semantic error list
void free_semantic_error_list(semantic_error_node_t* semantic_error_list);
