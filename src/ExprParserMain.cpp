/*
 * ExprParserMain.cpp
 *
 *  Created on: Oct 22, 2011
 *      Author: pavel
 */
#include "stdafx.h"

// ExprParser.exe 1*(2+2)*3
int main()
{
	char* arg = new char[100];
	cout << "Enter exprassion "<< endl;
	cin >> arg;
	AExprBuilder* treeBuilder = new CTreeBuilder();
	CExprParser* parser = new CExprParser(treeBuilder);
	Operand* tree = parser->CreateTree(arg);
	CalcVisitor theVisitor;
	double result = theVisitor.CalculateTree((ANode*)tree);
	delete tree;
	cout << "The result is " << result << endl;
	return 0;
}




