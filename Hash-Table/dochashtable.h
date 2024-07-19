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
// include additional header files as needed
#include <string>
#include <sstream>
#include <cctype>
#include "Heap.h"

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

//=============================================================================
class DocHASHTABLE
{
	private:
		MyList<HashNode>* buckets;	    //an array of Buckets, include your own Linked List Class called MyList
		Heap* MaxHeap;					//a MaxHeap to store the HashNodes in the HashTable
		int numTotal;					//number of total words in the table (consider the repeated words)
		int capacity;				    // The Capacity of HashTable
		// add more attributes as needed
		int hashMode;					//hash function number



	public:
		DocHASHTABLE(int capacity = 83939);			//constructor
		~DocHASHTABLE();				    //destructor
		long hashCode(string key); 			//use a hash function to generate a hash code for the provided key
		void select_hashFun(int choice = 5); 			    //choose one of the six implemented hash functions to construct the hash table		
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
		long hash5(string key);			//hash function 5 - FNV algorithm
		long hash6(string key);			//hash function 6 - Jerkins
		int compression(long key);		//compression function
		string cleanWord(string word);
};






#endif
