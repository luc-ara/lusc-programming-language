#ifndef NANBOXING_H
#define NANBOXING_H

#include <stdint.h>
#include <stddef.h>

// General purpose masks
#define SIGN_MASK      (0x8000000000000000L)
#define EXPONENT_MASK  (0x7FF0000000000000L)
#define QUIET_MASK     (0x0008000000000000L)
#define FLAG_MASK      (0x0007000000000000L)
#define TYPE_MASK      (0x0000FFFF00000000L)
#define VALUE_MASK     (0x00000000FFFFFFFFL)
#define PTR_MASK       (TYPE_MASK | VALUE_MASK)
#define NANBOX_MASK    (EXPONENT_MASK | QUIET_MASK)
#define SFLAG_MASK     (SIGN_MASK | FLAG_MASK)

// Flag masks
#define SFLAG_MASK_0    (0x0000000000000000L)
#define SFLAG_MASK_1    (0x0001000000000000L)
#define SFLAG_MASK_2    (0x0002000000000000L)
#define SFLAG_MASK_3    (0x0003000000000000L)
#define SFLAG_MASK_4    (0x0004000000000000L)
#define SFLAG_MASK_5    (0x0005000000000000L)
#define SFLAG_MASK_6    (0x0006000000000000L)
#define SFLAG_MASK_7    (0x0007000000000000L)
#define SFLAG_MASK_8    (0x8000000000000000L)
#define SFLAG_MASK_9    (0x8001000000000000L)
#define SFLAG_MASK_A    (0x8002000000000000L)
#define SFLAG_MASK_B    (0x8003000000000000L)
#define SFLAG_MASK_C    (0x8004000000000000L)
#define SFLAG_MASK_D    (0x8005000000000000L)
#define SFLAG_MASK_E    (0x8006000000000000L)
#define SFLAG_MASK_F    (0x8007000000000000L)

// Type masks
#define TYPE_NIL       (0x0000000100000000L | SFLAG_MASK_0 | NANBOX_MASK)
#define TYPE_BOOLEAN   (0x0000000200000000L | SFLAG_MASK_0 | NANBOX_MASK)
#define TYPE_COMP      (0x0000000300000000L | SFLAG_MASK_0 | NANBOX_MASK)
#define TYPE_CHAR      (0x0000000400000000L | SFLAG_MASK_0 | NANBOX_MASK)
#define TYPE_INT       (0x0000000500000000L | SFLAG_MASK_0 | NANBOX_MASK) 
#define TYPE_ERROR     (0x0000FFFF00000000L | SFLAG_MASK_0 | NANBOX_MASK)
#define TYPE_STRING    (SFLAG_MASK_1 | NANBOX_MASK)
#define TYPE_PAIR      (SFLAG_MASK_2 | NANBOX_MASK)

// Double type
#define is_nanbox(x)   ((((x) & NANBOX_MASK) == NANBOX_MASK) && ((x) & ~NANBOX_MASK))

typedef union Nanbox_U
{
    double d;
    uint64_t n;
} Nanbox_T;

#define is_double(x)   (!is_nanbox(x))
#define as_double(x)   (((Nanbox_T){.n = (x)}).d)
#define box_double(x)  (((Nanbox_T){.d = (x)}).n)

// Error type
#define is_error(x)    (((x) & (TYPE_MASK | SFLAG_MASK)) == TYPE_ERROR)

#define ERROR_ALLOC    (0x0000000000000001L | TYPE_ERROR)
#define ERROR_TYPE     (0x0000000000000002L | TYPE_ERROR)

// NIL type
#define NIL            (TYPE_NIL)
#define is_nil(x)      ((x) == NIL)

// Boolean type
#define BOOLEAN_FALSE  (0x0000000000000000L | TYPE_BOOLEAN)
#define BOOLEAN_TRUE   (0x0000000000000001L | TYPE_BOOLEAN)
#define is_boolean(x)  (((x) & (TYPE_MASK | SFLAG_MASK)) == TYPE_BOOLEAN)
#define as_boolean(x)  ((int) ((x) & VALUE_MASK))
#define box_boolean(x) ((x) ? BOOLEAN_TRUE : BOOLEAN_FALSE)

// Comparison type
#define COMP_LT        (0x00000000FFFFFFFFL | TYPE_COMP)
#define COMP_EQ        (0x0000000000000000L | TYPE_COMP)
#define COMP_GT        (0x0000000000000001L | TYPE_COMP)
#define is_comp(x)     (((x) & (TYPE_MASK | SFLAG_MASK)) == TYPE_COMP)
#define as_comp(x)     ((int) ((x) & VALUE_MASK))
#define box_comp(x)    ((x) < 0 ? COMP_LT : (x) > 0 ? COMP_GT : COMP_EQ)

// Character type
#define is_char(x)     (((x) & (TYPE_MASK | SFLAG_MASK)) == TYPE_CHAR)
#define as_char(x)     ((uint32_t) ((x) & VALUE_MASK))
#define box_char(x)    ((x) | TYPE_CHAR)

// Integer type
#define is_int(x)     (((x) & (TYPE_MASK | SFLAG_MASK)) == TYPE_INT)
#define as_int(x)     ((int32_t) ((x) & VALUE_MASK))
#define box_int(x)    ((x) | TYPE_INT)

//String type
#define is_string(x)  (((x) & SFLAG_MASK) == TYPE_STRING)
#define as_string(x)  ((struct String_S *)((x) & ~(NANBOX_MASK | SFLAG_MASK)))
#define box_string(x) ((uint64_t)(x) | TYPE_STRING)

//Pair type
#define is_pair(x)  (((x) & SFLAG_MASK) == TYPE_STRING)
#define as_pair(x)  ((struct Pair_S *)((x) & ~(NANBOX_MASK | SFLAG_MASK)))
#define box_pair(x) ((uint64_t)(x) | TYPE_PAIR)

#endif