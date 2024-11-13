#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "scanner.h"
#include "nanboxing.h"

static void print_str(char *s) //Used to inspect utf-8 byte sequences
{
    for(int i = 0; i < strlen(s); ++i)
    {
        printf("%d ", (char) s[i]);
    }
}

static void print_bitstring(uint64_t v) //used to inspect nanboxed values
{
    for (int i = 63; i >= 0; --i)
    {
        putchar((v & (1UL << i)) ? '1' : '0');
        if (i % 8 == 0) putchar(' ');
    }
    putchar('\n');
}

void test_scan_int(char *input, int32_t expected)
{
    int result = scan_int(input);
    char *status = result == expected ? "successful" : "failed";

    printf("Test %s; expected: %i; got %i\n", status, expected, result);
}

void test_scan_num(char *input, double expected)
{
    double result = scan_num(input);
    char *status = result == expected ? "successful" : "failed";

    printf("Test %s; expected: %.20f; got %.20f\n", status, expected, result);
}

void test_scan_esc_seq(char *input, char *expected)
{
    char result[5];
    scan_esc_seq(input, result);
    char *status = !strcmp(result, expected) ? "successful" : "failed";

    printf("Test %s;", status);
    printf(" Expected: ");
    print_str(expected);
    printf(" Got: ");
    print_str(result);
    putchar('\n');
}

int main(void)
{
    //write tests here


    return 0;
}