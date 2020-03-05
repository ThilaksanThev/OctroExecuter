#pragma once
#include "Object.hpp"
class Function
    :public Object
{
protected:
    Object*(*fun)(std::vector<Object*>&);
public:
    Function(Object*(*func)(std::vector<Object*>&));
    Function();
    virtual Object& operator()(std::vector<Object*> a);
};