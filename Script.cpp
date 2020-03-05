#include "Script.hpp"
#include <fstream>
#include <iostream>
#include "Number.hpp"
#include "String.hpp"
#include "Array.hpp"
#include "Function.hpp"
#include "Pointer.hpp"
#include "ScriptManager.hpp"
#include "InternalFunction.hpp"

std::string outOfIndex = "[String is out of index]";
static std::string parameterTypes[] ={
    "fb","fbs","bb","bbs",
    "f","fs","b","bs",
    "i","d","s","m",
    "f","b",
    "","b",
    "b","",
    "x","x","xs","s",
    "fb","bb",
    "sb",
    "m","mm","m",
    "","","","","",
    "","","","","",
    "","","","","",
    "","","","","",
    "","",""
};

Script::Script(){
    ScriptManager::get().push(this);
    stack.push_back(new Number);
    stack.push_back(new String);
    stack.push_back(new Array);
    stack.push_back(new Pointer);
    stack.push_back(new InternalFunction(this,0));
    stack.push_back(this);
    stack.push_back(octroNull);
    stack.push_back(new Function);


}

int& Script::runPos(){
    static int dummyInt = 0;
    return (runner.size())?runner[runner.size()-1]:dummyInt;
}

#define convertFunction(letter) int Script::convert##letter(){\
    static union CharToInt\
    {\
        char c[4];\
        int i;\
    }cti;\
    for (size_t i = 0; i<4; i++){\
        cti.c[i]= (i<max_##letter&&runPos()+i<code.length())?code[runPos()+i]:0;\
    }\
    runPos()+=max_##letter;\
    return cti.i;\
}

convertFunction(F);
convertFunction(B);
convertFunction(I);
convertFunction(S);
convertFunction(M);
convertFunction(X);

double Script::convertD(){
    union CharToDouble
    {
        char c[8];
        double d;
    }cti;
    for (size_t i = 0; i<8; i++){
        cti.c[i]= (runPos()+i<code.length())?code[runPos()+i]:0;
    }
    runPos()+=8;
    return cti.d;
}

std::string& Script::convertString(){
    auto s=  convertS();
    if(s>=strings.size()){
        error("String: Out of index");
        return outOfIndex;
    }
    return strings[s];
}
int Script::readInt(std::string& code,size_t& i){
    static union CharToInt
    {
        char c[4];
        int i;
    }cti;

    for (size_t e = 0; e < 4; e++)
    {
        cti.c[e] = (i<code.length())?code[i]:0;
        i++;
    }
    return cti.i;
}
std::string Script::readString(std::string& code,size_t& i){
    int t = readInt(code,i);
    std::string rv;
    rv.reserve(t);
    for (int e=0; e < t&&i<code.length(); e++)
    {
        rv+=code[i];
        i++;
    }
    return rv;
}

void Script::loadFromMemory(std::string code,std::string name){
    this->name = name;
    size_t i = 0;
    loadVersion(code,i);
    loadStrings(code,i);
    loadLibraries(code,i);
    loadParameterSize(code,i);
    this->code = code.length()>i?code.substr(i):"";
    postscriptPosition = this->code.length();
    loadMarkerRegistry();
    run(0);
}
void Script::loadFromFile(std::string path){
    std::string code;
    std::ifstream file (path,std::ios::in|std::ios::ate);
    if (file) {
        std::streampos filesize = file.tellg();
        code.reserve(filesize);
        file.seekg(0);
        while (!file.eof())
        {
            code += file.get();
        }   
    }
    loadFromMemory(code.substr(0,code.length()-1),path);
}

void Script::loadVersion(       std::string& code,size_t& i){
    octroversion = readInt(code,i);
    if(OCTROVERSION<octroversion)return error("This script uses a newer version of Octro");
    if(OCTROVERSION>octroversion)return error("This script uses an older version of Octro");
    info("Script Version: "+(version = readString(code,i)));
}
void Script::loadStrings(       std::string& code,size_t& i){
    int amount = readInt(code,i);
    strings.reserve(amount);
    for (size_t e = 0; e < amount; e++)
        strings.push_back(readString(code,i));
}
void Script::loadLibraries(     std::string& code,size_t& i){
    int amount = readInt(code,i);
    for (size_t e = 0; e < amount; e++)
    {
        auto name = readString(code,i);//name
        auto version = readString(code,i);//version
        auto size = readInt(code,i);//size
        auto x = ScriptManager().search(name,version);
        if(x==nullptr)
        {
            unrunable = true;
            return;
        }
        else {libraries.push_back(x);librarySize.push_back(size);libraryEndPoint+=size;}
    }
    //To-DO
}
void Script::loadParameterSize( std::string& code,size_t& i){
    max_F = readInt(code,i);
    max_B = readInt(code,i);
    max_I = readInt(code,i);
    max_S = readInt(code,i);
    max_M = readInt(code,i);
    max_X = readInt(code,i);
}

