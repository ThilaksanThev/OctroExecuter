#pragma once
#include "Object.hpp"
/*
    operator=
    deref
    condition
*/
class Pointer
    :public Object
{
    Object* value = octroNull;
public:
    Pointer(/* args */) {}
    Pointer(Object* o) {value = o;}
    ~Pointer() {}

    virtual void doOperation(void*,Operation,std::vector<Object*>p);
    virtual Object* clone();
    
    //the operators only for primitives
    virtual Object& operator=(int);
    virtual Object& operator=(double);
    virtual Object& operator=(std::string);
    virtual Object& operator[](int);
    virtual bool condition();
    
    //exception:
    /*
        die value kann geandert werden
    */
    virtual Object& operator=(Object& a);
    virtual Object& deref();

    //the operators
    virtual Object& operator+(Object&);
    virtual Object& operator-(Object&);
    virtual Object& operator*(Object&);
    virtual Object& operator/(Object&);
    virtual Object& operator%(Object&);
    virtual Object& operator+=(Object&);
    virtual Object& operator-=(Object&);
    virtual Object& operator*=(Object&);
    virtual Object& operator/=(Object&);
    virtual Object& operator%=(Object&);
    virtual Object& operator==(Object&);
    virtual Object& operator!=(Object&);
    virtual Object& operator<(Object&);
    virtual Object& operator<=(Object&);
    virtual Object& operator>(Object&);
    virtual Object& operator>=(Object&);
    virtual Object& operator&&(Object&);
    virtual Object& operator||(Object&);
    virtual Object& operator!();
    virtual Object& operator[](Object&);
    virtual Object& operator()(std::vector<Object*>);

    virtual void setUsed();
};

extern bool isPointer(Object&);
extern Pointer& toPointer(Object&);
extern bool isPointer(Object*);
extern Pointer* toPointer(Object*);
