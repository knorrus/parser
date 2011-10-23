/*
 * Visitor.cpp
 *
 *  Created on: Oct 23, 2011
 *      Author: pavel
 */
#include "stdafx.h"
#include "Visitor.h"

void CalcVisitor::Visit(TNode* pNode, AResult* pResult)
{
	((CalcResult*)pResult)->value = pNode->toDouble();
}

void CalcVisitor::Visit(UNode* pNode, AResult* pResult)
{
	(pNode->getLeft())->Accept(*this, pResult);
	switch(pNode->getOperation())
	{
		case UMIN:
			((CalcResult*)pResult)->value = - ((CalcResult*)pResult)->value;
			break;
		case FNC:
			break;
	}
}

void CalcVisitor::Visit(BNode* pNode, AResult* pResult)
{
	(pNode->getLeft())->Accept(*this, pResult);
	CalcResult& left_value = *((CalcResult*)pResult);

	CalcResult right_value;
	(pNode->getRight())->Accept( *this, (AResult*)(&right_value) );

	switch(pNode->getOperation())
	{
		case ADD:
			left_value.value = left_value.value + right_value.value;
			break;
		case MIN:
			left_value.value = left_value.value - right_value.value;
			break;
		case MULT:
			left_value.value = left_value.value * right_value.value;
			break;
		case DIVD:
		case DIVI:
			left_value.value = left_value.value / right_value.value;
			break;
	}
}

double CalcVisitor::CalculateTree(ANode* head)
{
	CalcResult node_value;
	head->Accept( *this, (AResult*)(&node_value) );
	return node_value.value;
}



