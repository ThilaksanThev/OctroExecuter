#include "Array.hpp"
#include "Number.hpp"
#include "String.hpp"
#include "Script.hpp"

Object* Array::clone(){
    auto rv  = new Array;
    for(auto x:children)
        rv->children.push_back(x->clone());
    return rv;
}

//the operators only for primitives
Object& Array::operator=(int i){
    if(isOverriden(SET))return *operation(SET,{new Number(i)});
    children = {new Number(i)};
    return *this;
}
Object& Array::operator=(double d){
    if(isOverriden(SET))return *operation(SET,{new Number(d)});
    children = {new Number(d)};
    return *this;
}
Object& Array::operator=(std::string s){
    if(isOverriden(SET))return *operation(SET,{new String(s)});
    children = {new String(s)};
    return *this;
}
Object& Array::operator[](int i){
    if(isOverriden(INDEX))return *operation(INDEX,{new Number(i)});
    if(children.size()>i)
        return *children[i];
    return *octroNull;
}
Object& Array::array_insert(int i,Object* o){
    if(children.size()>=i)
        children.insert(children.begin()+i,o);
    return *this;
}
Object& Array::array_get(std::string s){
    for(auto& x : children)
        if(x->name==s)
            return *x;
    return *octroNull;
}
void Array::array_remove(int i){
    if(children.size()>i)
        children.erase(children.begin()+i);
}
void Array::collect(std::vector<Object*>& a){
    children = a;
}
std::vector<Object*> Array::anticollect(){
    auto rv = children;
    children.clear();
    return rv;
}
bool Array::condition(){
    auto s = &array_get("condition");
    if(s!=octroNull){
        return (*s)({this}).condition();
    }
    return children.size();
}
    
Object& Array::operator+(Object& a){
    if(isOverriden(ADD))return *operation(ADD,{&a});
    Array* rv = new Array;
    rv->children = children;
    rv->children.push_back(&a);
    return *rv;
}
Object& Array::operator-(Object& a){
    if(isOverriden(SUB))return *operation(SUB,{&a});
    if(!isNumber(a))
        return *this;
    int n = ((Number*)&a)->value;
    Array* rv = new Array;
    rv->children = children;
    while(n--){
        rv->children.pop_back();
    }
    return *rv;
}
Object& Array::operator+=(Object& a){
    if(isOverriden(SETADD))return *operation(SETADD,{&a});
    children.push_back(&a);
    return *this;
}
Object& Array::operator-=(Object& a){
    if(isOverriden(SETSUB))return *operation(SETSUB,{&a});
    if(!isNumber(a))
        return *this;
    int n = ((Number*)&a)->value;
    while(n--){
        this->children.pop_back();
    }
    return *this;
}
Object& Array::operator=(Object& a){
    if(isOverriden(SET))return *operation(SET,{&a});
    if(isNumber(a))
        (*this)=((Number*)&a)->value;
    if(isString(a))
        (*this)=((Number*)&a)->value;
    if(isArray(a))
        children=toArray(a).children;
    return *this;
}
Object& Array::operator==(Object& a){
    if(isOverriden(EQUALS))return *operation(EQUALS,{&a});
    Number* num = new Number(0);
    if(isArray(a)){
        Array& r = toArray(a);
        num->value = r.children.size()==children.size();
        if(num->value)
            for (size_t i = 0; i < children.size(); i++){
                if(num->value)
                    num->value = children[i]==r.children[i];
            }
    }
    return *num;
}
Object& Array::operator!=(Object& a){
    if(isOverriden(UNEQUALS))return *operation(UNEQUALS,{&a});
    Number* num = new Number(0);
    if(isArray(a)){
        Array& r = toArray(a);
        num->value = r.children.size()==children.size();
        if(num->value)
            for (size_t i = 0; i < children.size(); i++){
                if(num->value)
                    num->value = children[i]==r.children[i];
            }
    }
    num->value =!num->value;
    return *num;
}
Object& Array::operator<(Object& a){
    if(isOverriden(SMALLER))return *operation(SMALLER,{&a});
    Number* num = new Number(0);
    if(isArray(a)){
        Array& r = toArray(a);
        num->value = children.size()<r.children.size();
    }
    return *num;
}
Object& Array::operator<=(Object& a){
    if(isOverriden(SMALLERSAME))return *operation(SMALLERSAME,{&a});
    Number* num = new Number(0);
    if(isArray(a)){
        Array& r = toArray(a);
        num->value = children.size()<=r.children.size();
    }
    return *num;
}
Object& Array::operator>(Object& a){
    if(isOverriden(BIGGER))return *operation(BIGGER,{&a});
    Number* num = new Number(0);
    if(isArray(a)){
        Array& r = toArray(a);
        num->value = children.size()>r.children.size();
    }
    return *num;
}
Object& Array::operator>=(Object& a){
    if(isOverriden(BIGGERSAME))return *operation(BIGGERSAME,{&a});
    Number* num = new Number(0);
    if(isArray(a)){
        Array& r = toArray(a);
        num->value = children.size()>=r.children.size();
    }
    return *num;
}
Object& Array::operator[](Object& a){
    if(isOverriden(INDEX))return *operation(INDEX,{&a});
    if(isNumber(a)){
        Number& r = toNumber(a);
        if(children.size()>r.value)
            return *children[(int)r.value];
    }
    return *octroNull;
}
Object* Array::operation(Operation o,std::vector<Object*> p){
    auto s = &array_get(operatorOverride[o]);
    if(s!=octroNull){
        p.insert(p.begin(),this);
        return &(*s)(p);
    }
    return this;
}

