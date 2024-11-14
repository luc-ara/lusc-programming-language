#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>

#include "nanboxing.h"
#include "strings.h"

uint64_t new_string(char *s)
{
    String_T *new = calloc(1, sizeof(String_T));

    new->len = strlen(s);
    new->chars = calloc(new->len, sizeof(char));

    memcpy(new->chars, s, new->len);

    return box_string(new);
}

void print_string(uint64_t s)
{
    printf("%.*s\n", (int)as_string(s)->len, as_string(s)->chars);
}