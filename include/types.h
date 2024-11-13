#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>
#include <stddef.h>

typedef struct Pair_S
{
    uint64_t fst;
    uint64_t snd;
} Pair_T;

typedef struct String_S
{
    size_t len;
    char *str;
} String_T ;

#endif