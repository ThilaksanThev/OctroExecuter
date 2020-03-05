#include "Object.hpp"
#include "Number.hpp"
#include "Pointer.hpp"
#include "MemoryManager.hpp"
#include "Script.hpp"

std::string operatorOverride[] = {
    "operatorADD","operatorSUB","operatorMULTI","operatorDIV","operatorMOD",
    "operatorSETADD","operatorSETSUB","operatorSETMULTI","operatorSETDIV","operatorSETMOD",
    "operatorSET","operatorEQUALS","operatorUNEQUALS","operatorSMALLER","operatorSMALLERSAME",
    "operatorBIGGER","operatorBIGGERSAME","operatorAND","operatorOR","operatorNOT",
    "operatorDEREF","operatorADDRESS","operatorINDEX",
    "operatorEXEC","constructor","destructor",
};

Object* octroNull = new Object();

Object::Object(){
    MemoryManager::push(this);
}
void Object::doOperation(void*v,Operation o,std::vector<Object*>p){
    Script* script = (Script*)v;
        switch (o)
        {
        case ADD:
        script->push(&this->operator+(*p[0]));
        break;
        case SUB:
        script->push(&this->operator-(*p[0]));
        break;
        case MULTI:
        script->push(&this->operator*(*p[0]));
        break;
        case DIV:
        script->push(&this->operator/(*p[0]));
        break;
        case MOD:
        script->push(&this->operator%(*p[0]));
        break;
        case SETADD:
        script->push(&this->operator+=(*p[0]));
        break;
        case SETSUB:
        script->push(&this->operator-=(*p[0]));
        break;
        case SETMULTI:
        script->push(&this->operator*=(*p[0]));
        break;
        case SETDIV:
        script->push(&this->operator/=(*p[0]));
        break;
        case SETMOD:
        script->push(&this->operator%=(*p[0]));
        break;
        case SET:
        script->push(&this->operator=(*p[0]));
        break;
        case EQUALS:
        script->push(&this->operator==(*p[0]));
        break;
        case UNEQUALS:
        script->push(&this->operator!=(*p[0]));
        break;
        case SMALLER:
        script->push(&this->operator<(*p[0]));
        break;
        case SMALLERSAME:
        script->push(&this->operator<=(*p[0]));
        break;
        case BIGGER:
        script->push(&this->operator>(*p[0]));
        break;
        case BIGGERSAME:
        script->push(&this->operator>=(*p[0]));
        break;
        case AND:
        script->push(&this->operator&&(*p[0]));
        break;
        case OR:
        script->push(&this->operator||(*p[0]));
        break;
        case NOT:
        script->push(&this->operator!());
        break;
        case DEREF:
        script->push(&this->deref());
        break;
        case ADDRESS:
        script->push(&this->address());
        break;
        case INDEX:
        script->push(&this->operator[](*p[0]));
        break;
        case EXEC:
        script->push(&this->operator()(p));
        break;
        case CONSTRUCTOR:
        script->push(&this->constructor(p));
        break;
        case DESTRUCTOR:
        this->destructor();
        break;
        default:
            break;
        }
    
}

Object* Object::clone(){
    return this;
}
Object* Object::operation(Operation,std::vector<Object*>){
    return this;
}
Object& Object::operator=(int){
    return *this;
}
Object& Object::operator=(double){
    return *this;
}
Object& Object::operator=(std::string){
    return *this;
}
Object& Object::operator[](int){
    return *this;
}
Object& Object::array_insert(int,Object*){
    return *this;
}
Object& Object::array_get(std::string){
    return *this;
}
void Object::array_remove(int){
}
void Object::collect(std::vector<Object*>&){
}
std::vector<Object*> Object::anticollect(){
    return {};
}
bool Object::condition(){
    return false;
}



Object& Object::operator+(Object&a){
    return *this->operation(ADD,{&a});
}
Object& Object::operator-(Object& a){
    return *this->operation(SUB,{&a});
}
Object& Object::operator*(Object& a){
    return *this->operation(MULTI,{&a});
}
Object& Object::operator/(Object& a){
    return *this->operation(DIV,{&a});
}
Object& Object::operator%(Object& a){
    return *this->operation(MOD,{&a});
}
Object& Object::operator+=(Object&a){
    return *this->operation(SETADD,{&a});
}
Object& Object::operator-=(Object&a){
    return *this->operation(SETSUB,{&a});
}
Object& Object::operator*=(Object& a){
    return *this->operation(SETMULTI,{&a});
}
Object& Object::operator/=(Object& a){
    return *this->operation(SETDIV,{&a});
}
Object& Object::operator%=(Object& a){
    return *this->operation(SETMOD,{&a});
}
Object& Object::operator=(Object& a){
    return *this->operation(SET,{&a});
}
Object& Object::operator==(Object& a){
    return *this->operation(EQUALS,{&a});
}
Object& Object::operator!=(Object& a){
    return *this->operation(UNEQUALS,{&a});
}
Object& Object::operator<(Object& a){
    return *this->operation(SMALLER,{&a});
}
Object& Object::operator<=(Object& a){
    return *this->operation(SMALLERSAME,{&a});
}
Object& Object::operator>(Object& a){
    return *this->operation(BIGGER,{&a});
}
Object& Object::operator>=(Object& a){
    return *this->operation(BIGGERSAME,{&a});
}
Object& Object::operator&&(Object& a){
    return *new Number(condition()&&a.condition());
}
Object& Object::operator||(Object& a){
    return *new Number(condition()||a.condition());
}
Object& Object::operator!(){
    return *this->operation(NOT,{});
}
Object& Object::operator[](Object& a){
    return *this->operation(INDEX,{&a});
}
Object& Object::operator()(std::vector<Object*> a){
    return *this->operation(EXEC,a);
}
Object& Object::deref(){
    return *this->operation(DEREF,{});
}
Object& Object::address(){
    return *new Pointer(this);
}
Object& Object::constructor(std::vector<Object*> a){
    return *this->operation(CONSTRUCTOR,a);
}
void Object::destructor(){
    this->operation(DESTRUCTOR,{});
}
Object* Object::rename(std::string name){
    this->name = name;
    return this;
}

void Object::setUsed(){
    used = true;
}
