// parse.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "TreeNode.h"

#include "LexType.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
using namespace std;
TreeNode* parse(void);
TreeNode* Program(void);
vector<string> split(string s, char ch);
TreeNode* ProgramHead(void);
TreeNode* DeclarePart(void);
TreeNode* TypeDec(void);
TreeNode* TypeDeclaration(void);
TreeNode* TypeDecList(void);
TreeNode* TypeDecMore(void);
void TypeId(TreeNode* t);
void TypeDef(TreeNode* t);
void BaseType(TreeNode* t);
void StructureType(TreeNode* t);
void ArrayType(TreeNode* t);
void RecType(TreeNode* t);
TreeNode* FieldDecList(TreeNode* t);
TreeNode* FieldDecMore(void);
void IdList(TreeNode* t);
void IdMore(TreeNode* t);
TreeNode* VarDec(void);
TreeNode* VarDeclaration(void);
TreeNode* VarDecList(void);
TreeNode* VarDecMore(void);
void VarIdList(TreeNode* t);
void VarIdMore(TreeNode* t);
TreeNode* ProcDec(void);
TreeNode* ProcDeclaration(void);
void ParamList(TreeNode* t);
TreeNode* ParamDecList(void);
TreeNode* ParamMore(void);
TreeNode* Param(void);
void FormList(TreeNode* t);
void FidMore(TreeNode* t);
TreeNode* ProcDecPart();
TreeNode* ProcBody();
TreeNode* ProgramBody();
TreeNode* StmList();
TreeNode* StmMore();
TreeNode* Stm();
TreeNode* AssCall();
TreeNode* AssignmentRest();
TreeNode* ConditionalStm();
TreeNode* LoopStm();
TreeNode* InputStm();
TreeNode* OutputStm();
TreeNode* ReturnStm();
TreeNode* CallStmRest();
TreeNode* ActParamList();
TreeNode* ActParamMore();
TreeNode* Exp();
TreeNode* Simple_exp();
TreeNode* term();
TreeNode* factor();
TreeNode* variable();
void variMore(TreeNode* t);
TreeNode* fieldvar();
void fieldvarMore(TreeNode* t);
void match(LexType);

void ReadWord();
int StringtoInt(string s);
string DelBlank(string s);


ifstream f("out.txt");

Token tok;




int main()
{


    TreeNode* t = nullptr;
    t = parse();
    


    f.close();
    return 0;
    //output syntax tree
    ofstream of("ast.txt");
    queue<TreeNode*> q;
    q.push(t);
    string s = "";
    while (!q.empty())
    {
        TreeNode* p = q.front();
        q.pop();
        if (p == nullptr)
        {
            s.push_back(' ');
            continue;
        }
        cout << s;
        if (p->sibling != nullptr)
        {
            q.push(p->sibling);
        }
        else
        {
            q.push(nullptr);
        }
        for (int i = 0; i < 3; i++)
        {
            if (p->child[i] != nullptr)
            {
                q.push(p->child[i]);
            }
        }
    }
    of.close();
    return 0;
    
}

TreeNode* parse(void)
{
    TreeNode* t = nullptr;
    
    ReadWord();
    t = Program();


    

    if (tok.Lex != ENDFILE)
    {
        //文件提前结束错误处理
        cout << tok.Lineshow<<" 文件提前结束错误" << endl;
    }
        
    return t;
}

//总程序处理分析程序
TreeNode* Program(void)
{
    
    TreeNode *t = nullptr, *q = nullptr, *s = nullptr;
 
    t = ProgramHead();
    q = DeclarePart();
	
    s = ProgramBody();
    TreeNode*root = new TreeNode;
    root->nodekind = ProK;
    if (root == nullptr)//创建失败
    {
        ;
    }
    else
    {
        if (t == nullptr)
        {
            //错误信息提示 
            cout << "不存在程序头" << endl;
        }
        else
        {
            root->child[0] = t;
        }

        if (q != nullptr)
        {
            root->child[1] = q;
        }

        if (s == nullptr)
        {
            //错误信息提示
            cout << "不存在程序体" << endl;
        }
        else
        {
            root->child[2] = s;
        }

        
    }

    

    match(DOT);
    //当前单词和DOT匹配
    return root;
}


