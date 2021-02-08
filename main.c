#include <stdio.h>

int isRunning();

extern int is_running;

int main() {
    int token = 0;

    while (isRunning()) {
        token = yylex();
        printf("Token lido: %d\n", token);
    }

    return 0;
}
