/*
 * ExprTypes.h
 *
 *  Created on: Oct 22, 2011
 *      Author: pavel
 */

#ifndef EXPRTYPES_H_
#define EXPRTYPES_H_

enum ErrorCodes {
	DIVBYZERO = 1,
	OUTOFTYPE = 2,
	ZEROINZERO =3
};

enum DataType {
	INT, DBL, NCONST //DATA types witch can be saved in terminal element
};

enum UOperation {
	UMIN = '-', FNC //Types of unary operations: unary minus and math function like sin, tg, ln ...
};

enum BOperation {
	ADD = '+', MIN = '-', MULT = '*', DIVD = '/', DIVI = '\\' //Binary operations types
};

enum OperandType {
	isTerminal, isUnary, isBinary	//Types of syntax tokens
};

class Operand {
public:
	virtual OperandType GetType() = 0; //Abstract concept witch represent mathematical operation element
};

enum token_value { // Possibility types of token
	NAME = NCONST,
	DNUMBER = DBL,
	INUMBER = INT,
	BEGIN = 100,
	END = 101,
	PLUS = '+',
	MINUS = '-',
	MUL = '*',
	DIV = '/',
	IDIV = '\\',
	LP = '(',
	RP = ')'
};

/*Memento saved input string and current token type value*/
struct Memento {
	token_value token;
	char* tokenStr;

	virtual ~Memento() {
		delete tokenStr;
	}
};

/*Abstract expression builder, based on mathematical laws*/
class AExprBuilder {
public:
	virtual Operand* BuildTerminal(Memento* pCurrentState) = 0; 	//Terminal element represent expression values
	virtual Operand* BuildUnaryOperation(Memento* pCurrentState,	//Unary element represent all math unary operations
			Operand* pLeft) = 0;
	virtual Operand* BuildBinaryOperation(token_value token, Operand* pLeft,	//Binary element represent all math binary operations
			Operand* pRight) = 0;
};

/*Name table: name table use for save known in advance variables and constants */
const int TBLSZ = 25;

struct name {
	char* string;
	name* next;
	double value;
};

class NameTable {
	name* table[TBLSZ];
public:
	name* look(const char* p, int ins=0);
	name* insert(const char* s) {return look(s,1);}
};

#endif /* EXPRTYPES_H_ */
