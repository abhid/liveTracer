/*
 * Matrix.h
 * Author : abhinavdevireddy
 * The generic matrix class that contains a nxn matrix of dataType
 * The Matrix can also be expressed as a n array of vectors of dimensions n
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include "Vector.h"
#include "utilMatrix.h"

using namespace std;

class Matrix {
public:

	/**
	 * Creates a new 4x4 identity matrix of the given rank
	 * @param rank Then rank of the matrix that is generated
	 */
	Matrix();

	/**
	 * Creates a matrix from the given array of vectors
	 * @param dataArray The array of data that is used to generate the Matrix
	 * @param The rank of the matrix that is generated
	 */
	Matrix(double dataArray[]);

	~Matrix();

	/**
	 * Set an element of the matrix
	 * @param row The row of the element to be set
	 * @param column The column of the element to be set
	 * @param element The element that is to be inserted into the Matrix
	 */
	void SetElement(int row, int column, double element) {
		data[arrayIdx(row, column)] = element;
	}

	/**
	 * Get an element of the matrix
	 * @param row The row of the element to be obtained
	 * @param column The column of the element to be obtained
	 * @return A reference to the element at the specified row and column.
	 */
	double &GetElement(int row, int column) {
		return data[arrayIdx(row, column)];
	}

	/**
	 * Output the matrix as a string
	 * @return A string representation of the matrix
	 */
	string toString();

	//Overloaded opearators on the matrix
	Matrix& operator+(Matrix& rhs); //Add 2 matrices
	Matrix& operator-(Matrix& rhs); //Subtract 2 matrices
	Matrix& operator*(double rhs); //Scalar multiply with a floatShape
	Matrix& operator*(Matrix& rhs); //Post multiply with a Matrix
	Vector& operator*(Vector& rhs); //Multiply with a vector
	Matrix& operator/(double rhs); //Scalar divide with a float
	void operator=(Matrix& rhs); //Assignment operator for a matrix

	/**
	 * Get the determinant of the matrix
	 * @return The determinant of the matrix
	 */
	double Determinant();

	/**
	 * Clear the matrix and set it equal to the Identity Matrix
	 */
	void Clear();

	/**
	 * Compute the inverse of the matrix
	 * @return The inverse of the matrix
	 */
	Matrix Inverse();

	/**
	 * Get row as a Vector
	 * @param row The required row
	 * @return The specified row as a vector
	 */
	Vector& GetRow(int row);

	/**
	 * Get column as a Vector
	 * @param column The required column
	 * @return The specified column as a vector
	 */
	Vector& GetColumn(int column);

	/**
	 * Set row as a Vector
	 * @param rowVector The vector to be used as a row
	 * @param row The row to be set
	 * @return True if the row can be set
	 */
	void SetRow(Vector& rowVector, int row);

	/**
	 * Set column as a Vector
	 * @param columnVector The vector to be used as a column
	 * @param column The column to be set
	 * @return True if the row can be set
	 *
	 */
	void SetColumn(Vector& columnVector, int column);

	double* GetArray() { return data; }

private:
	//The array that will hold all the data in the matrix
	double* data;

	//Translate i,j positions into indices for the array
	int arrayIdx(int row, int column) {
		return ((row - 1) * 4) + (column - 1);
	}
};

#endif /* MATRIX_H_ */
