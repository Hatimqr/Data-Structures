#include "Heap.h"
#include "dochashtable.h"

// for it to expand like a vector (wont be nessesary because the size of the heap is known)
void Heap::adjustSize()
{
	if(this->size==this->capacity -1)
	{
		HashNode **newArray = new HashNode*[capacity*2];
		for(int i=0; i<capacity; i++)
			newArray[i] = array[i];
		delete[] array;
		array = newArray;
		capacity = capacity*2;	
	}
}
// constructor
Heap::Heap(int capacity)
{
	this->array = new HashNode*[capacity];
	this->capacity = capacity;
	this->size = 0;
}
// special case destructor - loop through the array, set all pointers to NULL, and then delete the array itself.
// cannot mess with the node itself because that is the responsibility of the hash table.
Heap::~Heap()
{
	for (int i = 1; i <= size; i++)
	{
		array[i] = NULL;
	}
	delete[] array;
}

int Heap:: getSize()
{
	return size;
}

// standard insertion algorithm to the end and then sift up
void Heap:: insert(HashNode* key)
{
	adjustSize();
	++size;
	array[size] = key;
	siftup(size);
}
// return adress of the hashnode at the top of the list.
HashNode& Heap:: getMax()
{
	if (size == 0) throw out_of_range("Error. Heap is empty.");
	return *array[1];
}
// parent index
int Heap:: parent(int k)
{
	return k/2; 
}
// left index
int Heap:: left(int k)
{
	return k*2;
}
// right index
int Heap:: right(int k)
{
	return (k*2)+1;
}
void Heap:: siftup(int index)
{
	// take an index, compare it with the parent. if the parent is greater than the current, swap. repeat until head is reached or the condition is false. also swap index attributes of the node.
	int current = index;
	while (current>1 && array[parent(current)]->repetitions <= array[current]->repetitions){
		swap(array[parent(current)], array[current]);
		swap(array[parent(current)]->heapIndex, array[current]->heapIndex);
		current = parent(current);
	}
}