#include "hashMap_funcs.h"


void printHashMap(const request &request) {
    ifstream file(request.file, ios::in); //������ ������
    string variableLine; //����������� ������ � �����
    if (request.query.size == 1){ //������� ��� ����������
        fileData var;
        while (getline(file, variableLine)) { //��������� ��� ������������ ����������
            if (variableLine == " " || variableLine.empty()) continue;
            var.name = splitToArr(variableLine, ';')[0]; //���������� �� �����
            var.data = splitToArr(variableLine, ';')[1]; //� ��, ��� ��� ������
            //���������� �������� ���������� ����� ���� ������
            hashMap currVar = hMFromStr(var.data);
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
                hashMap currVar = hMFromStr(var.data); //���������� �������� ���������� ����� ���� ������
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
//��������� �������: insert ���������� ���� ��������
    fstream file(request.file, ios::in);
    fstream tmpFile("tmp.data", ios::out);
    if(!tmpFile.is_open()) throw runtime_error("Tmp file doesn't exist");
    if (request.query.size != 4) throw runtime_error("Wrong command syntax");
    string name = request.query[1];
    string key = request.query[2]; //����
    string value = request.query[3]; //��������
    string variableLine; //����������� ������ � �����
    fileData var;
    bool varIsExist = false;
    while (getline(file, variableLine)){ //��������� ��� ������������ ����������
        if (variableLine == " " || variableLine.empty()) continue;
        var.name = splitToArr(variableLine, ';')[0]; //���������� �� �����
        var.data = splitToArr(variableLine, ';')[1]; //� ��, ��� ��� ������
        if (var.name == name){ //���� ����� ���������� ����������
            varIsExist = true; //��������� �������
            hashMap currVar = hMFromStr(var.data); //���������� �������� ���������� ����� ���� ������
            currVar.insert(key, value); //���������� ��, ��� ������
            variableLine = var.name + ';' + strFromHM(currVar);//���������� ���������� � �����
            tmpFile << variableLine << endl;
        }
        else {
            tmpFile << variableLine << endl;
        }
    }
    if (!varIsExist){
        cout << "making new HashMap" << endl;
        hashMap newVar;//��, ������ ��� ������.
        newVar.insert(key, value);
        variableLine = name + ';' + strFromHM(newVar);//���������� ���������� � �����
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
    //�������: del ���������� ����
    fstream tmpFile("tmp.data", ios::out);
    if(!tmpFile.is_open()) throw runtime_error("Tmp file doesn't exist");
    fstream file(request.file, ios::in);
    if (request.query.size != 3) throw runtime_error("Wrong command syntax");
    string name = request.query[1]; //��� �������
    string key = request.query[2];
    string variableLine; //����������� ������ � �����
    fileData var;
    bool varIsExist = false;
    while (getline(file, variableLine)){ //��������� ��� ������������ ����������
        if (variableLine == " " || variableLine.empty()) continue;
        var.name = splitToArr(variableLine, ';')[0]; //���������� �� �����
        var.data = splitToArr(variableLine, ';')[1]; //� ��, ��� ��� ������
        if (var.name == name){ //���� ����� ���������� ����������
            varIsExist = true; //��������� �������
            hashMap currVar = hMFromStr(var.data); //���������� �������� ���������� ����� ���� ������
            currVar.del(key);
            variableLine = var.name + ';' + strFromHM(currVar);//���������� ���������� � �����
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
//��������� �������: Get ���������� [����]
    fstream file(request.file, ios::in);
    if (request.query.size == 2) {
        string name = request.query[1];
        string variableLine; //����������� ������ � �����
        fileData var;
        bool varIsExist = false;
        while (getline(file, variableLine)){ //��������� ��� ������������ ����������
            if (variableLine == " " || variableLine.empty()) continue;
            var.name = splitToArr(variableLine, ';')[0]; //���������� �� �����
            var.data = splitToArr(variableLine, ';')[1]; //� ��, ��� ��� ������
            if (var.name == name){ //���� ����� ���������� ����������
                varIsExist = true; //��������� �������
                hashMap currVar = hMFromStr(var.data); //���������� �������� ���������� ����� ���� ������
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
        string variableLine; //����������� ������ � �����
        fileData var;
        bool varIsExist = false;
        while (getline(file, variableLine)){ //��������� ��� ������������ ����������
            if (variableLine == " " || variableLine.empty()) continue;
            var.name = splitToArr(variableLine, ';')[0]; //���������� �� �����
            var.data = splitToArr(variableLine, ';')[1]; //� ��, ��� ��� ������
            if (var.name == name){ //���� ����� ���������� ����������
                varIsExist = true; //��������� �������
                hashMap currVar = hMFromStr(var.data); //���������� �������� ���������� ����� ���� ������
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

