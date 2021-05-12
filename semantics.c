#include "semantics.h"

#include <strings.h>

semantic_error_node_t* global_semantic_error_list = 0;

// Adds an error to the list of semantic errors
void add_semantic_error(char* error_message);

// Creates an error message buffer with a default size
char* get_error_message_buffer();

// Declaration check functions

// Checks if the current variable has been redeclared, if not declared marks as declared
void check_and_mark_declaration(ast_node_t* node);

// Verify declarations

void verify_declarations(ast_node_t* node)
{
    if (!node)
        return;

    switch (node->type) {
        case AST_VARIABLE_DECLARATION:
        case AST_VECTOR_DECLARATION:
        case AST_FUNCTION_DECLARATION:
            check_and_mark_declaration(node);
    }

    int i = 0;
    for (i = 0; i < NUM_SONS; i++)
        verify_declarations(node->sons[i]);
}

void check_and_mark_declaration(ast_node_t* node)
{
    if (node->symbol->declared) {
        // Already marked as declared
        char* error_message = get_error_message_buffer();
        sprintf(error_message, "variable %s already declared", node->symbol->value);
        add_semantic_error(error_message);
    } else {
        // Mark variable as declared
        node->symbol->declared = 1;
    }
}

void add_semantic_error(char* error_message)
{
    semantic_error_node_t* new_error = malloc(sizeof(semantic_error_node_t));
    new_error->error_message = strdup(error_message);
    new_error->next_error = 0;

    if (!global_semantic_error_list) {
        global_semantic_error_list = new_error;
    } else {
        semantic_error_node_t* last_error = global_semantic_error_list;
        while (last_error->next_error)
            last_error = last_error->next_error;
        last_error->next_error = new_error;
    }
}

char* get_error_message_buffer()
{
    const int BUFFER_SIZE = 1024;
    char *buffer = (char*) malloc(BUFFER_SIZE * sizeof(char));
    return buffer;
}

void print_semantic_error_list(semantic_error_node_t* semantic_error_list)
{
    if (!semantic_error_list)
        return;
    
    // Prints each node
    semantic_error_node_t* current_error = semantic_error_list;
    semantic_error_node_t* next_error = current_error->next_error;
    fprintf(stderr, "Semantic error: %s\n", current_error->error_message);

    while(next_error) {
        current_error = next_error;
        next_error = current_error->next_error;
        fprintf(stderr, "Semantic error: %s\n", current_error->error_message);
    }
}

void free_semantic_error_list(semantic_error_node_t* semantic_error_list)
{
    if (!semantic_error_list)
        return;
    
    // Frees each node and their error message buffers
    semantic_error_node_t* current_error = semantic_error_list;
    semantic_error_node_t* next_error = current_error->next_error;
    free(current_error->error_message);
    free(current_error);

    while(next_error) {
        current_error = next_error;
        next_error = current_error->next_error;
        free(current_error->error_message);
        free(current_error);
    }
}
