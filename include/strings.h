#ifndef STRINGS_H
#define STRINGS_H

#include <stdint.h>
#include "nanboxing.h"


static inline size_t get_len_string(uint64_t s) {return as_string(s)->len;}
static inline char *get_chars_string(uint64_t s) {return as_string(s)->chars;}

uint64_t new_string(char *s);

void print_string(uint64_t s);

uint64_t concatenate_string(uint64_t s1, uint64_t s2);

#endif