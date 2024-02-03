#pragma once

#include <string>
#include <iostream>
#include <map>
#include <memory>
#include <vector>


class Expression;

typedef const Expression* ExpressionPtr;

typedef std::map<ExpressionPtr, std::vector<ExpressionPtr>> if_array ;

/*
explanation: we don't need to immediately evaluate any individual node - we just need
the compiler to tell what type of node it is (variable, number, arithmetic/logic, function, control flow etc etc)and what the relevant information
for the node is (variable type and value, left and right arithmetic/logic expressions, function parameters&body&return type, control conditions and sub expressions)
and then the compiler does the hard work of converting it to assembly
*/

class Expression
{
public:
    virtual ~Expression()
    {}

    virtual std::string expressionType() const{
        throw std::runtime_error("Not implemented.[1]");
    }
    virtual ExpressionPtr getRetExpr() const{
        throw std::runtime_error("Not implemented.[2]");
    }
    virtual const if_array getConditions() const{
        throw std::runtime_error("Not implemented.[3]");
    }
    virtual void changeConditions(ExpressionPtr cond, std::vector<ExpressionPtr> body) {
        throw std::runtime_error("Not implemented.[4]");
    }
    virtual ExpressionPtr getCondition() const{
        throw std::runtime_error("Not implemented.[5]");
    }
    virtual const std::vector<ExpressionPtr> getForCondition() const{
        throw std::runtime_error("Not implemented.[6]");
    }
    virtual const std::vector<ExpressionPtr> getBody() const{
        throw std::runtime_error("Not implemented.[7]");
    }
    virtual const if_array getOutcomes() const{
        throw std::runtime_error("Not implemented.[8]");
    }
    virtual void updateOutcomes(ExpressionPtr value, std::vector<ExpressionPtr> body) {
        throw std::runtime_error("Not implemented.[9]");
    }
    virtual ExpressionPtr getVariable() const {
        throw std::runtime_error("Not implemented.[10]");
    }
    virtual ExpressionPtr getValue() const {
        throw std::runtime_error("Not implemented.[11]");
    }
    virtual ExpressionPtr getLeft() const {
        throw std::runtime_error("Not implemented.[12]");
    }
    virtual ExpressionPtr getRight() const {
        throw std::runtime_error("Not implemented.[13]");
    }
    virtual const std::vector<ExpressionPtr> getExpressions() const {
        throw std::runtime_error("Not implemented.[14]");
    }
    virtual void updateExpressions(ExpressionPtr expr) {
        throw std::runtime_error("Not implemented.[15]");
    }
    virtual const std::vector<ExpressionPtr> getArgs() const{
        throw std::runtime_error("Not implemented.[16]");
    }
    virtual std::string getName() const {
        throw std::runtime_error("Not implemented.[17]");
    }
    virtual const ExpressionPtr getSize() const{
        throw std::runtime_error("Not implemented.[18]");
    }
    virtual void updateValue(int index, ExpressionPtr value){
        throw std::runtime_error("Not implemented.[19]");
    }
    virtual ExpressionPtr getIndex() const{
        throw std::runtime_error("Not implemented.[20]");
    }
    virtual int getIntValue() const{
        throw std::runtime_error("Not implemented.[21]");
    }
    virtual const std::vector<ExpressionPtr> getIntArrValue() const{
        throw std::runtime_error("Not implemented.[22]");
    }
    virtual std::string funcType() const{
        throw std::runtime_error("Not implemented.[23]");
    }
};
