#include <stdio.h>

int isRunning();

extern int is_running;

int main() {
    int token = 0;

    while (isRunning()) {
        token = yylex();
        printf("Token lido: %d\n", token);
        printf("Linha atual: %d\n", getLineNumber());
    }

    return 0;
}
