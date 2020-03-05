#include "InternalFunction.hpp"

InternalFunction::InternalFunction(Script* s,int i){
    script = s;
    marker = i;
}

Object* InternalFunction::clone(){
    return new InternalFunction(script,marker);
}
Object& InternalFunction::operator()(std::vector<Object*> a){
    script->pushParameter_intern(a);
    return script->inscriptfunction(marker);
}
Object& InternalFunction::operator=(int i){
    marker = i;
    return *this;
}

void InternalFunction::doOperation(void*v,Operation o,std::vector<Object*>p){
    Script* s = (Script*)v;
    if(o==EXEC){
        if(s!=script){
            //returnskript ist das hier
            script->interScriptualTransmissionMode(true,s);//das ist der slave
            s->interScriptualTransmissionMode(false,script);//das ist der master

        }
        
        script->pushParameter_intern(p);
        script->inscriptfunction_intern(marker);
    }else Object::doOperation(v,o,p);
}