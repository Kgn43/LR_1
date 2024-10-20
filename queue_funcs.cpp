#include "queue_funcs.h"


void printQueue(const request& request){
    ifstream file(request.file, ios::in); //откуда читаем
    string variableLine; //считываемая строка с файла
    if (request.query.size == 1){ //вывести все переменные
        fileData var;
        while (getline(file, variableLine)) { //проверяем все существующие переменные
            if (variableLine == " " || variableLine.empty()) continue;
            var.name = splitToArr(variableLine, ';')[0]; //определяем их имена
            var.data = splitToArr(variableLine, ';')[1]; //и то, что они хранят
            queue<string> currVar = splitToQueue(var.data); //определяем реальную переменную этого Типа данных
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
                queue<string> currVar = splitToQueue(var.data); //определяем реальную переменную этого Типа данных
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


void queuePush(const request& request){
//структура команды: push имяОчереди чтоЗаписать
    fstream file(request.file, ios::in);
    fstream tmpFile("tmp.data", ios::out);
    if(!tmpFile.is_open()) throw runtime_error( "Tmp file doesn't exist");
    if (request.query.size != 3) throw runtime_error("Wrong command syntax");
    string name = request.query[1]; //имя очереди
    string value = request.query[2]; //что записать
    string variableLine; //считываемая строка с файла
    fileData var;
    bool varIsExist = false;
    while (getline(file, variableLine)){ //проверяем все существующие переменные
        if (variableLine == " " || variableLine.empty()) continue;
        var.name = splitToArr(variableLine, ';')[0]; //определяем их имена
        var.data = splitToArr(variableLine, ';')[1]; //и то, что они хранят
        if (var.name == name){ //если такая переменная существует
            varIsExist = true; //закрываем защёлку
            queue<string> currVar = splitToQueue(var.data); //определяем реальную переменную этого Типа данных
            currVar.push(value);
            variableLine = var.name + ';' + unSplitQueue(currVar);//превращаем переменную в текст
            currVar.clear();
            tmpFile << variableLine << endl;
        }
        else {
            tmpFile << variableLine << endl;
        }
    }
    if (!varIsExist){
        cout << "making new queue" << endl;
        queue<string> newVar;//да, делаем это всегда.
        newVar.push(value);
        variableLine = name + ';' + unSplitQueue(newVar);//превращаем переменную в текст
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


void queuePop(const request& request){
//команда: pop имяОчереди
    fstream file(request.file, ios::in);
    fstream tmpFile("tmp.data", ios::out);
    if(!tmpFile.is_open()) throw runtime_error("Tmp file doesn't exist");
    if (request.query.size != 2) throw runtime_error("Wrong command syntax");
    string name = request.query[1]; //имя очереди
    string variableLine; //считываемая строка с файла
    fileData var;
    bool varIsExist = false;
    while (getline(file, variableLine)){ //проверяем все существующие переменные
        if (variableLine == " " || variableLine.empty()) continue;
        var.name = splitToArr(variableLine, ';')[0]; //определяем их имена
        var.data = splitToArr(variableLine, ';')[1]; //и то, что они хранят
        if (var.name == name){ //если такая переменная существует
            varIsExist = true; //закрываем защёлку
            queue<string> currVar = splitToQueue(var.data); //определяем реальную переменную этого Типа данных
            currVar.pop();
            variableLine = var.name + ';' + unSplitQueue(currVar);//превращаем переменную в текст
            currVar.clear();
            if (currVar.head == nullptr){
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
        cout << "Tis queue doesn't exist" << endl;
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


void queueGet(const request& request){
//структура команды: get имяОчереди
    fstream file(request.file, ios::in);
    if (request.query.size != 2) throw runtime_error("Wrong command syntax");
    string name = request.query[1]; //в какой очереди искать
    string variableLine; //считываемая строка с файла
    fileData var;
    bool varIsExist = false;
    while (getline(file, variableLine)){ //проверяем все существующие переменные
        if (variableLine == " " || variableLine.empty()) continue;
        var.name = splitToArr(variableLine, ';')[0]; //определяем их имена
        var.data = splitToArr(variableLine, ';')[1]; //и то, что они хранят
        if (var.name == name){ //если такая переменная существует
            varIsExist = true; //закрываем защёлку
            queue<string> currVar = splitToQueue(var.data); //определяем реальную переменную этого Типа данных
            cout << currVar.getFirst() << endl;
            currVar.clear();
        }
    }
    if (!varIsExist){
        cout << "This queue isn't exist" << endl;
    }
}