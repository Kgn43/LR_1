#include "arr_funcs.h"


void printArr(const request& request){
    ifstream file(request.file, ios::in); //������ ������
    string variableLine; //����������� ������ � �����
    if (request.query.size == 1){ //������� ��� ����������
        fileData var;
        while (getline(file, variableLine)) { //��������� ��� ������������ ����������
            if (variableLine == " " || variableLine.empty()) continue;
            var.name = splitToArr(variableLine, ';')[0]; //���������� �� �����
            var.data = splitToArr(variableLine, ';')[1]; //� ��, ��� ��� ������
            arr<string> currVar = splitToArr(var.data); //���������� �������� ���������� ����� ���� ������
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
                arr<string> currVar = splitToArr(var.data); //���������� �������� ���������� ����� ���� ������
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
//��������� �������1 (�� �������): push ���������� ���� ���
//��������� �������2 (� �����): push ���������� ���
    fstream file(request.file, ios::in);
    fstream tmpFile("tmp.data", ios::out);
    if(!tmpFile.is_open()){
        throw runtime_error("Tmp file doesn't exist");
    }
    string name; //���� ��������
    string value; //��� ��������
    int index;
    string variableLine; //����������� ������ � �����
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
    while (getline(file, variableLine)){ //��������� ��� ������������ ����������
        if (variableLine == " " || variableLine.empty()) continue;
        var.name = splitToArr(variableLine, ';')[0]; //���������� �� �����
        var.data = splitToArr(variableLine, ';')[1]; //� ��, ��� ��� ������
        if (var.name == name){ //���� ����� ���������� ����������
            varIsExist = true; //��������� �������
            arr<string> currVar = splitToArr(var.data); //���������� �������� ���������� ����� ���� ������
            currVar.push_back(value); //���������� ��, ��� ������ � �����
            if (currVar.size - 1 != index && index != -1){
                string tmp;//������ ������
                for(size_t i = currVar.size - 1; i > index; --i){ //� ������ ������� �� ������� �������
                    tmp = currVar.data[i];
                    currVar.data[i] = currVar.data[i - 1];
                    currVar.data[i - 1] = tmp;
                }
            }
            variableLine = var.name + ';' + unsplit(currVar);//���������� ���������� � �����
            tmpFile << variableLine << endl;
            //currVar.clear();
        }
        else {
            tmpFile << variableLine << endl;
        }
    }
    if (!varIsExist){
        cout << "making new array" << endl;
        if (index != 0 && index != -1){//������� �������� �� �����-���� ������ ����� ���� � �������������� ����������. ����-����.
            throw runtime_error("Wrong index");
        }
        arr<string> newVar;//��, ����� � �� ������ �����. �� �� �������. ������, ��� �����.
        newVar.push_back(value);
        variableLine = name + ';' + unsplit(newVar);//���������� ���������� � �����
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
//��������� �������: del ���������� ������
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
    string name = request.query[1]; //�� ������ ������� �������
    size_t index = stoi(request.query[2]); //� ����� �������
    string variableLine; //����������� ������ � �����
    fileData var;
    bool varIsExist = false;
    while (getline(file, variableLine)){ //��������� ��� ������������ ����������
        if (variableLine == " " || variableLine.empty()) continue;
        var.name = splitToArr(variableLine, ';')[0]; //���������� �� �����
        var.data = splitToArr(variableLine, ';')[1]; //� ��, ��� ��� ������
        if (var.name == name){ //���� ����� ���������� ����������
            varIsExist = true; //��������� �������
            arr<string> currVar = splitToArr(var.data); //���������� �������� ���������� ����� ���� ������
            currVar.del(index);//��������
            variableLine = var.name + ';' + unsplit(currVar);//���������� ���������� � �����
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
//��������� �������: get ���������� ������
    fstream file(request.file, ios::in);
    if(!file.is_open()){
        stringstream serr;
        serr << "This file doesn't exist";
        throw runtime_error(serr.str());
    }
    string name = request.query[1]; //�� ������ ������� �������
    size_t index = stoi(request.query[2]); //� ����� �������
    string variableLine; //����������� ������ � �����
    fileData var;
    bool varIsExist = false;
    while (getline(file, variableLine)){ //��������� ��� ������������ ����������
        if (variableLine == " " || variableLine.empty()) continue;
        var.name = splitToArr(variableLine, ';')[0]; //���������� �� �����
        var.data = splitToArr(variableLine, ';')[1]; //� ��, ��� ��� ������
        if (var.name == name){ //���� ����� ���������� ����������
            varIsExist = true; //��������� �������
            arr<string> currVar = splitToArr(var.data); //���������� �������� ���������� ����� ���� ������
            if (index < currVar.size) cout << currVar[index] << endl;
            else cout << "Index out of range" << endl;
            //currVar.clear();
        }
    }
    if (!varIsExist){
        cout << "This array isn't exist" << endl;
    }
}
