#include <stdio.h>

#pragma once

typedef struct semantic_error_list_s {
    char* error_message;
    struct semantic_error_list_s* next_error;
} semantic_error_list_t;

extern semantic_error_list_t* global_semantic_error_list;

// Shows all the semantic errors to the user
void print_semantic_error_list(semantic_error_list_t* semantic_error_list);

// Frees memory associated with the semantic error list
void free_semantic_error_list(semantic_error_list_t* semantic_error_list);
