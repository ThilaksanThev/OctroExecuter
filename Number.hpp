#pragma once
#include "Object.hpp"


class Number
    :public Object
{
public:

    double value = 0;

    Number(/* args */) {type = NUMBER;}
    Number(int i) {value = i;type = NUMBER;}
    Number(double d) {value = d;type = NUMBER;}
    ~Number() {}
    
    virtual Object* clone()override;
    
    //primitiv setting
    virtual Object& operator=(int)override;
    virtual Object& operator=(double)override;
    virtual bool condition()override;
    
    virtual Object& operator+(Object&)override;
    virtual Object& operator-(Object&)override;
    virtual Object& operator*(Object&)override;
    virtual Object& operator/(Object&)override;
    virtual Object& operator%(Object&)override;
    virtual Object& operator+=(Object&)override;
    virtual Object& operator-=(Object&)override;
    virtual Object& operator*=(Object&)override;
    virtual Object& operator/=(Object&)override;
    virtual Object& operator%=(Object&)override;
    virtual Object& operator=(Object&)override;
    virtual Object& operator==(Object&)override;
    virtual Object& operator!=(Object&)override;
    virtual Object& operator<(Object&)override;
    virtual Object& operator<=(Object&)override;
    virtual Object& operator>(Object&)override;
    virtual Object& operator>=(Object&)override;
    virtual Object& operator&&(Object&)override;
    virtual Object& operator||(Object&)override;
    virtual Object& operator!()override;
};

extern bool isNumber(Object&);
extern Number& toNumber(Object&);
extern bool isNumber(Object*);
extern Number* toNumber(Object*);
