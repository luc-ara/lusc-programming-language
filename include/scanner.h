#ifndef SCANNER_H
#define SCANNER_H

#include <stdint.h>

int32_t scan_int(char *s);
double scan_num(char *s);
void scan_esc_seq(char *s, char *r);

#endif