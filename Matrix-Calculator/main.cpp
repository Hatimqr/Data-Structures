//============================================================================
// Name         : DS Assignment#1
// Author       : Mai Oudah
// Version      : 1.0
// Date Created : 09-02-2023
// Date Modified: 
// Description  : Matrix Computation - Main Program
//============================================================================
#include<iostream>
#include<string>
#include<fstream>
#include<exception>
#include<sstream>
#include<iomanip>

#include "matcomp.h"
using namespace std;

//=====================================
void listCommands()
{
	cout<<" ===================================================================================="<<endl
        <<" Welcome to the Matrix Computation system!\n"<<endl
        <<" List of available Commands:"<<endl
		<<" import <file_name>    : Read a matrix from <filename>"<<endl
		<<" export <file_name>    : Write a matrix into <filename>"<<endl
		<<" add                   : Add 2 matrices A and B and store the result in matrix A"<<endl
		<<" multi-by-const <const> : Multiply a matrix by a constant and update the matrix"<<endl
		<<" multi-by-matrix        : Multiply a matrix by another matrix and return the resultant"<<endl     
		<<" display               : Display a matrix in the optimized structure"<<endl
		<<" help                  : Display the list of available commands"<<endl
		<<" exit                  : Exit the Program"<<endl
		<<" ====================================================================================\n"<<endl;
		
}

// define the needed methods to execute the operations in the system (import, export, add, ...)

//check if file is valid
bool filecheck(string filename, string mode){
	
	//when export check extension
	if(mode == "export"){
		int index = filename.find_first_of(".");
		string substring = filename.substr(index+1);
		if(substring == "txt")
			return true;
		else
			return false;
	}
	//when importing, check
	else{
		fstream file(filename);
		if (file)
			return true;
		else
			return false;
	}
	

}
//check if index exists
bool indexCheck(MatComp& matCompSys, char c){
	int index = (int)c - 64;
	int list_size = matCompSys.getListSize();
		//if within range
	if (index <= list_size && index > 0)			
		return true;
	else
		return false;
}

// check if parameter is an integer
bool integer(string str){
	for(int i = 0; i < str.length(); i++)
    {
        if(isdigit(str[i]) == false)
            return false;
    }
    return true;

}

// =======================================
// main function


