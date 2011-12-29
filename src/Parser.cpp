#include "Parser.h";
using namespace std;

Parser::Parser()
{
    this->builder = new CTreeBuilder();;
    this->exprParser = new CExprParser(builder);
}


Parser::~Parser(){
    delete this->tree;
    delete this->exprParser;
    delete this->builder;
}

double abs (double value) {
        return value < 0 ? -value : value;
}

vector<point> Parser::tabulate (double start, double end, char* function){
    vector<point> resultSet;
    this->tree = this->exprParser->CreateTree(function);
    CalcVisitor* pVisitor = CalcVisitor::Instance();
    point p;
    double step = abs(end-start)/350;
    for (double i=start; i<end; i+=step) {
        pVisitor->loadParams("x", i);
        try {
            p.first = i;
            p.second = pVisitor->CalculateTree((ANode*) tree);
            resultSet.push_back(p);
        }
        catch (ErrorCodes errorCode){
                switch (errorCode) {
                        case 1:
                                cerr << "Division by zero";
                        break;
                        case 2:
                                cerr << "Out of function definition area";
                        break;
                        case 3:
                                cerr << "Zero pow zero";
                        break;
                };
        }
        catch (...){
            cerr << "Undefined error";
        }
    }
    return resultSet;
}
