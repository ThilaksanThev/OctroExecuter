#include "MemoryManager.hpp"
#include "ScriptManager.hpp"
void MemoryManager::push(Object* o){
    get()._push(o);
}
void MemoryManager::clear(){
    get()._clear();
}
void MemoryManager::_clear(){
    for (auto& x:memory)
    {
        x->used = false;
    }
    ScriptManager::updateUsedMemory();
    for (size_t i = 0; i < memory.size(); i++)
    {
        if(!memory[i]->used){
            delete memory[i];
            memory.erase(memory.begin()+i);
            i--;
        }
    }

    
}
void MemoryManager::_push(Object* o){
    memory.push_back(o);
}