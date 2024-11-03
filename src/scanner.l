%{
#include <stdio.h>
%}

BIT          [01]
OCTIT        [0-8]
DIGIT        [0-9]
HEXIT        [0-9a-fA-F]
ALPHA        [a-zA-Z]

BRACKET      [\(\)\[\]\{\}]
PUNCT        [\?\!\@\#\$\%\&\*\+\-\=\:\<\>\\\/]

SPACE        [\ \t\n]

SPACES       {SPACE}+

BIN-BASE     0[bB]
OCT-BASE     0[oO]
DEC-BASE     0[dD]
HEX-BASE     0[hH]

BITS         {BIT}+
OCTITS       {OCTIT}+
DIGITS       {DIGIT}+
HEXITS       {HEXIT}+

BIN-INT      {BIN-BASE}{BITS}
OCT-INT      {OCT-BASE}{OCTITS}
DEC-INT      {DEC-BASE}?{DIGITS}
HEX-INT      {HEX-BASE}{HEXITS}

BIN-NUM      {BIN-INT}\.{BITS}
OCT-NUM      {OCT-INT}\.{OCTITS}
DEC-NUM      {DEC-INT}\.{DIGITS}
HEX-NUM      {HEX-INT}\.{HEXITS}

IDENTIFIER   ({ALPHA}|{PUNCT})({ALPHA}|{PUNCT}|{DIGIT})*

DELIMITER    ({SPACES}|{BRACKET})

%%

"("                         {printf("Open parenthesis: \"(\"\n");}
")"                         {printf("Close parenthesis: \")\"\n");}

{BIN-INT}/{DELIMITER}       {printf("Binary Integer: %s\n", yytext);}
{OCT-INT}/{DELIMITER}       {printf("Octal Integer: %s\n", yytext);}
{DEC-INT}/{DELIMITER}       {printf("Decimal Integer: %s\n", yytext);}
{HEX-INT}/{DELIMITER}       {printf("Hexadecimal Integer: %s\n", yytext);}

{BIN-NUM}/{DELIMITER}       {printf("Binary Number: %s\n", yytext);}
{OCT-NUM}/{DELIMITER}       {printf("Octal Number: %s\n", yytext);}
{DEC-NUM}/{DELIMITER}       {printf("Decimal Number: %s\n", yytext);}
{HEX-NUM}/{DELIMITER}       {printf("Hexadecimal Number: %s\n", yytext);}

{IDENTIFIER}/{DELIMITER}    {printf("Identifier: %s\n", yytext);}

{SPACES}                    {;}

.                           {printf("Error: Unidentified sequence: %s\n", yytext); return 0;}

%%


