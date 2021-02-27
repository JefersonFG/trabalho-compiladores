#include <stdio.h>

#include "hash.h"
#include "y.tab.h"

extern FILE *yyin;
extern int yydebug;

int main(int argc, char* argv[]) {
    // Check that the program was called with an input file parameter
    if (argc < 2) {
        fprintf(stderr, "Error: parser called without an input file parameter, use the format etapa2 filename\n");
        return 1;
    } else if (argc > 2) {
        fprintf(stderr, "Error: parser called with too many parameters, use the format etapa2 filename\n");
        return 1;
    }

    // TODO: Remove this, for debug only
    yydebug = 1;

    // Open the input file
    yyin = fopen(argv[1], "r");
    if (yyin == 0) {
        fprintf(stderr, "Error opening file: %s\n", argv[1]);
        return 2;
    }

    // Initialize the hash table and parse the input file
    initMe();
    yyparse();

    // Show the final state of the hash table and free it before finishing without errors
    print_hash(global_hash_table);
    free_hash(global_hash_table);
    return 0;
}
