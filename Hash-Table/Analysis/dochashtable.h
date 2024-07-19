//=================================================================================
// Name         : DS Assignment#3
// Author       : Mai Oudah
// Version      : 1.0
// Date Created : 25-April-2023
// Date Modified: 
// Description  : Word Count Wizard - Hash Table Class in C++ 
//=================================================================================

#ifndef DocHASHTABLE_H
#define DocHASHTABLE_H

#include<iostream>
#include <algorithm>
#include "MyList.h"
#include<fstream>

#include <string>
#include <sstream>
#include <cctype>


using namespace std;

class HashNode
{
	private:
		long key; // hash code of the word
		int repetitions; //number of repetitions of the word
		string word; //the word itself
		int heapIndex; //index of the node in the heap
		HashNode* next; //pointer to the next node

	public:
		//define and implement the constructor 
		HashNode(long key, string word, int repetitions = 1);
		friend class DocHASHTABLE;
		friend class MyList<HashNode>;
		friend class Heap;
};

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
		bool find(string word);
	private:
		friend class DocHASHTABLE;
		void adjustSize(); //A method that doubles the size of the internal array when called. (Code already given)
};





//=============================================================================
class DocHASHTABLE
{
	private:
		MyList<HashNode>* buckets;	    //an array of Buckets, include your own Linked List Class called MyList
		Heap* MaxHeap;					//a MaxHeap to store the HashNodes in the HashTable
		int numTotal;					//number of total words in the table (consider the repeated words)
						    // The Capacity of HashTable
		// add more attributes as needed
		int hashMode;					//hash function number
        int count;



	public:
        int capacity;
		DocHASHTABLE(int capacity = 83939);			//constructor
		~DocHASHTABLE();				    //destructor
		long hashCode(string key); 			//use a hash function to generate a hash code for the provided key
		void select_hashFun(int choice = 1); 			    //choose one of the six implemented hash functions to construct the hash table		
		int import(string path); 			//Load a TXT file to the HashTable
		int count_collisions();				//return the number of collisions in the HashTable
		int count_unique_words();			//return the number of unique words in the laoded text
		int count_words();	                //return the total count of words in the laoded text
		int find_freq(string word);		    //return the frequency of the provided word, if it exists. Otherwise, return zero.
		string find_max();  				//return the word with the highest frequency

		// add more methods as needed	
		void insert(string word);		//insert a node in the hash table and the heap
		
		//hash functions
		long hash1(string key);			//hash function 1 - summation
		long hash2(string key);			//hash function 2 - polinomial
		long hash3(string key);			//hash function 3 - cycle-shift
		long hash4(string key);			//hash function 4 - djb2 algorithm
		long hash5(string key);			//hash function 5 -
		long hash6(string key);			//hash function 6 -
		int compression(long key);		//compression function
		string cleanWord(string word);


};


HashNode::HashNode(long key, string word, int repetitions){
    this->key = key;
    this->repetitions = repetitions;
    this->word = word;
    this->next = NULL;
}

DocHASHTABLE::DocHASHTABLE(int capacity){
    this->capacity = capacity;
    this->buckets = new MyList<HashNode>[capacity];
    this->MaxHeap = new Heap(capacity);
    this->numTotal = 0;
    this->hashMode = 1;

    this->count = 0;

}

DocHASHTABLE::~DocHASHTABLE(){
    delete MaxHeap;
    delete[] buckets;
}

long DocHASHTABLE::hashCode(string key){
    switch (hashMode)
    {
    case 1:
        return hash1(key);
    case 2:
        return hash2(key);
    case 3:
        return hash3(key);
    case 4:
        return hash4(key);
    case 5:
        return hash5(key);
    case 6:
        return hash6(key);
    default:
        return hash1(key);
    }
}

void DocHASHTABLE::select_hashFun(int choice){
    this->hashMode = choice;

}

int DocHASHTABLE::import(string path){
    



    ifstream fin(path);
    if (fin.is_open()){
        string word;
        while (fin >> word){ // get strings seperated by whitespaces
            word = cleanWord(word); // clean the word
            if (word.length()>0){ // check if string is empty
                insert(word);
                ++numTotal; // increament total number of words
            }
        }
    }
    else{
        cout << "Error opening file." << endl;
    }
    fin.close();
}

