/*
 * ExprParserMain.cpp
 *
 *  Created on: Oct 22, 2011
 *      Author: pavel
 */
#include "stdafx.h"

#include "math.h"

int main() {
	try {
		char* arg = new char[100];
		cout << "Enter expression " << endl;
		cin >> arg;
		AExprBuilder* treeBuilder = new CTreeBuilder();
		CExprParser* parser = new CExprParser(treeBuilder);
		Operand* tree = parser->CreateTree(arg);
		CalcVisitor* pVisitor = CalcVisitor::Instance();
		double result = pVisitor->CalculateTree((ANode*) tree);
			cout << "The result is " << result << endl;
		delete tree;
		delete pVisitor;
		delete parser;
		delete treeBuilder;
		return 0;
	}
	catch (string error)
	{
		cout << error << endl;
		return 1;
	}
	catch (...)
	{
		return 2;
	}
	return 3;
}

