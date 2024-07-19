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

#endif