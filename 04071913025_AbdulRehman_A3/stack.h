#include<iostream>
using namespace std;
template<typename T>
struct node {
    T data;
    node<T>* next;
};
template<typename T>
class stack {
    node<T>* top_ptr;
public:
    stack() {
        top_ptr = NULL;
    }
    ~stack() {
        make_empty();
    }
    void push(const T& val) {
        if (full())
            throw("Stack Overflow!");
        node<T>* temp;
        temp = new node<T>;
        temp->data = val;
        temp->next = top_ptr;
        top_ptr = temp;
    }
    void pop() {
        if (empty())
            throw("Stack Underflow!");
        node<T>* temp;
        temp = top_ptr;
        top_ptr = top_ptr->next;
        delete temp;
    }
    T top() const {
        if (empty())
            throw("Stack is empty!");
        return top_ptr->data;
    }
    bool empty() const {
        return top_ptr == NULL;
    }
    bool full() const {
        node<T>* temp;
        temp = new node<T>;
        if (temp == NULL)
            return true;
        else {
            delete temp;
            return false;
        }
    }
    void make_empty() {
        while (!empty()) {
            pop();
        }
    }
};