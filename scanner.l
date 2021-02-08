%{
#include "tokens.h"
int is_running = 1;
%}

%%

<<EOF>> {is_running = 0; return -1;}
. return TOKEN_ERROR;

%%

int yywrap(void) {
    return 1;
}

int isRunning() {
    return is_running;
}
