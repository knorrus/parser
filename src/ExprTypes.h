/*
 * ExprTypes.h
 *
 *  Created on: Oct 22, 2011
 *      Author: pavel
 */

#ifndef EXPRTYPES_H_
#define EXPRTYPES_H_


const double pi = 3.1415926535897932385;

enum DataType {
	INT,
	DBL,
	NCONST
};

enum UOperation
{
	UMIN = '-',
	FNC
};

enum BOperation{
	ADD = '+',
	MIN = '-',
	MULT = '*',
	DIVD = '/',
	DIVI = '\\'
};

enum OperandType{
	isTerminal, isUnary, isBinary
};

class Operand
{
public:
	virtual OperandType GetType() = 0;
};

enum token_value {
    NAME = NCONST,		DNUMBER = DBL,	INUMBER = INT,	BEGIN = 100,	END = 101,
    PLUS='+',	MINUS='-',  MUL='*',	DIV='/',	IDIV='\\',
    LP='(',		RP=')'
};

struct Memento
{
	token_value token;
	char* tokenStr;

	virtual ~Memento() {delete tokenStr;}
};

class AExprBuilder
{
public:
	virtual Operand* BuildTerminal(Memento* pCurrentState) = 0;
	virtual Operand* BuildUnaryOperation(Memento* pCurrentState, Operand* pLeft) = 0;
	virtual Operand* BuildBinaryOperation(token_value token, Operand* pLeft, Operand* pRight) = 0;
};


#endif /* EXPRTYPES_H_ */
