#ifndef SCANNER_H
#define SCANNER_H

#include <stdint.h>

int32_t scan_int(char *s);
double scan_num(char *s);

char *scan_esc_seq_ascii(char *s);
char *scan_esc_seq_oct(char *s);
char *scan_esc_seq_hex(char *s);
char *scan_esc_seq_u_4(char *s);
char *scan_esc_seq_u_6(char *s);
char *scan_esc_seq_name(char *s);

#endif