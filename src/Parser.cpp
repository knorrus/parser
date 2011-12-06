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

vector<point> Parser::tabulate (double start, double end, char* function){
    vector<point> resultSet;
    this->tree = this->exprParser->CreateTree(function);
    CalcVisitor* pVisitor = CalcVisitor::Instance();
    point p;
    int pos =0;
    for (double i=start; i<end; i+=0.01) {
        pVisitor->loadParams("x", i);
        try {
            p.first = i*100;
            p.second = pVisitor->CalculateTree((ANode*) tree)*100;
            resultSet.push_back(p);
            pos++;
        }
        catch (ErrorCodes errorCode){
                switch (errorCode) {
                        case 1:
                                cerr << "Division by zero";

                        break;
                        case 2:
                                cerr << "Out of function definition area";
                                return resultSet;
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
