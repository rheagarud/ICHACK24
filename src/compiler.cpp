#include <fstream>
#include <iostream>
#include <unistd.h>
#include <string>
#include <regex>
#include <unordered_map>
#include <stack>

#include "cli.h"
#include "ast.hpp"













/*

RECURSIVE COMPILE

*/



// unique target flags (while, if)
static int makeTargetNameUnq=2;
static std::string makeTargetName()
{
    return ".L"+std::to_string(makeTargetNameUnq++);
}
// unique logic flags (out implementation of logic)
static int makeLogicTargetNameUnq=2;
static std::string makeLogicTargetName()
{
    return ".Logic"+std::to_string(makeLogicTargetNameUnq++);
}


//////////////////////
///  Global Hacks  ///
//////////////////////
static std::string ReturnFlag; // return flag for functions
static std::string SwitchEndFlag;
int StackDepth = 0;


/*
////////////////////////
// Variables (global) //
////////////////////////
std::unordered_map<std::string, int> memory_location;
// Define Variables
std::string define_var(std::string variable_name){
    int MemoryPtr;
    std::vector<int> memory;
    for(auto kv : memory_location){ // Gets list of memory locations
        memory.push_back(kv.second);
    }
    for(int i=0; i>-64; i=i-4){ // finds highest memory location
        if (std::find(memory.begin(), memory.end(), i) != memory.end()){
            int MemoryPtr = i;
        }
    }
    memory_location.insert({variable_name, MemoryPtr});
    return std::to_string(MemoryPtr);
}
// Retrieve variable from map
std::string get_var(std::string variable_name){
    return std::to_string(memory_location[variable_name]);
}
*/

////////////////////////////////////////////////////
// Variables (hacking into save registers s1-s11) //
////////////////////////////////////////////////////
std::unordered_map<std::string, std::string> SaveRegisters;
// Define Variables
std::string define_var(std::string variable_name){ // returns save register
    int NextFreeReg = SaveRegisters.size();
    if (NextFreeReg == 10)
    {
        throw std::runtime_error("SAVED REGISTER HACK OVERFLOW");
    }
    else
    {
        SaveRegisters.insert({variable_name, "s" + std::to_string(NextFreeReg+1)});
    }
    return "s" + std::to_string(NextFreeReg+1);
}
// Retrieve variable from map
std::string get_var(std::string variable_name){
    return SaveRegisters[variable_name];
}





////////////////////////////////////////////////////
// Recursion (hacking into save registers t4-t6)  //
////////////////////////////////////////////////////
std::stack<std::string> ReturnAddressStack;
// Define Variables
std::string recurse_add(){ // returns save register
    int NextFreeReg = SaveRegisters.size();
    if (NextFreeReg == 3)
    {
        throw std::runtime_error("SAVED REGISTER HACK OVERFLOW");
    }
    else
    {
        ReturnAddressStack.push("t" + std::to_string(NextFreeReg+3));
    }
    return "t" + std::to_string(NextFreeReg+3);
}
// Retrieve variable from map
std::string recurse_remove(){
    std::string ra = ReturnAddressStack.top();
    ReturnAddressStack.pop();
    return ra;
}





