#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "scanner.yy.h"

int main(int argc, char **argv) {
    yylex();

    return 0;
}