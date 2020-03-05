#pragma once
#include "Object.hpp"
class String:
    public Object
{
public:
    std::string value;

    String(/* args */) {type=STRING;}
    String(std::string s) {type=STRING; value = s;}
    ~String() {}
    
    virtual Object* clone();
    

    //the operators only for primitives
    virtual Object& operator=(int);
    virtual Object& operator=(double);
    virtual Object& operator=(std::string);
    virtual Object& operator[](int);
    virtual Object& array_get(std::string);
    virtual bool condition();

    virtual Object& operator+(Object&);
    virtual Object& operator+=(Object&);
    virtual Object& operator=(Object&);
    virtual Object& operator==(Object&);
    virtual Object& operator!=(Object&);
    virtual Object& operator<(Object&);
    virtual Object& operator<=(Object&);
    virtual Object& operator>(Object&);
    virtual Object& operator>=(Object&);
    virtual Object& operator[](Object&);
};

extern bool isString(Object&);
extern String& toString(Object&);
extern bool isString(Object*);
extern String* toString(Object*);
