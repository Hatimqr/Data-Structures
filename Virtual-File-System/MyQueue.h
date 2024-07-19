#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<exception>

using namespace std;

#ifndef MYQUEUE_H
#define MYQUEUE_H

template <typename T>
class MyQueue
{
	private:
		T *array;
		int capacity;	//Max Capacity of the Queue
		int size;		//current number of elements in the Queue
		int front;		//front of the Queue
		int rear;		//index where a new element will be added
	public:
		MyQueue();
		~MyQueue();
		void enqueue(T elem);
		T dequeue();
		bool isEmpty();
		bool isFull();
		int getFront();
		int getRear();
		T& operator[](int index);
		
};

// #include "MyQueue.cpp"

#endif
