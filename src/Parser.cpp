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

vector<point> Parser::tabulate (double start, double end, double dpi, char* function){
    vector<point> resultSet;
    try {
        this->tree = this->exprParser->CreateTree(function);
    }
    catch (...){
        throw WRONGFORMAT;
    }
    CalcVisitor* pVisitor = CalcVisitor::Instance();
    point p;
    double step = abs(end-start)/dpi;
    for (double i=start; i<end; i+=step) {
        pVisitor->loadParams("x", i);
        try {
            p.second = pVisitor->CalculateTree((ANode*) tree);
            p.first = i;
            p.type = GRAPHPOINT;
            resultSet.push_back(p);
        }
        catch (ErrorCodes errorCode){
            switch (errorCode) {
                case DIVBYZERO:
                    //cerr << "Division by zero";
                    p.second = 0;
                    p.first = i;
                    p.type = PDFK;
                    resultSet.push_back(p);
                    break;
                case OUTOFTYPE:
                    //cerr << "Out of function definition area";
                    p.second = 0;
                    p.first = i;
                    p.type = PDSK;
                    resultSet.push_back(p);
                    break;
                case ZEROINZERO:
                    cerr << "Zero pow zero" << endl;
                    break;
                };
        }
        catch (...){
            cerr << "Undefined error"<< endl;
        }
    }
    return resultSet;
}
