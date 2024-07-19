
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


#include "dochashtable.h"

//==========================================================
void listCommands()
{
	cout<<"\n ==================================================================="<<endl
        <<" Welcome to the Word Count Wizard!"<<endl<<endl
        <<" List of available Commands:"<<endl
        <<" import <path>           :Import a TXT file"<<endl
        <<" select_hashFun          :Choose a hash function"<<endl
		<<" count_collisions        :Print the number of collisions"<<endl
		<<" count_unique_words      :Print the number of unique words"<<endl
		<<" count_words             :Print the the total number of words"<<endl
		<<" find_freq <word>        :Search for a word and return its frequency"<<endl
		<<" find_max                :Print the word with the highest frequency"<<endl
		<<" exit                    :Exit the program"<<endl
		<<" ===================================================================\n"<<endl<<endl
		<<" Please Provide the Path to the TXT file you wish to Anlayze:"<<endl;
}

void help(){
	cout<<"\n ==================================================================="<<endl
        <<" List of available Commands:"<<endl
        <<" import <path>           :Import a TXT file"<<endl
        <<" select_hashFun          :Choose a hash function"<<endl
		<<" count_collisions        :Print the number of collisions"<<endl
		<<" count_unique_words      :Print the number of unique words"<<endl
		<<" count_words             :Print the the total number of words"<<endl
		<<" find_freq <word>        :Search for a word and return its frequency"<<endl
		<<" find_max                :Print the word with the highest frequency"<<endl
		<<" exit                    :Exit the program"<<endl
		<<" ===================================================================\n"<<endl;
}
//==========================================================

// to be completed with any necessary method definitions



bool isPrime(int n){
	if (n <= 1) return false; // 1 is not prime
    for (int i = 2; i <= sqrt(n); i++) { // check from 2 to sqrt(n)
        if (n % i == 0) return false; // if n is divisible by i, n is not prime
    }
    return true; // n is prime if it's not divisible by any number between 2 and sqrt(n)
}
// to get the size of the hashtable to be used in the constructor
int getCapacity(string path){
	DocHASHTABLE hashTable;
	hashTable.import(path);
	int cap = hashTable.count_unique_words()*1.25;

	while(!isPrime(cap)){
		cap++;
	}
	return cap;

}

//==========================================================
// main function
int main()
{
	DocHASHTABLE* myDocHASHTABLE;

	string user_input;
	string command;
	string argument;

	//keeps the path and capacity constant until the file is changed
	string path;
	int capacity;

	// get the path of the file. dont allow user to proceed until a valid path is entered
	listCommands();
	while (true){
		cout << ">";
		getline(cin,path);
		if (ifstream(path).fail())
			cout << "Error. File could not be opened. Please try again." << endl;
		else
			break;
	}
		
	capacity = getCapacity(path);
	myDocHASHTABLE = new DocHASHTABLE(capacity);
	cout << "processing file..." << endl;
	myDocHASHTABLE->import(path);
	cout << "The number of collisions is: " << myDocHASHTABLE->count_collisions() << endl
		 << "The number of unique words is: " << myDocHASHTABLE->count_unique_words() << endl
		 << "The total number of words is: " << myDocHASHTABLE->count_words() << endl << endl;
	
	
	help();
	while(true)
	{
		try
		{
			cout<<">";
			getline(cin,user_input);
			stringstream sstr(user_input);
			getline(sstr,command,' ');
			getline(sstr,argument);

			// if import, get the path and capacity and create a new hashtable
			if(command =="import" || command == "i"){ 
				capacity = getCapacity(argument);
				delete myDocHASHTABLE;
				myDocHASHTABLE = new DocHASHTABLE(capacity);
				path = argument;
				myDocHASHTABLE->import(path);

				cout << "Done!" << endl << endl
					<< "The number of collisions is: " << myDocHASHTABLE->count_collisions() << endl
					<< "The number of unique words is: " << myDocHASHTABLE->count_unique_words() << endl
					<< "The total number of words is: " << myDocHASHTABLE->count_words() << endl << endl << endl;
				
			}
			// if select_hashFun, get the hash function and create a new hashtable.
			// give the user 3 tries to enter a valid input
			else if(command =="select_hashFun" || command == "s"){
				cout << "Enter the Hash Function ID: [1, 2, 3, 4, 5, 6]: " << endl << ">";
				for (int i = 0; i < 3; i++){
					cin >> argument;
					if (argument == ""|| argument == "1" || argument == "2" || argument == "3" || argument == "4" || argument == "5" || argument == "6"){
						break;
					}
					else{
						if (i == 2){
							cin.ignore();
							cin.clear();
							throw invalid_argument("Error. Invalid Input.");
						} 
						cout << "Invalid Input! Please try again: " << endl << ">";
					}
				}
				// if a valid input is entered, create a new hashtable with the new hash function
				delete myDocHASHTABLE;
				myDocHASHTABLE = new DocHASHTABLE(capacity);
				//if user enters a number 1-6, use that hash function. otherwise, use the default hash function
				if (argument != ""){
					myDocHASHTABLE->select_hashFun(stoi(argument));
					cout << "Hash Function " << argument << " has been chosen!" << endl << endl; 
				}
				else{
					myDocHASHTABLE->select_hashFun();
					cout << "The default Hash Function has been chosen!" << endl << endl;
				}
				// import and display the file again with the new hash function
				myDocHASHTABLE->import(path);
				cout << "The number of collisions is: " << myDocHASHTABLE->count_collisions() << endl
					<< "The number of unique words is: " << myDocHASHTABLE->count_unique_words() << endl
					<< "The total number of words is: " << myDocHASHTABLE->count_words() << endl << endl;
				cin.ignore();
				cin.clear();


			}
			// if count_collisions, count_unique_words, or count_words, display the corresponding value
			else if(command =="count_collisions"|| command == "c") {
				cout << "The number of collisions is: " << myDocHASHTABLE->count_collisions() << endl; 					
			}
			else if(command =="count_unique_words"|| command == "u") {
				cout << "The number of unique words is: " << myDocHASHTABLE->count_unique_words() << endl;      
			}
			else if(command =="count_words"|| command == "w") {
				cout << "The total number of words is: " << myDocHASHTABLE->count_words() << endl;         					
			}
			// if find freq, take the argument, clean it, and display the frequency of the word
			else if(command == "find_freq"|| command == "f") {
				if (argument == "") throw invalid_argument("Error. Invalid Input.");
				string cleanedWord = myDocHASHTABLE->cleanWord(argument);
				string freq = to_string(myDocHASHTABLE->find_freq(cleanedWord));
				cout << "The frequency of the word '" << argument << "' is: " << freq << endl;        	
			}
			// if find_max, display the word with the highest frequency. top of heap
			else if(command == "find_max"|| command == "m") {
				cout << "The Word with the highest frequency is: " << myDocHASHTABLE->find_max() << endl;
			}
			else if(command == "help") {
				help();			
			}
			else if(command == "exit" or command == "quit") {
				break;
			}
			else{
				cout<<"Invalid command !!!"<<endl;
			}
		}
		// catch exceptions
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
		// clear the argument string
		argument = "";
		
		
		
	}
	return EXIT_SUCCESS;
}


