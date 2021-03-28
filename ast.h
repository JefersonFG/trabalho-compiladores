#include "hash.h"

#pragma once

#define NUM_SONS 4

typedef struct ast_node_s {
    int type;
    hash_node_t* token;
    struct ast_node_s* sons[NUM_SONS];
} ast_node_t;

// Creates a new AST node to be added to the final tree
ast_node_t* create_ast_node(int type, hash_node_t* token, ast_node_t* son0, ast_node_t* son1, ast_node_t* son2, ast_node_t* son3);

// Prints the complete table starting from the root node passed
void print_ast_tree(ast_node_t* root);
