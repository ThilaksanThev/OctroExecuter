#include "String.hpp"
#include "Number.hpp"

Object* String::clone(){
    return new String(value);
}
    

//the operators only for primitives
Object& String::operator=(int i){
    value = std::to_string(i);
    return *this;
}
Object& String::operator=(double d){
    value = std::to_string(d);
    return *this;
}
Object& String::operator=(std::string s){
    value = s;
    return *this;
}
Object& String::operator[](int i){
    return *new Number(value[i]);
}
Object& String::array_get(std::string s){
    //spaetere Methoden
    return *this;
}
bool String::condition(){
    return value.length();
}
Object& String::operator+(Object& a){
    if(!isString(a))
        return *this;
    return *new String(value+toString(a).value);
}
Object& String::operator+=(Object&a){
    if(!isString(a))
        return *this;
        value+=toString(a).value;
    return *this;
}
Object& String::operator=(Object&a){
    value = toString(a).value;
    return *this;
}
Object& String::operator==(Object&a){
    if(isString(a))
        return *new Number(toString(a).value==value);
    return *this;
}
Object& String::operator!=(Object&a){
    if(isString(a))
        return *new Number(toString(a).value!=value);
    return *this;
}
Object& String::operator<(Object&a){
    if(isString(a))
        return *new Number(value<toString(a).value);
    return *this;
}
Object& String::operator<=(Object&a){
    if(isString(a))
        return *new Number(value<=toString(a).value);
    return *this;
}
Object& String::operator>(Object&a){
    if(isString(a))
        return *new Number(value>toString(a).value);
    return *this;
}
Object& String::operator>=(Object&a){
    if(isString(a))
        return *new Number(value>=toString(a).value);
    return *this;
}
Object& String::operator[](Object&a){
    if(isNumber(a))
        return *new Number(value[(int)toNumber(a).value]);
    return *this;
}

bool isString(Object& a){
    return a.type==STRING;
}
String& toString(Object& a){
    return *(String*)&a;
}
bool isString(Object* a){
    return a->type==STRING;
}
String* toString(Object* a){
    return (String*)a;
}
