#ifndef GENERAL_FUNCS_H
#define GENERAL_FUNCS_H


#include <iostream>
#include <fstream>
#include "arr.h"


enum commands{
    Get,
    push,
    pop,
    del,
    insert,
    set
};


enum structures{
    Array,
    List,
    Queue,
    stack,
    HashMap
};


struct request{
    arr<string> query;
    string file;
    bool isCallHelp = false; //проиграли бит, но выиграли больше на обработке запроса
};


struct fileData{
    string name;
    string data;
};


void callHelp();
bool isFileExist(const std::string& fileName);

#endif //GENERAL_FUNCS_H
