#include "arr_funcs.h"


void printArr(const request& request){
    ifstream file(request.file, ios::in); //откуда читаем
    string variableLine; //считываемая строка с файла
    if (request.query.size == 1){ //вывести все переменные
        fileData var;
        while (getline(file, variableLine)) { //проверяем все существующие переменные
            if (variableLine == " " || variableLine.empty()) continue;
            var.name = splitToArr(variableLine, ';')[0]; //определяем их имена
            var.data = splitToArr(variableLine, ';')[1]; //и то, что они хранят
            arr<string> currVar = splitToArr(var.data); //определяем реальную переменную этого Типа данных
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
                arr<string> currVar = splitToArr(var.data); //определяем реальную переменную этого Типа данных
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


void arrPush(const request& request){
//структура команды1 (по индексу): push имяМассива куда что
//структура команды2 (в конец): push имяМассива что
    fstream file(request.file, ios::in);
    fstream tmpFile("tmp.data", ios::out);
    if(!tmpFile.is_open()){
        throw runtime_error("Tmp file doesn't exist");
    }
    string name; //куда записать
    string value; //что записать
    int index;
    string variableLine; //считываемая строка с файла
    fileData var;
    if (request.query.size == 3) {
        name = request.query[1];
        index = -1;
        value = request.query[2];
    }
    else if (request.query.size == 4){
        name = request.query[1];
        index = stoi(request.query[2]);
        value = request.query[3];
    }
    else {
        stringstream serr;
        serr << "Wrong command syntax";
        throw runtime_error(serr.str());
    }
    bool varIsExist = false;
    while (getline(file, variableLine)){ //проверяем все существующие переменные
        if (variableLine == " " || variableLine.empty()) continue;
        var.name = splitToArr(variableLine, ';')[0]; //определяем их имена
        var.data = splitToArr(variableLine, ';')[1]; //и то, что они хранят
        if (var.name == name){ //если такая переменная существует
            varIsExist = true; //закрываем защёлку
            arr<string> currVar = splitToArr(var.data); //определяем реальную переменную этого Типа данных
            currVar.push_back(value); //закидываем то, что просят в конец
            if (currVar.size - 1 != index && index != -1){
                string tmp;//третий стакан
                for(size_t i = currVar.size - 1; i > index; --i){ //и меняем местами до нужного индекса
                    tmp = currVar.data[i];
                    currVar.data[i] = currVar.data[i - 1];
                    currVar.data[i - 1] = tmp;
                }
            }
            variableLine = var.name + ';' + unsplit(currVar);//превращаем переменную в текст
            tmpFile << variableLine << endl;
            //currVar.clear();
        }
        else {
            tmpFile << variableLine << endl;
        }
    }
    if (!varIsExist){
        cout << "making new array" << endl;
        if (index != 0 && index != -1){//попытка вставить на какой-либо индекс кроме нуля в несуществующую переменную. рука-лицо.
            throw runtime_error("Wrong index");
        }
        arr<string> newVar;//да, можно и не делать этого. но мы сделаем. потому, что можем.
        newVar.push_back(value);
        variableLine = name + ';' + unsplit(newVar);//превращаем переменную в текст
        tmpFile << variableLine;
        //newVar.clear();
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


void arrDel(const request& request){
//структура команды: del имяМассива индекс
    fstream file(request.file, ios::in);
    if(!file.is_open()){
        stringstream serr;
        serr << "This file doesn't exist";
        throw runtime_error(serr.str());
    }
    fstream tmpFile("tmp.data", ios::out);
    if(!tmpFile.is_open()){
        stringstream serr;
        serr << "This file doesn't exist";
        throw runtime_error(serr.str());
    }
    string name = request.query[1]; //из какого массива удалять
    size_t index = stoi(request.query[2]); //с какой позиции
    string variableLine; //считываемая строка с файла
    fileData var;
    bool varIsExist = false;
    while (getline(file, variableLine)){ //проверяем все существующие переменные
        if (variableLine == " " || variableLine.empty()) continue;
        var.name = splitToArr(variableLine, ';')[0]; //определяем их имена
        var.data = splitToArr(variableLine, ';')[1]; //и то, что они хранят
        if (var.name == name){ //если такая переменная существует
            varIsExist = true; //закрываем защёлку
            arr<string> currVar = splitToArr(var.data); //определяем реальную переменную этого Типа данных
            currVar.del(index);//удаление
            variableLine = var.name + ';' + unsplit(currVar);//превращаем переменную в текст
            if (currVar.size == 0) variableLine = "";
            //currVar.clear();
            tmpFile << variableLine << endl;
        }
        else {
            tmpFile << variableLine << endl;
        }
    }
    file.close();
    tmpFile.close();
    if (!varIsExist){
        cout << "This array isn't exist" << endl;
    }
    else{
        file.open(request.file, ios::out);
        tmpFile.open("tmp.data", ios::in);
        while (getline(tmpFile, variableLine)){
            file << variableLine << endl;
        }
        file.close();
        tmpFile.close();
    }
}


void arrGet(const request& request){
//структура команды: get имяМассива индекс
    fstream file(request.file, ios::in);
    if(!file.is_open()){
        stringstream serr;
        serr << "This file doesn't exist";
        throw runtime_error(serr.str());
    }
    string name = request.query[1]; //из какого массива считать
    size_t index = stoi(request.query[2]); //с какой позиции
    string variableLine; //считываемая строка с файла
    fileData var;
    bool varIsExist = false;
    while (getline(file, variableLine)){ //проверяем все существующие переменные
        if (variableLine == " " || variableLine.empty()) continue;
        var.name = splitToArr(variableLine, ';')[0]; //определяем их имена
        var.data = splitToArr(variableLine, ';')[1]; //и то, что они хранят
        if (var.name == name){ //если такая переменная существует
            varIsExist = true; //закрываем защёлку
            arr<string> currVar = splitToArr(var.data); //определяем реальную переменную этого Типа данных
            if (index < currVar.size) cout << currVar[index] << endl;
            else cout << "Index out of range" << endl;
            //currVar.clear();
        }
    }
    if (!varIsExist){
        cout << "This array isn't exist" << endl;
    }
}
