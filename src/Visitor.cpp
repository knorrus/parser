/*
 * Visitor.cpp
 *
 *  Created on: Oct 23, 2011
 *      Author: pavel
 */
#include "stdafx.h"
#include "Visitor.h"
#include <math.h>

using namespace ExprTree;

CalcVisitor* CalcVisitor::_instance = NULL;
STRING2FNC CalcVisitor::function;

typedef pair<string, MATH_FNC> _pairS2F;

const int FNC_COUNT = 9;

_pairS2F fnc_array[FNC_COUNT] = {
	_pairS2F("sin", &sin),
	_pairS2F("cos", &cos),
	_pairS2F("tg", &tan),
	_pairS2F("exp", &exp),
	_pairS2F("lg", &log10),
	_pairS2F("ln", &log),
	_pairS2F("arctg", &atan),
	_pairS2F("arcsin", &asin),
	_pairS2F("arccos", &acos)
};

CalcVisitor* CalcVisitor::Instance()
{
	if(_instance == NULL)
	{
		_instance = new CalcVisitor;
		for(int i=0; i < FNC_COUNT; i++)
			function[fnc_array[i].first] = fnc_array[i].second;
	}
	return _instance;
}

void CalcVisitor::Visit(TNode* pNode, AResult* pResult)
{
	nodeVariant data;
	pNode->getData(data);
	switch(data.type)
	{
		case INT:
			((CalcResult*)pResult)->value = data.varData.i;
			break;
		case DBL:
			((CalcResult*)pResult)->value = data.varData.d;
			break;
		case NCONST:
			((CalcResult*)pResult)->value = 0;
			break;
		default:
			((CalcResult*)pResult)->value = 0;
	}
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
			{
				MATH_FNC fnc = NULL;
				fnc = function[pNode->getFunction()];
				if(fnc) ((CalcResult*)pResult)->value = (*fnc)(((CalcResult*)pResult)->value);
			}
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



