#pragma once

#include "ast/ast_expression.hpp"
#include "ast/ast_primitives.hpp"
#include "ast/ast_operators.hpp"


// Declare parseAST function
extern const Expression* parseAST();

// Declare main compile function
void compile(
    std::ostream &w,
    ExpressionPtr ast
);

