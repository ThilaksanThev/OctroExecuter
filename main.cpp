#include "ScriptManager.hpp"
#include "Function.hpp"
#include "String.hpp"
#include "Number.hpp"
#include "Array.hpp"
#include <iostream>

int main(){
    

    Script script;
    script.loadFromFile("test.bin");
    while(script.isTickable())
        script.tick();
}