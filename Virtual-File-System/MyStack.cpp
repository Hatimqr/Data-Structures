#include "MyStack.h"
#include "vfs_tree.h"

template <typename T>
MyStack<T>::MyStack(int capacity) : capacity(capacity), topIndex(-1) {
    elements = new T[capacity];
}

template <typename T>
MyStack<T>::~MyStack() {
    delete[] elements;
}

template <typename T>
int MyStack<T> :: size() const{
    return topIndex + 1;
}

template <typename T>
void MyStack<T>::push(T const& element) {
    if (topIndex + 1 >= capacity) throw invalid_argument("Stack is full");
    elements[++topIndex] = element;
}

template <typename T>
void MyStack<T>::pop() {
    if (topIndex < 0) throw invalid_argument("Stack is empty");
    --topIndex;
}

template <typename T>
T MyStack<T>::top() const {
    if (topIndex < 0) throw invalid_argument("Stack is empty");
    return elements[topIndex];
}

template <typename T>
bool MyStack<T>::empty() const {
    return topIndex < 0;
}

template class MyStack<string>; 
template class MyStack<Position>;
template class MyStack<Inode*>;