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
	cin >> arg;
	CExprParser parser;
	ANode* tree = parser.CreateTree(arg);
	delete tree;
	return 0;
}




