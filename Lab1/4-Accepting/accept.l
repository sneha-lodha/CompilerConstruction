%% 

((a(abbb+|b(abb+|b(ab+|b+a))))|(b+(a(abb+|(b+(ab+|b+a)))|b+(a(ab+|b+a)|b+aa))))b* {printf("accepted: %s\n", yytext);}
.* {printf("rejected: %s\n", yytext);} 
\n 
%% 
  
int yywrap(){return 1;}