void Script::loadMarkerRegistry(){
    std::vector<int> tmpMarkerRegistry;
    std::vector<int> usedMarker;
    for (int i = 0; i < code.length();)
    {
        int type = code[i];
        if(type<0||type>=49){
            return error("Unknown command: ID:"+std::to_string(type));
        }
        info(" CMD: "+std::to_string(type));
        tmpMarkerRegistry.push_back(i);
        i++;
        auto& params = parameterTypes[type];
        for (size_t e = 0; e < params.size(); e++)
            switch (params[e])
            {
            case 'f':i+=max_F;
                break;
            case 'b':i+=max_B;
                break;
            case 'i':i+=max_I;
                break;
            case 's':i+=max_S;
                break;
            case 'm':
            {
                union CharToInt
                {
                    char c[4];
                    int i;
                }cti;
                for (size_t a = 0; a < 4; a++)
                {
                    cti.c[a]=code.length()>i&&a<max_M?code[i]:0;
                    if(a<max_M)
                        i++;
                }
                usedMarker.push_back(cti.i);
            }
                break;
            case 'x':i+=max_X;
                break;
            case 'd':i+=8;
                break;
            default:
                break;
            }
    }
    for (auto& x :usedMarker)
        markerRegistry[x] = tmpMarkerRegistry[x];
}
void Script::run(int i){
    if(i>=code.length())
        return;
    postscriptMode = i>=postscriptPosition;
    runner.push_back(i);
}
void Script::end(int i){
    while(runner.size()&&i){runner.pop_back();i--;}
    postscriptMode = runPos()>=postscriptPosition;
}
void Script::error(std::string line){
    std::cout << "<!>[OCTRO]"<<line<<std::endl;
}
void Script::info(std::string line){
    std::cout << "[OCTRO]"<<line<<std::endl;
}

bool Script::isTickable(){
    return runner.size();
}
void Script::tick(){
    if(runPos()<0)
        interScriptualTransmission();
    if(runPos()>=code.length())
        return end(1);
    char type = code[runPos()];
    runPos()++;
    switch (type)
    {
    case 0: //con
    {
        front(convertF())->clone()->doOperation(this,CONSTRUCTOR,collectParameter(convertB()));    
    }
    break;
    case 1:
    {
        front(convertF())->clone()->rename(convertString())->doOperation(this,CONSTRUCTOR,collectParameter(convertB()));    
    }
    break;
    case 2:
        back(convertB())->clone()->doOperation(this,CONSTRUCTOR,collectParameter(convertB()));    
        break;
    case 3:{
        back(convertB())->clone()->rename(convertString())->doOperation(this,CONSTRUCTOR,collectParameter(convertB()));
    }
    break;
    case 4:
        stack.push_back(front(convertF())->clone());
        break;
    case 5:
        stack.push_back(front(convertF())->clone()->rename(convertString()));
        break;
    case 6:
        stack.push_back(back(convertB())->clone());
        break;
    case 7:
        stack.push_back(back(convertB())->clone()->rename(convertString()));
        break;
    case 8:
        *last() = convertI();
        break;
    case 9:
        *last() = convertD();
        break;
    case 10:
        *last() = convertString();
        break;
    case 11:
        *last() = markerRegistry[convertM()];
        break;
    case 12:
        stack.push_back(front(convertF()));
        break;
    case 13:
        stack.push_back(back(convertB()));
        break;
    case 14:
        end(convertI());
        break;
    case 15:
        {
            int size = convertB();
            while(size--)
                stack.pop_back();
        }
        break;
    case 16:
        {
            auto s = collectParameter(convertB());
            last()->collect(s);
        }
        break;
    case 17:
        {
            auto s = last()->anticollect();
            for(auto x:s)
                stack.push_back(x);
        }
        break;
    case 18:
        {
            back(1)->array_insert(convertX(),back(0));
            stack.pop_back();
        }
        break;
    case 19:
        last()->array_remove(convertX());
        break;
    case 20:
        last()[convertX()].rename(convertString());
        break;
    case 21:
        last()->array_get(convertString());
        break; 
    case 22:
        front(convertF())->doOperation(this,EXEC,collectParameter(convertB()));
        break;
    case 23:
        back(convertB())->doOperation(this,EXEC,collectParameter(convertB()));
        break;
    case 24:
        last()->doOperation(this,EXEC,collectParameter(convertB()));
        break;
    case 25:
        {
            auto a = convertM();
            if((*last()).condition())
                run(markerRegistry[a]);
            stack.pop_back();
        }
        break;
    case 26:
        {
            auto a = convertM();
            auto b = convertM();
            if((*last()).condition())
                run(markerRegistry[a]);
            else run(markerRegistry[b]);
            stack.pop_back();
        }
        break;
    case 27:
        {
            auto start = runPos()-1;
            auto a = convertM();
            runPos() = start;
            if((*last()).condition())
                run(markerRegistry[a]);
            stack.pop_back();
        }
        break;
    default:
        break;
    }
    if((28<=type&&46>=type)||type==50){
        auto x = back(1);
        auto y = back(0);
        remove2();
        x->doOperation(this,Operation(type-28),{y});
    }
    if(47<=type&&49>=type){
        auto x = last();
        stack.pop_back();
        x->doOperation(this,Operation(type-28),{});
    }
}

