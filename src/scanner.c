#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "scanner.h"

static inline int scan_hexit(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    switch (c)
    {
    case 'a':
    case 'A':
        return 10;
    case 'b':
    case 'B':
        return 11;
    case 'c':
    case 'C':
        return 12;
    case 'd':
    case 'D':
        return 13;
    case 'e':
    case 'E':
        return 14;
    case 'f':
    case 'F':
        return 15;
    }
}

static void get_sign_and_base(char *s, int *base, int *sign, char **start)
{
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

static void get_int_and_dec_parts(char *int_start, int *int_len, char **dec_start, int *dec_len){
    *int_len = (strchr(int_start, '.') - int_start)/sizeof(char);
    *dec_start = int_start + (*int_len + 1)*sizeof(char);
    *dec_len = strlen(*dec_start);
}

int32_t scan_digits(char *s, int len, int base)
{
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

int32_t scan_int (char *s) {
    int base, sign ;
    char *start ;

    get_sign_and_base(s, &base, &sign, &start);
    return sign * scan_digits(start, strlen(start), base);
}

double scan_num(char *s)
{
    int base, sign;
    char *int_start;
    char *dec_start;
    int int_len, dec_len;

    get_sign_and_base(s, &base, &sign, &int_start);
    get_int_and_dec_parts(int_start, &int_len, &dec_start, &dec_len);

    return sign * (scan_digits(int_start, int_len, base) + scan_digits(dec_start, dec_len, base)/pow(base, dec_len));
}

char *scan_esc_seq_ascii(char *s)
{
    char *result = calloc(2, sizeof(char));

    if (!result)
    {
        perror("Memory allocation failure");
        exit(1);
    }

    switch (s[1])
    {
    case '\\':
        result[0] = '\\';
        break;
    case '\'':
        result[0] = '\'';
        break;
    case '\"':
        result[0] = '\"';
        break;
    case '?':
        result[0] = '\?';
        break;
    case 'a':
        result[0] = '\a';
        break;
    case 'b':
        result[0] = '\b';
        break;
    case 'f':
        result[0] = '\f';
        break;
    case 'n':
        result[0] = '\n';
        break;
    case 'r':
        result[0] = '\r';
        break;
    case 't':
        result[0] = '\t';
        break;
    case 'v':
        result[0] = '\v';
        break;
    case '0':
        result[0] = '\0';
        break;
    case 'e':
        result[0] = '\e';
        break;
    }

    result[1] = '\0';
    return result;
}

char *scan_esc_seq_oct(char *s)
{
}

char *scan_esc_seq_hex(char *s)
{
}

char *scan_esc_seq_u_4(char *s)
{
}

char *scan_esc_seq_u_6(char *s)
{
}

char *scan_esc_seq_name(char *s)
{
}
