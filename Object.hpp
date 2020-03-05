#pragma once
#include <vector>
#include <string>
enum Operation{
    ADD,SUB,MULTI,DIV,MOD,
    SETADD,SETSUB,SETMULTI,SETDIV,SETMOD,
    SET,EQUALS,UNEQUALS,SMALLER,SMALLERSAME,
    BIGGER,BIGGERSAME,AND,OR,NOT,
    DEREF,ADDRESS,INDEX,
    EXEC,CONSTRUCTOR,DESTRUCTOR

};
extern std::string operatorOverride[];
/*
    condition
*/
enum Type{
    NUMBER,STRING,ARRAY,POINTER,FUNCTION,INTERNALFUNCTION,SCRIPT,VOID
};
class Object
{
private:
    /* data */
public:
    bool used = false;
    virtual void setUsed();

    Type type = VOID;
    std::string name;
    Object* rename(std::string);
    
    /*
        The Script only tries to do operations by doOperation
        the "doOperation" most likely leads to a stack.push of a "operator" methode

        if the "operator" is not overriden is will lead to the "operation" methode 
    */
    virtual void doOperation(void*,Operation,std::vector<Object*>p);

    Object();

    virtual Object* clone();
    virtual Object* operation(Operation,std::vector<Object*>);

    
    //the operators only for primitives
    virtual Object& operator=(int);
    virtual Object& operator=(double);
    virtual Object& operator=(std::string);
    virtual Object& operator[](int);
    virtual Object& array_insert(int,Object*);
    virtual Object& array_get(std::string);
    virtual void array_remove(int);
    virtual void collect(std::vector<Object*>&);
    virtual std::vector<Object*> anticollect();
    virtual bool condition();
    
    //the operators
    virtual Object& constructor(std::vector<Object*>);
    virtual void destructor();
    virtual Object& deref();
    virtual Object& address();
    virtual Object& operator+(Object&);
    virtual Object& operator-(Object&);
    virtual Object& operator*(Object&);
    virtual Object& operator/(Object&);
    virtual Object& operator%(Object&);
    virtual Object& operator+=(Object&);
    virtual Object& operator-=(Object&);
    virtual Object& operator*=(Object&);
    virtual Object& operator/=(Object&);
    virtual Object& operator%=(Object&);
    virtual Object& operator=(Object&);
    virtual Object& operator==(Object&);
    virtual Object& operator!=(Object&);
    virtual Object& operator<(Object&);
    virtual Object& operator<=(Object&);
    virtual Object& operator>(Object&);
    virtual Object& operator>=(Object&);
    virtual Object& operator&&(Object&);
    virtual Object& operator||(Object&);
    virtual Object& operator!();
    virtual Object& operator[](Object&);
    virtual Object& operator()(std::vector<Object*>);
};

extern Object* octroNull;