//程序头部分处理分析程序
TreeNode* ProgramHead(void)
{
    //创建新的程序头类型节点
    TreeNode* t = nullptr;
    t = new TreeNode;
    t->nodekind = PheadK;
 
    match(PROGRAM);


    

    //新语法树节点t创建成功，当前单词为ID
    
    if (t != nullptr && tok.Lex == ID)
    {
        
        ((t->attr).name).push_back(tok.Sem);//program name
    }
    match(ID);


    return t;
}


//程序声明部分处理分析程序
TreeNode* DeclarePart(void)
{
    TreeNode * typeP = nullptr, * pp = nullptr;
    typeP = new TreeNode;
    typeP->nodekind = TypeK;
    pp = new TreeNode;
    if (typeP != nullptr)
    {
        
        TreeNode *tp1 = TypeDec();//类型声明
        typeP->child[0] = tp1;

    }

    TreeNode* varP = nullptr;
    varP = new TreeNode;
    varP->nodekind = VarK;
    if (varP != nullptr)
    {
        
        TreeNode*tp2 = VarDec();//变量声明
        varP->child[0] = tp2;
    }

    
    TreeNode*s = ProcDec();//过程声明

    if (varP == nullptr)
    {
        varP = s;
    }
    if (typeP == nullptr)
    {
        pp = typeP = varP;
    }

    if (typeP != varP)
    {
        typeP->sibling = varP;
    }

    if (varP != s)
    {
        varP->sibling = s;
    }

    return pp;
}


TreeNode* TypeDec(void)
{
    TreeNode* t = new TreeNode;
    

    if (tok.Lex == TYPE)
    {
        
        t = TypeDeclaration();//类型声明
        return t;
    }

    if (tok.Lex == VAR)
    {
        return t;
    }

    if (tok.Lex == PROCEDURE)
    {
        return t;
    }

    if (tok.Lex == BEGIN1)
    {
        return t;
    }

    //读下一个单词，跳过此单词
    ReadWord();
}

//6.类型声明中的其他函数
TreeNode* TypeDeclaration(void)
{
    match(TYPE);
    TreeNode *t = TypeDecList();
    
    if (t == nullptr)
    {
        cout << "t为nullptr" << endl;
    }
    return t;
}


//7.类型声明中的其他函数
TreeNode* TypeDecList(void)
{
    TreeNode* t = nullptr;
    t = new TreeNode;
    t->nodekind = DecK;
    if (t != nullptr)
    {
        string token;
        TypeId(t);
        
        
        match(EQ);
		
        TypeDef(t);
        

        match(SEMI);


        TreeNode* p = nullptr;
        p = TypeDecMore();
        if (p == nullptr)
        {
            return t;
        }
        else
        {
            t->sibling = p;
        }

    }

    return t;

}


//8.类型声明中的其他函数
TreeNode* TypeDecMore(void)
{
    


    TreeNode* t = nullptr;
    if (tok.Lex == VAR || tok.Lex == PROCEDURE || tok.Lex == BEGIN1)
    {
        return t;
    }
    else
    {
        if (tok.Lex == ID)
        {
            TypeDecList();//递归调用下一条类型声明
        }
        ReadWord();//读入下一个单词
        
    }
}


//9.类型声明中的其他函数
void TypeId(TreeNode* t)
{
    
    if (tok.Lex == ID && t != nullptr)
    {
        int tnum = t->attr.idnum;
        t->attr.name.push_back(tok.Sem);//标识符名字
        tnum++;
        t->attr.idnum = tnum;
    }
    match(ID);
}


//10.具体类型处理分析程序
void TypeDef(TreeNode* t)
{
    
    
    if (t != nullptr)
    {
        if (tok.Lex == INTEGER || tok.Lex == CHAR1)
        {
            BaseType(t);
            

        }
        else
        {
            if (tok.Lex == ARRAY || tok.Lex == RECORD)
            {
                StructureType(t);
            }
            else
            {
                if (tok.Lex == ID)
                {
                    t->kind.dec = IdK;
                    t->attr.type_name[0] = tok.Sem;
                    match(ID);
                }
                else
                {
                    ReadWord();//read下一个单词
                }
            }
        }
    }
}


