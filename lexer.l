%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"
#include "AST.h"
#include "semantics.h"
#include "code_gen.h"
#include "parser.tab.h"

int chars = 0;
int words = 0;
int lines = 0;
int nConst = 0;
int nSymbols = 0;
int errors = 0;

extern int yywrap();

%}

%x COMMENT

%option yylineno

delim   [ \t\n]
digit [0-9]
character [a-zA-Z]


ID {character}+{digit}*
ws	{delim}+
CHARVAL	(\'[A-Za-z]\')


%%

"//".*					{ /* Do nothing, Eat up Comment */ } 

"/*"					{ BEGIN(COMMENT); }
<COMMENT>"*/" 		    { BEGIN(INITIAL); }
<COMMENT>[^*\n]+		
<COMMENT>"*"			
<COMMENT>"\n"		{ lines += 1; }

int								{words++; chars += strlen(yytext); return INT_T;}
char            				{words++; chars += strlen(yytext); return CHAR_T;}
float                           {words++; chars += strlen(yytext); return FLOAT_T;}
void                            {words++; chars += strlen(yytext); return VOID_T;}
writeln							{words++; chars += strlen(yytext); return WRITELN_T;}
write                           {words++; chars += strlen(yytext); return WRITE_T;}
while                           {words++; chars += strlen(yytext); return WHILE_T;}
if                              {words++; chars += strlen(yytext); return IF_T;}
else 		                    {words++; chars += strlen(yytext); return ELSE_T;}
return                          {words++; chars += strlen(yytext); return RETURN_T;}
break                           {words++; chars += strlen(yytext); return BREAK_T;}
read                            {words++; chars += strlen(yytext); return READ_T;}
{ID}+           			    {words++; insert(yytext, strlen(yytext), UNDEF, yylineno); chars += strlen(yytext); yylval.symtab_item = lookup(yytext); return ID;}
{digit}+						{nConst++; yylval.val.ival = atoi(yytext); return NUMBER;}
{digit}+"."{digit}*  	        {nConst++; yylval.val.fval = atof(yytext); return NUM_FLOAT;}
{CHARVAL}                       {nConst++; yylval.val.cval = yytext[1]; return CHAR_VAL;}
";"				  				{nSymbols++; return SEMICOLON;}
"="								{nSymbols++; return EQUAL;}
"("             				{nSymbols++; return LEFTPAREN;}
")"             				{nSymbols++; return RIGHTPAREN;}
"["             				{nSymbols++; return LEFTBRAC;}
"]"             				{nSymbols++; return RIGHTBRAC;}
"{"                             {nSymbols++; return LEFTCURLY;}
"}"                             {nSymbols++; return RIGHTCURLY;}
","                             {nSymbols++; return COMMA;}
"!"                             {nSymbols++; return EXCLAMCOND;}
"&&"							{nSymbols++; return ANDCOND;}
"||"							{nSymbols++; return ORCOND;}
"+"                             {nSymbols++; return PLUS;}
"-"                             {nSymbols++; return MINUS;}
"*"                             {nSymbols++; return TIMES;}
"/"                             {nSymbols++; return DIVIDE;}
"<"                             {nSymbols++; return LTCOND;}
">"                             {nSymbols++; return GTCOND;}
"<="                            {nSymbols++; return LTECOND;}
">="                            {nSymbols++; return GTECOND;}
"!="                            {nSymbols++; return NOTEQUAL;}
"=="                            {nSymbols++; return EQCOND;}    
{digit}+{character}+            {words++; errors++; printf("LEXICAL ERROR: %s Illegal Word. If you want to define a variable, it cannot start with a number.\n", yytext);}
\n						        {lines++; chars++;}
{ws}*							{/*do nothing, it is empty*/}
.								{}
%%

int yywrap() {return (1);}
