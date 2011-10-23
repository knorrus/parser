/*
 * Visitor.h
 *
 *  Created on: Oct 23, 2011
 *      Author: pavel
 */

#ifndef VISITOR_H_
#define VISITOR_H_
#pragma once

#include "ExprTree.h"
#include "string.h"
#include <map>

using namespace std;

namespace ExprTree{

struct CalcResult: public AResult
{
	double value;
};

typedef double (*MATH_FNC)(double);
typedef map<string, MATH_FNC> STRING2FNC;

class CalcVisitor: public AVisitor
{
private:
	static STRING2FNC function;
	static CalcVisitor* _instance;

protected:
	CalcVisitor() {};

public:
	virtual void Visit(TNode*, AResult*);
	virtual void Visit(UNode*, AResult*);
	virtual void Visit(BNode*, AResult*);

	static CalcVisitor* Instance();
	double CalculateTree(ANode* head);
};
}
#endif /* VISITOR_H_ */
