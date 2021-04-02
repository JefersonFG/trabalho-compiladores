#include <stdio.h>

#include "ast.h"
#include "y.tab.h"

extern FILE *yyin;

void initMe(void);
void decompile_ast(ast_node_t* root, FILE* output_file);

int main(int argc, char* argv[]) {
    // Check that the program was called with input and output file parameters
    if (argc < 3) {
        fprintf(stderr, "Error: parser called without input and output file parameters, use the format etapa3 inputfile outputfile\n");
        return 1;
    } else if (argc > 3) {
        fprintf(stderr, "Error: parser called with too many parameters, use the format etapa3 inputfile outputfile\n");
        return 1;
    }

    // Open the input file
    yyin = fopen(argv[1], "r");
    if (yyin == 0) {
        fprintf(stderr, "Error opening input file: %s\n", argv[1]);
        return 2;
    }

    // Open the output file
    FILE* output_file;
    output_file = fopen(argv[2], "w");
    if (output_file == 0) {
        fprintf(stderr, "Error opening output file: %s\n", argv[1]);
        return 2;
    }

    // Initialize the hash table and parse the input file
    initMe();
    yyparse();

    // Decompile the generated AST into the output file
    decompile_ast(global_ast_node, output_file);

    // Show the final state of the hash table and free it before finishing without errors
    print_hash(global_hash_table);
    free_hash(global_hash_table);

    fprintf(stdout, "Compilation successful\n");
    return 0;
}

void decompile_ast(ast_node_t* root, FILE* output_file) {
    // TODO: Implement method
    return;
}
