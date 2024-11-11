%{
#include <stdint.h>
#include <stdio.h>

extern int yylex(void);

void yyerror(const char *s);
%}

%union {
    double dval;
    int32_t ival;
    char *sval;
};

%token <ival> INTEGER
%token <dval> NUMBER
%token <sval> IDENTIFIER
%token <sval> STRING_TEXT ESC_SEQ
%token LPAREN RPAREN
%token LQUOTE RQUOTE

%%

list: LPAREN RPAREN
    | LPAREN expressions RPAREN
    ;

expressions: expression
           | expression expressions
           ;
expression: atom
          | list
          ;
atom: INTEGER
    | NUMBER
    | IDENTIFIER
    | string
    ;
string: LQUOTE RQUOTE
      | LQUOTE string_parts RQUOTE
      ;
string_parts: string_part
            | string_part string_parts
            ;
string_part: STRING_TEXT
           | ESC_SEQ
           ;

%%
void yyerror(const char *s){
    fprintf(stderr, "Error: %s\n", s);
}

