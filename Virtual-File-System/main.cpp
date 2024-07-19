//============================================================================
// Name         : DS Assignment#2
// Author       : Mai Oudah
// Version      : 2.0
// Date Created : 17-03-2023
// Date Modified: 
// Description  : Virtual Filesystem - Main Program
//============================================================================

#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<exception>

#include "MyStack.h"
#include "MyQueue.h"
#include "MyVector.h"
#include "inode.h"
#include "vfs_tree.h"

using namespace std;

VFS_Tree myVFS_Tree;

void pwd();
void realpath(string file);
void cd(string to);
void ls(string command);
void mkdir(string folderName);
void touch(string fileName, string sizeInString);
void find(string name);
void mv(string fileName, string folderName);
void rm(string name);
void size(string path);
void emptybin();
void showbin();
void recover();

bool nameCheck(string name);


//=====================================
void listCommands()
{
	cout<<" ===================================================================================="<<endl
        <<" Welcome to the Virtual Filesystem!\n"<<endl
        <<" List of available Commands:"<<endl
		<<" pwd                     : Print full path to the current working directory"<<endl
		<<" realpath <filename>     : Print the absolute/full path of a given filename of a file within the current directory"<<endl
		<<" ls                      : List files and folders inside the current folder"<<endl
		<<" mkdir <foldername>      : Make a new directory/folder"<<endl
		<<" touch  <filename> <size>            : Create a new file"<<endl     
		<<" find <filename|foldername>          : Return the path of the file (or the folder) if it exists"<<endl
        <<" cd <filename>                       : Change directory"<<endl
		<<" mv <filename> <foldername>          : Move a file"<<endl
		<<" rm <filename|foldername>            : Remove a file or a folder"<<endl
		<<" size <filename|foldername>          : Print size of an file/folder"<<endl     
		<<" find <filename|foldername>          : Return the path of the file (or the folder) if it exists"<<endl
        <<" emptybin                            : Empty the trash"<<endl
		<<" showbin                 : Print the oldest file/folder of the bin"<<endl
		<<" recover                 : Recover the oldest file/folder form bin if path still exists"<<endl
		<<" help                    : Display the list of available commands"<<endl
		<<" exit                    : Exit the Program"<<endl
		<<" ====================================================================================\n"<<endl;
		
}



//=======================================
// main function
int main() {

	// VFS_Tree myVFS_Tree;

    listCommands();


    string user_input;
    string command;
	string params[3];
    do {
        params[0] = "";
        params[1] = "";
        params[2] = "";
		cout<<">";
		getline(cin,user_input);

		istringstream ss(user_input);
		int i = 0;
		while (ss >> command) {
			params[i] = command;
			i++;
		}
		
		try
		{
			if(command == "help")               listCommands();
            else if(params[0]=="pwd")           pwd();
            else if(params[0]=="realpath")      realpath(params[1]);
            else if(params[0]=="ls")            ls(params[1]);
            else if(params[0]=="mkdir")         mkdir(params[1]);
            else if(params[0]=="touch")         touch(params[1], params[2]);
            else if(params[0]=="cd")            cd(params[1]);
            else if(params[0]=="find")          find(params[1]);
            else if(params[0]=="mv")            mv(params[1], params[2]);
            else if(params[0]=="rm")            rm(params[1]);
            else if(params[0]=="size")          size(params[1]);
            else if(params[0]=="emptybin")      emptybin();
            else if(params[0]=="showbin")       showbin();
            else if(params[0]=="recover")       recover();
			else if(command == "exit")          break;
			else if(user_input=="")             continue;
			else                                cout<<"Invalid Command!"<<endl;
		}
		catch(exception &e)
		{
			cout<<"Exception: "<<e.what()<<endl;
		}
	} while(command!="exit");
    

    return EXIT_SUCCESS;
}

// -----------------------------------------------------------------
// define the needed methods to execute the operations in the system (pwd, realpath, ls, ...) below

void pwd(){
	cout << myVFS_Tree.pwd(myVFS_Tree.current()) << endl;
}

void realpath(string file){
	myVFS_Tree.realpath(file);
}

void cd(string to){
	myVFS_Tree.cd(to);
}

void ls(string command){
	if (command == "sort")
		myVFS_Tree.lsSort();
	else 
		myVFS_Tree.ls();
}

void mkdir(string folderName){
	if (nameCheck(folderName))
		myVFS_Tree.mkdir(folderName);
	else
		throw invalid_argument("Invalid name");
}

void touch(string fileName, string sizeInString){
	if (nameCheck(fileName)){
		int size = stoi(sizeInString);
		myVFS_Tree.touch(fileName, size);
	}else{
		throw invalid_argument("Invalid name");
	}
	
}

void find(string name){
	if (nameCheck(name)){

		myVFS_Tree.find(name);
	}else{
		throw invalid_argument("Invalid name");
	}
}
	
void mv(string fileName, string folderName){
	if (nameCheck(fileName) && nameCheck(folderName)){
		myVFS_Tree.mv(fileName, folderName);
	}else{
		throw invalid_argument("Invalid names");
	}
}

void rm(string name){
	// if (nameCheck(name))
		myVFS_Tree.rm(name);
	// else
	// 	throw invalid_argument("Invalid name");
}

void size(string path){
	cout << myVFS_Tree.size(path) << " bytes" << endl;
}

void emptybin(){
	myVFS_Tree.emptyBin();
}

void showbin(){
	myVFS_Tree.showBin();
}

void recover(){
	myVFS_Tree.recover();
}

bool nameCheck(string name){
	//File names should be alphanumeric only (i.e., comprises the letters A to Z, a to z, and the digits 0 to 9) without whitespaces or special characters, except the period “.” that can be used prior to file extensions.
	for (int i = 0; i < name.length(); i++){
		if (!isalnum(name[i]) && name[i] != '.' && name[i] == ' '){
			return false;
		}
	}
	return true;
}