//
//  main.cpp
//  Project1
//
//  Created by Jacob Courtney on 1/28/19.
//  Copyright © 2019 Jacob Courtney. All rights reserved.
//
#include <iostream>
using namespace std;

/*
 *SparseRow Class. contains 3 integers: row, col, and value, which stores the row and column and value of a SparseMatrix object
 *This class is meant to be used in an array, where multiple SparseRow objects can be stored to represent a full matrix,
 *without having to store common values
 */
class SparseRow {
    
    
protected:
    int row;//Row#
    int col;//Column#
    int value;//We will assume that all our values will be integers
    int index;//The index at which this SparseRow is stored in the array
public:
    SparseRow (); //default constructor;row=-1;col=-1;value=0
    SparseRow(int i, int r, int c, int v); //regular constructor: r = row, c = column, v = value
    void display();// print Row#, Column#, value in the following format: "<r> <c> <v>"
    
    //simply returns a row
    int getRow() {
        return row;
    };
    //sets the row
    void setRow(int r);
    //gets the column
    int getCol() {
        return col;
    };
    //sets the column
    void setCol(int c);
    //gets the value of this SparseRow
    int getValue() {
        return value;
    };
    //sets the value of this SparseRow
    void setValue(int v);
     // gets the index of this SparseRow
    int getIndex() {
        return index;
    };
    void setIndex(int i);
};

//SparseRow regular constructor, takes in r, c, and v and sets them equal to the appropriate values
SparseRow::SparseRow(int i, int r, int c, int v) {
    this->setCol(r);
    this->setRow(c);
    this->setValue(v);
    this->setIndex(i);
}

//Default Constructor, defaults row and col to -1, defaults the value to 0
//Generally, if a SparseRow object contains a value of 0, then there is a bug in the software
SparseRow::SparseRow() {
    this->setCol(-1);
    this->setRow(-1);
    this->setValue(0);
    this->setIndex(NULL);
}

/*
 *SparseMatrix class. contains 4 integers, noRows, noCols, commonValue and nonNonSparseValues
 *SparseMatrix also holds an array of SparseRows called myMatrix, which contains all of the values in
 *this matrix that are not equal to the common value. A SparseMatrix object is a condensed way to store a full
 *matrix. It achieves this by not storing any common values
 */
class SparseMatrix {
    
protected:
    int noRows; //Number of rows of the original matrix
    int noCols; //Number of columns of the original matrix
    int commonValue; //common value of this SparseMatrix
    int noNonSparseValues; //number of non sparse values in this SparseMatrix object
    SparseRow* myMatrix; //Array of SparseRows that contains info about the points in the array that are not the common value
    
public:SparseMatrix ();
    SparseMatrix (int n, int m, int cv, int noNSV); //regular constructor. takes in the number of rows and columns, the commonValue and the number of nonSparseValues
    SparseMatrix*Transpose (); //Transposes the matrix
    SparseMatrix*Multiply (SparseMatrix& M); //Multiplies two matrices together
    SparseMatrix*Add (SparseMatrix& M); //Adds two matrices together
    void display();//Display the sparse matrix
    void displayMatrix (); //Display the matrix in its original format
    void setSparseRow(int index, int r, int c,int v); //allows the user to change full rows at a time within the SparseMatrix
    SparseRow getSparseRow(int c); //returns the SparseRow stored at index c in myMatrix
    bool ifThereExistsANonSparseVariableAtRowCol(int r, int c);
};

//simply returns the SparseRow object stored at index c in myMatrix
SparseRow SparseMatrix::getSparseRow(int c) {
    return this->myMatrix[c];
};

/*allows the user to essentially just set a new row in myMatrix. becuase of the way that memory allocation works
 *with arrays and the new operator, it is possible to create new objects of the myMatrix array that are out of
 *bounds of what the user originally set as the size of myMatrix. nsv can basically be set to any number
 */
void SparseMatrix::setSparseRow(int index, int r, int c, int v) {
    this->myMatrix[index].setRow(r);
    this->myMatrix[index].setCol(c);
    this->myMatrix[index].setValue(v);
    this->myMatrix[index].setIndex(index);
};

//sets the value of the SparseRow
void SparseRow::setValue(int v) {
    this->value = v;
};

//sets the row of the SparseRow
void SparseRow::setRow(int r) {
    this->row = r;
};

//sets the column of the SparseRow
void SparseRow::setCol(int c) {
    this->col = c;
};

//sets the index of the SparseRow
void SparseRow::setIndex(int i) {
    this->index = i;
}
//default constructor for SparseMatrix. takes in the number of rows and columns, the commonValue and the number of nonSparseValues, and initializes myMatrix
SparseMatrix::SparseMatrix (int n, int m, int cv, int noNSV) {
    noRows = n;
    noCols = m;
    commonValue = cv;
    noNonSparseValues = noNSV;
    myMatrix = new SparseRow[noNSV];
};

