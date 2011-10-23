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

struct CalcResult: public AResult
{
	double value;
};

class CalcVisitor: public AVisitor
{
public:
	virtual void Visit(TNode*, AResult*);
	virtual void Visit(UNode*, AResult*);
	virtual void Visit(BNode*, AResult*);

	double CalculateTree(ANode* head);
};

#endif /* VISITOR_H_ */
