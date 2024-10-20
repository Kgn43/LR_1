#include "list_funcs.h"


void printList(const request& request){
    ifstream file(request.file, ios::in); //������ ������
    string variableLine; //����������� ������ � �����
    if (request.query.size == 1){ //������� ��� ����������
        fileData var;
        while (getline(file, variableLine)) { //��������� ��� ������������ ����������
            if (variableLine == " " || variableLine.empty()) continue;
            var.name = splitToArr(variableLine, ';')[0]; //���������� �� �����
            var.data = splitToArr(variableLine, ';')[1]; //� ��, ��� ��� ������
            list<string> currVar = splitToList(var.data); //���������� �������� ���������� ����� ���� ������
            cout << var.name << " = " << currVar << endl;
        }
    }
    else if (request.query.size == 2) { //������� ���� ����������
        string name = request.query[1]; //��� ������� ����������
        fileData var;
        bool varIsExist = false;
        while (getline(file, variableLine)){ //��������� ��� ������������ ����������
            if (variableLine == " " || variableLine.empty()) continue;
            var.name = splitToArr(variableLine, ';')[0]; //���������� �� �����
            var.data = splitToArr(variableLine, ';')[1]; //� ��, ��� ��� ������
            if (var.name == name){ //���� ����� ���������� ����������
                varIsExist = true; //��������� �������
                list<string> currVar = splitToList(var.data); //���������� �������� ���������� ����� ���� ������
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
//��������� �������: push ��������� ������������ �����������
    fstream file(request.file, ios::in);
    fstream tmpFile("tmp.data", ios::out);
    if(!tmpFile.is_open()) throw runtime_error("Tmp file doesn't exist");
    if (request.query.size != 4) {
        stringstream serr;
        serr << "Wrong command syntax";
        throw runtime_error(serr.str());
    }
    string name = request.query[1]; //��� ������
    string place = request.query[2]; // ������/�����
    if (place != "begin" && place != "end"){
        stringstream serr;
        serr << "Wrong insert place";
        throw runtime_error(serr.str());
    }
    string value = request.query[3]; //��� ��������
    string variableLine; //����������� ������ � �����
    fileData var;
    bool varIsExist = false;
    while (getline(file, variableLine)){ //��������� ��� ������������ ����������
        if (variableLine == " " || variableLine.empty()) continue;
        var.name = splitToArr(variableLine, ';')[0]; //���������� �� �����
        var.data = splitToArr(variableLine, ';')[1]; //� ��, ��� ��� ������
        if (var.name == name){ //���� ����� ���������� ����������
            varIsExist = true; //��������� �������
            list<string> currVar = splitToList(var.data); //���������� �������� ���������� ����� ���� ������
            if (place == "begin"){
                currVar.headInsert(value); //���������� ��, ��� ������ � ������
            }
            else {
                currVar.backInsert(value);
            }
            variableLine = var.name + ';' + unSplitList(currVar);//���������� ���������� � �����
            //currVar.clear();
            tmpFile << variableLine << endl;
        }
        else {
            tmpFile << variableLine << endl;
        }
    }
    if (!varIsExist){
        cout << "making new list" << endl;
        list<string> newVar;//��, ������ ��� ������.
        newVar.headInsert(value);
        variableLine = name + ';' + unSplitList(newVar);//���������� ���������� � �����
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
//�������: pop ��������� ������/����������������
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
    string variableLine; //����������� ������ � �����
    fileData var;
    bool varIsExist = false;
    while (getline(file, variableLine)){ //��������� ��� ������������ ����������
        if (variableLine == " " || variableLine.empty()) continue;
        var.name = splitToArr(variableLine, ';')[0]; //���������� �� �����
        var.data = splitToArr(variableLine, ';')[1]; //� ��, ��� ��� ������
        if (var.name == name){ //���� ����� ���������� ����������
            varIsExist = true; //��������� �������
            list<string> currVar = splitToList(var.data); //���������� �������� ���������� ����� ���� ������
            if (wh == "begin") {
                currVar.delFirst();
            }
            else if (wh == "end"){
                currVar.delLast();
            }
            else {
                currVar.delByVal(wh);
            }
            variableLine = var.name + ';' + unSplitList(currVar);//���������� ���������� � �����
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
//��������� �������: get ��������� ���������������
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
    string name = request.query[1]; //� ����� ������ ������
    string value = request.query[2]; //��� ����
    string variableLine; //����������� ������ � �����
    fileData var;
    bool varIsExist = false;
    while (getline(file, variableLine)){ //��������� ��� ������������ ����������
        if (variableLine == " " || variableLine.empty()) continue;
        var.name = splitToArr(variableLine, ';')[0]; //���������� �� �����
        var.data = splitToArr(variableLine, ';')[1]; //� ��, ��� ��� ������
        if (var.name == name){ //���� ����� ���������� ����������
            varIsExist = true; //��������� �������
            list<string> currVar = splitToList(var.data); //���������� �������� ���������� ����� ���� ������
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