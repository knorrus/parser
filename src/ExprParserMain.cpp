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
		delete tree;
		cout << "The result is " << result << endl;
		return 0;
	} catch (string error_string) {
		cout << error_string << '\n';
		return 1;
	} catch (...) {
		return 1;
	}
	return 2;
}

