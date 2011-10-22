/*
 * ExprParser.cpp
 *
 *  Created on: Oct 22, 2011
 *      Author: pavel
 */
#include "stdafx.h"

token_value CExprParser::GetToken(char*& fromSymbol, char* pBufer) {
	if (!(*fromSymbol))
		return END;
	if (isdigit(*fromSymbol)) {
		do {
			*pBufer++ = *fromSymbol++;
		} while (isdigit(*fromSymbol));
		if (*fromSymbol != '.') {
			*pBufer = 0;
			return INUMBER;
		}

		else {
			*pBufer++ = '.';
			if (isdigit(*(++fromSymbol))) {
				do {
					*pBufer++ = *fromSymbol++;
				} while (isdigit(*fromSymbol));
			}
			*pBufer = 0;
			return DNUMBER;
		}
	} else {
		switch (*fromSymbol) {
		case '*':
		case '/':
		case '\\':
		case '+':
		case '-':
		case '(':
		case ')': {
			token_value token = token_value(fromSymbol[0]);
			fromSymbol++;
			return token;
		}
		default: //FUNCTION NAMES
		{
			if (isalpha(*fromSymbol))
				do {
					*pBufer++ = *fromSymbol++;
				} while (isalpha(*fromSymbol));
			*pBufer = 0;
			return NAME;
		}
		}
	}
}

Operand* CExprParser::expr() {
	Operand* left = term();
	Operand* right = NULL;

	for (;;) {
		switch (currentToken) {
		case PLUS:
		case MINUS: {
			token_value operation = currentToken;
			currentToken = GetToken();
			right = term();
			left = theBuilder->BuildBinaryOperation(operation, left, right);
		}
			break;
		default:
			return left;
		}
	}
}

Operand* CExprParser::term() {
	Operand* left = prim();
	Operand* right = NULL;

	for (;;) {
		switch (currentToken) {
		case MUL:
		case DIV:
		case IDIV: {
			token_value operation = currentToken;
			currentToken = GetToken();
			right = prim();
			left = theBuilder->BuildBinaryOperation(operation, left, right);
		}
			break;
		default:
			return left;
		}

	}
}

Operand* CExprParser::prim() {
	Memento currentState;
	currentState.tokenStr = strcpy(new char[strlen(bufer)+1], bufer);
	currentState.token = currentToken;
	currentToken = GetToken();

	switch (currentState.token) {
	case INUMBER:
	case DNUMBER:
		return theBuilder->BuildTerminal(&currentState);
	case MINUS: //Unary minus
		return theBuilder->BuildUnaryOperation(&currentState, prim());
	case NAME:
		if (currentToken != LP)
			return theBuilder->BuildTerminal(&currentState);
		else
			return theBuilder->BuildUnaryOperation(&currentState, prim());
	case LP: {
		Operand* currentOperand = expr();
		if (currentToken != RP)
			return NULL;
		currentToken = GetToken();
		return currentOperand;
	}
	case END:
		return NULL;
	default:
		return NULL;
	}
}

Operand* CExprParser::CreateTree(char* exprStr) {
	pCurrentPosition = exprStr;
	currentToken = BEGIN;

	currentToken = GetToken();
	return treeHead = expr();
}