//11.基本类型处理分析程序
void BaseType(TreeNode* t)
{
    if (tok.Lex == INTEGER)
    {
        match(INTEGER);
        t->kind.dec = IntegerK;
    }
    else
    {
        if (tok.Lex == CHAR1)
        {
            match(CHAR1);
            t->kind.dec = CharK;
        }
        else
        {
            ReadWord();//读入下一个单词
        }
    }
}


//12.结构类型处理分析程序
void StructureType(TreeNode* t)
{
    ReadWord();
    if (tok.Lex == ARRAY)
    {
        ArrayType(t);
    }
    else
    {
        if (tok.Lex == RECORD)
        {
            t->kind.dec = RecordK;
            RecType(t);
        }
        else
        {
            //read the next word
            ReadWord();
        }
    }

}


//13.数组类型的处理分析程序
void ArrayType(TreeNode* t)
{
    match(ARRAY);
    
    match(LMIDPAREN);
    
    if (tok.Lex == INTC)
    {

        t->attr.arrayattr.low = StringtoInt(tok.Sem);//数组下界
    }

    match(INTC);
    
    match(UNDERANGE);
    if (tok.Lex == INTC)
    {
        t->attr.arrayattr.up = StringtoInt(tok.Sem);
    }

    match(INTC);
    match(RMIDPAREN);
    match(OF);
    BaseType(t);
    t->attr.arrayattr.childType = t->kind.dec;
    t->kind.dec = ArrayK;
}


//14.记录类型的处理分析程序 
void RecType(TreeNode *t)
{
	match(RECORD);
	TreeNode *p = nullptr;
	p = FieldDecList(t);
	if (p != nullptr)
	{
		t->child[0] = p;
	}
	else
	{
		// error hint
		cout << "line:" << lineno << "error" << endl;
	}
	

	match(END1);
}


//15.记录类型中的域声明处理分析函数
TreeNode * FieldDecList(TreeNode *t)
{
	TreeNode *p = new TreeNode;
    if (t != nullptr)
    {
        if (tok.Lex == INTEGER || tok.Lex == CHAR1)
        {
            BaseType(t);
            IdList(t);
            match(SEMI);
            p = FieldDecList(t);
            
        }
        else
        {
            if (tok.Lex != ARRAY)
            {
                ReadWord();//读下一个单词
            }
            else
            {
                ArrayType(t);
                IdList(t);
                match(SEMI);
                p = FieldDecMore();
            }

        }
        t->sibling = p;
    }
    return t;
}


//16
TreeNode* FieldDecMore(void)
{
    TreeNode* t = nullptr;
    if (tok.Lex == END1)
    {
        return t;
    }
    else
    {
        if (tok.Lex == INTEGER || tok.Lex == INTEGER || tok.Lex == INTEGER)
        {
            t = FieldDecList(t);
        }
        else
        {
            ReadWord();
        }
    }
}


//17
void IdList(TreeNode* t)
{
    if (tok.Lex == ID)
    {
        t->attr.name[t->attr.idnum] = tok.Sem;
        t->attr.idnum++;
    }
    IdMore(t);
}

//18
void IdMore(TreeNode* t)
{
    if (tok.Lex != SEMI)
    {
        if (tok.Lex == COMMA)
        {
            match(COMMA);
            IdList(t);
        }
        else
        {
            ReadWord();
        }
    }
}


//19
TreeNode* VarDec(void)
{
	
    TreeNode* t = nullptr;
    if (tok.Lex == PROCEDURE || tok.Lex == BEGIN1)
    {
        ;
    }
    else
    {
        if (tok.Lex == VAR)
        {
            VarDeclaration();
        }
        //ReadWord();//todo readword
    }
    return t;
}


//20
TreeNode* VarDeclaration(void)
{
    match(VAR);
    TreeNode *t = VarDecList();
    if (t == nullptr)
    {
        //语法错误信息提示
        cout << tok.Lineshow << " error" << endl;
    }
    return t;
}


