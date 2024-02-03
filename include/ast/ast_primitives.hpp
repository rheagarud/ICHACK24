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