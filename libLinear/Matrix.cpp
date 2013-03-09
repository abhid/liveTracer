/*
 * Matrix.cpp
 * Author: abhinavdevireddy
 * The implementation of the matrix class
 */
#include "Matrix.h"

Matrix::Matrix() {
	//Initialize the data pointer using the rank
	data = new double[16];

	//Set all the diagonal elements to 1
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 4; j++)
			(i == j) ? SetElement(i, j, (double) 1.0) : SetElement(i, j,
					(double) 0.0);
}

Matrix::Matrix(double dataArray[]) {
	//Initialize the data pointer using the rank
	data = new double[16];

	//Set all the elements from the Vectors
	for (int i = 0; i < 16; i++)
		data[i] = dataArray[i];
}

Matrix::~Matrix() {
}

string Matrix::toString() {
	ostringstream output("");
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			output << ((float) ((int) GetElement(i, j) * 100) / 100) << "\t\t";
		}
		output << "\n";
	}
	return output.str();
}

Matrix& Matrix::operator+(Matrix& rhs) {
	Matrix* outputMatrix = new Matrix();
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 4; j++)
			outputMatrix->SetElement(i, j, GetElement(i, j) + rhs.GetElement(i,
					j));
	return *outputMatrix;
}

Matrix& Matrix::operator-(Matrix& rhs) {
	Matrix* outputMatrix = new Matrix();
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 4; j++)
			outputMatrix->SetElement(i, j, GetElement(i, j) - rhs.GetElement(i,
					j));
	return *outputMatrix;
}

Matrix& Matrix::operator *(double rhs) {
	Matrix* outputMatrix = new Matrix();
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 4; j++)
			outputMatrix->SetElement(i, j, GetElement(i, j) * rhs);
	return *outputMatrix;
}

Matrix& Matrix::operator *(Matrix& rhs) {
	Matrix* outputMatrix = new Matrix();
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 4; j++) {
			Vector column = rhs.GetColumn(j);
			outputMatrix->SetElement(i, j, GetRow(i).Dot(column));
		}
	return *outputMatrix;
}

Vector& Matrix::operator *(Vector& rhs) {
	double vectorData[4];
	for (int i = 1; i <= 4; i++)
		vectorData[i - 1] = GetRow(i).Dot(rhs);
	return *(new Vector(vectorData, 4));
}

Matrix& Matrix::operator /(double rhs) {
	Matrix* outputMatrix = new Matrix();
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 4; j++)
			outputMatrix->SetElement(i, j, GetElement(i, j) / rhs);
	return *outputMatrix;
}

void Matrix::operator =(Matrix& rhs) {
	for (int i = 1; i <= 4; i++)
		this->SetRow(rhs.GetRow(i), i);
}

double Matrix::Determinant() {
	return (new utilMatrix(data, 4))->determinant();
}

void Matrix::Clear() {
	//Set all the diagonal elements to 1
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 4; j++)
			i == j ? data[arrayIdx(i, j)] = 1.0 : data[arrayIdx(i, j)] = 0.0;
}

Matrix Matrix::Inverse() {
	utilMatrix inv = utilMatrix(data, 4);
	return Matrix(inv.inverse().getData());
}

Vector& Matrix::GetRow(int row) {
	double* vecArr = new double[4];
	for (int j = 1; j <= 4; j++)
		vecArr[j - 1] = GetElement(row, j);
	return *(new Vector(vecArr, 4));
}

void Matrix::SetRow(Vector& rowVector, int row) {
	double* vecArr = rowVector.GetArray();
	for (int j = 1; j <= 4; j++)
		SetElement(row, j, vecArr[j - 1]);
}

Vector& Matrix::GetColumn(int column) {
	double* vecArr = new double[4];
	for (int i = 1; i <= 4; i++)
		vecArr[i - 1] = GetElement(i, column);
	return * (new Vector(vecArr, 4));
}

void Matrix::SetColumn(Vector& columnVector, int column) {
	double* vecArr = columnVector.GetArray();
	for (int i = 1; i <= 4; i++)
		SetElement(i, column, vecArr[i - 1]);
}
