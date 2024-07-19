//============================================================================
// Name         : DS Assignment#1
// Author       : Mai Oudah
// Version      : 1.0
// Date Created : 11-02-2023
// Date Modified:  
// Description  : Matrix Computation in C++ 
//============================================================================
#include<fstream>
#include<string>
#include<sstream>

#include "linkedmatrix.h"

#include<iostream>
using namespace std;
//=======================================
class MatComp
{
	private:
		LinkedMatrix* matrix_list; //the imported and generated matrices will be stored in this array

		//additions
        int numOfMatrices; //the number of matrices currently loaded in the program

	public:
        //constructor to initialize values
        MatComp(){
            matrix_list = NULL;
            numOfMatrices = 0;
        }
        // creates a matrix object from a file
		void importMatrix(LinkedMatrix& newMat, string filename){
            int numRows, numCols; 
            ifstream matrixfile(filename);
            //check if file is open
            if (matrixfile.is_open()){
                string line;
                //iterate through the lines
                while(getline(matrixfile, line)){
                    //get numrows
                    if(line.substr(0,4) == "Rows"){
                        numRows = stoi(line.substr(5));
                    }
                    //get numcols
                    else if(line.substr(0, 7) == "Columns"){
                        numCols = stoi(line.substr(8));
                    }
                    //get numnonzeros
                    else if(line.substr(0, 16) == "Non-ZeroElements"){
                        newMat.create(numRows, numCols);
                    }        
                    //get values to insert a node into the matrix           
                    else if (line.substr(0,1) == "("){
                        char dummy;
                        int row, col, value;
                        stringstream sstr(line);
                        sstr >> dummy >> row >> dummy >> col >> dummy >> dummy >> value;
                        newMat.insertElement(row,col,value);
                    }
                    else{
                        break;
                    }
                }  
            }
            matrixfile.close();

        }
        //multiply a matrix by a constant number    
		void multi(LinkedMatrix& Mat, int a){
            Node* pntr2 = Mat.colArray;
            //if  a = 0 remove all nodes
            if (a == 0)
            {
                for (int i = 0; i < Mat.getNumCols(); i++){
                    Node* pntrzero = &pntr2[i];
                    while (pntrzero->down != NULL)
                    {
                        Mat.removeElement(pntrzero->down->row, pntrzero->down->column);
                    }
                }
            }
            else
            {
                //iterate through column array
                for (int i = 0; i < Mat.getNumCols(); i++){
                    Node* pntr = &pntr2[i];
                    //iterate through linked list for each node in the array and multiply
                    while (pntr->down != NULL){
                        pntr = pntr->down;
                        pntr->value *= a;                    
                    }
                }
            }
            
            

        }
        //add 2 matrices
		void add(LinkedMatrix& Mat1, LinkedMatrix& Mat2){
            //dont do anything if dimensions dont allow for multiplication
            if(Mat1.numRows != Mat2.numRows || Mat1.numCols != Mat2.numCols){
                cout << "Dimensions do not allow for addition" << endl;
                return;
            }
            //get column index
            for (int c = 0; c<Mat1.getNumCols(); c++){
                //get row index
                for(int r = 0; r<Mat1.getNumRows(); r++){
                    // if mat1 value is zero at index, insert mat2 node (insert function protects against a zero value)
                    if (Mat1.getValue(r,c) == 0){
                        Mat1.insertElement(r,c, Mat2.getValue(r,c));
                    }
                    // if both matrices have values at the index, add values. check for zero value and insert/remove
                    else if(Mat1.getValue(r,c)>0 && Mat2.getValue(r,c)>>0){
                        int value = Mat1.getValue(r,c) + Mat2.getValue(r,c);
                        if(value != 0)
                            Mat1.insertElement(r,c,value);
                        else if(value == 0)
                            Mat1.removeElement(r,c);
                    }
                }
            }
            // display(Mat1);
        }    

        //matrix multiplication
		void multi(LinkedMatrix& Mat1, LinkedMatrix& Mat2, LinkedMatrix& Mat3){
            //check if dimensions allow multiplication
            if(Mat1.getNumCols() != Mat2.getNumRows()){
                cout << "Dimensions are not compatible with matrix multiplication" << endl;
                return;
            }
            // prepare matrix objects and initialize the value of the node to 0
            Node* mat1pntr = Mat1.rowArray; Node* mat2pntr = Mat2.colArray; 
            Mat3.create(Mat1.getNumCols(), Mat2.getNumRows());
            Node* mat3pntr = Mat3.colArray;
            int value = 0;

            // get indexe to insert with the first 2 loops
            for(int c = 0; c < Mat3.getNumCols(); c++){
                for(int r = 0; r < Mat3.getNumRows(); r++){
                    mat1pntr = &mat1pntr[r]; mat2pntr = &mat2pntr[c];
                    int value = 0;
                    //loop through row and column to perform multiplication and insert the value into mat3
                    for (int i = 0; i<Mat1.getNumCols(); i++){
                        value += Mat1.getValue(r, i) * Mat2.getValue(i,c);
                    }
                    Mat3.insertElement(r,c,value);
                }
            }
            display(Mat3);
        }
        // exports matrix to a file
    	void exportMat(LinkedMatrix& Mat, string filename){
            ofstream matrixFile(filename);
            //do the first 3 lines
            matrixFile << "Rows=" << Mat.getNumRows() << endl;
            matrixFile << "Columns=" << Mat.getNumCols() << endl;
            matrixFile << "Non-ZeroElements=" << Mat.numNonZeros << endl;

            //insert nodes in order of columns
            Node* colpntr = Mat.colArray;
            for(int c = 0; c<Mat.getNumCols(); c++){
                Node* pntr = &colpntr[c];
                while(pntr->down != NULL){
                    pntr = pntr->down;
                    matrixFile << "("<<pntr->row<<","<<pntr->column<<")="<<pntr->value<< endl;
                }
	        }
            matrixFile.close();

        }
        // call the display function of a matrix object
		void display(LinkedMatrix& Mat)     {Mat.display_mat();}

	//add any other necessary code here

		//store matrix objects in the libnked list
        void store(LinkedMatrix& mat){
            LinkedMatrix* head = this->matrix_list;
            //special case for the first matrix
            if (head == NULL){
                this->matrix_list = &mat;
            }
            // add to the end of the list
            else
            {
                while (head->next != NULL){
                    head = head->next;
                }
                head->next = &mat;
            } 
            numOfMatrices +=1;    
        }
        
        //iterate through the list to get a matrix object
        LinkedMatrix& getFromList(char c){
            int index = (int)c - 65;
            LinkedMatrix* pntr = matrix_list;
            for(int i = 0; i<index; i++){
                pntr = pntr->next;
            }
            return *pntr;
        }
        //returns size of linked list
        int getListSize(){
            return numOfMatrices;
        }

        char getID(LinkedMatrix& matrix){
            return (char)numOfMatrices+64;
        }
};

