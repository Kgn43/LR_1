#include "stack_funcs.h"


void printStack(const request& request){
    ifstream file(request.file, ios::in); //откуда читаем
    string variableLine; //считываемая строка с файла
    if (request.query.size == 1){ //вывести все переменные
        fileData var;
        while (getline(file, variableLine)) { //проверяем все существующие переменные
            if (variableLine == " " || variableLine.empty()) continue;
            var.name = splitToArr(variableLine, ';')[0]; //определяем их имена
            var.data = splitToArr(variableLine, ';')[1]; //и то, что они хранят
            Stack<string> currVar = splitToStack(var.data); //определяем реальную переменную этого Типа данных
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
                Stack<string> currVar = splitToStack(var.data); //определяем реальную переменную этого Типа данных
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


void stackPush(const request& request){
//структура команды: push имяСтека чтоЗаписать
    fstream file(request.file, ios::in);
    fstream tmpFile("tmp.data", ios::out);
    if(!tmpFile.is_open()) throw runtime_error("Tmp file doesn't exist");
    if (request.query.size != 3) throw runtime_error("Wrong command syntax");
    string name = request.query[1];
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
            Stack<string> currVar = splitToStack(var.data); //определяем реальную переменную этого Типа данных
            currVar.push(value); //закидываем то, что просят в конец
            variableLine = var.name + ';' + unSplitStack(currVar);//превращаем переменную в текст
            currVar.clear();//никаких утечек!
            tmpFile << variableLine << endl;
        }
        else {
            tmpFile << variableLine << endl;
        }
    }
    if (!varIsExist){
        cout << "making new Stack" << endl;
        Stack<string> newVar;//да, делаем это всегда.
        newVar.push(value);
        variableLine = name + ';' + unSplitStack(newVar);//превращаем переменную в текст
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


void stackPop(const request& request){
//команда: pop имяСтека
    fstream file(request.file, ios::in);
    fstream tmpFile("tmp.data", ios::out);
    if(!tmpFile.is_open()) throw runtime_error("Tmp file doesn't exist");
    if (request.query.size != 2) throw runtime_error("Wrong command syntax");
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
            Stack<string> currVar = splitToStack(var.data); //определяем реальную переменную этого Типа данных
            currVar.pop(); //удаляем
            variableLine = var.name + ';' + unSplitStack(currVar);//превращаем переменную в текст
            if (currVar.head != nullptr){
                tmpFile << variableLine << endl;
            }
            currVar.clear();
        }
        else {
            tmpFile << variableLine << endl;
        }
    }
    file.close();
    tmpFile.close();
    if (!varIsExist){
        cout << "Tis stack doesn't exist" << endl;
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


void stackGet(const request& request){
//структура команды: get имяСтека
    fstream file(request.file, ios::in);
    if (request.query.size != 2) throw runtime_error("Wrong command syntax");
    string name = request.query[1]; //из какого стека считать
    string variableLine; //считываемая строка с файла
    fileData var;
    bool varIsExist = false;
    while (getline(file, variableLine)){ //проверяем все существующие переменные
        if (variableLine == " " || variableLine.empty()) continue;
        var.name = splitToArr(variableLine, ';')[0]; //определяем их имена
        var.data = splitToArr(variableLine, ';')[1]; //и то, что они хранят
        if (var.name == name){ //если такая переменная существует
            varIsExist = true; //закрываем защёлку
            Stack<string> currVar = splitToStack(var.data); //определяем реальную переменную этого Типа данных
            cout << currVar.getLast() << endl;
            currVar.clear();
        }
    }
    if (!varIsExist){
        cout << "This stack isn't exist" << endl;
    }
}