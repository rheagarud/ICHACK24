#pragma once
#include "ast_expression.hpp"
#include <string>
#include <iostream>
#include <vector>

// parent class for all variable types - will implement more than int later
class Variable : public Expression{
private:
    std::string name;
public:
    Variable() {throw std::runtime_error("Variable name not given");}
    Variable (const std::string& _name)
    : name(_name) {}

    virtual std::string getName() const override{
        return name;
    }

    virtual std::string expressionType() const override{
        return "Variable";
    }
};


// int type wrapper
class Int : public Expression{
private:
    int value;
public:
    Int()
    : value(0){}
    Int(int _value)
    : value(_value){}

    virtual int getIntValue() const override{
        return value;
    }
    virtual std::string expressionType() const override{
        return "Int";
    }
};