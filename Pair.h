#ifndef LAB_1_PAIR_H
#define LAB_1_PAIR_H

#include <string>
#include <sstream>

using namespace std;

struct Pair{
    string key;
    string value;

    Pair(): key(""), value("") {};
    Pair(string k, string v): key(k), value(v) {};


    bool operator==(const Pair& other) const {
        return (key == other.key) && (value == other.value);
    }


    friend ostream& operator<<(ostream& os, const Pair& pr) {
        os << pr.key << ", " << pr.value;
    return os;
}


};


Pair splitToPair(const string& inputLine, char delimiter);
string unsplitFromPair(const Pair& input, char delimiter);

#endif //LAB_1_PAIR_H
