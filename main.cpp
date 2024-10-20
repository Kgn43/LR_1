#include "lab_1.h"


int main(int argc, char *argv[]) {
    try {
        request request = getRequest(argc, argv);
        if (argc == 1){
            cout << "0 arguments were entered." << endl << "add --help for more information" << endl;
            return 1;
        }
        if (request.isCallHelp){
            callHelp();
            return 1;
        }
        if (request.query.size == 0){
            cout << "An empty query was given: add --help" << endl;
            return 1;
        }
        if (request.query[0] == "print"){
            if (!isFileExist(request.file) || request.file.empty()){ //проверяем доступ указанного файла/указан ли файл
                throw runtime_error(("Error: wrong file name or file doesn't exist"));
            }
            consolePrint(request);
        } else {
            structures strucType = structRequest(request.query[0][0]); //определяем по букве структуру
            if (!isFileExist(request.file) || request.file.empty()){ //проверяем доступ указанного файла/указан ли файл
                throw runtime_error(("Error: wrong file name or file doesn't exist"));
            }
            request.query[0] = delFirstLetter(request.query[0]); //убираем букву для упрощения чтения команды
            switch (strucType) {
                case Array:
                    switch (commandRequest(request.query[0])) {
                        case push:
                            arrPush(request);
                            break;
                        case del:
                            arrDel(request);
                            break;
                        case Get:
                            arrGet(request);
                            break;
                        default:
                            cout << "There is no such Array processing command" << endl;
                    }
                    break;
                case stack:
                    switch (commandRequest(request.query[0])) {
                        case push:
                            stackPush(request);
                            break;
                        case pop:
                            stackPop(request);
                            break;
                        case Get:
                            stackGet(request);
                            break;
                        default:
                            cout << "There is no such Stack processing command" << endl;
                    }
                    break;
                case List:
                    switch (commandRequest(request.query[0])) {
                        case push:
                            listPush(request);
                            break;
                        case del:
                            listDel(request);
                            break;
                        case Get:
                            listGet(request);
                            break;
                        default:
                            cout << "There is no such List processing command" << endl;
                    }
                    break;
                case Queue:
                    switch (commandRequest(request.query[0])) {
                        case push:
                            queuePush(request);
                            break;
                        case pop:
                            queuePop(request);
                            break;
                        case Get:
                            queueGet(request);
                            break;
                        default:
                            cout << "There is no such Queue processing command" << endl;
                    }
                    break;
                case HashMap:
                    switch (commandRequest(request.query[0])) {
                        case insert:
                            hashSetInsert(request);
                            break;
                        case del:
                            hashSetDel(request);
                            break;
                        case Get:
                            hashSetGet(request);
                            break;
                        default:
                            cout << "There is no such HashSet processing command" << endl;
                    }
                    break;
            }
        }
    }
    catch (exception &ex) {
        cout << ex.what() << endl;
        return -1;
    }
}



void consolePrint(const request& request){
    fstream file(request.file, ios::in);
    structures type = getType(request.file);
    switch (type) {
        case Array:
            printArr(request);
            break;
        case List:
            printList(request);
            break;
        case Queue:
            printQueue(request);
            break;
        case stack:
            printStack(request);
            break;
        case HashMap:
            printHashMap(request);
            break;
    }
}