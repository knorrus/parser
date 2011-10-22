/*
 * ExprParser.cpp
 *
 *  Created on: Oct 22, 2011
 *      Author: pavel
 */
#include "stdafx.h"

token_value CExprParser::GetToken(char*& fromSymbol, char* pBufer)
{
	if(!(*fromSymbol)) return END;
	if(isdigit(*fromSymbol))
	{
		do{
			*pBufer++ = *fromSymbol++;
		}while (isdigit(*fromSymbol));
		if(*fromSymbol != '.')
		{
			*pBufer = 0;
			return INUMBER;
		}

		else
		{
			*pBufer++ = '.';
			if(isdigit(*(++fromSymbol)))
			{
				do{
					*pBufer++ = *fromSymbol++;
				}while (isdigit(*fromSymbol));
			}
			*pBufer = 0;
			return DNUMBER;
		}
	}
	else
	{
		switch(*fromSymbol)
		{
			case '*':
			case '/':
			case '\\':
			case '+':
			case '-':
			case '(':
			case ')':
			   {
				token_value token = token_value(fromSymbol[0]);
				fromSymbol++;
				return token;
			   }
			default: //FUNCTION NAMES
			   {
				if(isalpha(*fromSymbol))
					do{
						*pBufer++ = *fromSymbol++;
					}while(isalpha(*fromSymbol));
				*pBufer = 0;
				return NAME;
			   }
		}
	}
}

ANode* CExprParser::expr()
{
	ANode *left = term();
	ANode *currentNode;

	for(;;)
	{
		switch(currentToken)
		{
			case PLUS:
 				currentNode = new BNode(ADD);
				break;
			case MINUS:
				currentNode = new BNode(MIN);
				break;
			default:
				return left;
		}
		currentNode->setLeft(left);
		currentToken = GetToken();
		currentNode->setRight(term());
		left = currentNode;
	}
}

ANode* CExprParser::term()
{
	ANode *left = prim();
	ANode *currentNode;

	for(;;)
	{
		switch(currentToken)
		{
			case MUL:
				currentNode = new BNode(MULT);
				break;
			case DIV:
				currentNode = new BNode(DIVD);
				break;
			case IDIV:
				currentNode = new BNode(DIVI);
				break;
			default:
				return left;
		}
		currentNode->setLeft(left);
		currentToken = GetToken();
		currentNode->setRight(prim());
		left = currentNode;
	}
}

ANode* CExprParser::prim()
{
	ANode *currentNode;

	switch(currentToken)
	{
		case INUMBER:
			currentNode = new TNode();
			*((TNode*)(currentNode)) = atoi(bufer);
			currentToken = GetToken();
			return currentNode;
		case DNUMBER:
			currentNode = new TNode();
			*((TNode*)(currentNode)) = atof(bufer);
			currentToken = GetToken();
			return currentNode;
		case NAME:
			currentToken = GetToken();
			if (currentToken == LP )
			{
				currentNode = new UNode(bufer);
				currentNode->setLeft(prim());
			}
			else
			{
				currentNode = new TNode();
				*((TNode*)currentNode) = bufer;
			}
			return currentNode;
		case MINUS: //Unary minus
			currentNode = new UNode(UMIN);
			currentToken = GetToken();
			currentNode->setLeft(prim());
			return currentNode;
		case LP:
			currentToken = GetToken();
			currentNode = expr();
			if(currentToken != RP) return NULL;
			currentToken = GetToken();
			return currentNode;
		case END:
			return NULL;
		default:
			return NULL;
	}
}

ANode* CExprParser::CreateTree(char* exprStr)
{
	pCurrentPosition = exprStr;
	currentToken = BEGIN;

	currentToken = GetToken();
	return treeHead = expr();
}