//default constructor for myMatrix. initializes noRows, noCols, commonValue and noNonSparseValues to 0, and leaves myMatrix pointing to the null pointer
SparseMatrix::SparseMatrix () {
    noRows = 0;
    noCols = 0;
    commonValue = 0;
    noNonSparseValues = 0;
    myMatrix = nullptr;
};

bool SparseMatrix::ifThereExistsANonSparseVariableAtRowCol(int r, int c) {
    for (int i = 0; i < noNonSparseValues; i++) {
        if (this->getSparseRow(i).getRow() == r && this->getSparseRow(i).getCol() == c) {
            return true;
        }
    }
    return false;
};

//displays the single SparseRow in the following format: "<row> <col> <value>" and and endline
void SparseRow::display() {
    cout << this->getRow() << " " << this->getCol() << " " << this->getValue() << endl;
};

//transposes the matrix
SparseMatrix* SparseMatrix::Transpose() {
    
    //stores the temporary row, column and value inside of each iteration of the for loop below
    int r, c, v;
    
    //temp SparseMatrix object for return
    SparseMatrix* copy = new SparseMatrix(noRows,noCols,commonValue,noNonSparseValues);
    
    //this for loop initializes each SparseRow in myMatrix before use to make sure there is room for them
    for (int j = 0; j < noNonSparseValues; j++) {
        copy->getSparseRow(j) = getSparseRow(j);
    }
    
    //main for loop of this function. loops through all of the values in myMatrix and switches the row and column value
    for (int i = 0; i < noNonSparseValues; i++) {
        r = this->getSparseRow(i).getRow();
        c = this->getSparseRow(i).getCol();
        v = this->getSparseRow(i).getValue();
        copy->setSparseRow(i, c, r, v);
    }
    //returning the copy that has the switched row and column values
    return copy;
};

//multiplies two matrices together
SparseMatrix* SparseMatrix::Multiply(SparseMatrix &M) {
    
    SparseMatrix* copy = new SparseMatrix(noRows,noCols,commonValue,0);
    
    int firstOneRow, firstOneCol, secondOneRow, secondOneCol, side, current;
    firstOneRow = 0;
    firstOneCol = 0;
    secondOneRow = 0;
    secondOneCol = 0;
    current = 0;
    side = noRows-1;
    
    for (int i = 0; i < ((noRows-1)*(noCols-1)); i++) {
        
        //checking to see if i is 0 and if the matrix's side is 2 or less. required step in order to run properly on small matrices
        if (((noRows > 2) || (noCols > 2)) && (i == 0)) {
            i++;
        }
        
        for (int j = 0; j < noNonSparseValues; j++) {
            if ((firstOneCol == myMatrix[j].getCol() && firstOneRow == myMatrix[j].getRow()) && secondOneCol == M.myMatrix[j].getCol() && secondOneRow == M.myMatrix[j].getRow()) {
                current += (myMatrix[i].getValue()*M.getSparseRow(i).getValue());
            }
            firstOneCol++;
            secondOneRow++;
            
        }
        if (current != 0) {
            (*copy).myMatrix[i].setCol(secondOneCol);
            (*copy).myMatrix[i].setRow(firstOneRow);
            (*copy).myMatrix[i].setValue(current);
        }
        if (secondOneCol != side) {
            secondOneCol++;
        }
        else {
            firstOneRow++;
            secondOneCol = 0;
        }
    
}
    
    return copy;
};

//adds two matrices together
SparseMatrix* SparseMatrix::Add(SparseMatrix &M) {
    //creating a copy of the array
    SparseMatrix* copy = new SparseMatrix(noRows,noCols,commonValue,0);
    
    //starting values for the while loop and the value to be added once it is found
    int i = 0, j, valueToAdd;

    //whether the value has been found or not
    bool found;
    
    //boolean array so we dont have to instantiate a new bool every time
    bool* mArray = new bool[M.noNonSparseValues];
    
    //initializing all values in mArray
    for (int k=0; k < M.noNonSparseValues; k++) {
        mArray[k] = false;
    }
    
    //main while loop. loops through all non sparse values
    while (i < noNonSparseValues) {
        
        //reset j to 0 and found to false each iteration
        j = 0;
        found = false;
        
        //sets the row and column of the new one before its found
        (*copy).myMatrix[(*copy).noNonSparseValues].setRow(myMatrix[i].getRow());
        (*copy).myMatrix[(*copy).noNonSparseValues].setCol(myMatrix[i].getCol());
        
        //resetting valueToAdd
        valueToAdd = 0;
        
        //iterates through until either the value is found or we have gone through every entry in myMatrix
        while ((j < M.noNonSparseValues) && (!found)) {
            
            //checking the rows and columns of both matrices to see if they match,
            if ((myMatrix[i].getRow() == M.myMatrix[j].getRow()) &&
                (myMatrix[i].getCol() == M.myMatrix[j].getCol()) ) {
                
                //and if they do, then we set found to true, the value to valueToAdd, and also switch mArray[j] to true
                found = true;
                valueToAdd = M.myMatrix[j].getValue();
                mArray[j] = true;
                
            }
            //otherwise just keep going
            else j++;
        }
        
        //check to make sure that the two values dont equal the commonValue, otherwise we'll skip it
        if (myMatrix[i].getValue() + valueToAdd != commonValue) {
            (*copy).myMatrix[(*copy).noNonSparseValues++].setValue(myMatrix[i].getValue() + valueToAdd);
        }
        
        //increment i
        i++;
    }
    
    //adds the values to the copy's myMatrix
    for (int k=0; k < M.noNonSparseValues; k++) {
        if (!mArray[k]) {
            (*copy).myMatrix[(*copy).noNonSparseValues].setRow(myMatrix[k].getRow());
            (*copy).myMatrix[(*copy).noNonSparseValues].setCol(myMatrix[k].getCol());
            (*copy).myMatrix[(*copy).noNonSparseValues++].setValue(myMatrix[k].getValue());
        }
    }
    
    //returning the copy
    return copy;
};

