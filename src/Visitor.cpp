/*
 * Visitor.cpp
 *
 *  Created on: Oct 23, 2011
 *      Author: pavel
 */
#include "stdafx.h"
#include <math.h>

CalcVisitor* CalcVisitor::_instance = NULL;	//use in implementation of singleton pattern
STRING2FNC CalcVisitor::function; //array of pairs witch represent all possible unary math function like cos, tg, ln and others in view: function name <-> link to function
NameTable* CalcVisitor::namedParams= NULL; //hash-map witch used for saved values of known in advance constants or variables

double ctg(double value) {
	return (1 / tan(value));
}

const int FNC_COUNT = 10;

_pairS2F fnc_array[FNC_COUNT] = {
		_pairS2F("sin", &sin),
		_pairS2F("cos", &cos),
		_pairS2F("tg", &tan),
		_pairS2F("exp", &exp),
		_pairS2F("lg", &log10),
		_pairS2F("ln", &log),
		_pairS2F("arctg", &atan),
		_pairS2F("arcsin", &asin),
		_pairS2F("arccos", &acos),
		_pairS2F("ctg", &ctg) };

bool operator < (PtrS2F left, PtrS2F right) {
	return (strcmp(left->first, right->first) < 0);
}

MATH_FNC STRING2FNC::operator [](char* key) {
	iterator Result;
	Result = lower_bound(begin(), end(), key);

	if (Result != end() && !strcmp((*Result)->first, key))
		return (*(*Result)).second;
	else
		return NULL;
}

CalcVisitor* CalcVisitor::Instance() {
	if (_instance == NULL)
	{
		_instance = new CalcVisitor;
		for (int i = 0; i < FNC_COUNT; i++){
			function.push_back(&fnc_array[i]);
		}
		function.DoSort();
		namedParams = new NameTable();
		namedParams->insert("pi")->value = 3.1415926535897932385;
		namedParams->insert("e")->value = 2.7182818284590452354;
		/*for (int i = 0; i < FNC_COUNT; i++)
		 cout << function.at(i)->first << '\n';*/
	}
	return _instance;
}

void CalcVisitor::Visit(TNode* pNode, AResult* pResult) {
	nodeVariant data;
	pNode->getData(data);
	char* name = data.varData.namedConst;
	switch (data.type) {
	case INT:
		((CalcResult*) pResult)->value = data.varData.i;
		break;
	case DBL:
		((CalcResult*) pResult)->value = data.varData.d;
		break;
	case NCONST:
		((CalcResult*) pResult)->value = namedParams->look(name)->value;
		break;
	default:
		((CalcResult*) pResult)->value = 0;
	}
}

void CalcVisitor::Visit(UNode* pNode, AResult* pResult) {
	(pNode->getLeft())->Accept(*this, pResult);
	switch (pNode->getOperation()) {
	case UMIN:
		((CalcResult*) pResult)->value = -((CalcResult*) pResult)->value;
		break;
	case FNC: {
		MATH_FNC fnc = function[pNode->getFunction()];
		if (fnc)
			((CalcResult*) pResult)->value = (*fnc)(((CalcResult*) pResult)->value);
		else
			throw string("Unknown function < ") + pNode->getFunction() + string(" > in parsed expression");
	}
		break;
	}
}

void CalcVisitor::Visit(BNode* pNode, AResult* pResult) {
	(pNode->getLeft())->Accept(*this, pResult);
	CalcResult& left_value = *((CalcResult*) pResult);

	CalcResult right_value;
	(pNode->getRight())->Accept(*this, (AResult*) (&right_value));
	switch (pNode->getOperation()) {
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
		if (right_value.value == 0) throw 1;
		left_value.value = left_value.value / right_value.value;
		break;
	}
}

double CalcVisitor::CalculateTree(ANode* head) {
	CalcResult node_value;
	try {
		head->Accept(*this, (AResult*) (&node_value));
	}
	catch (int error_code){
		cerr << "Division by zero";
	}
	return node_value.value;
}
;

name* NameTable::look(const char* p, int ins ) {
	int ii = 0;
	const char* pp = p;
	while (*pp)
		ii = ii << 1 ^ *pp++;
	if (ii < 0)
		ii = -ii;
	ii %= TBLSZ;
	for (name* n = table[ii]; n; n = n->next)
		if (strcmp(p, n->string) == 0)
			return n;

	if (ins == 0) throw 2;

	name* nn = new name;
	nn->string = new char[strlen(p) + 1];strcpy
	(nn->string, p);
	nn->value = 1;
	nn->next = table[ii];
	table[ii] = nn;
	return nn;
}

