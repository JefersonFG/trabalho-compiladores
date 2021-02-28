#include "hash.h"

#include <stdio.h>
#include <string.h>
#include <math.h>

hash_table_t* global_hash_table = 0;

hash_table_t* create_hash_table(int size) {
    if (size < 1)
        return 0;
    
    hash_table_t* hash_table = 0;

    // Allocate the table
    hash_table = malloc(sizeof(hash_table_t));
    if (!hash_table)
        return 0;
    
    hash_table->size = size;
    hash_table->table = 0;

    // Allocate the nodes
    hash_table->table = malloc(sizeof(hash_node_t*) * size);
    if (!hash_table->table)
        return 0;

    int i = 0;
    for (i = 0; i < size; i++) {
        hash_table->table[i] = 0;
    }

    return hash_table;
}

int calculate_hash_index(hash_table_t* hash_table, char* value) {
    // Implementation of the Jenkins Hash Function
    int hash = 0;
    size_t i = 0;
    size_t length = strlen(value);

    while (i < length) {
        hash += value[i++];
        hash += hash << 10;
        hash ^= hash >> 6;
    }

    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;

    return abs(hash) % hash_table->size;
}

int insert_hash_value(hash_table_t* hash_table, char* value, int token) {
    int hash_index = calculate_hash_index(hash_table, value);

    hash_node_t* current_node = hash_table->table[hash_index];
    hash_node_t* previous_node = 0;

    // Search the list for an empty spot
    while (current_node != 0 && current_node->next != 0 && strcmp(current_node->value, value) != 0) {
        previous_node = current_node;
        current_node = current_node->next;
    }

    // Check if found the same entry before
    if (current_node != 0 && strcmp(current_node->value, value) == 0) {
        // Ideally here we would change the value associated with the key
        // But in this case there is nothing to do as the pair will never change
        return 1;
    } else {
        // Allocate a new node
        hash_node_t* new_node = malloc(sizeof(hash_node_t));
        if (!new_node)
            return 0;
        
        new_node->value = strdup(value);
        if (!new_node->value)
            return 0;

        new_node->token = token;
        new_node->next = 0;

        if (current_node == hash_table->table[hash_index]) {
            // We're still at the start of the list
            new_node->next = current_node;
            hash_table->table[hash_index] = new_node;
        } else if (current_node == 0) {
            // End of the list
            previous_node->next = new_node;
        } else {
            // Middle of the list
            new_node->next = current_node;
            previous_node->next = new_node;
        }

        return 1;
    }
}

int get_hash_token(hash_table_t* hash_table, char* value) {
    int hash_index = calculate_hash_index(hash_table, value);

    hash_node_t* node = hash_table->table[hash_index];

    // Search the list for a valid entry
    while (node != 0 && node->next != 0 && strcmp(node->value, value) != 0) {
        node = node->next;
    }

    // Check if the node is valid
    if (node == 0 || strcmp(node->value, value) != 0) {
        return 0;
    } else {
        return node->token;
    }
}

void print_hash(hash_table_t* hash_table) {
    fprintf(stdout, "Hash current state:\n");
    int i = 0;
    for (i = 0; i < hash_table->size; i++) {
        hash_node_t* current_node = hash_table->table[i];

        while (current_node) {
            fprintf(stdout, "Node value: %s - token: %d\n", current_node->value, current_node->token);
            current_node = current_node->next;
        }
    }
}

void free_hash(hash_table_t* hash_table) {
    // Frees nodes
    int i = 0;
    for (i = 0; i < hash_table->size; i++) {
        hash_node_t* current_node = hash_table->table[i];
        hash_node_t* next_node = 0;

        while (current_node) {
            next_node = current_node->next;
            free(current_node);
            current_node = next_node;
        }
    }

    // Frees table and hash
    free(hash_table->table);
    free(hash_table);
}
