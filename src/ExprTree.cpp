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
	if (m_pFncName) delete m_pFncName;
	if (pArg) delete pArg;
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




