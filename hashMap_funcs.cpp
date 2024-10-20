#include "hashMap_funcs.h"


void printHashMap(const request &request) {
    ifstream file(request.file, ios::in); //откуда читаем
    string variableLine; //считываемая строка с файла
    if (request.query.size == 1){ //вывести все переменные
        fileData var;
        while (getline(file, variableLine)) { //проверяем все существующие переменные
            if (variableLine == " " || variableLine.empty()) continue;
            var.name = splitToArr(variableLine, ';')[0]; //определяем их имена
            var.data = splitToArr(variableLine, ';')[1]; //и то, что они хранят
            //определяем реальную переменную этого Типа данных
            hashMap currVar = hMFromStr(var.data);
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
                hashMap currVar = hMFromStr(var.data); //определяем реальную переменную этого Типа данных
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


void hashSetInsert(const request& request){
//структура команды: insert имяТаблицы ключ значение
    fstream file(request.file, ios::in);
    fstream tmpFile("tmp.data", ios::out);
    if(!tmpFile.is_open()) throw runtime_error("Tmp file doesn't exist");
    if (request.query.size != 4) throw runtime_error("Wrong command syntax");
    string name = request.query[1];
    string key = request.query[2]; //ключ
    string value = request.query[3]; //значение
    string variableLine; //считываемая строка с файла
    fileData var;
    bool varIsExist = false;
    while (getline(file, variableLine)){ //проверяем все существующие переменные
        if (variableLine == " " || variableLine.empty()) continue;
        var.name = splitToArr(variableLine, ';')[0]; //определяем их имена
        var.data = splitToArr(variableLine, ';')[1]; //и то, что они хранят
        if (var.name == name){ //если такая переменная существует
            varIsExist = true; //закрываем защёлку
            hashMap currVar = hMFromStr(var.data); //определяем реальную переменную этого Типа данных
            currVar.insert(key, value); //закидываем то, что просят
            variableLine = var.name + ';' + strFromHM(currVar);//превращаем переменную в текст
            tmpFile << variableLine << endl;
        }
        else {
            tmpFile << variableLine << endl;
        }
    }
    if (!varIsExist){
        cout << "making new HashMap" << endl;
        hashMap newVar;//да, делаем это всегда.
        newVar.insert(key, value);
        variableLine = name + ';' + strFromHM(newVar);//превращаем переменную в текст
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


void hashSetDel(const request& request){
    //команда: del имяТаблицы ключ
    fstream tmpFile("tmp.data", ios::out);
    if(!tmpFile.is_open()) throw runtime_error("Tmp file doesn't exist");
    fstream file(request.file, ios::in);
    if (request.query.size != 3) throw runtime_error("Wrong command syntax");
    string name = request.query[1]; //имя очереди
    string key = request.query[2];
    string variableLine; //считываемая строка с файла
    fileData var;
    bool varIsExist = false;
    while (getline(file, variableLine)){ //проверяем все существующие переменные
        if (variableLine == " " || variableLine.empty()) continue;
        var.name = splitToArr(variableLine, ';')[0]; //определяем их имена
        var.data = splitToArr(variableLine, ';')[1]; //и то, что они хранят
        if (var.name == name){ //если такая переменная существует
            varIsExist = true; //закрываем защёлку
            hashMap currVar = hMFromStr(var.data); //определяем реальную переменную этого Типа данных
            currVar.del(key);
            variableLine = var.name + ';' + strFromHM(currVar);//превращаем переменную в текст
            if (currVar.pairCount != 0){
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


void hashSetGet(const request& request){
//структура команды: Get имяТаблицы [ключ]
    fstream file(request.file, ios::in);
    if (request.query.size == 2) {
        string name = request.query[1];
        string variableLine; //считываемая строка с файла
        fileData var;
        bool varIsExist = false;
        while (getline(file, variableLine)){ //проверяем все существующие переменные
            if (variableLine == " " || variableLine.empty()) continue;
            var.name = splitToArr(variableLine, ';')[0]; //определяем их имена
            var.data = splitToArr(variableLine, ';')[1]; //и то, что они хранят
            if (var.name == name){ //если такая переменная существует
                varIsExist = true; //закрываем защёлку
                hashMap currVar = hMFromStr(var.data); //определяем реальную переменную этого Типа данных
                cout << currVar.Get() << endl;
            }
        }
        if (!varIsExist){
            cout << "This hashMap isn't exist" << endl;
        }
    }
    else if (request.query.size == 3){
        string name = request.query[1];
        string key = request.query[2];
        string variableLine; //считываемая строка с файла
        fileData var;
        bool varIsExist = false;
        while (getline(file, variableLine)){ //проверяем все существующие переменные
            if (variableLine == " " || variableLine.empty()) continue;
            var.name = splitToArr(variableLine, ';')[0]; //определяем их имена
            var.data = splitToArr(variableLine, ';')[1]; //и то, что они хранят
            if (var.name == name){ //если такая переменная существует
                varIsExist = true; //закрываем защёлку
                hashMap currVar = hMFromStr(var.data); //определяем реальную переменную этого Типа данных
                if (currVar.pairCount == 0) cout << "this HashMap is empty" << endl;
                else {
                    if (currVar.Get(key).key.empty()){
                        cout << "there is no value for this key" << endl;
                    }
                    else {
                        cout << currVar.Get(key) << endl;
                    }
                }
            }
        }
        if (!varIsExist){
            cout << "This hashMap isn't exist" << endl;
        }
    }
    else throw runtime_error("Wrong command syntax");

}

