#include "ast.h"

ast_node_t* global_ast_node = 0;

ast_node_t* create_ast_node(int type, hash_node_t* symbol, ast_node_t* son0, ast_node_t* son1, ast_node_t* son2, ast_node_t* son3) {
    ast_node_t* new_node = malloc(sizeof(ast_node_t));
    if (!new_node)
        return 0;
    
    new_node->type = type;
    new_node->symbol = symbol;
    new_node->sons[0] = son0;
    new_node->sons[1] = son1;
    new_node->sons[2] = son2;
    new_node->sons[3] = son3;

    return new_node;
}

void print_ast_tree_recursive(ast_node_t* node, int level) {
    if (!node)
        return;

    int i = 0;

    for (i = 0; i < level; i++) {
        fprintf(stdout, "-> ");
    }

    switch (node->type) {
        case AST_SYMBOL:
            fprintf(stdout, "AST_SYMBOL");
            break;
        case AST_BOOL:
            fprintf(stdout, "AST_BOOL");
            break;
        case AST_CHAR:
            fprintf(stdout, "AST_CHAR");
            break;
        case AST_INT:
            fprintf(stdout, "AST_INT");
            break;
        case AST_POINTER:
            fprintf(stdout, "AST_POINTER");
            break;
        case AST_IF:
            fprintf(stdout, "AST_IF");
            break;
        case AST_IF_ELSE:
            fprintf(stdout, "AST_IF_ELSE");
            break;
        case AST_WHILE:
            fprintf(stdout, "AST_WHILE");
            break;
        case AST_READ:
            fprintf(stdout, "AST_READ");
            break;
        case AST_PRINT:
            fprintf(stdout, "AST_PRINT");
            break;
        case AST_RETURN:
            fprintf(stdout, "AST_RETURN");
            break;
        case AST_ADD:
            fprintf(stdout, "AST_ADD");
            break;
        case AST_SUB:
            fprintf(stdout, "AST_SUB");
            break;
        case AST_MULT:
            fprintf(stdout, "AST_MULT");
            break;
        case AST_DIV:
            fprintf(stdout, "AST_DIV");
            break;
        case AST_LESSER:
            fprintf(stdout, "AST_LESSER");
            break;
        case AST_GREATER:
            fprintf(stdout, "AST_GREATER");
            break;
        case AST_OR:
            fprintf(stdout, "AST_OR");
            break;
        case AST_AND:
            fprintf(stdout, "AST_AND");
            break;
        case AST_LESSER_EQUAL:
            fprintf(stdout, "AST_LESSER_EQUAL");
            break;
        case AST_GREATER_EQUAL:
            fprintf(stdout, "AST_GREATER_EQUAL");
            break;
        case AST_EQUAL:
            fprintf(stdout, "AST_EQUAL");
            break;
        case AST_NOT_EQUAL:
            fprintf(stdout, "AST_NOT_EQUAL");
            break;
        case AST_NOT:
            fprintf(stdout, "AST_NOT");
            break;
        case AST_LEFT_ASSIGN:
            fprintf(stdout, "AST_LEFT_ASSIGN");
            break;
        case AST_RIGHT_ASSIGN:
            fprintf(stdout, "AST_RIGHT_ASSIGN");
            break;
        case AST_ADDRESS:
            fprintf(stdout, "AST_ADDRESS");
            break;
        case AST_DEREFERENCE:
            fprintf(stdout, "AST_DEREFERENCE");
            break;
        case AST_DECLARATION_LIST:
            fprintf(stdout, "AST_DECLARATION_LIST");
            break;
        case AST_VARIABLE_DECLARATION:
            fprintf(stdout, "AST_VARIABLE_DECLARATION");
            break;
        case AST_VECTOR_DECLARATION:
            fprintf(stdout, "AST_VECTOR_DECLARATION");
            break;
        case AST_VECTOR_INIT_DECLARATION:
            fprintf(stdout, "AST_VECTOR_INIT_DECLARATION");
            break;
        case AST_FUNCTION_DECLARATION:
            fprintf(stdout, "AST_FUNCTION_DECLARATION");
            break;
        case AST_VECTOR_INITIAL_VALUES:
            fprintf(stdout, "AST_VECTOR_INITIAL_VALUES");
            break;
        case AST_FUNCTION_DEFINITION_PARAMETERS:
            fprintf(stdout, "AST_FUNCTION_DEFINITION_PARAMETERS");
            break;
        case AST_FUNCTION_DEFINITION_PARAMETERS_RECURSIVE:
            fprintf(stdout, "AST_FUNCTION_DEFINITION_PARAMETERS_RECURSIVE");
            break;
        case AST_COMMAND_BLOCK:
            fprintf(stdout, "AST_COMMAND_BLOCK");
            break;
        case AST_COMMAND_LIST:
            fprintf(stdout, "AST_COMMAND_LIST");
            break;
        case AST_PRINT_LIST:
            fprintf(stdout, "AST_PRINT_LIST");
            break;
        case AST_PRINT_LIST_RECURSIVE:
            fprintf(stdout, "AST_PRINT_LIST_RECURSIVE");
            break;
        case AST_FUNCTION_CALL_PARAMETERS:
            fprintf(stdout, "AST_FUNCTION_CALL_PARAMETERS");
            break;
        case AST_FUNCTION_CALL_PARAMETERS_RECURSIVE:
            fprintf(stdout, "AST_FUNCTION_CALL_PARAMETERS_RECURSIVE");
            break;
        case AST_ASSIGNMENT:
            fprintf(stdout, "AST_ASSIGNMENT");
            break;
        case AST_REVERSE_ASSIGNMENT:
            fprintf(stdout, "AST_REVERSE_ASSIGNMENT");
            break;
        case AST_VECTOR_ASSIGNMENT:
            fprintf(stdout, "AST_VECTOR_ASSIGNMENT");
            break;
        case AST_REVERSE_VECTOR_ASSIGNMENT:
            fprintf(stdout, "AST_REVERSE_VECTOR_ASSIGNMENT");
            break;
        case AST_VECTOR:
            fprintf(stdout, "AST_VECTOR");
            break;
        case AST_PARENTHESIS:
            fprintf(stdout, "AST_PARENTHESIS");
            break;
        case AST_FUNCTION_CALL:
            fprintf(stdout, "AST_FUNCTION_CALL");
            break;
    }

    if (node->symbol)
        fprintf(stdout, " - %s\n", node->symbol->value);
    else
        fprintf(stdout, "\n");

    for (i = 0; i < NUM_SONS; i++)
        print_ast_tree_recursive(node->sons[i], level + 1);
}

void print_ast_tree(ast_node_t* root) {
    if (!root) {
        fprintf(stderr, "Empty root node\n");
        return;
    }

    print_ast_tree_recursive(root, 0);
}
