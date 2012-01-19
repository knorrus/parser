/*
 * Visitor.cpp
 *
 *  Created on: Oct 23, 2011
 *      Author: pavel
 */
#include "stdafx.h"
#include "MathFunctionsWrapper.h"

using namespace math;

CalcVisitor* CalcVisitor::_instance = NULL;	//use in implementation of singleton pattern
STRING2FNC CalcVisitor::function; //array of pairs witch represent all possible unary math function like cos, tg, ln and others in view: function name <-> link to function
NameTable* CalcVisitor::namedParams= NULL; //hash-map witch used for saved values of known in advance constants or variables

const int FNC_COUNT = 12;
_pairS2F fnc_array[FNC_COUNT] = {
    _pairS2F ("sqrt", &sqrt2),
    _pairS2F("sin", &sin),
    _pairS2F("cos", &cos),
    _pairS2F("tg", &tg),
    _pairS2F("ctg", &ctg),
    _pairS2F("exp", &exp),
    _pairS2F("lg", &lg),
    _pairS2F("ln", &ln),
    _pairS2F("arctg", &atan),
    _pairS2F("arcctg",&arcctg),
    _pairS2F("arcsin", arcsin),
    _pairS2F("arccos", arccos)
};

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
        namedParams->insert("x")->value = 3;
    }
    return _instance;
}

void CalcVisitor::loadParams(char* paramName, const double value){
    name* pos = namedParams->look(paramName);
    if (pos == NULL){
        namedParams->insert(paramName)->value = value;
    }
    try {
        namedParams->refresh(pos,value);
    }
    catch (...) {
        cerr << "Can't refresh param "<< paramName <<endl;
    }
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
    case INV:
        if( right_value.value == 0 &&  left_value.value == 0) throw ZEROINZERO;
        left_value.value = pow(left_value.value,right_value.value);
        break;
    case DIVD:
    case DIVI:
        if (abs(right_value.value) < 0.001) throw DIVBYZERO;
        left_value.value = left_value.value / right_value.value;
        break;
    }
}

double CalcVisitor::CalculateTree(ANode* head) {
    CalcResult node_value;
    head->Accept(*this, (AResult*) (&node_value));
    return node_value.value;
};

void NameTable::refresh(name* param, const double value){
    param->value = value;
}

name* NameTable::look(const char* p, int ins ) {
    int ii = 0;
    const char* pp = p;
    while (*pp)
        ii = ii << 1 ^ *pp++;
    if (ii < 0)
        ii = -ii;
    ii %= TBLSZ;
    for (name* n = table[ii]; n; n = n->next){
        if (strcmp(p, n->string) == 0)
            return n;
    }
    if (ins == 0) throw 2; //TODO:: Handle this throw exception;
    name* nn = new name;
    nn->string = new char[strlen(p) + 1];
    strcpy(nn->string, p);
    nn->value = 1;
    nn->next = table[ii];
    table[ii] = nn;
    return nn;
}
