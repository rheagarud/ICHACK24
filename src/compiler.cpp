#include <fstream>
#include <iostream>
#include <unistd.h>
#include <string>
#include <regex>
#include <unordered_map>
#include <stack>

#include "cli.h"
#include "../include/ast.hpp"


/*

RECURSIVE COMPILE

*/


std::string CompileRec(
    ExpressionPtr program
){
    std::cout << "GOING THROUGH: " << program->expressionType() << std::endl;

    /////////////////////////////
    // FROM ast_primitives.hpp //
    /////////////////////////////

    if (program->expressionType()=="Int"){
        return "{\"type\": \"int\", \"value\": " + std::to_string(program->getIntValue()) + "}";
        
    ////////////////////////////
    // FROM ast_operators.hpp //
    ////////////////////////////

    // For operators, may have to add some function for assigning registers instead of a4,a5 (idk)
    // AddOperator
    }else if (program->expressionType()=="Variable"){
        return "{\"type\": \"var\", \"name\": " + program->getName() + "}";
    }
    else if (program->expressionType()=="AddOperator"){
        std::cout << "GOING LEFT" << std::endl;
        std::string left = CompileRec(program->getLeft());
        std::cout << "GOING RIGHT" << std::endl;
        std::string right = CompileRec(program->getRight());
        return "{\"type\": \"add\", \"left\": " + left + ", \"right\": " + right + "}";

    // SubOperator
    }else if (program->expressionType()=="SubOperator"){
        return "{\"type\": \"sub\", \"left\": " + CompileRec(program->getLeft()) + ", \"right\": " + CompileRec(program->getRight()) + "}";

    // MultOperator
    }else if (program->expressionType()=="MultOperator"){
        return "{\"type\": \"mult\", \"left\": " + CompileRec(program->getLeft()) + ", \"right\": " + CompileRec(program->getRight()) + "}";

    // DivOperator
    }else if (program->expressionType()=="DivOperator"){
        return "{\"type\": \"div\", \"left\": " + CompileRec(program->getLeft()) + ", \"right\": " + CompileRec(program->getRight()) + "}";

    // ModuloOperator
    }else if (program->expressionType()=="ModuloOperator"){
        return "{\"type\": \"mod\", \"left\": " + CompileRec(program->getLeft()) + ", \"right\": " + CompileRec(program->getRight()) + "}";
    // LSOperator
    }else if (program->expressionType()=="PowerOperator"){
        return "{\"type\": \"power\", \"left\": " + CompileRec(program->getLeft()) + ", \"right\": " + CompileRec(program->getRight()) + "}";
    }
    else if (program->expressionType()=="LSOperator"){
        // TODO later

    // RSOperator
    }else if (program->expressionType()=="RSOperator"){
        // TODO later

    // AndOperator
    }else if (program->expressionType()=="AndOperator"){
        // TODO later

    // OrOperator
    }else if (program->expressionType()=="OrOperator"){
        // TODO later

    // EqualsOperator
    }else if (program->expressionType()=="EqualsOperator"){
        return "{\"type\": \"equals\", \"left\": " + CompileRec(program->getLeft()) + ", \"right\": " + CompileRec(program->getRight()) + "}";

    // NotEqualsOperator
    }else if (program->expressionType()=="NotEqualsOperator"){
        // TODO later

    // LessThanOperator
    }else if (program->expressionType()=="LessThanOperator"){
        return "{\"type\": \"<\", \"left\": " + CompileRec(program->getLeft()) + ", \"right\": " + CompileRec(program->getRight()) + "}";

    // MoreThanOperator
    }else if (program->expressionType()=="MoreThanOperator"){
        return "{\"type\": \">\", \"left\": " + CompileRec(program->getLeft()) + ", \"right\": " + CompileRec(program->getRight()) + "}";

    // LessThanEqualOperator
    }else if (program->expressionType()=="LessThanEqualOperator"){
        return "{\"type\": \"<=\", \"left\": " + CompileRec(program->getLeft()) + ", \"right\": " + CompileRec(program->getRight()) + "}";

    // MoreThanEqualOperator
    }else if (program->expressionType()=="MoreThanEqualOperator"){
        return "{\"type\": \">=\", \"left\": " + CompileRec(program->getLeft()) + ", \"right\": " + CompileRec(program->getRight()) + "}";

    // NotOperator - checks equal to 0
    }else if (program->expressionType()=="NotOperator"){
        // TODO later

    // NegateOperator - changes sign
    }else if (program->expressionType()=="NegateOperator"){
        std::string next = CompileRec(program->getValue());
        return "{\"type\": \"negate\", \"value\": " + next + "}";

    }else{
        throw std::runtime_error("Unknown construct '"+program->expressionType()+"'");
    }
}




    




/*

MAIN FUNCTION

*/


// TODO: uncomment the below if you're using Flex/Bison.
extern FILE *yyin;

int main(int argc, char **argv)
{
    // Parse CLI arguments, to fetch the values of the source and output files.
    std::string sourcePath = "";
    std::string outputPath = "";
    if (parse_command_line_args(argc, argv, sourcePath, outputPath))
    {
        return 1;
    }

    // TODO: uncomment the below lines if you're using Flex/Bison.
    // This configures Flex to look at sourcePath instead of
    // reading from stdin.
    yyin = fopen(sourcePath.c_str(), "r");
    if (yyin == NULL)
    {
        perror("Could not open source file");
        return 1;
    }

    // Parse the AST
    const ExpressionPtr ast = parseAST();
    // Compile
    const std::string res = CompileRec(ast);

    std::cout << res << std::endl;

    return 0;
}
