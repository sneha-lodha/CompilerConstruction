%% 

[a-yA-Y0-8] {printf("%c", yytext[0] + 1);} 
[z]   {printf("a");}
[Z]   {printf("A");}
[9]   {printf("0");} 

%% 
  
int yywrap(){return 1;}