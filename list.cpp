#include "list.h"


template<typename T>
void list<T>::backInsert(T value) {
    listNode<T>* newLast = new listNode(value);
    if (last == nullptr){
        last = newLast;
        first = newLast;
    }
    else{
        newLast->previous = last;
        last->next = newLast;
        last = newLast;
    }
}

template<typename T>
void list<T>::headInsert(T value) {
    listNode<T>* newFirst = new listNode(value);
    if (last == nullptr){
        last = newFirst;
        first = newFirst;
    }
    else{
        first->previous = newFirst;
        newFirst->next = first;
        first = newFirst;
    }
}


template<typename T>
void list<T>::delLast() {
    if (this->first->previous == nullptr){
        delete this->last;
        this->first = nullptr;
        this->last = nullptr;
    }
    else {
        last = last->previous;
        delete last->next;
        last->next = nullptr;
    }
}


template<typename T>
void list<T>::delFirst() {
    if (this->first->next == nullptr){
        delete this->first;
        this->first = nullptr;
        this->last = nullptr;
    }
    else {
        first = first->next;
        delete first->previous;
        first->previous = nullptr;
    }
}


template<typename T>
bool list<T>::find(T value) {
    listNode<T> *tmp = first;
    while (tmp != nullptr){
        if (tmp->value == value){
            return true;
        }
        tmp = tmp->next;
    }
    return false;
}



template<typename T>
void list<T>::delByVal(T val) {
    listNode<T> *tmp = first;
    while (tmp != nullptr){
        if (tmp->value == val){
            tmp->next->previous = tmp->previous;
            tmp->previous->next = tmp->next;
            delete tmp;
            break;
        }
        tmp = tmp->next;
    }
}


list<string> splitToList(const string &input, char delimiter){
    string word;
    list<string> output;
    for (auto ch : input){
        if (ch == delimiter) {
            output.backInsert(word);
            word = "";
        }
        else{
            word += ch;
        }
    }
    if (word != ""){
        output.backInsert(word);
    }
    return output;
}


list<Pair> splitToListPair(const string &input, const string& pairDelimiter, char keyValueDelimiter){
    string word;
    list<Pair> output;
    Pair currentPair;
    bool isDelim;
    int j;
    for (int i = 0; i < input.size(); ++i){
        if (input[i] == pairDelimiter[0]){
            isDelim = true;
            for (j = 0; j < pairDelimiter.size(); ++j){
                if (pairDelimiter[j] != input[i + j]) isDelim = false;
            }
            if (isDelim){
                output.backInsert(splitToPair(word, keyValueDelimiter));
                word = "";
                i += j - 1;
            }
            else {
                word += input[i];
            }
        }
        else {
            word += input[i];
        }
    }
    if (word != ""){
        output.backInsert(splitToPair(word, keyValueDelimiter));
    }
    return output;

}


string unSplitList(const list<string>& input, char delimiter){
    listNode<string>* curr = input.first;
    string output;
    while (curr != nullptr){
        output += curr->value + delimiter;
        curr = curr->next;
    }
    return output;
}
