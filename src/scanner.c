#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "scanner.h"

static int scan_hexit(char c) {
    if (c > '0' && c < '9')
        return c-'0';
    else {
        switch (c) {
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
}

int32_t bin_to_int(char *s){
    int cur = 0; //track current position
    bool neg = s[cur] == '-' ? (cur++,true) : false; //check sign and skip it
    int64_t result = 0;

    cur += 2; //skip base

    while (s[cur] != '\0') {
        result *= 2;
        result += (s[cur]-'0')*(neg ? -1 : 1);

        if (result < INT32_MIN || result > INT32_MAX) {
            perror("Integer value too big or too small");
            exit(1);
        }

        cur++;
    }

    return (int32_t) result;
}

int32_t oct_to_int(char *s){
    int cur = 0;
    bool neg = s[0] == '-' ? (cur++,true) : false;
    int64_t result = 0;
    
    cur += 2;

    while (s[cur] != '\0') {
        result *= 8;
        result += (s[cur]-'0')*(neg ? -1 : 1);

        if (result < INT32_MIN || result > INT32_MAX) {
            perror("Integer value too big or too small");
            exit(1);
        }

        cur++;
    }

    return (int32_t) result;
}

int32_t dec_to_int(char *s){
    int cur = 0;
    bool neg = s[0] == '-' ? (cur++,true) : false;
    int64_t result = 0;
    
    if (s[cur] == '0' && (s[cur+1] == 'd' || s[cur+1] == 'D')) //skip optional base
        cur += 2;

    while (s[cur] != '\0') {
        result *= 10;
        result += (s[cur]-'0')*(neg ? -1 : 1);

        if (result < INT32_MIN || result > INT32_MAX) {
            perror("Integer value too big or too small");
            exit(1);
        }

        cur++;
    }

    return (int32_t) result;
}

int32_t hex_to_int(char *s){
    int cur = 0;
    bool neg = s[0] == '-' ? (cur++,true) : false;
    int64_t result = 0;
    
    cur += 2 ;

    while (s[cur] != '\0') {
        result *= 16;
        result += scan_hexit(s[cur])*(neg ? -1 : 1);

        if (result < INT32_MIN || result > INT32_MAX) {
            perror("Integer value too big or too small");
            exit(1);
        }

        cur++;
    }

    return result;
}


double bin_to_num(char *s){
    double cur = 0;
    bool neg = s[0] == '-' ? (cur++,true) : false;
    double result = 0.0;
    int dec_pos = 0;

    cur += 2;

    while (s[cur] != '\0' && s[cur] != '.') {
        result *= 2;
        result += (s[cur]-'0')*(neg ? -1 : 1);
        cur++;
    }

    if (s[cur] == '\0')
        return result;
    
    cur++;

    while (s[cur] != '\0') {
        result += (s[cur]-'0')*(neg ? -1 : 1)/pow(2, ++dec_pos);
        cur++;
    }

    return result;
}

double oct_to_num(char *s){
    double cur = 0 ;
    bool neg = s[0] == '-' ? (cur++,true) : false ;
    double result = 0.0;
    int dec_pos = 0;

    cur += 2;
    
    while (s[cur] != '\0' && s[cur] != '.') {
        result *= 8;
        result += (s[cur]-'0')*(neg ? -1 : 1);
        cur++;
    }

    if (s[cur] == '\0')
        return result;
    
    cur++;

    while (s[cur] != '\0') {
        result += (s[cur]-'0')*(neg ? -1 : 1)/pow(8, ++dec_pos);
        cur++;
    }

    return result;
}

double dec_to_num(char *s){
    double cur = 0 ;
    bool neg = s[0] == '-' ? (cur++,true) : false ;
    double result = 0.0;
    int dec_pos = 0;

    if (s[cur] == 0 && (s[cur+1] == 'd' || s[cur+1] == 'D'))
        cur += 2;
    
    while (s[cur] != '\0' && s[cur] != '.') {
        result *= 10;
        result += (s[cur]-'0')*(neg ? -1 : 1);
        cur++;
    }

    if (s[cur] == '\0')
        return result;
    
    cur++;

    while (s[cur] != '\0') {
        result += (s[cur]-'0')*(neg ? -1 : 1)/pow(10, ++dec_pos);
        cur++;
    }

    return result;
}

double hex_to_num(char *s){
    double cur = 0 ;
    bool neg = s[0] == '-' ? (cur++,true) : false ;
    double result = 0.0;
    int dec_pos = 0;

    cur += 2;
    
    while (s[cur] != '\0' && s[cur] != '.') {
        result *= 10;
        result += scan_hexit(s[cur])*(neg ? -1 : 1);
        cur++;
    }

    if (s[cur] == '\0')
        return result;
    
    cur++;

    while (s[cur] != '\0') {
        result += scan_hexit(s[cur])*(neg ? -1 : 1)/pow(16, ++dec_pos);
        cur++;
    }

    return result;
}


char *scan_esc_seq_ascii(char *s){
    
}

char *scan_esc_seq_oct(char *s){
    
}

char *scan_esc_seq_hex(char *s){
    
}

char *scan_esc_seq_u_4(char *s){
    
}

char *scan_esc_seq_u_6(char *s){
    
}

char *scan_esc_seq_name(char *s){
    
}
