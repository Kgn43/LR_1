#include "list_funcs.h"


void printList(const request& request){
    ifstream file(request.file, ios::in); //откуда читаем
    string variableLine; //считываемая строка с файла
    if (request.query.size == 1){ //вывести все переменные
        fileData var;
        while (getline(file, variableLine)) { //проверяем все существующие переменные
            if (variableLine == " " || variableLine.empty()) continue;
            var.name = splitToArr(variableLine, ';')[0]; //определяем их имена
            var.data = splitToArr(variableLine, ';')[1]; //и то, что они хранят
            list<string> currVar = splitToList(var.data); //определяем реальную переменную этого Типа данных
            cout << var.name << " = " << currVar << endl;
        }
    }
    else if (request.query.size == 2) { //вывести одну переменную
        string name = request.query[1]; //имя искомой переменной
        fileData var;
        bool varIsExist = false;
        while (getline(file, variableLine)){ //проверяем все существующие переменные
            if (variableLine == " " || variableLine.empty()) continue;
            var.name = splitToArr(variableLine, ';')[0]; //определяем их имена
            var.data = splitToArr(variableLine, ';')[1]; //и то, что они хранят
            if (var.name == name){ //если такая переменная существует
                varIsExist = true; //закрываем защёлку
                list<string> currVar = splitToList(var.data); //определяем реальную переменную этого Типа данных
                cout << var.name << " = " << currVar << endl;
            }
        }
        if (!varIsExist){
            cout << "Wrong variable name" << endl;
        }
    }
    else {
        cout << "Wrong syntax" << endl;
    }
    file.close();
}


void listPush(const request& request){
//структура команды: push имяСписка кудаЗаписать чтоЗаписать
    fstream file(request.file, ios::in);
    fstream tmpFile("tmp.data", ios::out);
    if(!tmpFile.is_open()) throw runtime_error("Tmp file doesn't exist");
    if (request.query.size != 4) {
        stringstream serr;
        serr << "Wrong command syntax";
        throw runtime_error(serr.str());
    }
    string name = request.query[1]; //имя списка
    string place = request.query[2]; // начало/конец
    if (place != "begin" && place != "end"){
        stringstream serr;
        serr << "Wrong insert place";
        throw runtime_error(serr.str());
    }
    string value = request.query[3]; //что записать
    string variableLine; //считываемая строка с файла
    fileData var;
    bool varIsExist = false;
    while (getline(file, variableLine)){ //проверяем все существующие переменные
        if (variableLine == " " || variableLine.empty()) continue;
        var.name = splitToArr(variableLine, ';')[0]; //определяем их имена
        var.data = splitToArr(variableLine, ';')[1]; //и то, что они хранят
        if (var.name == name){ //если такая переменная существует
            varIsExist = true; //закрываем защёлку
            list<string> currVar = splitToList(var.data); //определяем реальную переменную этого Типа данных
            if (place == "begin"){
                currVar.headInsert(value); //закидываем то, что просят в начало
            }
            else {
                currVar.backInsert(value);
            }
            variableLine = var.name + ';' + unSplitList(currVar);//превращаем переменную в текст
            //currVar.clear();
            tmpFile << variableLine << endl;
        }
        else {
            tmpFile << variableLine << endl;
        }
    }
    if (!varIsExist){
        cout << "making new list" << endl;
        list<string> newVar;//да, делаем это всегда.
        newVar.headInsert(value);
        variableLine = name + ';' + unSplitList(newVar);//превращаем переменную в текст
        tmpFile << variableLine;
    }
    file.close();
    tmpFile.close();
    file.open(request.file, ios::out);
    tmpFile.open("tmp.data", ios::in);
    while (getline(tmpFile, variableLine)){
        file << variableLine << endl;
    }
    file.close();
    tmpFile.close();
}


void listDel(const request& request){
//команда: pop имяСписка откуда/поКакомуЗначению
    fstream file(request.file, ios::in);
    fstream tmpFile("tmp.data", ios::out);
    if(!tmpFile.is_open()) throw runtime_error("Tmp file doesn't exist");
    if (request.query.size != 3) {
        stringstream serr;
        serr << "Wrong command syntax";
        throw runtime_error(serr.str());
    }
    string name = request.query[1];
    string wh = request.query[2]; //what/where
    string variableLine; //считываемая строка с файла
    fileData var;
    bool varIsExist = false;
    while (getline(file, variableLine)){ //проверяем все существующие переменные
        if (variableLine == " " || variableLine.empty()) continue;
        var.name = splitToArr(variableLine, ';')[0]; //определяем их имена
        var.data = splitToArr(variableLine, ';')[1]; //и то, что они хранят
        if (var.name == name){ //если такая переменная существует
            varIsExist = true; //закрываем защёлку
            list<string> currVar = splitToList(var.data); //определяем реальную переменную этого Типа данных
            if (wh == "begin") {
                currVar.delFirst();
            }
            else if (wh == "end"){
                currVar.delLast();
            }
            else {
                currVar.delByVal(wh);
            }
            variableLine = var.name + ';' + unSplitList(currVar);//превращаем переменную в текст
            //currVar.clear();
            if (currVar.first != nullptr){
                tmpFile << variableLine << endl;
            }
        }
        else {
            tmpFile << variableLine << endl;
        }
    }
    file.close();
    tmpFile.close();
    if (!varIsExist){
        cout << "Tis list doesn't exist" << endl;
    } else {
        file.open(request.file, ios::out);
        tmpFile.open("tmp.data", ios::in);
        while (getline(tmpFile, variableLine)){
            file << variableLine << endl;
        }
        file.close();
        tmpFile.close();
    }
}


void listGet(const request& request){
//структура команды: get имяСписка искомоеЗначение
    fstream file(request.file, ios::in);
    if(!file.is_open()){
        stringstream serr;
        serr << "This file doesn't exist";
        throw runtime_error(serr.str());
    }
    if (request.query.size != 3) {
        stringstream serr;
        serr << "Wrong command syntax";
        throw runtime_error(serr.str());
    }
    string name = request.query[1]; //в каком списке искать
    string value = request.query[2]; //что ищем
    string variableLine; //считываемая строка с файла
    fileData var;
    bool varIsExist = false;
    while (getline(file, variableLine)){ //проверяем все существующие переменные
        if (variableLine == " " || variableLine.empty()) continue;
        var.name = splitToArr(variableLine, ';')[0]; //определяем их имена
        var.data = splitToArr(variableLine, ';')[1]; //и то, что они хранят
        if (var.name == name){ //если такая переменная существует
            varIsExist = true; //закрываем защёлку
            list<string> currVar = splitToList(var.data); //определяем реальную переменную этого Типа данных
            if (currVar.find(value)){
                cout << "value " << value << " is in the list " << name << endl;
            }
            else {
                cout << "value " << value << " isn't in the list " << name << endl;
            }
            //currVar.clear();
        }
    }
    if (!varIsExist){
        cout << "This list isn't exist" << endl;
    }
}