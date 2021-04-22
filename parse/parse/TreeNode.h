#pragma once

#include <string>
#include <vector>
#include "LexType.h"

using namespace std;
struct Token {
	int Lineshow;
	LexType Lex;//�����﷨��Ϣ��ö��
	string Sem;//����������Ϣ 
};
//ȫ�ֱ���
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
	Paramt param;//��¼���̵Ĳ������ͣ���ʾ���̵Ĳ�����ֵ�λ��Ǳ��
};

struct ExpAttr
{
	Token op;//��¼�﷨���ڵ����������ʣ�Ϊ��������
	int val;//��¼�﷨���ڵ����ֵ
	varType varkind;//��¼���������
	ExpType type;//��¼�﷨���ڵ�ļ������

};

struct Attr
{
	ArrayAttr arrayattr;//��¼�������͵�����
	ProcAttr procAttr;//��¼��������
	ExpAttr expattr;//��¼���ʽ������
	vector<string>name;//name[0] ���������
	int idnum = 0;
	vector<string>type_name;
};


struct TreeNode
{
	TreeNode* child[3] = { nullptr, nullptr, nullptr };//ָ�����﷨���ڵ�ָ��

	TreeNode* sibling = nullptr;//ָ���ֵ��﷨���ڵ�ָ��
	int lineno;//��¼Դ�����к�
	NodeKind nodekind;
	//string nodekind;
	Kind kind;//��¼�﷨���ڵ�ľ�������
	int idnum = 0;//��¼һ���ڵ��еı�ʶ������



	string name;//�ڵ��б�ʶ������
	int* table[104]; //???�����Ա�ǽڵ��и�����ʶ���ڷ��ű��е����
	vector<string> type_name;//???��¼�����������ڵ�Ϊ�������ͣ��������������ͱ�ʶ����ʾʱ��Ч
	Attr attr;//��¼�﷨���ڵ��������ԣ�Ϊ�ṹ������


};