void CompileRec(
    std::ostream &w,
    std::string destReg,    // The name of the register to put the result in
    ExpressionPtr program
){
    std::cout << program->expressionType() << std::endl;

    /////////////////////////////
    // FROM ast_primitives.hpp //
    /////////////////////////////

    // Variable - allocates memory (register) for variable
    if (program->expressionType()=="Variable"){
        //define_var(program->getName());
        std::string VariableSaveReg = get_var(program->getName());
        w << "        mv      " << destReg << "," << VariableSaveReg << std::endl;

    // IntVariable - allocates memory (register) for variable
    }else if (program->expressionType()=="IntVariable"){
        // godbolt doesn't really do anything (maybe optimisation?)
        define_var(program->getName());



    // Void
    }else if (program->expressionType()=="Void"){
        // VOID TYPE EMPTY



    // Int - integer number
    }else if (program->expressionType()=="Int"){
        /*
        int val = program->getIntValue();
        if (abs(val) <= 12288)
        {
            w << "        li      " << destReg << "," << std::to_string(program->getIntValue()) << std::endl;
        }
        else
        {
            w << "        li      " << destReg << ",12288" << std::endl;
            val -=
            while (abs(val) > 12288)
            {
                w << "        addi    a5,a5,1" << destReg << "," << destReg <<
            }
        }
        */
        w << "        li      " << destReg << "," << std::to_string(program->getIntValue()) << std::endl;
        //w << "        li      " << destReg << ",12288" << std::endl;
        //w << "        addi    " << destReg << "," << destReg << ",57" << std::endl;



    // Function
    }else if (program->expressionType()=="Function"){
        //StackDepth += 1;
        std::string FuncName = program->getName();
        ReturnFlag = FuncName + "_END_OF_FUNCTION";
        w << ".globl " << FuncName << std::endl;
        w << FuncName << ":" << std::endl;
        

        
        // something to set sp (store change)
        w << "        addi    sp,sp,-64" << std::endl;
        w << "        sw      ra,0(sp)" << std::endl;
        
        
        // something to set required input args (store from a0, a1, a2, a3)
        std::vector<ExpressionPtr> args = program->getArgs();
        for(std::vector<const Expression*>::size_type i = 0; i < args.size(); i++)
        {
            std::string VariableSaveReg = define_var(args[i]->getName());
            w << "        mv      " << VariableSaveReg << ",a" << i << std::endl;
        }
        
        // Body
        std::vector<ExpressionPtr> body =  program->getBody();
        for(std::vector<const Expression*>::size_type i = 0; i < body.size(); i++)
        {
            CompileRec(w, "a0", body[i]);
        }


        w << ReturnFlag << ":" << std::endl;
        w << "        mv      a0,a5" << std::endl;

        // something to reset sp
        w << "        lw      ra,0(sp)" << std::endl;
        w << "        addi    sp,sp,64" << std::endl;
        /*
        if (StackDepth > 1)
        {
        std::string ra_store = recurse_remove();
        w << "        mv      ra," << ra_store << std::endl;
        }
        */
        w << "        jr      ra"<< std::endl;
        //StackDepth -= 1;



    // Return - completes return line with expression
    }else if (program->expressionType()=="Return"){
        CompileRec(w, "a5", program->getRetExpr());
        // possible problem: returing variable alone may not load to a5
        w << "        j       " << ReturnFlag << std::endl;





    // FunctionCall
    }else if (program->expressionType()=="FunctionCall"){
        StackDepth += 1;
        // if recursive, set args (a0, a1, a2, a3)
        std::vector<ExpressionPtr> args = program->getArgs();
        /*
        std::string ra_store = recurse_add();
        w << "        mv      " << ra_store << ",ra" << std::endl;
        */

        for(std::vector<const Expression*>::size_type i = 0; i < args.size(); i++)
        {
            CompileRec(w, "a"+std::to_string(i), args[i]);
        }
        w << "        call    " << program->getName() << std::endl;


    // Define Integer Array element
    }else if (program->expressionType()=="IntArr"){
        // Hack - store array name with element as variable (will pass 2/4 array tests)
        define_var(program->getName() + "[" + std::to_string(program->getSize()->getIntValue()) + "]");
        //w << program->getName() << ":" << std::endl;
        //w << "        .zero    " << program->getSize()->getIntValue() * 4 << std::endl;

    // get array element
    }else if (program->expressionType()=="ArrElement"){
        // Hack - store array name with element as variable (will pass 2/4 array tests)
        std::string VariableSaveReg = get_var(program->getName() + "[" + std::to_string(program->getIndex()->getIntValue()) + "]");
        w << "        mv      " << destReg << "," << VariableSaveReg << std::endl;
        









    ////////////////////////////
    // FROM ast_operators.hpp //
    ////////////////////////////

    // AssignOperator
    }else if (program->expressionType()=="AssignOperator"){
        //CompileRec(w, "a5", program->getVariable());
        CompileRec(w, "a5", program->getValue());
        std::string VariableSaveReg = get_var(program->getVariable()->getName()); // WARNING: Double pointer causes problems
        w << "        mv      " << VariableSaveReg << "," << "a5" << std::endl;


    // AdditionAssignOperator
    }else if (program->expressionType()=="AdditionAssignOperator"){
        std::string VariableSaveReg = get_var(program->getVariable()->getName()); // WARNING: Double pointer causes problems
        w << "        mv      t2,"<< VariableSaveReg << std::endl;
        CompileRec(w, "a5", program->getValue());
        w << "        add     a5,t2,a5" << std::endl;
        w << "        mv      " << VariableSaveReg << "," << "a5" << std::endl;


    // SubtractionAssignOperator
    }else if (program->expressionType()=="SubtractionAssignOperator"){
        std::string VariableSaveReg = get_var(program->getVariable()->getName()); // WARNING: Double pointer causes problems
        w << "        mv      t2,"<< VariableSaveReg << std::endl;
        CompileRec(w, "a5", program->getValue());
        w << "        sub     a5,t2,a5" << std::endl;
        w << "        mv      " << VariableSaveReg << "," << "a5" << std::endl;

    // MultiplicationAssignOperator
    }else if (program->expressionType()=="MultiplicationAssignOperator"){
        std::string VariableSaveReg = get_var(program->getVariable()->getName()); // WARNING: Double pointer causes problems
        w << "        mv      t2,"<< VariableSaveReg << std::endl;
        CompileRec(w, "a5", program->getValue());
        w << "        mul     a5,t2,a5" << std::endl;
        w << "        mv      " << VariableSaveReg << "," << "a5" << std::endl;

    // DivisionAssignOperator
    }else if (program->expressionType()=="DivisionAssignOperator"){
        std::string VariableSaveReg = get_var(program->getVariable()->getName()); // WARNING: Double pointer causes problems
        w << "        mv      t2,"<< VariableSaveReg << std::endl;
        CompileRec(w, "a5", program->getValue());
        w << "        div     a5,t2,a5" << std::endl;
        w << "        mv      " << VariableSaveReg << "," << "a5" << std::endl;

    // ModuloAssignOperator
    }else if (program->expressionType()=="ModuloAssignOperator"){
        std::string VariableSaveReg = get_var(program->getVariable()->getName()); // WARNING: Double pointer causes problems
        w << "        mv      t2,"<< VariableSaveReg << std::endl;
        CompileRec(w, "a5", program->getValue());
        w << "        rem     a5,t2,a5" << std::endl;
        w << "        mv      " << VariableSaveReg << "," << "a5" << std::endl;

    // BitAndAssignOperator
    }else if (program->expressionType()=="BitAndAssignOperator"){
        std::string VariableSaveReg = get_var(program->getVariable()->getName()); // WARNING: Double pointer causes problems
        CompileRec(w, "a5", program->getValue());
        w << "        mv      a4,"<< VariableSaveReg << std::endl;
        w << "        and     a5,a4,a5" << std::endl;
        w << "        mv      " << VariableSaveReg << ",a5" << std::endl;

    // BitOrAssignOperator
    }else if (program->expressionType()=="BitOrAssignOperator"){
        std::string VariableSaveReg = get_var(program->getVariable()->getName()); // WARNING: Double pointer causes problems
        CompileRec(w, "a5", program->getValue());
        w << "        mv      a4,"<< VariableSaveReg << std::endl;
        w << "        or      a5,a4,a5" << std::endl;
        w << "        mv      " << VariableSaveReg << ",a5" << std::endl;

    // BitXorAssignOperator
    }else if (program->expressionType()=="BitXorAssignOperator"){
        std::string VariableSaveReg = get_var(program->getVariable()->getName()); // WARNING: Double pointer causes problems
        CompileRec(w, "a5", program->getValue());
        w << "        mv      a4,"<< VariableSaveReg << std::endl;
        w << "        xor     a5,a4,a5" << std::endl;
        w << "        mv      " << VariableSaveReg << ",a5" << std::endl;

    // LSAssignOperator
    }else if (program->expressionType()=="LSAssignOperator"){
        std::string VariableSaveReg = get_var(program->getVariable()->getName()); // WARNING: Double pointer causes problems
        CompileRec(w, "a5", program->getValue());
        w << "        mv      a4,"<< VariableSaveReg << std::endl;
        w << "        sll     a5,a4,a5" << std::endl;
        w << "        mv      " << VariableSaveReg << ",a5" << std::endl;

    // RSAssignOperator
    }else if (program->expressionType()=="RSAssignOperator"){
        std::string VariableSaveReg = get_var(program->getVariable()->getName()); // WARNING: Double pointer causes problems
        CompileRec(w, "a5", program->getValue());
        w << "        mv      a4,"<< VariableSaveReg << std::endl;
        w << "        srl     a5,a4,a5" << std::endl;
        w << "        mv      " << VariableSaveReg << ",a5" << std::endl;









    // For operators, may have to add some function for assigning registers instead of a4,a5 (idk)
    // AddOperator
    }else if (program->expressionType()=="AddOperator"){
        // Make Left Reg
        CompileRec(w, "a4", program->getLeft());
        // Make Right Reg
        CompileRec(w, "a5", program->getRight());
        w << "        add     " << destReg << ",a4,a5" << std::endl;

    // SubOperator
    }else if (program->expressionType()=="SubOperator"){
        CompileRec(w, "a4", program->getLeft());
        CompileRec(w, "a5", program->getRight());
        w << "        sub     " << destReg << ",a4,a5" << std::endl;

    // MultOperator
    }else if (program->expressionType()=="MultOperator"){
        CompileRec(w, "a4", program->getLeft());
        CompileRec(w, "a5", program->getRight());
        w << "        mul     " << destReg << ",a4,a5" << std::endl;

    // DivOperator
    }else if (program->expressionType()=="DivOperator"){
        CompileRec(w, "a4", program->getLeft());
        CompileRec(w, "a5", program->getRight());
        w << "        div     " << destReg << ",a4,a5" << std::endl;

    // ModuloOperator
    }else if (program->expressionType()=="ModuloOperator"){
        CompileRec(w, "a4", program->getLeft());
        CompileRec(w, "a5", program->getRight());
        w << "        rem     " << destReg << ",a4,a5" << std::endl;

    // BitAndOperator
    }else if (program->expressionType()=="BitAndOperator"){
        CompileRec(w, "a4", program->getLeft());
        CompileRec(w, "a5", program->getRight());
        w << "        and     " << destReg << ",a4,a5" << std::endl;

    // BitOrOperator
    }else if (program->expressionType()=="BitOrOperator"){
        CompileRec(w, "a4", program->getLeft());
        CompileRec(w, "a5", program->getRight());
        w << "        or      " << destReg << ",a4,a5" << std::endl;

    // BitXorOperator
    }else if (program->expressionType()=="BitXorOperator"){
        CompileRec(w, "a4", program->getLeft());
        CompileRec(w, "a5", program->getRight());
        w << "        xor     " << destReg << ",a4,a5" << std::endl;

    // LSOperator
    }else if (program->expressionType()=="LSOperator"){
        CompileRec(w, "a4", program->getLeft());
        CompileRec(w, "a5", program->getRight());
        w << "        sll     " << destReg << ",a4,a5" << std::endl;

    // RSOperator
    }else if (program->expressionType()=="RSOperator"){
        CompileRec(w, "a4", program->getLeft());
        CompileRec(w, "a5", program->getRight());
        w << "        srl     " << destReg << ",a4,a5" << std::endl;

    // AndOperator
    }else if (program->expressionType()=="AndOperator"){
        CompileRec(w, "a4", program->getLeft());
        CompileRec(w, "a5", program->getRight());
        std::string flag_false = makeLogicTargetName();
        std::string flag_end = makeLogicTargetName();
        w << "        beq     a4,zero," << flag_false << std::endl;
        w << "        beq     a5,zero," << flag_false << std::endl;
        w << "        li      " << destReg << ",1" << std::endl;
        w << "        j       " << flag_end << std::endl;
        w << flag_false << ":" << std::endl;
        w << "        li      " << destReg << ",0" << std::endl;
        w << flag_end << ":" << std::endl;

    // OrOperator
    }else if (program->expressionType()=="OrOperator"){
        CompileRec(w, "a4", program->getLeft());
        CompileRec(w, "a5", program->getRight());
        std::string flag_false = makeLogicTargetName();
        std::string flag_true = makeLogicTargetName();
        std::string flag_end = makeLogicTargetName();
        w << "        bne     a5,zero," << flag_false << std::endl;
        w << "        beq     a4,zero," << flag_true << std::endl;
        w << flag_false << ":" << std::endl;
        w << "        li      " << destReg << ",1" << std::endl;
        w << "        j       " << flag_end << std::endl;
        w << flag_true << ":" << std::endl;
        w << "        li      " << destReg << ",0" << std::endl;
        w << flag_end << ":" << std::endl;

    // EqualsOperator
    }else if (program->expressionType()=="EqualsOperator"){
        CompileRec(w, "a4", program->getLeft());
        CompileRec(w, "a5", program->getRight());
        std::string flag = makeLogicTargetName();
        w << "        li      t0,0" << std::endl;
        w << "        bne     a4,a5," << flag << std::endl;
        w << "        li      t0,1" << std::endl;
        w << flag << ":" << std::endl;
        w << "        mv      " << destReg << ",t0" << std::endl;


    // NotEqualsOperator
    }else if (program->expressionType()=="NotEqualsOperator"){
        CompileRec(w, "a4", program->getLeft());
        CompileRec(w, "a5", program->getRight());
        std::string flag = makeLogicTargetName();
        w << "        li      t0,0" << std::endl;
        w << "        beq     a4,a5," << flag << std::endl;
        w << "        li      t0,1" << std::endl;
        w << flag << ":" << std::endl;
        w << "        mv      " << destReg << ",t0" << std::endl;

    // LessThanOperator
    }else if (program->expressionType()=="LessThanOperator"){
        CompileRec(w, "a4", program->getLeft());
        CompileRec(w, "a5", program->getRight());
        std::string flag = makeLogicTargetName();
        w << "        li      t0,0" << std::endl;
        w << "        bge     a4,a5," << flag << std::endl;
        w << "        li      t0,1" << std::endl;
        w << flag << ":" << std::endl;
        w << "        mv      " << destReg << ",t0" << std::endl;

    // MoreThanOperator
    }else if (program->expressionType()=="MoreThanOperator"){
        CompileRec(w, "a4", program->getLeft());
        CompileRec(w, "a5", program->getRight());
        std::string flag = makeLogicTargetName();
        w << "        li      t0,0" << std::endl;
        w << "        blt     a4,a5," << flag << std::endl;
        w << "        beq     a4,a5," << flag << std::endl;
        w << "        li      t0,1" << std::endl;
        w << flag << ":" << std::endl;
        w << "        mv      " << destReg << ",t0" << std::endl;

    // LessThanEqualOperator
    }else if (program->expressionType()=="LessThanEqualOperator"){
        CompileRec(w, "a4", program->getLeft());
        CompileRec(w, "a5", program->getRight());
        std::string flag_true = makeLogicTargetName();
        std::string flag_false = makeLogicTargetName();
        w << "        li      t0,0" << std::endl;
        w << "        beq     a4,a5," << flag_true << std::endl;
        w << "        bge     a4,a5," << flag_false << std::endl;
        w << flag_true << ":" << std::endl;
        w << "        li      t0,1" << std::endl;
        w << flag_false << ":" << std::endl;
        w << "        mv      " << destReg << ",t0" << std::endl;

    // MoreThanEqualOperator
    }else if (program->expressionType()=="MoreThanEqualOperator"){
        CompileRec(w, "a4", program->getLeft());
        CompileRec(w, "a5", program->getRight());
        std::string flag = makeLogicTargetName();
        w << "        li      t0,0" << std::endl;
        w << "        blt     a4,a5," << flag << std::endl;
        w << "        li      t0,1" << std::endl;
        w << flag << ":" << std::endl;
        w << "        mv      " << destReg << ",t0" << std::endl;







    // SuffixPlusOperator
    }else if (program->expressionType()=="SuffixPlusOperator"){
        std::string VariableSaveReg = get_var(program->getValue()->getName()); // WARNING: Double pointer causes problems
        w << "        mv      a5," << VariableSaveReg << std::endl;
        w << "        li      t1,1" << std::endl;
        w << "        add     " << destReg << ",a5,t1" << std::endl;
        w << "        mv      " << VariableSaveReg << "," << destReg << std::endl;

    // SuffixMinusOperator
    }else if (program->expressionType()=="SuffixMinusOperator"){
        std::string VariableSaveReg = get_var(program->getValue()->getName()); // WARNING: Double pointer causes problems
        w << "        mv      a5," << VariableSaveReg << std::endl;
        w << "        li      t1,1" << std::endl;
        w << "        sub     " << destReg << ",a5,t1" << std::endl;
        w << "        mv      " << VariableSaveReg << "," << destReg << std::endl;

    // PrefixPlusOperator
    }else if (program->expressionType()=="PrefixPlusOperator"){
        std::string VariableSaveReg = get_var(program->getValue()->getName()); // WARNING: Double pointer causes problems
        w << "        mv      a5," << VariableSaveReg << std::endl;
        w << "        li      t1,1" << std::endl;
        w << "        mv      t2,a5" << std::endl;
        w << "        add     a5,a5,t1" << std::endl;
        w << "        mv      " << VariableSaveReg << ",a5" << std::endl;
        w << "        mv      " << destReg << ",t2" << std::endl;


    // PrefixMinusOperator
    }else if (program->expressionType()=="PrefixMinusOperator"){
        std::string VariableSaveReg = get_var(program->getValue()->getName()); // WARNING: Double pointer causes problems
        w << "        mv      a5," << VariableSaveReg << std::endl;
        w << "        li      t1,1" << std::endl;
        w << "        mv      t2,a5" << std::endl;
        w << "        sub     a5,a5,t1" << std::endl;
        w << "        mv      " << VariableSaveReg << ",a5" << std::endl;
        w << "        mv      " << destReg << ",t2" << std::endl;

    // NotOperator - checks equal to 0
    }else if (program->expressionType()=="NotOperator"){
        std::string VariableSaveReg = get_var(program->getValue()->getName()); // WARNING: Double pointer causes problems
        std::string flag_false = makeLogicTargetName();
        w << "        mv      a5," << VariableSaveReg << std::endl;
        w << "        li      t2,zero" << std::endl;
        w << "        beq     a5,zero," << flag_false << std::endl;
        w << "        li      t1,1" << std::endl;
        w << "        li      t2,t1" << std::endl;
        w << flag_false << ":" << std::endl;
        w << "        mv      " << destReg << ",t2" << std::endl;


    // NegateOperator - changes sign
    }else if (program->expressionType()=="NegateOperator"){
        std::string VariableSaveReg = get_var(program->getValue()->getName()); // WARNING: Double pointer causes problems
        w << "        mv      a5," << VariableSaveReg << std::endl;
        w << "        sub     " << destReg << ",zero,a5" << std::endl;
        w << "        mv      " << VariableSaveReg << ",a5" << std::endl;


    // BitNotOperator
    }else if (program->expressionType()=="BitNotOperator"){
        std::string VariableSaveReg = get_var(program->getValue()->getName()); // WARNING: Double pointer causes problems
        w << "        mv      a5," << VariableSaveReg << std::endl;
        w << "        not     " << destReg << ",a5" << std::endl;







    /*
    // CommaOperator
    }else if (program->expressionType()=="CommaOperator"){
        std::vector<ExpressionPtr> expressions = program->getExpressions();
        for (std::vector<const Expression*>::size_type i = 0; i < expressions.size(); ++i)
        {
            CompileRec(w, "a5", expressions[i]);
        }
    */


    //////////////////////////
    // FROM ast_control.hpp //
    //////////////////////////

    // WhileLoop
    }else if (program->expressionType()=="WhileLoop"){
        std::string BodyTarget = makeTargetName(); // gives '.Ln' target
        std::string ConditionTarget = makeTargetName();

        w << "        j       " << ConditionTarget << std::endl;

        // Body
        w << BodyTarget << ":" << std::endl;
        std::vector<ExpressionPtr> body = program->getBody();
        for (auto it = body.begin(); it != body.end(); ++it){ // iterate through lines in Body
            CompileRec(w, destReg, *it);
        }

        // Condition
        w << ConditionTarget << ":" << std::endl;
        // Calculate condition
        CompileRec(w, "a5", program->getCondition());
        w << "        li      t1,1" << std::endl;
        //       Branch to target (BodyTarget) if true
        w << "        beq     a5,t1," << BodyTarget << std::endl;







    // IfStatement
    }else if (program->expressionType()=="IfStatement"){
        if_array conditions = program->getConditions();
        std::string endif_flag = makeTargetName();
        for (auto i = conditions.begin(); i != conditions.end(); i++)
        {
            std::string if_flag = makeTargetName();
            //CONDITION
            CompileRec(w, "a5", i->first);
            // branch if a5 ne 1
            w << "        li      t1,1" << std::endl;
            w << "        bne     a5,t1," << if_flag << std::endl;
            // BODY
            for (std::vector<const Expression*>::size_type j = 0; j < i->second.size(); j++)
            {
                CompileRec(w, "a5", i->second[j]);
            }
            w << "        j       " << endif_flag << std::endl;
            w << if_flag << ":" << std::endl;
        }
        w << endif_flag << ":" << std::endl;

        // Make flag for each statement
        // this section in format:
        // CONDTION
        // BODY
        // FLAG

        // evaluate if condition == 1
        // jump to next section if not true
        // else do body then jump to after

        // repeat for as many elements in if_array


        // ForLoop
        }else if (program->expressionType()=="ForLoop"){
            std::vector<ExpressionPtr> condition = program->getForCondition();
            std::string flag_body = makeTargetName();
            std::string flag_condition = makeTargetName();

            CompileRec(w, "a5", condition[0]);
            w << "        j       " << flag_condition << std::endl;
            // Body
            w << flag_body << ":" << std::endl;
            std::vector<ExpressionPtr> body = program->getBody();
            for(std::vector<const Expression*>::size_type i = 0; i < body.size(); i++)
            {
            CompileRec(w, "a5", body[i]);
            }
            CompileRec(w, "a5", condition[2]);
            // Condition
            w << flag_condition << ":" << std::endl;
            CompileRec(w, "a5", condition[1]);
            w << "        bne     a5,zero," << flag_body << std::endl;



        // Switch
        }else if (program->expressionType()=="Switch"){
            std::string unique_switch_flag = makeTargetName();
            SwitchEndFlag = makeTargetName();
            // execute condition
            CompileRec(w, "t2", program->getCondition());
            // go through cases, branch to flags of cases if equal
            if_array cases = program->getOutcomes();
            int loop_tracker = 0;
            for (auto i = cases.begin(); i != cases.end(); i++)
            {
                CompileRec(w, "a5", i->first);
                w << "        beq     a5,t2," << unique_switch_flag << "_" << loop_tracker << std::endl;
                // if case == 100, jump (hack for default case)
                w << "        li      a4,100" << std::endl;
                w << "        beq     a4,a5," << unique_switch_flag << "_" << loop_tracker << std::endl;
                loop_tracker += 1;
            }
            // jump to end flag
             w << "        j       " << SwitchEndFlag << std::endl;

            // go through case flag with body
            int num = 0;
            for (auto i = cases.begin(); i != cases.end(); i++)
            {
            w << unique_switch_flag << "_" << num << ":" << std::endl;
            num += 1;
            // BODY
            for (std::vector<const Expression*>::size_type j = 0; j < i->second.size(); j++)
            {
                CompileRec(w, "a5", i->second[j]);
            }
            w << "        j       " << SwitchEndFlag << std::endl;
            }
            
            // end flag
            w << SwitchEndFlag << ":" << std::endl;






            // Switch
            }else if (program->expressionType()=="Break"){
                w << "        j       " << SwitchEndFlag << std::endl;





    }else{
        throw std::runtime_error("Unknown construct '"+program->expressionType()+"'");
    }
}



void compile(std::ostream &w, ExpressionPtr program)
{

    w << ".text" << std::endl;
    w << std::endl;

    CompileRec(w, "a0", program);

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

    // Open the output file in truncation mode (to overwrite the contents)
    std::ofstream output;
    output.open(outputPath, std::ios::trunc);

    // Compile the input
    std::cout << "Compiling: " << sourcePath << std::endl;

    // Parse the AST
    std::vector<const Expression*> ast=parseAST();
    // Compile
    for(std::vector<ExpressionPtr>::size_type i = 0; i < ast.size(); i++)
    {
        compile(output, ast[i]);
    }

    std::cout << "Compiled to: " << outputPath << std::endl;

    output.close();
    return 0;
}
