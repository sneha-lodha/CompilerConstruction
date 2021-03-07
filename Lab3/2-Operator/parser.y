%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

extern int yylex(void);
extern void yylex_destroy(void);
extern char *yytext;

int x = 0;
int y = 0;
int z = 0;

void yyerror(char const *msg) {
  printf("%s\n", msg);
  yylex_destroy();
  exit(EXIT_SUCCESS);
}
%}

%define parse.error verbose
%union {
   u_int num;
   char character;
};
%type <num> factor
%type <num> statement
%type <num> expression
%token <character> IDENTIFIER

%start program
%token NUMBER PLUS MINUS TIMES DIVIDE LEFT_PARENTHESIS RIGHT_PARENTHESIS EXPO ASSIGNMENT LET PRINT SEMICOLON
%token NEWLINE INVALID PERIOD

%left PLUS MINUS
%left TIMES DIVIDE
%left UMINUS

%right EXPO

%%

program : statement
        | program SEMICOLON statement

statement : LET IDENTIFIER ASSIGNMENT expression {
            switch ($2) {
                case 'x':
                    x = $4;
                    break;
                case 'y':
                    y = $4;
                    break;
                case 'z':
                    z = $4;
                    break;
                default:
                    yyerror("unknown variable in statement");
            }      
          }
          | PRINT expression {printf("%d\n", $2);}

expression : factor {$$ = $1;}
           | expression PLUS expression {$$ = $1 + $3;}
           | expression MINUS expression {$$ = $1 - $3;}
           | expression TIMES expression {$$ = $1 * $3;}
           | expression DIVIDE expression {$$ = $1 / $3;}
           | expression EXPO expression {$$ = pow($1, $3);}
           ;

factor : NUMBER {$$ = atoi(yytext);}
       | MINUS factor %prec UMINUS {$$ = -($2);}
       | LEFT_PARENTHESIS expression RIGHT_PARENTHESIS {$$ = $2;}
       | IDENTIFIER {
            switch ($1){
                case 'x':
                    $$ = x;
                    break;
                case 'y':
                    $$ = y;
                    break;
                case 'z':
                    $$ = z;
                    break;
                default:
                    yyerror("unkown variable in expression");
            }
       }
       ;

%%

int main(void) {
  yyparse();
  yylex_destroy();
  return EXIT_SUCCESS;
}
