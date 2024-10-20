#ifndef LAB_1_NODE_H
#define LAB_1_NODE_H
#include <string>

using namespace std;

template <typename T>
struct Node {
public:
    T value;
    Node* next;

    //������������
    Node(T val, Node* following) : value(val), next(following) {}
    Node(T val) : value(val), next(nullptr) {}
    Node() : value(T()), next(nullptr){} //�� ������, �� ��� ����� ��������� ������, ���� ��� ������������ �� ��������� ��� ���
};

template struct Node<int>;
template struct Node<string>;

#endif //LAB_1_NODE_H
