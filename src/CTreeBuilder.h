/*
 * CTreeBuilder.h
 *
 *  Created on: Oct 22, 2011
 *      Author: pavel
 */

#ifndef CTREEBUILDER_H_
#define CTREEBUILDER_H_

#include "ExprTypes.h"

class CTreeBuilder: public AExprBuilder
{
public:
	virtual Operand* BuildTerminal(Memento* pCurrentState);
	virtual Operand* BuildUnaryOperation(Memento* pCurrentState, Operand* pLeft);
	virtual Operand* BuildBinaryOperation(token_value token, Operand* pLeft, Operand* pRight);
};



#endif /* CTREEBUILDER_H_ */
