#include "Number.hpp"

double rest(double a,double b){
    while(a>=b){
        a-=b;
    }
    return a; 
}

bool isNumber(Object& a){
    return a.type==NUMBER;
}
Number& toNumber(Object&a){
    return *((Number*)&a);
}
bool isNumber(Object* a){
    return a->type==NUMBER;
}
Number* toNumber(Object*a){
    return ((Number*)a);
}
Object* Number::clone(){
    auto rv = new Number;
    rv->value = value;
    return rv;
}
Object& Number::operator=(int i){
    value = i;
    return *this;
}
Object& Number::operator=(double d){
    value = d;
    return *this;
}
bool Number::condition(){
    return value;
}
Object& Number::operator+(Object& b){
    if(b.type!=NUMBER)
        return *octroNull;
    auto rv = new Number;
    rv->value = value +toNumber(b).value;
    return *rv;
}
Object& Number::operator-(Object& b){
    if(b.type!=NUMBER)
        return *octroNull;
    auto rv = new Number;
    rv->value = value-toNumber(b).value;
    return *rv;
}
Object& Number::operator*(Object& b){
    if(b.type!=NUMBER)
        return *octroNull;
    auto rv = new Number;
    rv->value = value*toNumber(b).value;
    return *rv;
}
Object& Number::operator/(Object& b){
    if(b.type!=NUMBER)
        return *octroNull;
    auto rv = new Number;
    rv->value = value/toNumber(b).value;
    return *rv;
}
Object& Number::operator%(Object& b){
    if(b.type!=NUMBER)
        return *octroNull;
    auto rv = new Number;
    rv->value = rest(value,toNumber(b).value);
    return *rv;
}
Object& Number::operator+=(Object& b){
    if(b.type!=NUMBER)
        return *octroNull;
    value+=toNumber(b).value;
    return *this;
}
Object& Number::operator-=(Object& b){
    if(b.type!=NUMBER)
        return *octroNull;
    value-=toNumber(b).value;
    return *this;
}
Object& Number::operator*=(Object& b){
    if(b.type!=NUMBER)
        return *octroNull;
    value*=toNumber(b).value;
    return *this;
}
Object& Number::operator/=(Object& b){
    if(b.type!=NUMBER)
        return *octroNull;
    value/=toNumber(b).value;
    return *this;
}
Object& Number::operator%=(Object& b){
    if(b.type!=NUMBER)
        return *octroNull;
    value=rest(value,toNumber(b).value);
    return *this;
}
Object& Number::operator=(Object& b){
    if(b.type!=NUMBER)
        return *octroNull;
    value=toNumber(b).value;
    return *this;
}
Object& Number::operator==(Object& b){
    if(b.type!=NUMBER)
        return *octroNull;
    auto rv = new Number;
    rv->value = value==toNumber(b).value;
    return *rv;
}
Object& Number::operator!=(Object& b){
    if(b.type!=NUMBER)
        return *octroNull;
    auto rv = new Number;
    rv->value = value!=toNumber(b).value;
    return *rv;
}
Object& Number::operator<(Object& b){
    if(b.type!=NUMBER)
        return *octroNull;
    auto rv = new Number;
    rv->value = value<toNumber(b).value;
    return *rv;
}
Object& Number::operator<=(Object& b){
    if(b.type!=NUMBER)
        return *octroNull;
    auto rv = new Number;
    rv->value = value<=toNumber(b).value;
    return *rv;
}
Object& Number::operator>(Object& b){
    if(b.type!=NUMBER)
        return *octroNull;
    auto rv = new Number;
    rv->value = value>toNumber(b).value;
    return *rv;
}
Object& Number::operator>=(Object& b){
    if(b.type!=NUMBER)
        return *octroNull;
    auto rv = new Number;
    rv->value = value>=toNumber(b).value;
    return *rv;
}
Object& Number::operator&&(Object& b){
    if(b.type!=NUMBER)
        return *octroNull;
    auto rv = new Number;
    rv->value = value&&toNumber(b).value;
    return *rv;
}
Object& Number::operator||(Object&b){
    if(b.type!=NUMBER)
        return *octroNull;
    auto rv = new Number;
    rv->value = value||toNumber(b).value;
    return *rv;
}
Object& Number::operator!(){
    auto rv = new Number;
    rv->value = !value;
    return *rv;
}