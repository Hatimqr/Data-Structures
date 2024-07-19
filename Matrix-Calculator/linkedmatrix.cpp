//============================================================================
// Name         : DS Assignment#1
// Author       : Mai Oudah
// Version      : 1.0
// Date Created : 14-02-2023
// Date Modified: 
// Description  : Linked List-based Matrix class for an optimized structure
//============================================================================

#include <iostream>
using namespace std;

class Node
{
	private:
		int row; //the row index
		int column; //the column index
		int value; //the value of the element
		Node* next; //pointer to the next node within the same row
		Node* down; //pointer to the next node within the same column

		// additions
		friend class LinkedMatrix;
        friend class MatComp;
		
	public:
		Node(int row, int column, int value) : row(row), column(column), value(value), next(NULL), down(NULL)
		{}

	//add any other necessary code here
        // colTravel Node
        Node(){
            row = 0;
            column = 0;
            value = 0;
            next = NULL;
            down = NULL;
        }
        // display function for nodes
        void display(){
            std::cout<<"("<<this->row<<","<<this->column<<")"<<"="<<this->value<<std::endl;
        }
		
};

class LinkedMatrix
{
	private:
		int numRows; //the number of rows
		int numCols; //the number of columns
        Node* rowArray;
		Node* colArray;
		LinkedMatrix* next;

		// my additions
        int numNonZeros;
		friend class MatComp;
	
	public:
		LinkedMatrix(){;
            this->numRows = 0;
            this->numCols = 0;
            this->numNonZeros = 0;
            this->rowArray = NULL;
            this->colArray = NULL;
            this->next = NULL;
        }

		void create(int numRows, int numCols){
            this->numRows = numRows;
            this->numCols = numCols;

            this->rowArray = new Node[numRows];
	        for (int r = 0; r < numRows; r++){
                this->rowArray[r] = Node(r,0,0); 
                 
	        }
            this->colArray = new Node[numCols];
	        for (int c = 0; c < numCols; c++){
                this->colArray[c] = Node(0, c, 0);
	        }
        };

		int getNumRows() const{return this->numRows;}; 
		int getNumCols() const{return this->numCols;}; 

		void display_mat() const{

            std::cout << "NumRows = " << this->numRows << "\t NumCols = " << this->numCols << "\t NumNonZero Elements = " << numNonZeros << std::endl;
            for(int c = 0; c<this->numCols; c++){
                Node *pntr = &colArray[c];
                while(pntr->down != NULL){
                    pntr->down->display();
                    pntr = pntr->down;
                }
            }
        }; 
		
        void insertElement(int Row_Indx, int Col_Indx, int value){
            Node *node = new Node(Row_Indx, Col_Indx, value);

            if (value == 0){
                return;
            }
            

            Node *rowTravel = &rowArray[Row_Indx];
            if (rowTravel->next == NULL || rowTravel->next->column > Col_Indx){
                node->next = rowTravel->next;
                rowTravel->next = node;
                ++numNonZeros;
            }
            else{
                rowTravel = rowTravel->next;
                while(rowTravel->next != NULL && rowTravel->next->column < Row_Indx){
                    rowTravel = rowTravel->next;
                    }
                if(rowTravel->column == node->column){
                    rowTravel->value = node->value;
                    delete node;
                    return;
                }
                node->next = rowTravel->next;
                rowTravel->next = node;
                ++numNonZeros;
            }

                Node *colTravel = &colArray[Col_Indx];
                if(colTravel->down == NULL || colTravel->down->row > Row_Indx){
                    node->down = colTravel->down;
                    colTravel->down = node;
                }
                else{
                    colTravel = colTravel->down;
                    while(colTravel->down != NULL && colTravel->down->row < Row_Indx){
                        colTravel = colTravel->down;
                    }
                    node->down = colTravel->down;
                    colTravel->down = node;
                }

        }      
        // removes element for given index
		void removeElement(int Row_Indx, int Col_Indx){
            //gets the row array index
            Node* traverser = rowArray[Row_Indx].next;
            Node* prev = NULL;

            // gets to where the required node is in the linked list for that index in the row array
            while(traverser != NULL && traverser->column < Col_Indx){
                prev = traverser;
                traverser = traverser->next;
            }
            // if the element does not exist, exit the function
            if (traverser == NULL || traverser->column != Col_Indx){
                return;
            }
            // if prev is null the element is a first node in the linked list
            if(prev == NULL){
                rowArray[Row_Indx].next = traverser->next;
            }
            else{ // else change the pointer to skip the node to be removed
                prev->next = traverser->next;
            }

            //removes pointer in the col array in the same way
            traverser = colArray[Col_Indx].down;
            prev = NULL;
            while(traverser->row != Row_Indx){
                prev = traverser;
                traverser = traverser->down;
            }
            if(prev == NULL){
                colArray[Col_Indx].down = traverser->down;
            }
            else{
                prev->down = traverser->down;
            }
            // after pointers are released, delete the removed node and deiterate the number of non-zero elements
            delete traverser;
            --numNonZeros;
            traverser = NULL;

        };
		
        // destructor deletes each node and then deletes the row and column arrays
        ~LinkedMatrix(){
            for(int i = 0; i<numCols; i++){
                Node* below = colArray[i].down;
                while (below != NULL){
                    Node *toRemove = below;
                    below = below->down;
                    delete toRemove;
                    toRemove = NULL;
                }
            }
            delete[] rowArray;
            delete[] colArray;
            delete this;
        }; 
    

	//add any other necessary code here
        // gets value at an index in a matrix object. if the node doesnt exist, returns 0.
        int getValue(int r, int c){
            Node* coltrav = &colArray[c];
            while (coltrav->down != NULL){
                if (coltrav->down->row == r){
                    return coltrav->down->value;
                }
                coltrav = coltrav->down;
            }
            return 0;   
        }

	};

