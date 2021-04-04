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
            fprintf(output_file, "%s", node->symbol->value);
            break;
        
        // Variable definitions
        case AST_BOOL:
            fprintf(output_file, "bool");
            break;
        case AST_CHAR:
            fprintf(output_file, "char");
            break;
        case AST_INT:
            fprintf(output_file, "int");
            break;
        case AST_POINTER:
            fprintf(output_file, "pointer");
            break;

        // Loop controls
        case AST_IF:
            fprintf(output_file, "if (");
            decompile_ast(node->sons[0], output_file);
            fprintf(output_file, ") then\n");
            decompile_ast(node->sons[1], output_file);
            break;
        case AST_IF_ELSE:
            fprintf(output_file, "if (");
            decompile_ast(node->sons[0], output_file);
            fprintf(output_file, ") then\n");
            decompile_ast(node->sons[1], output_file);
            fprintf(output_file, "\nelse\n");
            decompile_ast(node->sons[2], output_file);
            break;
        case AST_WHILE:
            fprintf(output_file, "while (");
            decompile_ast(node->sons[0], output_file);
            fprintf(output_file, ")\n");
            decompile_ast(node->sons[1], output_file);
            break;
        
        // Language commands
        case AST_READ:
            fprintf(output_file, "read %s", node->symbol->value);
            break;
        case AST_PRINT:
            fprintf(output_file, "print ");
            decompile_ast(node->sons[0], output_file);
            break;
        case AST_RETURN:
            fprintf(output_file, "return ");
            decompile_ast(node->sons[0], output_file);
            break;
        
        // Expressions
        case AST_ADD:
            decompile_ast(node->sons[0], output_file);
            fprintf(output_file, " + ");
            decompile_ast(node->sons[1], output_file);
            break;
        case AST_SUB:
            decompile_ast(node->sons[0], output_file);
            fprintf(output_file, " - ");
            decompile_ast(node->sons[1], output_file);
            break;
        case AST_MULT:
            decompile_ast(node->sons[0], output_file);
            fprintf(output_file, " * ");
            decompile_ast(node->sons[1], output_file);
            break;
        case AST_DIV:
            decompile_ast(node->sons[0], output_file);
            fprintf(output_file, " / ");
            decompile_ast(node->sons[1], output_file);
            break;
        case AST_LESSER:
            decompile_ast(node->sons[0], output_file);
            fprintf(output_file, " < ");
            decompile_ast(node->sons[1], output_file);
            break;
        case AST_GREATER:
            decompile_ast(node->sons[0], output_file);
            fprintf(output_file, " > ");
            decompile_ast(node->sons[1], output_file);
            break;
        case AST_OR:
            decompile_ast(node->sons[0], output_file);
            fprintf(output_file, " | ");
            decompile_ast(node->sons[1], output_file);
            break;
        case AST_AND:
            decompile_ast(node->sons[0], output_file);
            fprintf(output_file, " & ");
            decompile_ast(node->sons[1], output_file);
            break;
        case AST_LESSER_EQUAL:
            decompile_ast(node->sons[0], output_file);
            fprintf(output_file, " <= ");
            decompile_ast(node->sons[1], output_file);
            break;
        case AST_GREATER_EQUAL:
            decompile_ast(node->sons[0], output_file);
            fprintf(output_file, " >= ");
            decompile_ast(node->sons[1], output_file);
            break;
        case AST_EQUAL:
            decompile_ast(node->sons[0], output_file);
            fprintf(output_file, " == ");
            decompile_ast(node->sons[1], output_file);
            break;
        case AST_NOT_EQUAL:
            decompile_ast(node->sons[0], output_file);
            fprintf(output_file, " != ");
            decompile_ast(node->sons[1], output_file);
            break;
        case AST_NOT:
            fprintf(output_file, " ~");
            decompile_ast(node->sons[0], output_file);
            break;
        case AST_LEFT_ASSIGN:
            decompile_ast(node->sons[0], output_file);
            fprintf(output_file, " <- ");
            decompile_ast(node->sons[1], output_file);
            break;
        case AST_RIGHT_ASSIGN:
            decompile_ast(node->sons[0], output_file);
            fprintf(output_file, " -> ");
            decompile_ast(node->sons[1], output_file);
            break;
        case AST_ADDRESS:
            fprintf(output_file, " $");
            decompile_ast(node->sons[0], output_file);
            break;
        case AST_DEREFERENCE:
            fprintf(output_file, " #");
            decompile_ast(node->sons[0], output_file);
            break;
        
        // Declarations
        case AST_DECLARATION_LIST:
            // declaration declaration_list
            decompile_ast(node->sons[0], output_file);
            if (node->sons[1]) {
                decompile_ast(node->sons[1], output_file);
            }
            break;
        case AST_VARIABLE_DECLARATION:
            // bool b : false;
            decompile_ast(node->sons[0], output_file);
            fprintf(output_file, " %s : ", node->symbol->value);
            decompile_ast(node->sons[1], output_file);
            fprintf(output_file, ";\n");
            break;
        case AST_VECTOR_DECLARATION:
            // int[10] mat;
            decompile_ast(node->sons[0], output_file);
            fprintf(output_file, "[");
            decompile_ast(node->sons[1], output_file);
            fprintf(output_file, "] %s", node->symbol->value);
            fprintf(output_file, ";\n");
            break;
        case AST_VECTOR_INIT_DECLARATION:
            // int[10] v : 0 0 0 0 0 0 0 0 0 0;
            decompile_ast(node->sons[0], output_file);
            fprintf(output_file, "[");
            decompile_ast(node->sons[1], output_file);
            fprintf(output_file, "] %s : ", node->symbol->value);
            decompile_ast(node->sons[2], output_file);
            fprintf(output_file, ";\n");
            break;
        case AST_FUNCTION_DECLARATION:
            // int incn (int x , int n ) { return x+n; };
            decompile_ast(node->sons[0], output_file);
            fprintf(output_file, " %s (", node->symbol->value);
            decompile_ast(node->sons[1], output_file);
            fprintf(output_file, ")\n");
            decompile_ast(node->sons[2], output_file);
            fprintf(output_file, ";\n");
            break;
        
        // Parameters
        case AST_VECTOR_INITIAL_VALUES:
            // 0 0 0 0 0
            decompile_ast(node->sons[0], output_file);
            if (node->sons[1]) {
                fprintf(output_file, " ");
                decompile_ast(node->sons[1], output_file);
            }
            break;
        case AST_FUNCTION_DEFINITION_PARAMETERS:
            // ->int x<-, int n
            if (node->sons[0]) {
                decompile_ast(node->sons[0], output_file);
                fprintf(output_file, " %s", node->symbol->value);
            }
            break;
        case AST_FUNCTION_DEFINITION_PARAMETERS_RECURSIVE:
            // int x ->, int n<-
            if (node->sons[0]) {
                fprintf(output_file, ", ");
                decompile_ast(node->sons[0], output_file);
                fprintf(output_file, "%s", node->symbol->value);
            }
            break;
        
        // Commands
        case AST_COMMAND_BLOCK:
            // { command_list }
            fprintf(output_file, "{\n");
            decompile_ast(node->sons[0], output_file);
            fprintf(output_file, "}");
            break;
        case AST_COMMAND_LIST:
            // command; command_list
            decompile_ast(node->sons[0], output_file);
            fprintf(output_file, ";\n");
            decompile_ast(node->sons[1], output_file);
            break;
        
        // Parameters
        case AST_PRINT_LIST:
            // string print_list_recursive
            decompile_ast(node->sons[0], output_file);
            decompile_ast(node->sons[1], output_file);
            break;
        case AST_PRINT_LIST_RECURSIVE:
            // , string|expression print_list_recursive
            if (node->sons[0]) {
                fprintf(output_file, ", ");
                decompile_ast(node->sons[0], output_file);
                decompile_ast(node->sons[1], output_file);
            }
            break;
        case AST_FUNCTION_CALL_PARAMETERS:
            // expression function_call_parameters_recursive
            if (node->sons[0]) {
                decompile_ast(node->sons[0], output_file);
                decompile_ast(node->sons[1], output_file);
            }
            break;
        case AST_FUNCTION_CALL_PARAMETERS_RECURSIVE:
            // , expression function_call_parameters_recursive
            if (node->sons[0]) {
                fprintf(output_file, ", ");
                decompile_ast(node->sons[0], output_file);
                decompile_ast(node->sons[1], output_file);
            }
            break;
        
        // Assignments
        case AST_ASSIGNMENT:
            // identifier <- expression
            fprintf(output_file, "%s <- ", node->symbol->value);
            decompile_ast(node->sons[0], output_file);
            break;
        case AST_REVERSE_ASSIGNMENT:
            // expression -> identifier
            decompile_ast(node->sons[0], output_file);
            fprintf(output_file, " -> %s", node->symbol->value);
            break;
        case AST_VECTOR_ASSIGNMENT:
            // identifier[expression] <- expression
            fprintf(output_file, "%s[", node->symbol->value);
            decompile_ast(node->sons[0], output_file);
            fprintf(output_file, "] <- ");
            decompile_ast(node->sons[1], output_file);
            break;
        case AST_REVERSE_VECTOR_ASSIGNMENT:
            // expression -> identifier[expression]
            decompile_ast(node->sons[0], output_file);
            fprintf(output_file, " -> %s", node->symbol->value);
            decompile_ast(node->sons[1], output_file);
            fprintf(output_file, "]");
            break;
        
        // Expressions
        case AST_VECTOR:
            // identifier[expression]
            fprintf(output_file, "%s[", node->symbol->value);
            decompile_ast(node->sons[0], output_file);
            fprintf(output_file, "]");
            break;
        case AST_PARENTHESIS:
            // (expression)
            fprintf(output_file, "(");
            decompile_ast(node->sons[0], output_file);
            fprintf(output_file, ")");
            break;
        case AST_FUNCTION_CALL:
            // identifier(expression)
            fprintf(output_file, "%s(", node->symbol->value);
            decompile_ast(node->sons[0], output_file);
            fprintf(output_file, ")");
            break;
        case AST_VECTOR_SIZE:
            // integer literal
            fprintf(output_file, "%s", node->symbol->value);
            break;
        default:
            fprintf(stderr, "Unrecognized literal on AST\n");
    }
}
