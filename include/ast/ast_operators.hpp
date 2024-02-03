#pragma once
#include "ast_expression.hpp"
#include <string>
#include <iostream>
#include <vector>

enum Operators{
    ASSIGN,
    ADDITION,
    SUBTRACTION,
    MULTIPLICATION,
    DIVISION,
    MODULO,
    LESS,
    MORE,
    LESSOREQUAL,
    MOREOREQUAL,
    POWER
};

class ArithCompOperator : public Expression {
private:
    ExpressionPtr left;
    ExpressionPtr right;
    int optype;

public:
    ArithCompOperator(){
        throw std::runtime_error("Arithemetic/Comparison Operator not initialised with values");
    }
    ArithCompOperator(ExpressionPtr _left, ExpressionPtr _right)
    : left(_left), right(_right), optype(ASSIGN){}
    ArithCompOperator(ExpressionPtr _left, ExpressionPtr _right, int _optype)
    : left(_left), right(_right), optype(_optype){}
    virtual ~ArithCompOperator()
    {
        delete left;
        delete right;
    }
    virtual ExpressionPtr getLeft() const override {
        return left;
    }
    virtual ExpressionPtr getRight() const override{
        return right;
    }

    virtual std::string expressionType() const override{
        switch(optype){
            case ADDITION:
                return "AddOperator";
                break;
            case SUBTRACTION:
                return "SubOperator";
                break;
            case MULTIPLICATION:
                return "MultOperator";
                break;
            case DIVISION:
                return "DivOperator";
                break;
            case MODULO:
                return "ModuloOperator";
                break;
            case LESS:
                return "LessThanOperator";
                break;
            case MORE:
                return "MoreThanOperator";
                break;
            case LESSOREQUAL:
                return "LessThanEqualOperator";
                break;
            case MOREOREQUAL:
                return "MoreThanEqualOperator";
                break;
            case POWER:
                return "Power";
                break;
            default:
                throw std::runtime_error("Invalid Arithmetic, Logic or Comparison operator");
        }
    }
};
