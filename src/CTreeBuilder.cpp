/*
 * CTreeBuilder.cpp
 *
 *  Created on: Oct 22, 2011
 *      Author: pavel
 */

#include "stdafx.h"

#ifdef _DEBUG
void debugPrn(ANode* node)
{
	TNode* tn = dynamic_cast<TNode*> (node);
	if(tn)
	{
		nodeVariant var;
		tn->getData(var);
		switch(var.type)
		{
			case INT:
				cout << var.varData.i << '\n';
				return;
			case DBL:
				cout << var.varData.d << '\n';
				return;
			case NCONST:
				cout << var.varData.namedConst << '\n';
				return;
			default:
				cout << "undefined type\n";
				return;
		}
	}
	UNode* un = dynamic_cast<UNode*> (node);
	if(un)
	{
		cout << "Unary operation " << un->getOperation() << '\n';
		return;
	}
	BNode* bn = dynamic_cast<BNode*> (node);
	if(bn)
	{
		cout << "Binary operation " << bn->getOperation() << '\n';
		return;
	}
}
#endif

Operand* CTreeBuilder::BuildTerminal(Memento* pCurrentState)
{
	TNode* currentNode = new TNode();
	switch(pCurrentState->token)
	{
		case INT:
			*currentNode = atoi(pCurrentState->tokenStr);
			break;
		case DBL:
			*currentNode = atof(pCurrentState->tokenStr);
			break;
		case NCONST:
			*currentNode = pCurrentState->tokenStr;
			break;
	}

#ifdef _DEBUG
	debugPrn(currentNode);
#endif

	return (Operand*)currentNode;
}

Operand* CTreeBuilder::BuildUnaryOperation(Memento* pCurrentState, Operand* pLeft)
{
	UNode* currentNode = new UNode(pCurrentState->token != MINUS ? FNC : UMIN);
	currentNode->setLeft((ANode*)pLeft);

#ifdef _DEBUG
	debugPrn(currentNode);
	cout << pCurrentState->tokenStr << '\n';
#endif

	return (Operand*)currentNode;
}

Operand* CTreeBuilder::BuildBinaryOperation(token_value token, Operand* pLeft, Operand* pRight)
{
	BNode* currentNode = new BNode((BOperation)token);
	currentNode->setLeft((ANode*)pLeft);
	currentNode->setRight((ANode*)pRight);

#ifdef _DEBUG
	debugPrn(currentNode);
#endif

	return (Operand*)currentNode;
}



