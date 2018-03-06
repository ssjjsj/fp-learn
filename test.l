%{
#include <stdio.h>
#include <y.tab.h>
%}
 
%%
GET               return METHOD;
POST              return METHOD;
HEAD              return METHOD;
Connection        return CONNECTION;
":"               return SEPARATOR;
Date              return DATE;
[.]+         return INFO;
"\r\n"            return BLANKLINE;
%%