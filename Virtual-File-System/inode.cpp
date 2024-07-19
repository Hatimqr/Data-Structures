#include "inode.h"
#include "MyStack.h"

Inode:: Inode(string name, int size, bool isFile, string date){
    //initialize an inode
    this->fname = name;
    this->fsize = size;
	this->date = date;
	this->isFile = isFile;
    this->parent = NULL; 
    children = MyVector<Inode*>();
    this->isInTree = true;
}
//recursively delete all children
Inode:: ~Inode(){
    for (int i = 0; i<children.size(); i++)
        delete children.at(i);
}

//getters
string Inode:: getFName() const { 
    return fname; 
}
int Inode::getFSize() const{ 
    return fsize;
}
string Inode::getDate() const{ 
    return date; 
}
bool Inode::getIsFile() const{ 
    return isFile; 
}
Inode* Inode::getParent() const { 
    return parent; 
}
MyVector<Inode*>& Inode::getChildren(){ 
    return children; 
}

//recursively set isInTree to true or false for subtree
void Inode:: inTree(bool inTree){
    MyStack<Inode*> NodeStack = MyStack<Inode*>(1000);
    Inode* current = this;
    NodeStack.push(current);

    while (!NodeStack.empty()){
        current = NodeStack.top();
        NodeStack.pop();
        
        current->isInTree = inTree;

        MyVector<Inode*>* children = &current->getChildren();
        for (int i = 0; i<children->size(); i++){
            NodeStack.push(children->at(i));
        }
    }

}

