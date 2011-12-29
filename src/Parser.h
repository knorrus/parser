#ifndef PARSER_H
#define PARSER_H
#include "stdafx.h"

class Parser {
    private:
        AExprBuilder* builder;
        CExprParser* exprParser;
        Operand* tree;
    public:
        Parser();
        Parser(AExprBuilder* builder);
        vector<point> tabulate (double start, double end, char* function);
        ~Parser();
};

#endif // PARSER_H
