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
    SparseRow getRow(int c);
    
    //other methods that are necessary such as get and set
    
};

SparseMatrix::SparseMatrix (int n, int m, int cv, int noNSV) {
    noRows = n;
    noCols = m;
    commonValue = cv;
    noNonSparseValues = noNSV;
    myMatrix = new SparseRow[noNSV];
    
};
//write the methods after the class definition

void SparseRow::display() {
    cout << this->getRow() << " " << this->getCol() << " " << this->getValue() << endl;
};

SparseMatrix* SparseMatrix::Transpose() {
    return 0;
};

SparseMatrix* SparseMatrix::Multiply(SparseMatrix &M) {
    return 0;
};

SparseMatrix* SparseMatrix::Add(SparseMatrix &M) {
    return 0;
};

void SparseMatrix::display() {
    for (int i = 0; i < this->noNonSparseValues; i++) {
        this->getRow(i).display();
    }
};

void SparseMatrix::displayMatrix() {
    
};

SparseRow SparseMatrix::getRow(int c) {
    return this->myMatrix[c];
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
    
    int n, m, cv, noNSV, nsv, r, c, value;
    c = 0;
    r = 0;
    nsv = 0;
//    SparseMatrix* temp;
    
    cin >> n >> m >> cv >> noNSV;
    SparseMatrix* firstOne = new SparseMatrix(n, m, cv, noNSV);
    
    //Write the Statements to read in the first matrix
    //write code to put the rows, columns and values into the matrix here
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> value;
            if (value != cv) {
                (*firstOne).setRow(nsv,i,j,value);
                cout << nsv << endl;
                nsv++;
            }
        }
    }
    
//    SparseMatrix* secondOne = new SparseMatrix(n, m, cv, noNSV);
    //Write the Statements to read in the second matrix
    
    //Statements to print the matrix
    cout << "First one in sparse matrix format" << endl;
    (*firstOne).display();
//    cout << "First one in normal matrix format" << endl;
//    (*firstOne).displayMatrix();
    /*
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
     */
    
    return 0;

}
