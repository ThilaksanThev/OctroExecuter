#pragma once
#include "Object.hpp"
#include <string>
#include <vector>
#include "Object.hpp"
#include <map>

#define OCTROVERSION 0

class Script
    :public Object
{
    bool unrunable = false;

    int octroversion = 0;
    
    int max_F = 4,
        max_B = 4,
        max_I = 4,
        max_S = 4,
        max_M = 4,
        max_X = 4;

    inline int& runPos();

    inline int convertF();
    inline int convertB();
    inline int convertI();
    inline int convertS();
    inline int convertM();
    inline int convertX();
    inline double convertD();
    
    inline std::string& convertString();

    std::vector<std::string> strings;
    std::vector<Script*> libraries;
    std::vector<int> librarySize;
    int libraryEndPoint = 0;
    std::string code = "";
    std::vector<int> runner;
    std::map<int,int> markerRegistry; //[marker]=codepos
    int postscriptPosition = 0;
    bool postscriptMode = false;
    std::vector<Object*> stack;

    //loading help functions
    int readInt(            std::string& code,size_t& i);
    std::string readString( std::string& code,size_t& i);

    //loading
    void loadVersion(       std::string& code,size_t& i);
    void loadStrings(       std::string& code,size_t& i);
    void loadLibraries(     std::string& code,size_t& i);
    void loadParameterSize( std::string& code,size_t& i);
    void loadMarkerRegistry();
    
    void run(int);
    void end(int);

    void error(std::string line);
    void info(std::string line);

    Object* front(unsigned int i);
    Object* back(unsigned int i);
    Object* last();
    std::vector<Object*> collectParameter(unsigned int);
    void operation(Operation){}//platzhalter

    void remove2();
public:
    std::string version = "";
    void _updateUsedMemory();
    Script();

    void loadFromMemory(std::string code,std::string name);
    void loadFromFile(std::string file);

    void tick();
    bool isTickable();

    Object& inscriptfunction(int markerID);     //Wenn der c++ nutzer eine octro funktion ausruft
    void inscriptfunction_intern(int markerID); //Wenn der Octro nutzer eine octro function ausruft
    void pushParameter_intern(std::vector<Object*>);

    void push(Object*);
    Object* requestObject(unsigned int i);
    void interScriptualTransmissionMode(bool,Script*);//true = slave mode,false = master mode 
    void interScriptualTransmission();
    bool interScriptualTransmission_readyForReturn(Script*);
    
};