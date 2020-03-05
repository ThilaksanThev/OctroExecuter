#include "Pointer.hpp"
#include "Script.hpp"

Object* Pointer::clone(){
    auto rv = new Pointer;
    rv->value = value;
    return rv;
}
Object& Pointer::operator=(int i){
    return (*value)=i;
}
Object& Pointer::operator=(double d){
    return (*value)=d;
}
Object& Pointer::operator=(std::string s){
    return (*value)=s;
}
Object& Pointer::operator[](int i){
    return (*value)[i];
}
bool Pointer::condition(){
    return (value!=octroNull);
}
Object& Pointer::operator=(Object& a){
    value = &a;
    return *this;
}
Object& Pointer::deref(){
    return (*value);
}
Object& Pointer::operator+(Object& a){
    return (*value)+a;
}
Object& Pointer::operator-(Object& a){
    return (*value)-a;
}
Object& Pointer::operator*(Object& a){
    return (*value)*a;
}
Object& Pointer::operator/(Object& a){
    return (*value)/a;
}
Object& Pointer::operator%(Object& a){
    return (*value)%a;
}
Object& Pointer::operator+=(Object& a){
    return (*value)+=a;
}
Object& Pointer::operator-=(Object& a){
    return (*value)-=a;
}
Object& Pointer::operator*=(Object& a){
    return (*value)*=a;
}
Object& Pointer::operator/=(Object& a){
    return (*value)/=a;
}
Object& Pointer::operator%=(Object& a){
    return (*value)%=a;
}
Object& Pointer::operator==(Object& a){
    return (*value)==a;
}
Object& Pointer::operator!=(Object& a){
    return (*value)!=a;
}
Object& Pointer::operator<(Object& a){
    return (*value)<a;
}
Object& Pointer::operator<=(Object& a){
    return (*value)<=a;
}
Object& Pointer::operator>(Object& a){
    return (*value)>a;
}
Object& Pointer::operator>=(Object& a){
    return (*value)>=a;
}
Object& Pointer::operator&&(Object& a){
    return (*value)&&a;
}
Object& Pointer::operator||(Object& a){
    return (*value)||a;
}
Object& Pointer::operator!(){
    return !(*value);
}
Object& Pointer::operator[](Object& a){
    return (*value)[a];
}
Object& Pointer::operator()(std::vector<Object*> s){
    return (*value)(s);
}

bool isPointer(Object& a){
    return(a.type==POINTER);
}
Pointer& toPointer(Object& a){
    return *(Pointer*)&a;
}
bool isPointer(Object*a){
    return a->type==POINTER;
}
Pointer* toPointer(Object*a){
    return (Pointer*)a;
}
void Pointer::setUsed(){
    used = true;
    value->setUsed();
}

void Pointer::doOperation(void* v,Operation o,std::vector<Object*>p){
    if(o==DEREF){
        ((Script*)v)->push(&this->deref());
    }else if(o==SET){
        ((Script*)v)->push(&((*this)=(*p[0])));
    }
    else value->doOperation(v,o,p);
}
