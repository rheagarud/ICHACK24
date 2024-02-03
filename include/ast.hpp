#pragma once

#include "ast/ast_expression.hpp"

// Declare parseAST function
extern std::vector<const Expression*> parseAST();

// Declare main compile function
void compile(
    std::ostream &w,
    ExpressionPtr ast
);