int main()
{
	MatComp matCompSys;

matCompSys = MatComp();

	listCommands();
	string user_input;
	string command;
	string parameter;





	do
	{
		// cout << "number of matrices is: "<< matCompSys.getListSize()<< endl;
		getline(cin,user_input);
		
		// parse userinput into command and parameter(s)
		stringstream sstr(user_input);
		getline(sstr,command,' ');
		getline(sstr,parameter);

		LinkedMatrix *mat = new LinkedMatrix();
		matCompSys.importMatrix(*mat, "mat.txt");
		
		//add code as necessary
		
		
		
		
		
		
		if(command == "import"){
			
			//do this if input not valid
			if (!filecheck(parameter, "import"))
			{
				//3 tries to get input right
				for (int i = 0; i<3; i++){
					if (i < 2) cout << "Invalid input. please try again: ";
					cin >> parameter;
					if(filecheck(parameter, "import")){
						break;
				}
				cin.ignore();
				}
			}
			//do if input is valid
			if (filecheck(parameter, "import")){
				LinkedMatrix* matrix = new LinkedMatrix();
				matCompSys.importMatrix(*matrix, parameter);
				matCompSys.store(*matrix);
				cout << "Done! This is matrix '"<< matCompSys.getID(*matrix) << "'."<< endl;
			}
			else{ // exit if statement if invalid input
				cout << "Import failed. Enter Command." << endl;
			}
			
		}




		else if(command == "export"){
			char ID;
			
			// check if filename has a valid extention
			if (!filecheck(parameter, "export"))
			{
				//loop to give 3 tries;
				cout << "Invalid File name. Please try again: ";
				for (int i = 0; i < 3; i++)
				{
					
					cin >> parameter;
					if (filecheck(parameter, "export")){ 
						break;
					}	
					if(i < 2) cout << "Invalid filename. please try again: ";
					cin.ignore();
				}
			}
			//if parameter is true get the Index
			if (filecheck(parameter, "export"))
			{
				cout << "Please Provide matrix ID [A, B, C,...]: ";
				//another loop to give 3 tries
				for (int i = 0; i<3; i++){
					cin >> ID;
					if (indexCheck(matCompSys, ID)){
						break;
					}
					if(i < 2) cout << "Invalid ID. please try again: ";
					cin.ignore();
				}
			}
			//now both index and paramter are valid so call the function.
			if (indexCheck(matCompSys, ID))	
			{
				LinkedMatrix *outputfile = &matCompSys.getFromList(ID); 
				matCompSys.exportMat(*outputfile, parameter);
				cout << "Done! Exported Successfully as "<< parameter << endl;
			}
			else{
				cout << "Export failed. Enter Command." << endl;
			}
		}







		else if(command == "add"){
			char ID1, ID2;
			cout << "Please Provide the first matrix ID [A, B, C,...]: ";

			//check if first ID is valid
			for (int i = 0; i<3; i++){
				cin >> ID1;
				if (indexCheck(matCompSys, ID1)){
					break;
				}
				if(i < 2) cout << "Invalid ID. please try again: ";
				cin.ignore();
			}
			//If first ID is valid, check the second ID
			if (indexCheck(matCompSys, ID1))
			{
				cout << "Please Provide the second matrix ID [A, B, C,...]: ";
				for (int i = 0; i < 3; i++)
				{
					cin>>ID2;
					//if the 2nd ID is valid, call the function
					if (indexCheck(matCompSys, ID2))
					{
						LinkedMatrix* mat1 = &matCompSys.getFromList(ID1);
						LinkedMatrix* mat2 = &matCompSys.getFromList(ID2);
						matCompSys.add(*mat1, *mat2);
						cout << ID1 << "+" << ID2 << " is saved in " << ID1 << endl;
						cout << "Done!" << endl;
						break;
					}
					if(i < 2) cout << "Invalid input. please try again: ";
					cin.ignore();
				}
				// is second ID is not valid do nothing
				if (!indexCheck(matCompSys,ID2))
				{
					cout << "Invalid Input" << endl;
				}
				
			//if 1st index is not valid do nothing
			}else{
				cout << "Invalid input" << endl;
			}
		}






		
		else if(command == "multi-by-const"){
			char ID;
			//do if parameter is not valid
			if (!integer(parameter))
			{   // give 3 tries
				for (int i = 0; i < 3; i++)
				{
					cout << "Invalid Constant. Please try again: ";
					cin >> parameter;
					if (integer(parameter)){ 
						break;
					}	
					if(i < 2) cout << "Invalid Constant. please try again: ";
					cin.ignore();
				}
			}
			//if parameter is valid, get the ID
			if (integer(parameter))
			{
				cout << "Please Provide matrix ID [A, B, C,...]: ";
				//give 3 tries
				for (int i = 0; i<3; i++){
					cin >> ID;
					if (indexCheck(matCompSys, ID)){
						break;
					}
					if(i < 2) cout << "Invalid ID. please try again: ";
					cin.ignore();
				}
			}
			// if index is valid call the fucntion, else do nothing
			if (indexCheck(matCompSys, ID))	
			{
				LinkedMatrix *mat = &matCompSys.getFromList(ID);
				matCompSys.multi(*mat, stoi(parameter));
				cout<< "Done!" << endl;
			}
			else{
				cout << "Export failed. Enter Command." << endl;
			}
		}






		
		else if(command == "multi-by-matrix"){
			char ID1, ID2;
			cout << "Please Provide first matrix ID [A, B, C,...]: ";

			// 3 tries to get index 1
			for (int i = 0; i<3; i++){
				cin >> ID1;
				if (indexCheck(matCompSys, ID1)){
					break;
				}
				if(i < 2) cout << "Invalid input. please try again: ";
				cin.ignore();
			}
			//if index 1 is valid do this
			if (indexCheck(matCompSys, ID1))
			{
				cout << "Please Provide second matrix ID [A, B, C,...]: ";
				//3 tries to get index 2
				for (int i = 0; i < 3; i++)
				{
					cin>>ID2;
					if (indexCheck(matCompSys, ID2))
					{
						LinkedMatrix* Mat3 = new LinkedMatrix();
						matCompSys.multi(matCompSys.getFromList(ID1), matCompSys.getFromList(ID2), *Mat3);
						matCompSys.store(*Mat3);
						break;
					}
					if(i < 2) cout << "Invalid input. please try again: ";
					cin.ignore();
				} //if index 2 is invalid do nothing
				if (!indexCheck(matCompSys,ID2))
				{
					cout << "Invalid Input" << endl;
				}
				// if index 1 is invalid do nothing
			}else{
				cout << "Invalid input" << endl;
			}
		}






		else if(command == "display"){
			char ID;
			cout << "Enter ID of Matrix to display: ";
			//check if index is valid and give 3 tries
			for (int i = 0; i < 3; i++)
			{
				cin >> ID;
				if (indexCheck(matCompSys, ID))
				{
					matCompSys.display(matCompSys.getFromList(ID));
					break;
				}
				if(i < 2) cout << "Invalid input. please try again: ";
				cin.ignore();
			}
            if (!indexCheck(matCompSys, ID)) {
                cout << "Invalid Input." << endl;
            }
		}



		else if(command == "help")			listCommands();


		else if(command == "exit")			break;


		else 							cout<<"Invalid Command!"<<endl;

		fflush(stdin);

	}while(true);


	return EXIT_SUCCESS;
}

