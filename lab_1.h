#ifndef LAB_1_H
#define LAB_1_H

#include "generalFuncs.h"
#include "arr_funcs.h"
#include "list_funcs.h"
#include "stack_funcs.h"
#include "queue_funcs.h"
#include "hashMap_funcs.h"
#include "singleConnList.h"

#include <fstream>
#include <iostream>


structures getType(const string& fName);


string delFirstLetter(const string &input);


void consolePrint(const request& request);

structures structRequest(const char& input);
commands commandRequest(const string& input);
request getRequest(int argc, char *argv[]);

#endif // LAB_1_H