//21
TreeNode* VarDecList(void)
{
    TreeNode* t = new TreeNode;
    t->nodekind = DecK;
    TreeNode* p = nullptr;
    if (t != nullptr)
    {
		
        TypeDef(t);
        VarIdList(t);
        match(SEMI);
        p = VarDecMore();
        t->sibling = p;
    }
    return t;
}


//todo 22 
TreeNode* VarDecMore(void)
{
	
    TreeNode* t = nullptr;
    if (tok.Lex == PROCEDURE || tok.Lex == BEGIN1)
    {
        ;
    }
    else
    {
        if (tok.Lex == INTEGER || tok.Lex == CHAR1 || tok.Lex == ARRAY || tok.Lex == RECORD || tok.Lex == ID)
        {
            t = VarDecList();
        }
        else
        {
            ReadWord();
        }
    }
    return t;
}


//23
void VarIdList(TreeNode* t)
{
	
    if (tok.Lex == ID)
    {
        t->attr.name.push_back(tok.Sem);
        t->attr.idnum++;
    }
    else
    {
        //错误提示，读入下一个单词
        cout << tok.Lineshow << " error" << endl;
        ReadWord();
    }
    VarIdMore(t);
}


//todo 24 
void VarIdMore(TreeNode* t)
{
    ReadWord();
	if (tok.Lex != SEMI)
	{
		if (tok.Lex == COMMA)
		{
			match(COMMA);
			VarIdList(t);
		}
		else
		{
			ReadWord();
		}
	}
}


//25
TreeNode* ProcDec(void)
{
	TreeNode* t = nullptr;
	if (tok.Lex != BEGIN1)
	{
		if (tok.Lex == PROCEDURE)
		{
			t = ProcDeclaration();
		}
		else
		{
			ReadWord();
		}
	}
	return t;
}


//todo 26 
TreeNode* ProcDeclaration(void)
{
	TreeNode* t = nullptr;
	t = new TreeNode;
    t->nodekind = ProcDeck;
	match(PROCEDURE);
	if (t != nullptr)
	{
		
		if (tok.Lex == ID)
		{
			t->attr.name.push_back(tok.Sem);//记录函数名
			t->attr.idnum++;
			match(ID);

		}
		
		match(LPAREN);
		ParamList(t);
		//ReadWord();
		match(RPAREN);
		
		//match(COLON);
		match(SEMI);
		t->child[1] = ProcDecPart();
		t->child[2] = ProcBody();


		
	}
	return t;
	
}


//27
void ParamList(TreeNode* t)
{
	
	TreeNode* p = nullptr;
	if (tok.Lex != RPAREN)
	{
		if (tok.Lex == INTEGER || tok.Lex == CHAR1 || tok.Lex == RECORD || tok.Lex == ARRAY || tok.Lex == ID || tok.Lex == VAR)
		{
			p = ParamDecList();
			t->child[0] = p;
		}
		else
		{
			ReadWord();
		}
	}

}


//28
TreeNode* ParamDecList(void)
{
	TreeNode* t = Param();
	TreeNode* p = ParamMore();
	if (p != nullptr)
	{
		t->sibling = p;
	}
	return t;
}


//29
TreeNode* ParamMore(void)
{
	TreeNode* t = nullptr;
	if (tok.Lex != RPAREN)
	{
		if (tok.Lex == SEMI)
		{
			match(SEMI);
			t = ParamDecList();
			if (t == nullptr)
			{
				// error
				cout << tok.Lineshow << " error" << endl;
			}
		}
		else
		{
			ReadWord();
		}
	}
	return t;
}


//30
TreeNode* Param(void)
{
	TreeNode* t = nullptr;
	t = new TreeNode;
    t->nodekind = ParamListK;
	if (t != nullptr)
	{
		if (tok.Lex == INTEGER || tok.Lex == CHAR1 || tok.Lex == RECORD || tok.Lex == ARRAY || tok.Lex == ID)
		{
			t->attr.procAttr.param = valparamtype;
			TypeDef(t);
			FormList(t);
		}
		else
		{
			if (tok.Lex == VAR)
			{
				match(VAR);
				t->attr.procAttr.param = varparamtype;
				TypeDef(t);
				FormList(t);
			}
			else
			{
				ReadWord();
			}
		}
	}
	return t;
}


