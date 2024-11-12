#include <stdio.h>

#include "scanner.h"

void test_scan_int(int32_t (*function)(char *), char *input, int32_t expected)
{
    int result = function(input);
    char *status = result == expected ? "successful" : "failed";

    printf("Test %s; expected: %i; got %i\n", status, expected, result);
}

int main(void)
{

    printf("Testing bin_to_int:\n");
    test_scan_int(bin_to_int, "0b0", 0b0);
    test_scan_int(bin_to_int, "-0b0", -0b0);
    test_scan_int(bin_to_int, "0b1101", 0b1101);
    test_scan_int(bin_to_int, "0b001101", 0b001101);
    test_scan_int(bin_to_int, "0b1010101", 0b1010101);
    test_scan_int(bin_to_int, "0b0011001100", 0b0011001100);
    test_scan_int(bin_to_int, "-0b11001101", -0b11001101);
    test_scan_int(bin_to_int, "-0B110011", -0b110011);

    printf("Testint oct_to_int:\n");
    test_scan_int(oct_to_int, "0o0", 00);
    test_scan_int(oct_to_int, "-0o0", -00);
    test_scan_int(oct_to_int, "0o76362", 076362);
    test_scan_int(oct_to_int, "-0o3264723", -03264723);
    test_scan_int(oct_to_int, "-0O23746", -023746);
    test_scan_int(oct_to_int, "0o123455", 0123455);

    printf("Testing dec_to_int:\n");
    test_scan_int(dec_to_int, "0d0", 0);
    test_scan_int(dec_to_int, "0", 0);
    test_scan_int(dec_to_int, "-0d0", -0);
    test_scan_int(dec_to_int, "-0", -0);
    test_scan_int(dec_to_int, "12345", 12345);
    test_scan_int(dec_to_int, "-67890", -67890);
    test_scan_int(dec_to_int, "0d9876", 9876);
    test_scan_int(dec_to_int, "-0d5432", -5432);
    test_scan_int(dec_to_int, "0D112233", 112233);
    test_scan_int(dec_to_int, "-0D445566", -445566);

    printf("Testing hex_to_int:\n");
    test_scan_int(hex_to_int, "0x0", 0x0);
    test_scan_int(hex_to_int, "-0x0", -0x0);
    test_scan_int(hex_to_int, "0x1A3F", 0x1A3F);
    test_scan_int(hex_to_int, "-0x4B2", -0x4B2);
    test_scan_int(hex_to_int, "0X5D3C", 0x5D3C);
    test_scan_int(hex_to_int, "-0XABCDEF", -0xABCDEF);
    test_scan_int(hex_to_int, "-0xFF", -0xFF);

    return 0;
}