#include "queue_funcs.h"


void printQueue(const request& request){
    ifstream file(request.file, ios::in); //������ ������
    string variableLine; //����������� ������ � �����
    if (request.query.size == 1){ //������� ��� ����������
        fileData var;
        while (getline(file, variableLine)) { //��������� ��� ������������ ����������
            if (variableLine == " " || variableLine.empty()) continue;
            var.name = splitToArr(variableLine, ';')[0]; //���������� �� �����
            var.data = splitToArr(variableLine, ';')[1]; //� ��, ��� ��� ������
            queue<string> currVar = splitToQueue(var.data); //���������� �������� ���������� ����� ���� ������
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
                queue<string> currVar = splitToQueue(var.data); //���������� �������� ���������� ����� ���� ������
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
//��������� �������: push ���������� �����������
    fstream file(request.file, ios::in);
    if(!file.is_open()){
        stringstream serr;
        serr << "This file doesn't exist";
        throw runtime_error(serr.str());
    }
    fstream tmpFile("tmp.data", ios::out);
    if(!tmpFile.is_open()){
        stringstream serr;
        serr << "Tmp file doesn't exist";
        throw runtime_error(serr.str());
    }
    if (request.query.size != 3) {
        stringstream serr;
        serr << "Wrong command syntax";
        throw runtime_error(serr.str());
    }
    string name = request.query[1]; //��� �������
    string value = request.query[2]; //��� ��������
    string variableLine; //����������� ������ � �����
    fileData var;
    bool varIsExist = false;
    while (getline(file, variableLine)){ //��������� ��� ������������ ����������
        if (variableLine == " " || variableLine.empty()) continue;
        var.name = splitToArr(variableLine, ';')[0]; //���������� �� �����
        var.data = splitToArr(variableLine, ';')[1]; //� ��, ��� ��� ������
        if (var.name == name){ //���� ����� ���������� ����������
            varIsExist = true; //��������� �������
            queue<string> currVar = splitToQueue(var.data); //���������� �������� ���������� ����� ���� ������
            currVar.push(value);
            variableLine = var.name + ';' + unSplitQueue(currVar);//���������� ���������� � �����
            currVar.clear();
            tmpFile << variableLine << endl;
        }
        else {
            tmpFile << variableLine << endl;
        }
    }
    if (!varIsExist){
        cout << "making new queue" << endl;
        queue<string> newVar;//��, ������ ��� ������.
        newVar.push(value);
        variableLine = name + ';' + unSplitQueue(newVar);//���������� ���������� � �����
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
//�������: pop ����������
    fstream file(request.file, ios::in);
    if(!file.is_open()){
        stringstream serr;
        serr << "This file doesn't exist";
        throw runtime_error(serr.str());
    }
    fstream tmpFile("tmp.data", ios::out);
    if(!tmpFile.is_open()){
        stringstream serr;
        serr << "Tmp file doesn't exist";
        throw runtime_error(serr.str());
    }
    if (request.query.size != 2) {
        stringstream serr;
        serr << "Wrong command syntax";
        throw runtime_error(serr.str());
    }
    string name = request.query[1]; //��� �������
    string variableLine; //����������� ������ � �����
    fileData var;
    bool varIsExist = false;
    while (getline(file, variableLine)){ //��������� ��� ������������ ����������
        if (variableLine == " " || variableLine.empty()) continue;
        var.name = splitToArr(variableLine, ';')[0]; //���������� �� �����
        var.data = splitToArr(variableLine, ';')[1]; //� ��, ��� ��� ������
        if (var.name == name){ //���� ����� ���������� ����������
            varIsExist = true; //��������� �������
            queue<string> currVar = splitToQueue(var.data); //���������� �������� ���������� ����� ���� ������
            currVar.pop();
            variableLine = var.name + ';' + unSplitQueue(currVar);//���������� ���������� � �����
            currVar.clear();
            tmpFile << variableLine << endl;
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
//��������� �������: get ����������
    fstream file(request.file, ios::in);
    if(!file.is_open()){
        stringstream serr;
        serr << "This file doesn't exist";
        throw runtime_error(serr.str());
    }
    if (request.query.size != 2) {
        stringstream serr;
        serr << "Wrong command syntax";
        throw runtime_error(serr.str());
    }
    string name = request.query[1]; //� ����� ������� ������
    string variableLine; //����������� ������ � �����
    fileData var;
    bool varIsExist = false;
    while (getline(file, variableLine)){ //��������� ��� ������������ ����������
        if (variableLine == " " || variableLine.empty()) continue;
        var.name = splitToArr(variableLine, ';')[0]; //���������� �� �����
        var.data = splitToArr(variableLine, ';')[1]; //� ��, ��� ��� ������
        if (var.name == name){ //���� ����� ���������� ����������
            varIsExist = true; //��������� �������
            queue<string> currVar = splitToQueue(var.data); //���������� �������� ���������� ����� ���� ������
            cout << currVar.getFirst() << endl;
            currVar.clear();
        }
    }
    if (!varIsExist){
        cout << "This queue isn't exist" << endl;
    }
}