Object* Script::front(unsigned int i){
    if(i<0)
        return octroNull;
    if(i<7)
        return stack[i];
    if(i<7+libraryEndPoint){
        int pos = i-7;
        size_t currentpos = 0;
        for (size_t e = 0; e < librarySize.size(); e++)
        {
            currentpos += librarySize[e];
            if(currentpos>pos){
                return libraries[e]->requestObject(pos-(currentpos-librarySize[e]));
            }
        }
        return octroNull;
    }
    return i-libraryEndPoint<stack.size()?stack[i-libraryEndPoint]:octroNull;
}
Object* Script::back(unsigned int i){
    return i<stack.size()?stack[stack.size()-i-1]:octroNull;
}
Object* Script::last(){
    return stack.size()?stack[stack.size()-1]:octroNull;
}
std::vector<Object*> Script::collectParameter(unsigned int e){
    int start = stack.size()>e?stack.size()-e:0;
    std::vector<Object*> rv;
    for (size_t i = start; i < stack.size(); i++)
    {
        rv.push_back(stack[i]);
    }
    stack.resize(start);
    return rv;
}
void Script::remove2(){
    stack.pop_back();
    stack.pop_back();
}

void Script::_updateUsedMemory(){
    for(auto& x:stack)
        x->setUsed();
}
Object& Script::inscriptfunction(int markerID){
    size_t count = runner.size();
    run(markerRegistry[markerID]);
    while(count<=runner.size()){
        tick();
    }
    auto rv = last();
    stack.pop_back();
    return *rv;
}
void Script::inscriptfunction_intern(int markerID){
    run(markerRegistry[markerID]);
}
void Script::pushParameter_intern(std::vector<Object*>a){
    for(auto&x:a)
        stack.push_back(x);
}

void Script::push(Object* o){
    stack.push_back(o);
}

Object* Script::requestObject(unsigned int i){
    return stack[7+i];
}
void Script::interScriptualTransmissionMode(bool b,Script* s)//true = slave mode,false = master mode
{
    push(s);
    if(b){
        runner.push_back(-2);//slave mode
    }else {
        runner.push_back(-1);//master mode
    }
};
 
void Script::interScriptualTransmission(){
    if(runPos()==-1){
        return;
    }else if(runPos()==-2){
        Script* s = (Script*)back(1);
        if(!s->interScriptualTransmission_readyForReturn(this))
            return;
        runner.pop_back();
        s->push(last());
        stack.pop_back();
        stack.pop_back();
    }
}
bool Script::interScriptualTransmission_readyForReturn(Script*s){
    if(runPos()==-1)
        if(last()==s)
            return true;
    return false;
}
