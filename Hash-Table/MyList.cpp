#include "dochashtable.h"
#include "MyList.h"

//constructor
template <typename T>
MyList <T> ::MyList ()
{
	this->head = NULL;
    this->size = 0;
}
//destructor
template <typename T>
MyList <T> ::~MyList ()
{
    while (!empty())
    {
        removeFront();
    }
    delete head;
}
// if the head poiunts to NULL, then the list is empty
template <typename T>
bool MyList <T> ::empty() const
{
    return head == NULL;
}
// return attribute size
template <typename T>
int MyList <T> ::getSize() const
{
    return size;
}
// add a node to the front of the list
template <typename T>
void MyList <T> ::addFront(T* node)
{
	node->next = head;
	head = node;
    size++;
}
// remove the node at the front of the list
template <typename T>
void MyList <T> ::removeFront()
{
    T *old = head;
    head = head->next;
    delete old;
    size--;
}
// return an iterator pointing to the head of the list (start)
template<typename T>
typename MyList<T>::iterator MyList<T>::begin()
{
	return iterator(head);
}
// return an iterator pointing to the end of the list (should be NULL because the iteration excludes the last element)
template<typename T>
typename MyList<T>::iterator MyList<T>::end()
{
	return iterator(NULL);
}
// constructor for iterator
template<typename T>
MyList<T>::iterator::iterator(T * newPtr)
{
    ptr = newPtr;
}
// use ++ to move the iterator to the next node
template<typename T>
typename MyList<T>::iterator MyList<T>::iterator::operator++()
{
    ptr = ptr->next;
    return *this;
}
// return the iterator itself
template<typename T>
typename MyList<T>::iterator MyList<T>::iterator::operator*()
{
    return *this;
}
// return true if the iterator is not pointing to the same node as the other iterator
template<typename T>
bool MyList<T>::iterator::operator!=(const iterator & other)
{
    return ptr != other.ptr;
}


template class MyList<HashNode>;
