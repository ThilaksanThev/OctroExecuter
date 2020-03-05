#include "Function.hpp"
#include "Number.hpp"
#include "String.hpp"
#include <iostream>
#include "Script.hpp"

Object* dummy(std::vector<Object*>& param){
    if(isNumber(param[0]))
        std::cout <<toNumber(param[0])->value<<std::endl;
    if(isString(param[0]))
        std::cout <<toString(param[0])->value<<std::endl;
    
    return octroNull;   
}

Function::Function(){
    fun = dummy;
    type = FUNCTION;
}
Function::Function(Object*(*func)(std::vector<Object*>&)) {
    fun = func;
}
Object& Function::operator()(std::vector<Object*> a){
    return *fun(a);
}