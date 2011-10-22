/*
 * ExprParser.h
 *
 *  Created on: Oct 22, 2011
 *      Author: pavel
 */

#ifndef EXPRPARSER_H_
#define EXPRPARSER_H_

class ANode;

	class Operand;
	class AExprBuilder;

const int MAX_TERM_STR_LEN = 1024;

class CExprParser
{
	char* pCurrentPosition;
	char bufer[MAX_TERM_STR_LEN +1];
	token_value currentToken;

	/*ANode* treeHead;*/
	Operand* treeHead;
	AExprBuilder* theBuilder;


protected:
	virtual token_value GetToken(char*& fromSymbol, char* pBufer);
	inline token_value GetToken()
			{return GetToken(pCurrentPosition, bufer);}

	Operand* expr();
	Operand* term();
	Operand* prim();

public:
	CExprParser(AExprBuilder* pBuilder) : theBuilder(pBuilder) {};
	Operand* CreateTree(char* expr);

	friend struct Memento;
};



#endif /* EXPRPARSER_H_ */
