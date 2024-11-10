#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "scanner.yy.h"

int main(int argc, char **argv) {

    if (argc != 3) {
        printf("Wrong number of arguments\nUsage format: lusc [input_file] [output_file]\n");
        return 1;
    }

    if (!strcmp(argv[1], "stdin")) {
        yyin = stdin;
    } else {
        yyin = fopen(argv[1], "r");

        if (!yyin) {
            printf("Could not open input file %s\n", argv[1]);
            return 1;
        }
    }

    if (!strcmp(argv[2], "stdout")) {
        yyout = stdout;
    } else {
        yyout = fopen(argv[2], "w");

        if (!yyout) {
            printf("Could not open output file %s\n", argv[2]);
            return 1;
        }
    }

    yylex();

    return 0;
}