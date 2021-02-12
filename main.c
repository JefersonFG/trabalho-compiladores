#include <stdio.h>

#include "hash.h"

int isRunning();

extern int is_running;

int main() {
    int token = 0;

    initMe();

    while (isRunning()) {
        token = yylex();
        fprintf(stdout, "Token lido: %d\n", token);
        fprintf(stdout, "Linha atual: %d\n", getLineNumber());
    }

    print_hash(global_hash_table);
    free_hash(global_hash_table);
    return 0;
}