//31
void FormList(TreeNode* t)
{
	if (tok.Lex == ID)
	{
		t->attr.name.push_back(tok.Sem);
		t->attr.idnum++;
		match(ID);
	}
	FidMore(t);
}


//32
void FidMore(TreeNode* t)
{
	if (tok.Lex != SEMI && tok.Lex != RPAREN)
	{
		if (tok.Lex == COMMA)
		{
			match(COMMA);
			FormList(t);
		}
		else
		{
			ReadWord();
		}
	}
}


//33
TreeNode* ProcDecPart()
{
	TreeNode* t = DeclarePart();
	return t;
}


//34
TreeNode* ProcBody()
{
	TreeNode* t = nullptr;
	t = ProgramBody();
	if (t == nullptr)
	{
		//error
		cout << tok.Lineshow << " error" << endl;
	}
	return t;
}

//todo 35
TreeNode* ProgramBody()
{
	TreeNode* t = nullptr;
	t = new TreeNode;
    t->nodekind = StmLK;
	match(BEGIN1);
	if (t != nullptr)
	{
		t->child[0] = StmList();
	}
	match(END1);
	return t;
}


//36 ****
TreeNode* StmList()
{
	TreeNode* t = Stm();
	TreeNode* p = nullptr;
	p = StmMore();
	if (p != nullptr)
	{
		t->sibling = p;
	}
	return t;
}


//37
TreeNode* StmMore()
{
	TreeNode* t = nullptr;
	if (tok.Lex != END1 && tok.Lex != ENDWH)
	{
		if (tok.Lex == SEMI)
		{
			match(SEMI);
			t = StmList();
		}
		else
		{
			ReadWord();
		}
	}
	return t;
}


string temp_name;
//todo 38
TreeNode* Stm()
{
	
	TreeNode* t = nullptr;
	switch (tok.Lex)
	{
	case IF: t = ConditionalStm(); break;
	case WHILE: t = LoopStm(); break;
	case RETURN1: t = ReturnStm(); break;
	case READ: t = InputStm(); break;
	case WRITE: t = OutputStm(); break;
	case ID: 
        match(ID);//todo match(id)
		temp_name = tok.Sem;
		t = AssCall();
		break;
	default:
		cout << tok.Lineshow << " 非预期单词语法错误" << endl;//跳过当前错误
		ReadWord();
		break;
	}
    return t;
}


//39
TreeNode* AssCall()
{
	//ReadWord();//todo assign
	TreeNode* t = nullptr;
	if (tok.Lex == ASSIGN)
	{
		t = AssignmentRest();
	}
	else
	{
		if (tok.Lex == LPAREN)
		{
			t = CallStmRest();
		}
		else
		{
			ReadWord();
		}
	}
	return t;
}


//40
TreeNode* AssignmentRest()
{
	TreeNode* t = nullptr;
	t = new TreeNode;
	//match(EQ);
	match(ASSIGN);
	if (t != nullptr)
	{
		
		t->child[0] = Exp();
		t->attr.name.push_back(temp_name);
		t->attr.idnum++;
	}
	return t;
}


//41
TreeNode* ConditionalStm()
{
	TreeNode* t = nullptr;
	t = new TreeNode;
	match(IF);
	if (t != nullptr)
	{
		t->child[0] = Exp();//作为IF语句的条件表达式

	}
	match(THEN);
	if (t != nullptr)
	{
		t->child[1] = Stm();
	}
	
	if (tok.Lex == ELSE)
	{
		match(ELSE);
		if (t != nullptr)
		{
			t->child[2] = Stm();//作为条件假的处理语句
		}
	}
	match(FI);
	return t;
}




//42
TreeNode* LoopStm()
{
	TreeNode* t = nullptr;
	t = new TreeNode;
	match(WHILE);
	if (t != nullptr)
	{
		t->child[0] = Exp();//while语句条件表达式
		match(DO);
		t->child[1] = StmList();//循环语句部分

	}
	return t;
}


