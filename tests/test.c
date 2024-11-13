#include <stdio.h>

#include "scanner.h"

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

int main(void)
{
    /* write tests here */
    return 0;
}