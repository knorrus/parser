/*
 * ExprParser.h
 *
 *  Created on: Oct 22, 2011
 *      Author: pavel
 */

#ifndef EXPRPARSER_H_
#define EXPRPARSER_H_

class ANode;

const int MAX_TERM_STR_LEN = 1024;
class CExprParser
{
	char* pCurrentPosition;
	char bufer[MAX_TERM_STR_LEN +1];
	token_value currentToken;

	ANode* treeHead;

protected:
	virtual token_value GetToken(char*& fromSymbol, char* pBufer);
	inline token_value GetToken()
			{return GetToken(pCurrentPosition, bufer);}

	ANode* expr();
	ANode* term();
	ANode* prim();

public:
	ANode* CreateTree(char* expr);
};


#endif /* EXPRPARSER_H_ */
