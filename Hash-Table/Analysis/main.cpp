
//=================================================================================
// Name         : DS Assignment#3
// Author       : Mai Oudah
// Version      : 1.0
// Date Created : 25-April-2023
// Date Modified: 
// Description  : Starter Code for Word Count Wizard using HASH TABLE in C++
//=================================================================================
#include<iostream>
#include<cstdlib>
#include<sstream>


#include<string>
#include<fstream>
#include<vector>
#include<filesystem>


#include "dochashtable.h"

bool isPrime(int n){
	if (n <= 1) return false; // 1 is not prime
    for (int i = 2; i <= sqrt(n); i++) { // check from 2 to sqrt(n)
        if (n % i == 0) return false; // if n is divisible by i, n is not prime
    }
    return true; // n is prime if it's not divisible by any number between 2 and sqrt(n)
}

int getCapacity(string path){
	DocHASHTABLE hashTable;
	hashTable.import(path);
	int cap = hashTable.count_unique_words()*1.25;

	while(!isPrime(cap)){
		cap++;
	}
	return cap;

}




class FileAnalysis
{
public:
	string fileName;
	int uniqueWords;
	int capacity;
	int* collisionArray;

	FileAnalysis(string fileName, int uniqueWords, int capacity)
	{
		this->fileName = fileName;
		this->uniqueWords = uniqueWords;
		this->capacity = capacity;
		this->collisionArray = new int[6];
	}
	void output(fstream& fout){
		fout << fileName <<"," << uniqueWords << "," << capacity;

		for (int i = 0; i < 6; i++)
		{
			fout << "," << collisionArray[i];
		}
		fout << endl;
	}
	
};


using namespace std;

int main()
{
	DocHASHTABLE *myDocHASHTABLE = new DocHASHTABLE();

	vector<FileAnalysis*>* fileAnalysis = new vector<FileAnalysis*>();

	int counter = 0;
	
	string path = "test_files/";
	for (const auto& entry : std::filesystem::directory_iterator(path)) {
        string filename = entry.path().filename().string();

		cout << "file number: " << ++counter << "\t";
		
		int capacity = getCapacity(path+filename);
		cout << "capacity: " << capacity << endl;
		myDocHASHTABLE = new DocHASHTABLE(capacity);
		myDocHASHTABLE->import(path+filename);
		
		int* collisionArray = new int[6];

		for (int i = 1; i <= 6; i++)
		{
			
			delete myDocHASHTABLE;
			myDocHASHTABLE = new DocHASHTABLE(capacity);
			
			myDocHASHTABLE->select_hashFun(i);
			myDocHASHTABLE->import(path+filename);
			// cout << "imported" << endl;
			collisionArray[i-1] = myDocHASHTABLE->count_collisions();
		}
		

		fileAnalysis->push_back(new FileAnalysis(filename, myDocHASHTABLE->count_unique_words(), myDocHASHTABLE->capacity));
		fileAnalysis->back()->collisionArray = collisionArray;

    }

	fstream fout;
	fout.open("report.csv", ios::out);
	fout << "Filename,Unique Words,Table Capacity,Collisions 1,Collisions 2,Collisions 3,Collisions 4,Collisions 5,Collisions 6" << endl;

	for (auto i : *fileAnalysis)
	{
		i->output(fout);
	}
	return EXIT_SUCCESS;
}


// file reading is reading whitespaces as well