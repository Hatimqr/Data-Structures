#include <iostream>
#include <exception>
#include <string>



#ifndef Heap_H
#define Heap_H

class HashNode;
using namespace std;



class Heap
{
	private:
		HashNode **array;
		int capacity;
		int size;
	public:
		Heap(int capacity = 10);
		~Heap();
		int getSize();
		void insert(HashNode* key);
		HashNode& getMax();
		int parent(int k);
		int left(int k);
		int right(int k);
		void siftup(int index);
	private:
		friend class DocHASHTABLE;
		void adjustSize(); //A method that doubles the size of the internal array when called. (Code already given)
};

#endif