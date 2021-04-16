#pragma once
#include "const.h"
typedef enum  {

	/*保留字*/
	PROGRAM, PROCEDURE, TYPE, VAR, IF, THEN, ELSE, FI, WHILE, DO, ENDWH,
	BEGIN1, END1, READ, WRITE, ARRAY, OF, RECORD, RETURN1,
	//类型
	INTEGER, CHAR1,
	/*多字符单词符号*/
	ID, INTC, CHARC,
	/*特殊符号*/
	ASSIGN, EQ, LT, PLUS, MINUS, TIMES, OVER, LPAREN, RPAREN, DOT, COLON,
	SEMI, COMMA, LMIDPAREN, RMIDPAREN, UNDERANGE,

	ENDFILE, ERROR
}LexType;


static struct
{
	const char* str;
	LexType tok;
}reservedWords[MAXRESERVED] = //保留字和类型  21个
	{	{"program",PROGRAM},{"procedure",PROCEDURE},{"type",TYPE},{"var",VAR},{"if",IF},{"then",THEN},
		{"else",ELSE},{"fi",FI},{"while",WHILE},{"do",DO},{"endwh",ENDWH},{"begin",BEGIN1},
		{"end",END1},{"read",READ},{"write",WRITE},{"array",ARRAY},{"of",OF},{"record",RECORD},
		{"return",RETURN1},

		{"integer",INTEGER},{"char",CHAR1}
	};


static struct
{
	const char* str;
	LexType tok;
}LexToChar[MAXLEX] = //42
	{ 
		{"program",PROGRAM},{"procedure",PROCEDURE},{"type",TYPE},{"var",VAR},{"if",IF},
		{"then",THEN},{"else",ELSE},{"fi",FI},{"while",WHILE},{"do",DO},
		{"endwh",ENDWH},{"begin",BEGIN1},{"end",END1},{"read",READ},{"write",WRITE},
		{"array",ARRAY},{"of",OF},{"record",RECORD}, {"return",RETURN1},{"integer",INTEGER},
		{"char",CHAR1},{"ID",ID},{"INTC",INTC},{"CHARC",CHARC},
		//{"assign",ASSIGN},{"eq",EQ},{"lt",LT,},{"plus",PLUS},{"minus",MINUS},{"times",TIMES},{"over",OVER},
		//{"lparen",LPAREN},{"rparen",RPAREN},{"dot",DOT},{"colon",COLON},{"semi",SEMI},{"comma",COMMA},
		//{"lmidparen",LMIDPAREN},{"rmidraren",RMIDPAREN},{"underange",UNDERANGE},

		{":=",ASSIGN},{"=",EQ},{"<",LT,},{"+",PLUS},{"-",MINUS},{"*",TIMES},{"/",OVER},
		{"(",LPAREN},{")",RPAREN},{".",DOT},{":",COLON},{";",SEMI},{",",COMMA},
		{"[",LMIDPAREN},{"]",RMIDPAREN},{"..",UNDERANGE},

		{"program",PROGRAM},{"error",ERROR}
	};

