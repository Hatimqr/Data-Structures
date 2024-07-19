#include "MyQueue.h"
#include "vfs_tree.h"

template<typename T> 
MyQueue<T>::MyQueue()
{
    capacity = 20;
    size = 0;
    front = 0;
    rear = 0;
    array = new T[capacity];
} 
template<typename T> 
MyQueue<T>::~MyQueue()
{
    delete [] array;
}
//===========================================
template<typename T> void 
MyQueue<T>::enqueue(T element)
{
	if (size==capacity) dequeue(); // should this be capacity or capacity -1
    array[rear] = element;
    rear = (rear+1) % capacity;
    ++size;
}
//===========================================
template<typename T> 
T MyQueue<T>::dequeue()
{
	if (isEmpty()) throw invalid_argument("Queue is Empty");
    T var = array[front];
    front = (front + 1) % capacity;
    --size;
    return var;
}
//===========================================
template<typename T> 
bool MyQueue<T>::isEmpty()
{
	return size == 0;
}
//===========================================
template<typename T> 
bool MyQueue<T>::isFull()
{
    return size == capacity;
}

template<typename T>  
int MyQueue<T>::getFront()
{
    return this->front;
}


template<typename T>  
int MyQueue<T>::getRear()
{
    return this->rear;
}

template<typename T>
T& MyQueue<T>::operator[](int index){
    return array[index];
}

template class MyQueue<Position*>;
template class MyQueue<string>;