int DocHASHTABLE::count_collisions(){
    int collisions = 0;
    for (int i = 0; i < capacity; i++){
        int bucketSize = buckets[i].getSize();
        if (bucketSize > 1) // if there are more than one elements in the bucket, there is a collision
            collisions += (bucketSize-1); //-1 because the first element is not a collision
    }
    return collisions;
}

int DocHASHTABLE::count_unique_words(){
    return MaxHeap->getSize();
}

int DocHASHTABLE::count_words(){
    return numTotal;
}

void DocHASHTABLE::insert(string word){
    
    int key = compression(hashCode(word)); // get hashcode
    if (key < 0) key *= -1; // make sure key is positive

    MyList<HashNode>* bucket = &buckets[key];
    for (auto it : *bucket){ // check if word is already in hashtable
        HashNode* node = it.ptr;
        if (node->word == word){ // if the word is found in the hashtable, increment its value
            node->repetitions++; // increment repetitions in hashtable
            MaxHeap->siftup(node->heapIndex); // adjust the heap
            return;
        }
    }
    // if not in hashtable, add it
    HashNode* node = new HashNode(key, word);
    node->heapIndex = MaxHeap->getSize()+1;
    buckets[key].addFront(node);
    MaxHeap->insert(node);
}   

int DocHASHTABLE:: find_freq(string word){
    int key = hashCode(word);
    MyList<HashNode>* bucket = &buckets[key];
    for (auto it : *bucket){ // check if word is already in hashtable
        HashNode* node = it.ptr;
        if (node->word == word){ // if the word is found in the hashtable, increment its value
            return node->repetitions;
        }
    }
    return 0;
}

string DocHASHTABLE:: find_max(){
    return MaxHeap->getMax().word;
}


long DocHASHTABLE:: hash1(string word){
    long hash = 0;
    for (char c : word){
        hash+=(int)c;
    }
    return hash;
}

long DocHASHTABLE:: hash2(string word){
    long hash = 0;
    int m = word.length();
    int a = 3;
    for (char c : word){
        hash+=((int)c*pow(a,m));
        m--;
    }
    return hash;
}

long DocHASHTABLE:: hash3(string word){
    unsigned long hash = 0;

    for (char c : word){
        c = c << 5 | c >> 11;
        hash+=(unsigned int)c;
    }
    return hash;
}

long DocHASHTABLE:: hash4(string word){ // make this the djb2 hash
    unsigned long hash = 5381;
    for (char c : word) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

long DocHASHTABLE:: hash5(string word){ // fnv hash function
    const unsigned int fnv_prime = 0x811C9DC5;
	unsigned int hash = 0;

	for (char c : word) {
        hash *= fnv_prime;
        hash ^= c;
    }
	return hash;
}

long DocHASHTABLE:: hash6(string word){ // jenkins one at a time hash function
    unsigned long hash = 0;
    for (char c : word) {
        hash = (hash << 4) + c;
        unsigned long g = hash & 0xF0000000L;
        if (g != 0) {
            hash ^= g >> 24;
        }
        hash &= ~g;
    }
    return hash;
}

int DocHASHTABLE:: compression(long hash){
    if (hash < 0) hash *= -1; // make sure key is positive
    int a = 3;
    int b = 5;
    return (a*hash + b) % capacity;
}


string DocHASHTABLE:: cleanWord(string word){
    string chars_to_remove = ".,\!?;";
    for (char c : chars_to_remove){ // remove punctuation
        while (word.back() == c)
            word.pop_back();
    }
    transform(word.begin(), word.end(), word.begin(), ::tolower); // convert to lowercase
    return word;
}



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

Heap::Heap(int capacity)
{
	this->array = new HashNode*[capacity];
	this->capacity = capacity;
	this->size = 0;
}

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

void Heap:: insert(HashNode* key)
{
	adjustSize();
	++size;
	array[size] = key;
	siftup(size);
}

HashNode& Heap:: getMax()
{
	if (size == 0) throw out_of_range("Error. Heap is empty.");
	return *array[1];
}

int Heap:: parent(int k)
{
	return k/2; 
}

int Heap:: left(int k)
{
	return k*2;
}

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


#endif
