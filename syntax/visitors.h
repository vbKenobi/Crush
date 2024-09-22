#ifndef visitor_h
#define visitor_h

#include <iostream>
#include <string>
#include "tree.h"
#include "../inc/token.h"
#include "tree.h"

template <typename T>
class Visitor {
public: 
	virtual T visitBinaryExpr(Binary<T>* element) = 0;
	virtual T visitGroupingExpr(Grouping<T>* element) = 0;
	virtual T visitLiteralExpr(Literal<T>* element) = 0;
	virtual T visitUnaryExpr(Unary<T>* element) = 0;
};

class AstPrinter : public Visitor<std::string> 
{
    public:
        std::string print(Expr<std::string>* expression) { 
            return expression->accept(this); 
        }
        
        inline std::string visitBinaryExpr(Binary<std::string>* element) override {return "a";};
        inline std::string visitGroupingExpr(Grouping<std::string>* element) override {return "b";};
        inline std::string visitLiteralExpr(Literal<std::string>* element) override {return "c";};
        inline std::string visitUnaryExpr(Unary<std::string>* element) override {return "d";};
};

#endif