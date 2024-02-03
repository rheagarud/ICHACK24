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
    POWER,
    NEGATE,
    EQUAL
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
                return "PowerOperator";
                break;
            case EQUAL:
                return "EqualsOperator";
                break;
            default:
                throw std::runtime_error("Invalid Arithmetic, Logic or Comparison operator");
        }
    }
};

class Unary : public Expression {
private:
    ExpressionPtr val;
    int optype;
public:
    Unary(){
        throw std::runtime_error("Class not initialised");
    }
    Unary(ExpressionPtr _val)
    : val(_val), optype(NEGATE) {} //defaults to -a
    Unary(ExpressionPtr _val, int _optype)
    : val(_val), optype(_optype) {}

    virtual ~Unary(){
        delete val;
    }
    virtual ExpressionPtr getValue() const override{
        return val;
    }
    virtual std::string expressionType() const override{
        switch(optype){
            case (NEGATE):
                return "NegateOperator";
                break;
            default:
                throw std::runtime_error("Invalid Unary operator");
        }
    }
};
