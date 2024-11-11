%{
#include <stdio.h>
#include <string.h>

#include "scanner.h"
#include "parser.tab.h"
%}

%x STR

BIT             [01]
OCTIT           [0-8]
DIGIT           [0-9]
HEXIT           [0-9a-fA-F]
ALPHA           [a-zA-Z]

BRACKET         [\(\)\[\]\{\}]
PUNCT           [\?\!\@\#\$\%\&\*\+\-\=\:\<\>\\\/]

SPACE           [\ \t\n]

SPACES          {SPACE}+

BIN-BASE        0[bB]
OCT-BASE        0[oO]
DEC-BASE        0[dD]
HEX-BASE        0[xX]

BITS            {BIT}+
OCTITS          {OCTIT}+
DIGITS          {DIGIT}+
HEXITS          {HEXIT}+

BIN-INT         \-?{BIN-BASE}{BITS}
OCT-INT         \-?{OCT-BASE}{OCTITS}
DEC-INT         \-?{DEC-BASE}?{DIGITS}
HEX-INT         \-?{HEX-BASE}{HEXITS}

BIN-NUM         {BIN-INT}\.{BITS}
OCT-NUM         {OCT-INT}\.{OCTITS}
DEC-NUM         {DEC-INT}\.{DIGITS}
HEX-NUM         {HEX-INT}\.{HEXITS}

INT             {BIN-INT}|{OCT-INT}|{DEC-INT}|{HEX-INT}
NUM             {BIN-NUM}|{OCT-NUM}|{DEC-NUM}|{HEX-NUM}

IDENTIFIER      ({ALPHA}|{PUNCT})({ALPHA}|{PUNCT}|{DIGIT})*

DELIMITER       {SPACE}|{BRACKET}

ESC-SEQ-ASCII   \\[\\\'\"\?abfnrtv0e]
ESC-SEQ-OCT     \\{OCTIT}{3}
ESC-SEQ-HEX     \\[xX]{HEXIT}{2}
ESC-SEQ-U-4     \\[uU]{HEXIT}{4}
ESC-SEQ-U-6     \\[uU]00{HEXIT}{6}
ESC-SEQ-NAME    \\[nN]\{[a-zA-Z0-9 _-]+\}

ESC-SEQ         {ESC-SEQ-ASCII}|{ESC-SEQ-OCT}|{ESC-SEQ-HEX}|{ESC-SEQ-U-4}|{ESC-SEQ-U-6}|{ESC-SEQ-NAME}

STRING-TEXT     ([^\\\"\'\n])+

COMMENT         ;.*

STRING-LINE     \\{SPACES}?{COMMENT}?\n{SPACES}?\\
%%

"("                         {return LPAREN;}
")"                         {return RPAREN;}

{BIN-INT}/{DELIMITER}       {yylval.ival = bin_to_int(yytext); return INTEGER;}
{OCT-INT}/{DELIMITER}       {yylval.ival = oct_to_int(yytext); return INTEGER;}
{DEC-INT}/{DELIMITER}       {yylval.ival = dec_to_int(yytext); return INTEGER;}
{HEX-INT}/{DELIMITER}       {yylval.ival = hex_to_int(yytext); return INTEGER;}

{BIN-NUM}/{DELIMITER}       {yylval.dval = bin_to_num(yytext); return NUMBER;}
{OCT-NUM}/{DELIMITER}       {yylval.dval = oct_to_num(yytext); return NUMBER;}
{DEC-NUM}/{DELIMITER}       {yylval.dval = dec_to_num(yytext); return NUMBER;}
{HEX-NUM}/{DELIMITER}       {yylval.dval = hex_to_num(yytext); return NUMBER;}

{IDENTIFIER}/{DELIMITER}    {yylval.sval = strdup(yytext); return IDENTIFIER;}

{SPACES}                    {;}

{COMMENT}                   {;}

\"                          {return LQUOTE;}

<STR>{STRING-TEXT}          {yylval.sval = strdup(yytext); return STRING_TEXT;}

<STR>{ESC-SEQ-ASCII}        {yylval.sval = scan_esc_seq_ascii(yytext); return ESC_SEQ;}
<STR>{ESC-SEQ-OCT}          {yylval.sval = scan_esc_seq_oct(yytext); return ESC_SEQ;}
<STR>{ESC-SEQ-HEX}          {yylval.sval = scan_esc_seq_hex(yytext); return ESC_SEQ;}
<STR>{ESC-SEQ-U-4}          {yylval.sval = scan_esc_seq_u_4(yytext); return ESC_SEQ;}
<STR>{ESC-SEQ-U-6}          {yylval.sval = scan_esc_seq_u_6(yytext); return ESC_SEQ;}
<STR>{ESC-SEQ-NAME}         {yylval.sval = scan_esc_seq_name(yytext); return ESC_SEQ;}

<STR>{STRING-LINE}          {;}

<STR>\"                     {return RQUOTE;}

<INITIAL>.                  {fprintf(yyout, "Error: Unidentified character\n"); return 0;}
<STR>(.|\n)                 {fprintf(yyout, "Error: Invalid character inside string\n"); return 0;}
