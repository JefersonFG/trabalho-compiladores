#include "ast.h"

ast_node_t* create_ast_node(int type, hash_node_t* token, ast_node_t* son0, ast_node_t* son1, ast_node_t* son2, ast_node_t* son3) {
    ast_node_t* new_node = malloc(sizeof(ast_node_t));
    if (!new_node)
        return 0;
    
    new_node->type = type;
    new_node->token = token;
    new_node->sons[0] = son0;
    new_node->sons[1] = son1;
    new_node->sons[2] = son2;
    new_node->sons[3] = son3;

    return new_node;
}

void print_ast_tree(ast_node_t* root) {
    // TODO: Implementar print da árvore
    return;
}
