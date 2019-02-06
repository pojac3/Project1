//
//  main.cpp
//  Project1
//
//  Created by Jacob Courtney on 1/28/19.
//  Copyright © 2019 Jacob Courtney. All rights reserved.
//
#include <iostream>
using namespace std;
//define all your classes here (as given above)

class SparseRow {
protected:
    int row;//Row#
    int col;//Column#
    int value;//We will assume that all our values will be integers
public:
    SparseRow (); //default constructor;row=-1;col=-1;value=0
    SparseRow(int r, int c, int v);
    void display();// print Row#, Column#, value
    
    //other methods that are necessary such as get and set
    int getRow() {
        return row;
        
    };
    void setRow(int r);
    int getCol() {
        return col;
        
    };
    void setCol(int c);
    int getValue() {
        return value;
    };
    void setValue(int v);
};

SparseRow::SparseRow(int r, int c, int v) {
    this->setCol(r);
    this->setRow(c);
    this->setValue(v);
}


SparseRow::SparseRow() {
    this->setCol(-1);
    this->setRow(-1);
    this->setValue(0);
}

class SparseMatrix {
    
protected:
    int noRows; //Number of rows of the original matrix
    int noCols; //Number of columns of the original matrix
    int commonValue; //read from input
    int noNonSparseValues;
    SparseRow* myMatrix; //Array
    
public:SparseMatrix ();
    SparseMatrix (int n, int m, int cv, int noNSV);
    SparseMatrix*Transpose (); //Matrix Transpose
    SparseMatrix*Multiply (SparseMatrix& M);
    SparseMatrix*Add (SparseMatrix& M);
    void display();//Display the sparse matrix
    void displayMatrix (); //Display the matrix in its original format
    void setRow(int nsv, int r, int c,int v);
    SparseRow getSparseRow(int c);
    void convert();
    
    //other methods that are necessary such as get and set
    
};

SparseMatrix::SparseMatrix (int n, int m, int cv, int noNSV) {
    noRows = n;
    noCols = m;
    commonValue = cv;
    noNonSparseValues = noNSV;
    myMatrix = new SparseRow[noNSV];
};
SparseMatrix::SparseMatrix () {
    noRows = 0;
    noCols = 0;
    commonValue = 0;
    noNonSparseValues = 0;
    myMatrix = nullptr;
}
//write the methods after the class definition

void SparseRow::display() {
    cout << this->getRow() << " " << this->getCol() << " " << this->getValue() << endl;
};

SparseMatrix* SparseMatrix::Transpose() {
    //temp SparseMatrix object for return
    int r, c, v;
    SparseMatrix* copy = new SparseMatrix(this->noRows,this->noCols,this->commonValue,0);
    for (int j = 0; j < noNonSparseValues; j++) {
        copy->getSparseRow(j) = getSparseRow(j);
    }
    
    for (int i = 0; i < noNonSparseValues; i++) {
        r = this->getSparseRow(i).getRow();
        c = this->getSparseRow(i).getCol();
        v = this->getSparseRow(i).getValue();
        copy->setRow(i, c, r, v);
    }
    return copy;
};

SparseMatrix* SparseMatrix::Multiply(SparseMatrix &M) {
    
    SparseMatrix* copy = new SparseMatrix(noRows,noCols,commonValue,0);
    
    int firstOneRow, firstOneCol, secondOneRow, secondOneCol, side, current;
    firstOneRow = 0;
    firstOneCol = 0;
    secondOneRow = 0;
    secondOneCol = 0;
    current = 0;
    side = noRows;
    
    for (int i = 0; i < ((noRows-1)*(noCols-1)); i++) {
        
        //checking to see if i is 0 and if the matrix's side is 2 or less. required step in order to run properly on small matrices
        if (((noRows > 2) || (noCols > 2)) && (i == 0)) {
            i++;
        }
        for (int j = 0; j < side-1; j++) {
            if ((firstOneCol == myMatrix[i].getCol() && firstOneRow == myMatrix[i].getRow()) && secondOneCol == M.myMatrix[i].getCol() && secondOneRow == M.myMatrix[i].getRow()) {
                current += (myMatrix[i].getValue()*M.getSparseRow(i).getValue());
            }
            firstOneCol++;
            secondOneRow++;
        }
        if (current != 0) {
            (*copy).myMatrix[i].setCol(secondOneCol);
            (*copy).myMatrix[i].setRow(firstOneRow);
            (*copy).myMatrix[i].setValue(current);
        if (secondOneCol != side-1) {
            secondOneCol++;
        }
        else {
            firstOneRow++;
            secondOneCol = 0;
        }
    }
}
    
    return copy;
};

