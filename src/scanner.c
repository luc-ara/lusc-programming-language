#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "scanner.h"

static inline int scan_hexit(char c)
{ /*
    Converts a character representing a hexit into it's numeric value;
    Input must be a hexit
  */
    if (c >= '0' && c <= '9')
        return c - '0';
    switch (c)
    {
    case 'a': case 'A': return 10;
    case 'b': case 'B': return 11;
    case 'c': case 'C': return 12;
    case 'd': case 'D': return 13;
    case 'e': case 'E': return 14;
    case 'f': case 'F': return 15;
    }
}

static void get_sign_and_base(char *s, int *base, int *sign, char **start)
{ /* 
     Reads a string representing a number, gets it's sign, base,
     and sets start to the first character after the base;
     - input must contain an optional sign, an optional base specifier, 
       followed by a string of hexits, followed by an optional 
       dot and another string of hexits.
  */
    *start = s;
    *sign = 1;

    if ((*start)[0] == '-') 
    {
        *sign = -1; 
        *start += sizeof(char);
    }


    if ((*start)[0] == '0' && (*start)[1] != '\0' && strchr("bBoOdDxX", (*start)[1]))
    {
        switch((*start)[1])
        {
            case 'b': case 'B': *base = 2; break;
            case 'o': case 'O': *base = 8; break;
            case 'd': case 'D': *base = 10; break;
            case 'x': case 'X': *base = 16; break;
        }

        *start += 2*sizeof(char);
    } else 
    {
        *base = 10;
    }
}

static void get_int_and_dec_parts(char *int_start, int *int_len, char **dec_start, int *dec_len)
{ /*
     Receives a string representing a number without the base or sign, sets 
     int_start and dec_start to the first digit of the integer and decimal
     parts, respectively, and then sets int_len and dec_len to the number of
     digits in their respective parts;
     - Input must be a string of hexits followed by a dot followed by another
       string of hexits.
  */
    *int_len = (strchr(int_start, '.') - int_start)/sizeof(char);
    *dec_start = int_start + (*int_len + 1)*sizeof(char);
    *dec_len = strlen(*dec_start);
}

int32_t scan_digits(char *s, int len, int base)
{ /*
     Converts a string of hexits into the equivalent integer value according
     to the specified base.
     - base must be one of:
        - b or B for binary;
        - o or O for octal;
        - d or D for decimal;
        - x or X for hexadecimal;
     - The characters in s must be valid digits for the base.
     - If a string represents an integer too big for int32_t, throws an error
       and exits
  */
    int cur = 0;
    int64_t result = 0;

    while (cur < len)
    {
        result = result * base + scan_hexit(s[cur++]);

        if (result >= INT32_MAX)
        {
            perror("scan_digits: Value too big for an int32_t\n");
            exit(1);
        }
    }

    return (int32_t)result;
}

int32_t scan_int (char *s)
{ /*
     Receives a string representing an int, with optional sign and base specifier,
     and returns the corresponding integer value
  */
    int base, sign ;
    char *start ;

    get_sign_and_base(s, &base, &sign, &start);
    return sign * scan_digits(start, strlen(start), base);
}

double scan_num(char *s)
{ /*
     Receives a string representing a floating-point number, with optional sign 
     and base specifier, and mandatory integer and decimal parts, and returns
     the corresponding double
  */
    int base, sign;
    char *int_start;
    char *dec_start;
    int int_len, dec_len;

    get_sign_and_base(s, &base, &sign, &int_start);
    get_int_and_dec_parts(int_start, &int_len, &dec_start, &dec_len);

    return sign * (scan_digits(int_start, int_len, base) + scan_digits(dec_start, dec_len, base)/pow(base, dec_len));
}

static void unicode_to_utf8(uint32_t cp, char *utf8)
{ /*
     Receives a Unicode code point and converts it to a UTF-8 byte sequence
  */
    if (cp <= 0x0000007F)
    {
        utf8[0] = (char) cp;
        utf8[1] = '\0';
    } else if (cp <= 0x000007FF)
    {
        utf8[0] = 0xC0 | (cp >> 6);
        utf8[1] = 0x80 | (cp & 0x3F);
        utf8[2] = '\0';
    } else if (cp <= 0x0000FFFF)
    {
        utf8[0] = 0xE0 | (char)(cp >> 12);
        utf8[1] = 0x80 | (char)((cp >> 6) & 0x3F);
        utf8[2] = 0x80 | (char)(cp & 0x3F);
        utf8[3] = '\0';
    } else if (cp <= 0x001FFFFF)
    {
        utf8[0] = 0xF0 | (char)(cp >> 18);
        utf8[1] = 0x80 | (char)((cp >> 12) & 0x3F);
        utf8[2] = 0x80 | (char)((cp >> 6) & 0x3F);
        utf8[3] = 0x80 | (char)(cp & 0x3F);
        utf8[4] = '\0';
    } else {
        perror("Unicode codepoint too big\n");
        exit(1);
    }
}

void scan_esc_seq(char *s, char *r)
{
    switch (s[1])
    {
    case '\\': r[0] = '\\'; r[1] = '\0'; break;
    case '\'': r[0] = '\''; r[1] = '\0'; break;
    case '\"': r[0] = '\"'; r[1] = '\0'; break;
    case '?': r[0] = '\?'; r[1] = '\0'; break;
    case 'a': r[0] = '\a'; r[1] = '\0'; break;
    case 'b': r[0] = '\b'; r[1] = '\0'; break;
    case 'f': r[0] = '\f'; r[1] = '\0'; break;
    case 'n': r[0] = '\n'; r[1] = '\0'; break;
    case 'r': r[0] = '\r'; r[1] = '\0'; break;
    case 't': r[0] = '\t'; r[1] = '\0'; break;
    case 'v': r[0] = '\v'; r[1] = '\0'; break;
    case '0':
        if (s[2] != '\0' && strchr("01234567", s[2]) && s[3] != '\0' && strchr("01234567", s[3])) 
            unicode_to_utf8(scan_digits(s+sizeof(char), 3, 8), r);
        else 
        {
            r[0] = '\0';
            r[1] = '\0';
        } break;
    case 'e': r[0] = '\e'; r[1] = '\0'; break;
    case '1': case '2': case '3': unicode_to_utf8(scan_digits(s+sizeof(char), 3, 8), r); break;
    case 'x': unicode_to_utf8(scan_digits(s+2*sizeof(char), 2, 16), r); break;
    case 'u': unicode_to_utf8(scan_digits(s+2*sizeof(char), 4, 16), r); break;
    case 'U': unicode_to_utf8(scan_digits(s+2*sizeof(char), 8, 16), r); break;
    case 'N': break;
    }
}
