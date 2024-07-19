//============================================================================
// Name         : DS Assignment#2
// Author       : Mai Oudah
// Version      : 2.0
// Date Created : 05-04-2023
// Date Modified: 
// Description  : Virtual Filesystem - Tree class
//============================================================================

#include<iostream>
#include<string>
#include <ctime>

#include "MyVector.h" //create this header file where you define the vector class
#include "MyStack.h" //create this header file where you define the stack class
#include "MyQueue.h" //create this header file where you define the queue class
#include "inode.h"

using namespace std;

#ifndef VFS_TREE_H
#define VFS_TREE_H

class Position
{
	private:
		Inode* inode;
		Position(Inode* inode);
		Position();

		//give access because the constructor is private
		friend class VFS_Tree;
        friend class MyVector<Position>;
		friend class MyStack<Position>;
		friend class MyQueue<Position*>;
		
	public:
		~Position();
		Position parent() const;
		bool isRoot() const;
    	bool isExternal() const;
		MyVector<Position>* childrenPositions() const;

		//getter methods
		string getName()const;
		int getFileSize()const;
		bool isFile();
		string getDate()const;

		//operations
		void addNode(Inode* newFile);
		void displayNode();
		Position* removeChild(string name);
		bool checkUniqueName(string name, bool isFile);

};

//=============================================================================
class VFS_Tree
{
	private:
		Position* rootNode;  //the root inode
		Position* currentNode;  //the current inode
		Position* previousNode; // the previous inode
		int n; //number of inodes in the tree
		MyQueue<Position*> bin; // the bin queue to store removed inodes

	public:
		VFS_Tree(); 
		~VFS_Tree(); 
		
        bool empty() const; // check if the tree is empty
        Position* root() const; // returns the position to the root inode
        Position* current() const; // returns the position to the current inode

        Position* find(string name) const;
        void touch(string filename, int size); 
        void mkdir(string foldername); 
        void ls(); 
		void lsSort(); 
		void cd(string arg); 
        void realpath(string name) const; 
        string pwd(Position* current) const; 
        void mv(string filename, string foldername); 
        void rm(string name); 
        void emptyBin(); 
        void showBin(); 
        void recover(); 
		int size(string path);
        
		//add any other necessary code and additional supporting methods here to achieve the capabilities of the system
		Position* findHelper(string name, Position pos)const;

		string getDate(); // get current date and time
		void writefile(string filename);
		void writeHelper(Position* pos, ofstream& myfile);
		void addNode(string name, int size, bool isFile, string date);


		void readfile(string filename);
};

#endif
