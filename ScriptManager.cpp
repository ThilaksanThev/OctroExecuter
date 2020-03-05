#include "ScriptManager.hpp"
#include <iostream>

void ScriptManager::push(Script* s){
    get()._push(s);
}
void ScriptManager::updateUsedMemory(){
    get()._updateUsedMemory();
}
Script* ScriptManager::search(std::string name,std::string version){
    return ScriptManager::get()._search(name,version);
}

void ScriptManager::_push(Script*s){
    scripts.push_back(s);
}

void ScriptManager::_updateUsedMemory(){
    for(auto& x : scripts)
        x->_updateUsedMemory();
}
Script* ScriptManager::_search(std::string name,std::string version){
    for(auto& x:scripts){
        if(x->name == name){
            if(x->version==version)
                return x;
            else {
                std::cout << "<!>[Octro]\""<<name<<"\" has to be \""<<version<<"\" but is \""<<x->version<<"\""<<std::endl;
                return nullptr;
            }
        }
    }
    std::cout << "<!>[Octro]Library needed:\""<<name<<"\": \""<<version<<"\""<<std::endl;
    return nullptr;
}
