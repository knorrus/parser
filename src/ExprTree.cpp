/*
 * ExprTree.cpp
 *
 *  Created on: Oct 22, 2011
 *      Author: pavel
 */
#include "stdafx.h"

int UNode::maxNameLength = 10;

UNode::~UNode()
{
	if(pArg) delete pArg;
	if(fncName) delete fncName;
}

void UNode::setFunction(char* name)
{
	fncName = strcpy(new char[strlen(name)+1], name);
}

BNode::~BNode()
{
	if (pArgR) delete pArgR;
	if (pArgL) delete pArgL;
}

TNode& TNode::operator = (int iVal)
{
	data.type = INT;
	data.varData.i = iVal;
	return *this;
}

TNode& TNode::operator = (double dVal)
{
	data.type = DBL;
	data.varData.d = dVal;
	return *this;
}

TNode& TNode::operator = (char* str)
{
	data.type = NCONST;
	strncpy(data.varData.namedConst, str, MAX_NAMED_CONST_LEN);
	return *this;
}

double TNode::toDouble() const
{
	switch(data.type)
	{
		case INT: return data.varData.i;
		case DBL: return data.varData.d;
		default: return 0;
	}
}

void TNode::Accept(AVisitor& theVisitor, AResult* pResult)
{
	theVisitor.Visit(this, pResult);
}

void UNode::Accept(AVisitor& theVisitor, AResult* pResult)
{
	theVisitor.Visit(this, pResult);
}

void BNode::Accept(AVisitor& theVisitor, AResult* pResult)
{
	theVisitor.Visit(this, pResult);
}