//display method in SparseMatrix format. simply loops through myMatrix and calls display on each entry
void SparseMatrix::display() {
    for (int i = 0; i < this->noNonSparseValues; i++) {
        this->getSparseRow(i).display();
    }
};

//method to display the matrix in its original format
void SparseMatrix::displayMatrix() {
    
    //the current coordinate in the matrix that we will be comparing. it will be compared to every single entry
    //in the myMatrix array to see if it has the same row and col
    int currentRow = 0;
    int currentCol = 0;
    
    //looping through all of the values in the original matrix, which turns out to be noRows*noCols
    //(1 has to be subtracted from each of these values because c++ starts counting at 0) and checks them all against myMatrix
    for (int i = 0; i < ((noRows-1)*(noCols-1)); i++) {
        if (((noRows > 2) || (noCols > 2)) && (i == 0)) {
            i++;
        }
        
        //comparing the current row and col to each entry in myMatrix
        for (int j = 0; j < noNonSparseValues; j++) {
            //if the row and col match,
            if ((this->getSparseRow(j).getCol() == currentCol) && (this->getSparseRow(j).getRow() == currentRow)) {
                //then print the value and and a space
                cout << this->getSparseRow(j).getValue() << " ";
            }
            
            //if the current row and col do not match,
            else {
                //then print the common value and a space
                cout  << this->commonValue << " ";
            }
            
            //if at the end of the row, add an endl and reset current col
            if (currentCol == (this->noCols - 1)) {
                cout << endl;
                currentRow++;
                currentCol = 0;
            }
            //increment the current column if not at the end of a line
            else {
                currentCol++;
            }
        }
    }
};

//main method. the code to insert values into the matrices is here, as well as the calls to all of the methods above
int main () {
    
    //initializing some variables before we use them
    int n, m, cv, noNSV, index, value;
    SparseMatrix* temp;
    
    //reset index to 0
    index = 0;
    
    //prompts the user for input. the program needs the number of rows and columns, the common value and the number of non sparse values
    cin >> n >> m >> cv >> noNSV;
    
    //initializing the first SparseMatrix with the values entered by the user
    SparseMatrix* firstOne = new SparseMatrix(n, m, cv, noNSV);
    
    //this nested loop takes the input from the user and automatically assigns the row and column value of each
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            
            //taking input from the user
            cin >> value;
            
            //check to see if the input value is a common value or not
            if (value != cv) {
                
                //and if not then we add it to myMatrix and incremement which index that SparseRow is at
                (*firstOne).setSparseRow(index,i,j,value);
                index++;
            }
        }
    }
    
    //this process is exactly the same as the first one. please refer to the comments above
    cin >> n >> m >> cv >> noNSV;
    index = 0;
    
    SparseMatrix* secondOne = new SparseMatrix(n, m, cv, noNSV);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> value;
            if (value != cv) {
                (*secondOne).setSparseRow(index,i,j,value);
                index++;
            }
        }
    }
    
    //Statements to manipulate and print matrices
    cout << "First one in sparse matrix format" << endl;
    (*firstOne).display();
    cout << "First one in normal matrix format" << endl;
    (*firstOne).displayMatrix();
    cout << "Second one in sparse matrix format" << endl;
    (*secondOne).display();
    cout << "Second one in normal matrix format" << endl;
    (*secondOne).displayMatrix();
    cout << "After Transpose first one in normal format" << endl;
    temp = (*firstOne).Transpose();
    (*temp).displayMatrix();
    cout << "After Transpose second one in normal format" << endl;
    temp = (*secondOne).Transpose();
    (*temp).displayMatrix();
    cout << "Multiplication of matrices in sparse matrix form:" << endl;
    temp = (*secondOne).Multiply(*firstOne);
    (*temp).display();
    cout << "Addition of matrices in sparse matrix form:" << endl;
    temp = (*secondOne).Add(*firstOne);
    (*temp).display();
    
    
    return 0;

}
