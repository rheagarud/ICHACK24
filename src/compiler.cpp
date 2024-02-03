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
    std::cout << program->expressionType() << std::endl;

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
    }else if (program->expressionType()=="AddOperator"){
        return "{\"type\": \"add\", \"left\": " + CompileRec(program->getLeft()) + ", \"right\": " + CompileRec(program->getRight()) + "}";

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
    }else if (program->expressionType()=="LSOperator"){
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
        // TODO later

    // NotEqualsOperator
    }else if (program->expressionType()=="NotEqualsOperator"){
        // TODO later

    // LessThanOperator
    }else if (program->expressionType()=="LessThanOperator"){
        // TODO later

    // MoreThanOperator
    }else if (program->expressionType()=="MoreThanOperator"){
        // TODO later

    // LessThanEqualOperator
    }else if (program->expressionType()=="LessThanEqualOperator"){
        // TODO later

    // MoreThanEqualOperator
    }else if (program->expressionType()=="MoreThanEqualOperator"){
        // TODO later

    // NotOperator - checks equal to 0
    }else if (program->expressionType()=="NotOperator"){
        // TODO later

    // NegateOperator - changes sign
    }else if (program->expressionType()=="NegateOperator"){
        // TODO later


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

    return 0;
}
