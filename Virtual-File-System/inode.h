//============================================================================
// Name         : DS Assignment#2
// Author       : Mai Oudah
// Version      : 2.0
// Date Created : 01-04-2023
// Date Modified: 
// Description  : Virtual Filesystem - iNode class
//============================================================================

#include<iostream>
#include<string>
#include <ctime>
#include "MyVector.h"

using namespace std;

#ifndef INODE_H
#define INODE_H


class Inode
{
	private:
		string fname; //inode name (filename or folder name)
		int fsize; //file/folder size
		string date; //creation date
		bool isFile; //capture the type; true if this is a file, false if this is a folder/directory
		Inode* parent; //the parent directory
		MyVector<Inode*> children; //the container of children, if this inode is a folder

    friend class Position;
	friend class VFS_Tree;

	public:
		
		Inode(string name, int fSize, bool isFile, string date);
        ~Inode();

		string getFName() const;
    	int getFSize() const;
    	string getDate() const;
    	bool getIsFile() const;
    	Inode* getParent() const;
    	MyVector<Inode*>& getChildren();
		 
	
	
		//add any other necessary code and methods here
		bool isInTree;
		void inTree(bool inTree);
};

// #include "inode.cpp"

#endif
