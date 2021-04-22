#pragma once

#include <string>
#include <vector>
#include "LexType.h"

using namespace std;
struct Token {
	int Lineshow;
	LexType Lex;//单词语法信息，枚举
	string Sem;//单词语义信息 
};
//全局变量
int lineno;
FILE *source;
FILE *listing;
FILE* Fp;
int Tokennum;

enum NodeKind { ProK, PheadK, TypeK, VarK, ProcDeck, StmLK, DecK, StmtK, ExpK, ParamListK};
//enum LexType { ID, reserved_word, INTC};
enum Dec { ArrayK, CharK, IntegerK, RecordK, IdK };
enum Stmt { IfK, WhileK, AssignK, ReadK, WriteK };
enum Exp1 { OpK, ConstK, eIdK };

union Kind
{
	Dec dec;
	Stmt stmt;
	Exp1 exp;
};
enum varType { IdV, ArrayMembV, FieldMembV };
enum ExpType {Void, Integer, Boolean};
enum Paramt { valparamtype, varparamtype };

struct ArrayAttr
{
	int low;
	int up;
	string childType;
};

struct ProcAttr
{
	Paramt param;//记录过程的参数类型，表示过程的参数是值参还是变参
};

struct ExpAttr
{
	Token op;//记录语法树节点的运算符单词，为单词类型
	int val;//记录语法树节点的数值
	varType varkind;//记录变量的类别
	ExpType type;//记录语法树节点的检查类型

};

struct Attr
{
	ArrayAttr arrayattr;//记录数组类型的属性
	ProcAttr procAttr;//记录过程属性
	ExpAttr expattr;//记录表达式的属性
	vector<string>name;//name[0] 程序的名字
	int idnum = 0;
	vector<string>type_name;
};


struct TreeNode
{
	TreeNode* child[3] = { nullptr, nullptr, nullptr };//指向子语法树节点指针

	TreeNode* sibling = nullptr;//指向兄弟语法树节点指针
	int lineno;//记录源程序行号
	NodeKind nodekind;
	//string nodekind;
	Kind kind;//记录语法树节点的具体类型
	int idnum = 0;//记录一个节点中的标识符个数



	string name;//节点中标识符名字
	int* table[104]; //???数组成员是节点中各个标识符在符号表中的入口
	vector<string> type_name;//???记录类型名，当节点为声明类型，且类型是由类型标识符表示时有效
	Attr attr;//记录语法树节点其他属性，为结构体类型


};