//43
TreeNode* InputStm()
{
	TreeNode* t = nullptr;
	t = new TreeNode;
	match(READ);
	match(LPAREN);
	if (t != nullptr && tok.Lex == ID)
	{
		((t->attr).name).push_back(tok.Sem);//作为READ语句的标志符名
	}
	match(ID);
	match(RPAREN);
	return t;
}


//44
TreeNode* OutputStm()
{
	TreeNode* t = nullptr;
	t = new TreeNode;
	match(WRITE);
	
	match(LPAREN);
	if (t != nullptr)
	{
		t->child[0] = Exp();//作为write语句的表达式
	}
	match(RPAREN);
	return t;
}


//45
TreeNode* ReturnStm()
{
	TreeNode* t = new TreeNode;
	match(RETURN1);
	return t;
		
}




//46
TreeNode* CallStmRest()
{
	TreeNode* t = nullptr;
	t = new TreeNode;
	match(LPAREN);
	if (t != nullptr)
	{
		t->child[0] = ActParamList();
		//t->attr.name[0] = temp_name;//临时变量
        t->attr.name.push_back(temp_name);
	}
	match(RPAREN);
	return t;
}


//47
TreeNode* ActParamList()
{
	TreeNode* t = nullptr;
	if (tok.Lex != RPAREN)
	{
		if (tok.Lex == ID || tok.Lex == INTC)
		{
			t = Exp();
			if (t != nullptr)
			{
				t->sibling = ActParamMore();
			}
		}
	}
	return t;
}


//48
TreeNode* ActParamMore()
{
	TreeNode* t = nullptr;
	if (tok.Lex != RPAREN)
	{
		if (tok.Lex == ID || tok.Lex == INTC)
		{
			t = Exp();
			if (t != nullptr)
			{
				t->sibling = ActParamMore();
			}
		}
	}
	return t;
}


//49
TreeNode* Exp()
{
	TreeNode* t = Simple_exp();
	if (tok.Lex == LT || tok.Lex == EQ)
	{
		TreeNode* p = nullptr;
		p = new TreeNode;
		if (p != nullptr)
		{
			p->child[0] = t;//作为运算表达式的左运算简式
			p->attr.expattr.op = tok;//作为运算表达式运算符
			t = p;
		}
		//匹配LT EQ

        if (tok.Lex == LT)
        {
            match(LT);
        }
        else
        {
            match(EQ);
        }
		if (t != nullptr)
		{
			t->child[1] = Simple_exp();//作为运算表达式的right运算简式
		}
	}
	return t;
}


//50
TreeNode* Simple_exp()
{
    TreeNode* t = term();
    while (tok.Lex == PLUS || tok.Lex == MINUS)
    {
        TreeNode* p = nullptr;
        p = new TreeNode;
        if (p != nullptr)
        {
            p->child[0] = t;//作为运算简单表达式的左运算项
            p->attr.expattr.op = tok;//作为运算简单表达式的运算符
            t = p;
        }
        //match
        if (tok.Lex == PLUS)
        {
            match(PLUS);
        }
        else
        {
            match(MINUS);
        }
        t->child[1] = term();//作为运算简单表达式的右运算项
		
    }
    
   
    return t;
    
}




//51
TreeNode* term()
{
    TreeNode* t = factor();
	//ReadWord();
    while (tok.Lex == TIMES || tok.Lex == OVER)
    {
        TreeNode* p = nullptr;
        p = new TreeNode;
        if (p != nullptr)
        {
            p->child[0] = t;//作为运算简单表达式的左运算因子
            p->attr.expattr.op;//作为运算项的运算符
            t = p;
        }
        //match
        if (tok.Lex == TIMES)
        {
            match(TIMES);
        }
        else
        {
            match(OVER);
        }
        t->child[1] = factor();//作为运算项的右运算因子
		
    }
    
    
    return t;
    
}


//52
TreeNode* factor()
{
	
    TreeNode* t = nullptr;
    switch (tok.Lex)
    {
    case INTC:match(INTC); break;
    case ID:variable(); break;
    case LPAREN:
        match(LPAREN);
        t = Exp();
        match(RPAREN);

    default:
        //非预期单词错误
        cout << tok.Lineshow << " error " << tok.Sem << endl; 
        ReadWord();
        break;
    }
    return t;
}


