#pragma once
#include "Object.hpp"

class Array
    :public Object
{
    std::vector<Object*> children;
    bool isOverriden(Operation);
public:

    Array(/* args */) {type=ARRAY;}
    Array(std::vector<Object*>p) {type=ARRAY;for(auto x:p)children.push_back(x);}
    ~Array() {}

    virtual void doOperation(void*,Operation,std::vector<Object*>p);
    virtual Object* clone();
    virtual Object* operation(Operation,std::vector<Object*>);

    //the operators only for primitives
    virtual Object& operator=(int);
    virtual Object& operator=(double);
    virtual Object& operator=(std::string);
    virtual Object& operator[](int);
    virtual Object& array_insert(int,Object*);
    virtual Object& array_get(std::string);
    virtual void array_remove(int);
    virtual void collect(std::vector<Object*>&);
    virtual std::vector<Object*> anticollect();
    virtual bool condition();
    
    //the operators
    virtual Object& operator+(Object&);
    virtual Object& operator-(Object&);
    virtual Object& operator+=(Object&);
    virtual Object& operator-=(Object&);
    virtual Object& operator=(Object&);
    virtual Object& operator==(Object&);
    virtual Object& operator!=(Object&);
    virtual Object& operator<(Object&);
    virtual Object& operator<=(Object&);
    virtual Object& operator>(Object&);
    virtual Object& operator>=(Object&);
    virtual Object& operator[](Object&);

    //only here to be overrideable
    virtual Object& constructor(std::vector<Object*>);
    virtual void destructor();
    virtual Object& deref();
    virtual Object& address();
    virtual Object& operator*(Object&);
    virtual Object& operator/(Object&);
    virtual Object& operator%(Object&);
    virtual Object& operator*=(Object&);
    virtual Object& operator/=(Object&);
    virtual Object& operator%=(Object&);
    virtual Object& operator&&(Object&);
    virtual Object& operator||(Object&);
    virtual Object& operator!();
    virtual Object& operator()(std::vector<Object*>);

    virtual void setUsed();
};

extern bool isArray(Object&);
extern Array& toArray(Object&);
extern bool isArray(Object*);
extern Array* toArray(Object*);