bool Array::isOverriden(Operation o){
    auto s = &array_get(operatorOverride[o]);
    return s!=octroNull;
}

bool isArray(Object& a){
    return a.type == ARRAY;
}
Array& toArray(Object& a){
    return *(Array*)&a;
}
bool isArray(Object* a){
    return a->type==ARRAY;
}
Array* toArray(Object* a){
    return (Array*)a;
}



Object& Array::constructor(std::vector<Object*> s){
    if(isOverriden(CONSTRUCTOR))return *operation(CONSTRUCTOR,s);
    return Object::constructor(s);
}
void Array::destructor(){
    if(isOverriden(DESTRUCTOR))operation(DESTRUCTOR,{});
    Object::destructor();
}
Object& Array::deref(){
    if(isOverriden(DEREF))return *operation(DEREF,{});
    return Object::deref();
}
Object& Array::address(){
    if(isOverriden(ADDRESS))return *operation(ADDRESS,{});
    return Object::address();
}
Object& Array::operator*(Object&a){
    if(isOverriden(MULTI))return *operation(MULTI,{&a});
    return Object::operator*(a);
}
Object& Array::operator/(Object& a){
    if(isOverriden(DIV))return *operation(DIV,{&a});
    return Object::operator/(a);
}
Object& Array::operator%(Object& a){
    if(isOverriden(MOD))return *operation(MOD,{&a});
    return Object::operator%(a);
}
Object& Array::operator*=(Object& a){
    if(isOverriden(SETMULTI))return *operation(SETMULTI,{&a});
    return Object::operator*=(a);
}
Object& Array::operator/=(Object& a){
    if(isOverriden(SETDIV))return *operation(SETDIV,{&a});
    return Object::operator/=(a);
}
Object& Array::operator%=(Object& a){
    if(isOverriden(SETMOD))return *operation(SETMOD,{&a});
    return Object::operator%=(a);
}
Object& Array::operator&&(Object& a){
    if(isOverriden(AND))return *operation(AND,{&a});
    return Object::operator&&(a);
}
Object& Array::operator||(Object& a){
    if(isOverriden(OR))return *operation(OR,{&a});
    return Object::operator||(a);
}
Object& Array::operator!(){
    if(isOverriden(NOT))return *operation(NOT,{});
    return Object::operator!();
}
Object& Array::operator()(std::vector<Object*> s){
    if(isOverriden(EXEC))return *operation(EXEC,s);
    return Object::operator()(s);
}

void Array::setUsed(){
    used = true;
    for(auto& x:children)
        x->setUsed();
}
void Array::doOperation(void* v,Operation o,std::vector<Object*>p){
    if(isOverriden(o)){
        auto s = &array_get(operatorOverride[o]);
        if(s!=octroNull){
            s->operation(EXEC,p);
        }
    }else Object::doOperation(v,o,p);
}
