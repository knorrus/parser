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

#include <string>
#include <vector>
#include <algorithm>

#include <math.h>


using namespace std;

struct CalcResult: public AResult
{
	double value;
};

typedef double (*MATH_FNC)(double);
typedef pair<char*, MATH_FNC> _pairS2F;

class PtrS2F
{
	_pairS2F* _ptr;
	bool mine_ptr; // 1 - this create pair, 0 - pair has been attached

public:

	PtrS2F(_pairS2F* pointer = NULL) : _ptr(pointer), mine_ptr(false) {}

	// For use in STL algorithms
	PtrS2F(char* first)
	{
		_ptr = new _pairS2F(first, NULL);
		mine_ptr = true;
	}

	~PtrS2F(){if(mine_ptr) delete _ptr;}

	void Attach(_pairS2F* pointer)
	{
		if(mine_ptr) delete _ptr;
		_ptr = pointer;
		mine_ptr = false;
	}

	inline operator _pairS2F () { return *_ptr; }
	inline _pairS2F& operator * () { return *_ptr; }
	inline _pairS2F* operator -> () { return _ptr; }

	_pairS2F& operator = (_pairS2F& right)
	{
		if(mine_ptr) delete _ptr;
		_ptr = new _pairS2F(right);
		mine_ptr = true;
		return *_ptr;
	}

	_pairS2F& operator = (_pairS2F* right)
	{
		Attach(right);
		return *_ptr;
	}

	_pairS2F& operator = (MATH_FNC pfnc)
	{
		_ptr->second = pfnc;
		return *_ptr;
	}

	friend bool operator < (PtrS2F left, PtrS2F right);
};



class STRING2FNC: public vector<PtrS2F>
{
public:
	inline void DoSort() {sort(begin(), end());}
	MATH_FNC operator [](char* key);
};

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


#endif /* VISITOR_H_ */
