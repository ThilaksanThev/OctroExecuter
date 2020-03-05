#pragma once
#include <vector>
#include "Object.hpp"
class MemoryManager
{
    std::vector<Object*> memory;
    void _push(Object*);
    void _clear();
public:
    MemoryManager(/* args */) {}
    ~MemoryManager() {}

    static void clear();
    static void push(Object*);
    static MemoryManager& get(){
        static MemoryManager memoryManager;
        return memoryManager;
    }
    
};