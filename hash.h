#include <stdlib.h>

typedef struct node_s {
    char* value;
    int token;
    struct node_s* next;
} hash_node_t;

typedef struct hash_table_s {
    int size;
    struct node_s **table;
} hash_table_t;

// Creates a hash table with the given size
hash_table_t* create_hash_table(int size);

// Calculates the hash address for a given value on the hash table
int calculate_hash_index(hash_table_t* hash_table, char* value);

// Inserts a pair value-token on the hash table, indicates if was successful
int insert_hash_value(hash_table_t* hash_table, char* value, int token);

// Gets the token associated to the value
int get_hash_token(hash_table_t* hash_table, char* value);

// Helper function to print the data on the hash table
void print_hash(hash_table_t* hash_table);

// Frees the memory used on the hash table
void free_hash(hash_table_t* hash_table);
