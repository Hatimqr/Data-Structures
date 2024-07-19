#include <iostream>
#include "dochashtable.h"

#ifndef MYLIST_H
#define MYLIST_H

template <typename T>
class MyList
{
	private:
		T* head; // pointer to the head of list
		int size; // number of nodes in the list
	public:

		class iterator
		{
			private:
				T* ptr; // keep a pointer to MyList
			public:
				iterator(T* newPtr);
				iterator operator++();
				iterator operator *();
				bool operator !=(const iterator& other);
				friend class MyList<T>;
				friend class DocHASHTABLE;
		};
		

		MyList (); // empty list constructor
		~MyList (); // destructor to clean up all nodes
		bool empty() const; // is list empty?
		int getSize() const; // get number of nodes in list
		void addFront(T* node); // add a new Node at the front of the list
		void removeFront(); // remove front Node from the list
		iterator begin();
		iterator end();
};

template <typename T>
MyList <T> ::MyList ()
{
	this->head = NULL;
    this->size = 0;
}

template <typename T>
MyList <T> ::~MyList ()
{
    while (!empty())
    {
        removeFront();
    }
    delete head;
}

template <typename T>
bool MyList <T> ::empty() const
{
    return head == NULL;
}

template <typename T>
int MyList <T> ::getSize() const
{
    return size;
}

template <typename T>
void MyList <T> ::addFront(T* node)
{
	node->next = head;
	head = node;
    size++;
}

template <typename T>
void MyList <T> ::removeFront()
{
    T *old = head;
    head = head->next;
    delete old;
    size--;
}

template<typename T>
typename MyList<T>::iterator MyList<T>::begin()
{
	return iterator(head);
}

template<typename T>
typename MyList<T>::iterator MyList<T>::end()
{
	return iterator(NULL);
}

template<typename T>
MyList<T>::iterator::iterator(T * newPtr)
{
    ptr = newPtr;
}

template<typename T>
typename MyList<T>::iterator MyList<T>::iterator::operator++()
{
    ptr = ptr->next;
    return *this;
}

template<typename T>
typename MyList<T>::iterator MyList<T>::iterator::operator*()
{
    return *this;
}

template<typename T>
bool MyList<T>::iterator::operator!=(const iterator & other)
{
    return ptr != other.ptr;
}

#endif