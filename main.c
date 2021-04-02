#include <stdio.h>

#include "ast.h"
#include "y.tab.h"

extern FILE *yyin;

void initMe(void);
void decompile_ast(ast_node_t* node, FILE* output_file);

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

void decompile_ast(ast_node_t* node, FILE* output_file) {
    if (!node)
        return;

    switch (node->type) {
        // Literal
        case AST_SYMBOL:
            fprintf(output_file, " %s ", node->symbol->value);
            break;
        
        // Variable definitions
        case AST_BOOL:
            fprintf(output_file, "bool ");
            break;
        case AST_CHAR:
            fprintf(output_file, "char ");
            break;
        case AST_INT:
            fprintf(output_file, "int ");
            break;
        case AST_POINTER:
            fprintf(output_file, "pointer ");
            break;

        // Loop controls
        case AST_IF:
            fprintf(output_file, "if (");
            fprintf(output_file, ") then\n");
            fprintf(output_file, "    ");
            break;
        case AST_IF_ELSE:
            fprintf(output_file, "if (");
            fprintf(output_file, ") then\n");
            fprintf(output_file, "    ");
            fprintf(output_file, "else\n");
            fprintf(output_file, "    ");
            break;
        case AST_WHILE:
            fprintf(output_file, "while (");
            fprintf(output_file, ")\n");
            fprintf(output_file, "    ");
            break;
        
        // Language commands
        case AST_READ:
            fprintf(output_file, "read %s", node->symbol->value);
            break;
        case AST_PRINT:
            fprintf(output_file, "print ");
            break;
        case AST_RETURN:
            fprintf(output_file, "return ");
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
}
