#pragma once
#include "Script.hpp"
#include "Function.hpp"
class InternalFunction
    :public Function
{
    int marker = 0;
    Script* script;
public:
    InternalFunction(Script*,int);
    virtual Object* clone();
    virtual Object& operator()(std::vector<Object*> a);
    virtual void doOperation(void*,Operation,std::vector<Object*>p);
    virtual Object& operator=(int);
};