//53
TreeNode* variable()
{
    TreeNode* t = nullptr;
    t = new TreeNode;
    if (t != nullptr && tok.Lex == ID)
    {
        match(ID);
        t->lineno = tok.Lineshow;
        t->name = tok.Sem;//保留当前行号和ID的语义信息
        variMore(t);
    }
    return t;
}


//54 array and member variable
void variMore(TreeNode* t)
{
    if(tok.Lex == LMIDPAREN)
    {
        match(LMIDPAREN);
        t->child[0] = Exp();
        t->attr.expattr.varkind = ArrayMembV;
        t->child[0]->attr.expattr.varkind = IdV;
    }
    else
    {
        if (tok.Lex == DOT)
        {
            match(DOT);
            t->child[0] = fieldvar();
            t->attr.expattr.varkind = FieldMembV;
            t->child[0]->attr.expattr.varkind = IdV;
        }
    }
}


//55
TreeNode* fieldvar()
{
    TreeNode* t = nullptr;
    t = new TreeNode;
    if (t != nullptr && tok.Lex == ID)
    {
        t->lineno = tok.Lineshow;
        t->name = tok.Sem;
        match(ID);
        fieldvarMore(t);
    }
    return t;
}




//56
void fieldvarMore(TreeNode* t)
{
    if (tok.Lex == LMIDPAREN)
    {
        match(LMIDPAREN);
        t->child[0] = Exp();
        t->child[0]->attr.expattr.varkind = ArrayMembV;
        match(RMIDPAREN);
    }

}




int StringtoInt(string s)
{
    int n = s.size();
    int num = 0;
    for (int i = 0; i < n; i++)
    {
        int tmp = s[i] - '0';
        num = num * 10 + tmp;
    }
    return num;
}


void ReadWord()
{
    string line;
    getline(f, line);
    line = DelBlank(line);
    vector<string>tmp = split(line, ':');
	tok.Lineshow = StringtoInt(tmp[0]);
	int n = line.size();
	if (line[n - 1] == '=' && line[n - 2] == ':' && line[n-3] == ':')
	{
		tok.Lex = ASSIGN;
		
	}
	else
	{
		if (tmp.size() >= 3)
		{



			for (int i = 0; i < MAXLEX; i++)
			{
				if (LexToChar[i].str == tmp[2])
				{
					tok.Lex = LexToChar[i].tok;
					break;
				}
			}



		}
		else
		{


			if (tmp[1].size() > 1 && tmp[1] != "ERROR" && tmp[1] != "EOF")
			{
				tmp = split(tmp[1], ',');

				for (int i = 0; i < MAXLEX; i++)
				{
					if (LexToChar[i].str == tmp[0])
					{
						tok.Lex = LexToChar[i].tok;
						break;
					}
				}
				tmp = split(tmp[1], '=');
				tok.Sem = tmp[1];
			}
			else
			{
                if (tmp[1] == "ERROR")
                {
                    ReadWord();
                }
                else
                {
                    for (int i = 0; i < MAXLEX; i++)
                    {
                        if (LexToChar[i].str == tmp[1])
                        {
                            tok.Lex = LexToChar[i].tok;
                            break;
                        }
                    }
                }

			}

		}
	}
    
}


//57.匹配终极符
void match(LexType expected)
{

    if (tok.Lex == expected)
    {
        ReadWord();
    }
    else
    {
		cout << tok.Lineshow << " syntax error" << endl;
        exit(1);
    }
}





vector<string> split(string s, char ch)
{
    s.push_back(ch);
    int start = 0, endd = 0, len = s.size();
    vector<string> vs;

    for (int i = 0; i < len; i++)
    {
        if (s[i] == ch)
        {
            endd = i;
            string temp = s.substr(start, endd - start);
            start = i + 1;

            if (!temp.empty())
                vs.push_back(temp);
        }
		
    }
    return vs;
}


string DelBlank(string s)
{
    int len = s.size();
    for (int i = 0; i < len; i++)
    {
        if (s[i] == ' ')
        {
            s.erase(i, 1);
            len--;
        }
    }
    return s;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
