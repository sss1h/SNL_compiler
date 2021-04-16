#pragma once
#include <vector>
#include <string>
#include "Token.h"
#include "LexType.h"
using std::string;
using std::vector;

struct
{
	Token token;
	vector<Token>predict;
	
}Pre[104] =
{
	{PROGRAM}, {PROGRAM}, {ID}, {TYPE, VAR, PROCEDURE, BEGIN}, {VAR, PROCEDURE, BEGIN}, {TYPE}, {TYPE}, {ID}, {VAR, PROCEDURE, BEGIN}, {ID},
	{ID}, {INTEGER, CHAR}, {ARRAY, RECORD}, {ID}, {INTEGER}, {CHAR}, {ARRAY}, {RECORD}, {ARRAY}, {INTC},
	{INTC}, {RECORD}, {INTEGER, CHAR}, {ARRAY}, {END}, {INTEGER, CHAR, ARRAY}, {ID}, {; }, {COMMA}, {PROCEDURE, BEGIN},
	{VAR}, {VAR}, {INTEGER, CHAR, ARRAY, RECORD, ID}, {PROCEDURE, BEGIN}, {INTEGER, CHAR, ARRAY, RECORD, ID}, {ID}, {; }, {COMMA}, {BEGIN}, {PROCEDURE},
	{PROCEDURE}, {BEGIN}, {PROCEDURE}, {ID}, {)}, {INTEGER, CHAR, ARRAY, RECORD, ID, VAR}, {INTEGER, CHAR, ARRAY, RECORD, ID, VAR}, {(}, {; }, {INTEGER, CHAR, ARRAY, RECORD, ID},
	{VAR}, {ID}, {;, )}, {COMMA}, {TYPE, VAR, PROCEDURE, BEGIN}, {BEGIN}, {BEGIN}, {ID, IF, WHILE, RETURN, READ, WRITE}, {ELSE, FI, END, ENDWH}, {; },
	{IF}, {WHILE}, {READ}, {WRITE}, {RETURN}, {ID}, {:= }, {(}, {[, DOT, := }, {IF},
	{WHILE}, {READ},  {ID}, {WRITE}, {RETURN}, {(}, {)}, {(, INTC, ID}, {)}, {COMMA},
	{(, INTC, ID}, { <, =}, {(, INTC, ID}, { <, =, ], THEN, ELSE, FI, DO, ENDWH, ), END, ;, COMMA }, {+, -}, {(, INTC, ID}, {+, -, <, =, ], THEN, ELSE, FI, DO, ENDWH, ), END, ;, COMMA}, {*, / }, {(}, {INTC},
	{ID}, {ID}, {:=, *, /, +, -, <, =, THEN, ELSE,  FI, DO, ENDWH, ), END, ;, COMMA}, {[}, {DOT}, {ID}, {:=, *, /, +, -, <, =, THEN, ELSE, FI, DO, ENDWH, ), END, ;, COMMA}, {[}, {<}, {=},
	{+}, {-}, {*}, {/}
}
;

