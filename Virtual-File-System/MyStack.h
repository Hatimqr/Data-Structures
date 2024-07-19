#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<exception>


using namespace std;

#ifndef MYSTACK_H
#define MYSTACK_H

template <typename T>
class MyStack {
private:
    T* elements;
    int topIndex;
    int capacity;
public:
    MyStack(int capacity);
    ~MyStack();
    int size() const;
    void push(T const& element);
    void pop();
    T top() const;
    bool empty() const;
};

// #include "MyStack.cpp"

#endif