SparseMatrix* SparseMatrix::Add(SparseMatrix &M) {
    //creating a copy of the array
    SparseMatrix* copy = new SparseMatrix(noRows,noCols,commonValue,0);
    
    //starting values for the while loop and the value to be added once it is found
    int i = 0, j, valueToAdd;

    
    //whether the value has been found or not
    bool found;
    
    //boolean array so we dont have to instantiate a new one every time
    bool* mArray = new bool[M.noNonSparseValues];
    for (int k=0; k < M.noNonSparseValues; k++) {
        mArray[k] = false;
    }
    
    while (i < noNonSparseValues) {
        j = 0;
        found = false;
        (*copy).myMatrix[(*copy).noNonSparseValues].setRow(myMatrix[i].getRow());
        (*copy).myMatrix[(*copy).noNonSparseValues].setCol(myMatrix[i].getCol());
        valueToAdd = 0;
        while ((j < M.noNonSparseValues) && (!found)) {
            if ((myMatrix[i].getRow() == M.myMatrix[j].getRow()) &&
                (myMatrix[i].getCol() == M.myMatrix[j].getCol()) ) {
                found = true;
                valueToAdd = M.myMatrix[j].getValue();
                mArray[j] = true;
            }
            else j++;
        }
        if (myMatrix[i].getValue() + valueToAdd != 0) {
            (*copy).myMatrix[(*copy).noNonSparseValues++].setValue(myMatrix[i].getValue() + valueToAdd);
        }
        i++;
    }
    
    for (int k=0; k < M.noNonSparseValues; k++) {
        if (!mArray[k]) {
            (*copy).myMatrix[(*copy).noNonSparseValues].setRow(myMatrix[k].getRow());
            (*copy).myMatrix[(*copy).noNonSparseValues].setCol(myMatrix[k].getCol());
            (*copy).myMatrix[(*copy).noNonSparseValues++].setValue(myMatrix[k].getValue());
        }
    }
    
    return copy;
};

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
SparseRow SparseMatrix::getSparseRow(int c) {
    return myMatrix[c];
};

void SparseMatrix::setRow(int nsv, int r, int c, int v) {
    this->myMatrix[nsv].setRow(r);
    this->myMatrix[nsv].setCol(c);
    this->myMatrix[nsv].setValue(v);
};
void SparseRow::setValue(int v) {
    this->value = v;
};
void SparseRow::setRow(int r) {
    this->row = r;
};

void SparseRow::setCol(int c) {
    this->col = c;
};


int main () {
    
    int n, m, cv, noNSV, nsv, value;
    nsv = 0;
    SparseMatrix* temp;
    
    cin >> n >> m >> cv >> noNSV;
    SparseMatrix* firstOne = new SparseMatrix(n, m, cv, noNSV);
    
    //Write the Statements to read in the first matrix
    //write code to put the rows, columns and values into the matrix here
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> value;
            if (value != cv) {
                (*firstOne).setRow(nsv,i,j,value);
                nsv++;
            }
        }
    }
    
    cin >> n >> m >> cv >> noNSV;
    nsv = 0;
    
    SparseMatrix* secondOne = new SparseMatrix(n, m, cv, noNSV);
    //Write the Statements to read in the second matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> value;
            if (value != cv) {
                (*secondOne).setRow(nsv,i,j,value);
                nsv++;
            }
        }
    }
    
    //Statements to print the matrix
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
