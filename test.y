%{
    #include <stdio.h>
%}
 
/* Declarations (Optional token definitions) */
%token METHOD
%token CONNECTION
%token INFO
%token DATE
%token BLANKLINE
%token SPACE
%token LOE
%token SEPARATOR


 
%%
/* Parsing ruleset definitions*/
request: 
        state_line all_head_field blank_line content
        ;

state_line:    METHOD SPACE uri SPACE version LOE 
        {printf("get state line\n");}
        ;

all_head_field: head_field
                | head_field all_head_field
        ;


head_field:    |  
               CONNECTION SEPARATOR SPACE INFO
                {printf("get connction info\n");}
               |  DATE SEPARATOR SPACE INFO
               {printf("get date info\n");}
        ;


blank_line: BLANKLINE
            {printf("get blank line\n");}
        ;

content: 
        | INFO
        {printf("get body content\n");}
        ;


uri: INFO;

version: INFO;
%%

/* Additional C source code */