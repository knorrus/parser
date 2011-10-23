/*
 * ExprTree.h
 *
 *  Created on: Oct 22, 2011
 *      Author: pavel
 */

#ifndef EXPRTREE_H_
#define EXPRTREE_H_

#include "ExprTypes.h"

const int MAX_NAMED_CONST_LEN = 9;
class AVisitor;
struct AResult
{
};

class ANode : public Operand
{
public:
	virtual ANode* getRight() const =0;
	virtual ANode* getLeft() const =0;
	virtual OperandType GetType() = 0;
	virtual void setRight(ANode*) = 0;
	virtual void setLeft(ANode*) = 0;

	virtual void Accept(AVisitor& theVisitor, AResult*) = 0;

	virtual ~ANode() {};
};

struct nodeVariant {
	DataType type;
	union{
		int i;
		double d;
		char namedConst[MAX_NAMED_CONST_LEN + 1];
	} varData;
};

class TNode: public ANode
{
private:
	nodeVariant data;
public:
	TNode() {};
	virtual ~TNode() {};

	virtual ANode* getRight() const {return NULL;};
	virtual ANode* getLeft() const {return NULL;};
	virtual void setRight(ANode*) {};
	virtual void setLeft(ANode*) {};
	virtual OperandType GetType() {return isTerminal;};

	void getData(nodeVariant& d) {d.type = data.type; d.varData = data.varData;}

	TNode& operator = (int);
	TNode& operator = (double);
	TNode& operator = (char*);
	double toDouble() const;

	virtual void Accept(AVisitor& theVisitor, AResult*);
};

class UNode: public ANode
{
private:
	ANode* pArg;
	UOperation operation;
	char* fncName;

public:
	static int maxNameLength;

	UNode(UOperation o) : pArg(NULL), operation(o), fncName(NULL) {}
	virtual ~UNode();

	virtual OperandType GetType() {return isUnary;};

	virtual ANode* getRight() const {return pArg;}
	virtual ANode* getLeft() const {return pArg;}
	virtual void setRight(ANode* pNode) {pArg = pNode;}
	virtual void setLeft(ANode* pNode) {pArg = pNode;}

	UOperation getOperation() const {return operation;}

	char* getFunction() const {return fncName;}
	void setFunction(char*);

	virtual void Accept(AVisitor& theVisitor, AResult*);
};

class BNode: public ANode
{
private:
	ANode* pArgR;
	ANode* pArgL;
	BOperation operation;

public:
	BNode(BOperation o) : pArgR(NULL), pArgL(NULL), operation(o) {};
	virtual ~BNode();

	virtual ANode* getRight() const {return pArgR;}
	virtual ANode* getLeft() const {return pArgL;}
	virtual void setRight(ANode* pNode) {pArgR = pNode;}
	virtual void setLeft(ANode* pNode) {pArgL = pNode;}

	BOperation getOperation() const {return operation;}
	virtual OperandType GetType() {return isBinary;};

	virtual void Accept(AVisitor& theVisitor, AResult*);
};

class AVisitor
{
public:
	virtual void Visit(TNode*, AResult*) =0;
	virtual void Visit(UNode*, AResult*) =0;
	virtual void Visit(BNode*, AResult*) =0;
};


#endif /* EXPRTREE_H_ */
