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
    virtual ExpressionPtr getValue() const {
        throw std::runtime_error("Not implemented.[2]");
    }
    virtual ExpressionPtr getLeft() const {
        throw std::runtime_error("Not implemented.[3]");
    }
    virtual ExpressionPtr getRight() const {
        throw std::runtime_error("Not implemented.[4]");
    }
    virtual std::string getName() const {
        throw std::runtime_error("Not implemented.[5]");
    }
    virtual int getIntValue() const{
        throw std::runtime_error("Not implemented.[6]");
    }
    virtual float getFloatValue() const{
        throw std::runtime_error("Not implemented.[7]");
    }
};
