#pragma once
#include "Script.hpp"
#include <vector>

class ScriptManager
{
private:
    std::vector<Script*> scripts; 
    void _push(Script*s);
    void _updateUsedMemory();
    Script* _search(std::string name,std::string version);
public:
    static void push(Script*);
    static void updateUsedMemory();
    static Script* search(std::string name,std::string version);
    static ScriptManager& get(){
        static ScriptManager scriptManager;
        return scriptManager;
    }
};

