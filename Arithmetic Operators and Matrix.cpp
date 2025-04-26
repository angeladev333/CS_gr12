/*************************************************
Purpose of Code: Use overload operators to add, subtract, and multiply matrixes
Date: 05/09/2022
By: Angela Xu
**************************************************/
#include <iostream>
using namespace std;

class Exception{
private:
string message;

public:
	Exception(string msg){
		message = msg;
	}
	void getException(){
		cout << "Exception: " <<message<<endl;
	}
};

class Matrix{
	public:
	int col;
	int row;
	int **matrix = new int *[row];
	Matrix(int c, int r): col(c), row(r){
		for(int i=0; i<row; i++){
			matrix[i]= new int[col];
		}
	}
void printStatus(){
	for(int i=0; i<row; i++){
		for(int k=0; k<col; k++){
			cout << matrix[i][k] <<" ";
		}
		cout<<endl;
	}
}
};

Matrix& operator+ (Matrix& m, int num){
	int col = m.col;
	int row = m.row;

	for(int i=0; i<row; i++){
		for(int k=0; k<col; k++){
			m.matrix[i][k] +=num;
		}
	}
	return m;
}

Matrix& operator+ (Matrix& m, Matrix m2){
	int col = m.col;
	int row = m.row;
	int col2 = m2.col;
	int row2 = m2.row;

	if(col!=col2 || row!=row2){
		//throw exception
		throw Exception("One of matrix sizes is not valid");
	}

	for(int i=0; i<row; i++){
		for(int k=0; k<col; k++){
			m.matrix[i][k] += m2.matrix[i][k];
		}
	}
	return m;
}

Matrix& operator- (Matrix& m, int num){
	int col = m.col;
	int row = m.row;

	for(int i=0; i<row; i++){
		for(int k=0; k<col; k++){
			m.matrix[i][k] -=num;
		}
	}
	return m;
}

Matrix& operator- (Matrix& m, Matrix m2){
	int col = m.col;
	int row = m.row;
	int col2 = m2.col;
	int row2 = m2.row;

	if(col!=col2 || row!=row2){
		//throw exception
		throw Exception("One of matrix sizes is not valid");
	}

	for(int i=0; i<row; i++){
		for(int k=0; k<col; k++){
			m.matrix[i][k] -= m2.matrix[i][k];
		}
	}
	return m;
}

Matrix& operator* (Matrix& m, int num){
	int col = m.col;
	int row = m.row;

	for(int i=0; i<row; i++){
		for(int k=0; k<col; k++){
			m.matrix[i][k] *=num;
		}
	}
	return m;
}

Matrix& operator* (Matrix& m, Matrix m2){
	int col = m.col;
	int row = m.row;
	int col2 = m2.col;
	int row2 = m2.row;

	if(col!=col2 || row!=row2){
		//throw exception
		throw Exception("One of matrix sizes is not valid");
	}

	for(int i=0; i<row; i++){
		for(int k=0; k<col; k++){
			m.matrix[i][k] *= m2.matrix[i][k];
		}
	}
	return m;
}

int main() {
	int colA, rowA, colB, rowB;
	string nameA, nameB;
	int temp;

	//initialize matrixA
	cout << "What is the name of your first Matrix?: "<<endl;
	cin>> nameA;
	cout << "How many columns are in your first Matrix?: "<<endl;
	cin >> colA;
	cout << "How many rows are in your first Matrix?: "<<endl;
	cin >> rowA;
	
	Matrix objA(colA, rowA);
	cout<< "Please input Matrix "<<nameA <<": "<<endl;
	for(int i=0; i<rowA; i++){
		for(int k=0; k<colA; k++){
			cin >> temp;
			objA.matrix[i][k] = temp;
		}
	}


	//initialize matrixB
	cout << "What is the name of your second Matrix?: "<<endl;
	cin>> nameB;
	cout << "How many columns are in your second Matrix?: "<<endl;
	cin >> colB;
	cout << "How many rows are in your second Matrix?: "<<endl;
	cin >> rowB;
	Matrix objB(colB, rowB);
	
	cout<< "Please input Matrix "<<nameB <<": "<<endl;
	for(int i=0; i<rowB; i++){
		for(int k=0; k<colB; k++){
			cin >> temp;
			objB.matrix[i][k] = temp;
		}
	}	

	
	objA = objA+1;
	cout<< "Matrix "<<nameA<<" +1: "<<endl;
	objA.printStatus();

	objA = objA*2;
	cout<< "Matrix "<<nameA<<" *2: "<<endl;
	objA.printStatus();
	
	objA = objA-1;
	cout<< "Matrix "<<nameA<<" -1: "<<endl;
	objA.printStatus();

	cout<< "Matrix "<<nameA<<" + Matrix " << nameB << ": "<<endl;
	try{
		objA = objA+objB;
		objA.printStatus();
		}
	catch(Exception e){
		e.getException();
	}

	cout<< "Matrix "<<nameA<<" - Matrix " << nameB << ": "<<endl;
	try{
		objA = objA-objB;
		objA.printStatus();
	}
	catch(Exception e){
		e.getException();
	}

	cout<< "Matrix "<<nameA<<" * Matrix " << nameB << ": "<<endl;
	try{
		objA = objA*objB;
		objA.printStatus();
	}
	catch(Exception e){
		e.getException();
	}
}