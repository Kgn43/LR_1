#include "Pair.h"


Pair splitToPair(const string &inputLine, char delimiter) {
    string word;
    Pair output;
    bool z = true;
    for (auto ch: inputLine) {
        if (ch == delimiter && z) {
            output.key = word;
            word = "";
            z = false;
        } else {
            word += ch;
        }
    }
    output.value = word;
    return output;
}


string unsplitFromPair(const Pair &input, char delimiter) {
    return input.key + delimiter + input.value;
}