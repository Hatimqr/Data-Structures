#include "MyVector.h"
#include "inode.h"
#include "vfs_tree.h"

template <typename T> 
MyVector<T>::MyVector(int cap){
    this->data = new T[cap];
    this->v_capacity = cap;
    this->v_size = -1;
}

template <typename T> 
MyVector<T>::~MyVector(){
    delete[]data;
}

template <typename T> 
void MyVector<T>:: push_back(T element){
    if (v_size == v_capacity-1) expand();
    data[v_size+1] = element;
    v_size+=1;
}
template <typename T> 
void MyVector<T>:: insert(int index, T element){
   if (index > v_capacity) throw out_of_range("Index out of range");
    if (this->size() == this->capacity()) expand();

    for (int i = v_size; i>= index; i--){
        data[i+1] = data[i];
    }
    data[index] = element;
    v_size++;
}
template <typename T> 
void MyVector<T>:: erase(int index){
   if (empty()) throw invalid_argument("Vector is Empty");
   if (index > v_size) throw out_of_range("Index out of range");

    for (int i = index; i <= v_size; i++)
    {
        data[i] = data[i+1];
    }
    v_size--;
}
template <typename T> 
T& MyVector<T>:: at(int index){
   if (empty()) throw invalid_argument("Vector is Empty");
   if (index > v_size) throw out_of_range("Index out of range");
    return data[index];
}
template <typename T> 
const T& MyVector<T>:: front(){
   if (empty()) throw invalid_argument("Vector is Empty");
    return data[0];
}
template <typename T> 
const T& MyVector<T>::back(){
   if (empty()) throw invalid_argument("Vector is Empty");
    return data[v_size];

}
template <typename T> 
int MyVector<T>:: size() const{
    return v_size + 1;
}
template <typename T> 
int MyVector<T>:: capacity() const{
    return v_capacity;
}
template <typename T> 
bool MyVector<T>:: empty() const{
    return v_size < 0;
}
template <typename T> 
void MyVector<T>:: expand(){
    if (capacity()==0){
        ++v_capacity;
        data = new T[v_capacity];
        return;
    }
    v_capacity = v_capacity*2;
    T* newdata = new T[v_capacity];
    for (int i = 0; i<v_capacity; i++) {
        newdata[i]=data[i];
    }
    delete []data;
    data = newdata;
}
template <typename T> 
void MyVector<T>:: shrink_to_fit(){
    v_capacity = this->size();
    T* newdata = new T[v_capacity];
    for (int i = 0; i<v_capacity; i++) {
        newdata[i]=data[i];
    }
    delete []data;
    data = newdata;
}

template class MyVector<Position>;
template class MyVector<Inode*>;
