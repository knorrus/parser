/*
 * CTreeBuilder.cpp
 *
 *  Created on: Oct 22, 2011
 *      Author: pavel
 */

#include "stdafx.h"

void debugPrn(ANode* node) {
	TNode* tn = dynamic_cast<TNode*>(node);
	if (tn) {
		nodeVariant var;
		tn->getData(var);
		switch (var.type) {
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
	UNode* un = dynamic_cast<UNode*>(node);
	if (un) {
		cout << "Unary operation ";
		return;
	}
	BNode* bn = dynamic_cast<BNode*>(node);
	if (bn) {
		char t;
		switch (bn->getOperation()) {
		case ADD:
			t = '+';
			break;
		case MIN:
			t = '-';
			break;
		case MULT:
			t = '*';
			break;
		case DIVD:
			t = '/';
			break;
		case DIVI:
			t = '\\';
			break;
		}
		cout << "Binary operation " << t << '\n';
		return;
	}
}

Operand* CTreeBuilder::BuildTerminal(Memento* pCurrentState) {
	TNode* currentNode = new TNode();
	switch (pCurrentState->token) {
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
										/*Debug print*/
                                                                                //debugPrn(currentNode);
	return (Operand*) currentNode;
}

Operand* CTreeBuilder::BuildUnaryOperation(Memento* pCurrentState, Operand* pLeft) {
	UNode* currentNode;
	if (pCurrentState->token == MINUS) {
		currentNode = new UNode(UMIN);
	} else {
		currentNode = new UNode(FNC);
		currentNode->setFunction(pCurrentState->tokenStr);
	}
	currentNode->setLeft((ANode*) pLeft);
										/*Debug print*/
                                                                                //debugPrn(currentNode); cout << pCurrentState->tokenStr << '\n';
	return (Operand*) currentNode;
}

Operand* CTreeBuilder::BuildBinaryOperation(token_value token, Operand* pLeft, Operand* pRight) {
	BNode* currentNode = new BNode((BOperation) token);
	currentNode->setLeft((ANode*) pLeft);
	currentNode->setRight((ANode*) pRight);
										/*Debug print*/
                                                                                //debugPrn(currentNode);
	return (Operand*) currentNode;
}

