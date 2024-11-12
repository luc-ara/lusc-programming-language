#include <stdio.h>

#include "scanner.h"

void test_scan_int(int32_t (*function)(char *), char *input, int32_t expected)
{
    int result = function(input);
    char *status = result == expected ? "successful" : "failed";

    printf("Test %s; expected: %i; got %i\n", status, expected, result);
}

void test_scan_num(double (*function)(char *), char *input, double expected)
{
    double result = function(input);
    char *status = result == expected ? "successful" : "failed";

    printf("Test %s; expected: %f; got %f\n", status, expected, result);
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

    printf("Testing bin_to_num:\n");
    test_scan_num(bin_to_num, "0b0.0", 0.0);
    test_scan_num(bin_to_num, "-0b0.0", -0.0);
    test_scan_num(bin_to_num, "0b1.0", 1.0);
    test_scan_num(bin_to_num, "-0b1.0", -1.0);
    test_scan_num(bin_to_num, "0b1.1", 1.5);
    test_scan_num(bin_to_num, "-0b1.1", -1.5);
    test_scan_num(bin_to_num, "0b110110.0", 54.0);
    test_scan_num(bin_to_num, "-0b1.100101", -1.578125);
    test_scan_num(bin_to_num, "-0b10110110.1001101001", -182.6025390625);

    printf("Testing oct_to_num:\n");
    test_scan_num(oct_to_num, "0o0.0", 0.0);
    test_scan_num(oct_to_num, "-0o0.0", -0.0);
    test_scan_num(oct_to_num, "0o1.0", 1.0);
    test_scan_num(oct_to_num, "-0o1.0", -1.0);
    test_scan_num(oct_to_num, "0o1.4", 1.5);  // 1.4 octal is 1.5 in decimal
    test_scan_num(oct_to_num, "-0o1.4", -1.5);
    test_scan_num(oct_to_num, "0o12.0", 10.0);  // 12 octal is 10 in decimal
    test_scan_num(oct_to_num, "-0o14.3", -12.375);  // 14.3 octal is 12.375 in decimal
    test_scan_num(oct_to_num, "-0o173.45", -123.5625);  // 173.45 octal is 123.5625 in decimal

    printf("Testing dec_to_num:\n");
    test_scan_num(dec_to_num, "123.0", 123.0);
    test_scan_num(dec_to_num, "-678.0", -678.0);
    test_scan_num(dec_to_num, "0d9876.5", 9876.5);  // d prefix for decimal (though optional)
    test_scan_num(dec_to_num, "-0d5432.25", -5432.25);
    test_scan_num(dec_to_num, "0D112233.125", 112233.125);  // d prefix with capital D
    test_scan_num(dec_to_num, "-0D445566.75", -445566.75);

    printf("Testing hex_to_num:\n");
    test_scan_num(hex_to_num, "0x1.0", 1.0);  // 1 hex = 1.0 decimal
    test_scan_num(hex_to_num, "-0x4.8", -4.5);  // 4.8 hex = 4.5 decimal
    test_scan_num(hex_to_num, "0X5.3C", 5.234375);  // 5.3C hex = 5.234375 decimal
    test_scan_num(hex_to_num, "-0XABCDEF.5", -11259375.3125);  // ABCDEF hex = 11259375.3125 decimal
    test_scan_num(hex_to_num, "0x0.0", 0.0);  // 0x0 = 0.0
    test_scan_num(hex_to_num, "-0xFF.8", -255.5);  // FF hex = 255 decimal, with fractional part
    return 0;
}