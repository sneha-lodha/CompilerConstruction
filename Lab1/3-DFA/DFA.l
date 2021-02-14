%% 

(a|bb)*ba(a|b)* {printf("DFA1 accepted: %s\n", yytext);}
(ab|abb)(a|(bb)*|(bb)+a) {printf("DFA2 accepted: %s\n", yytext);}
(aa*b)*aa*c(db|(da(aa*b)*(aa*c)))* {printf("DFA3 accepted: %s\n", yytext);}
.|\n {}
%% 
  
int yywrap(){return 1;}