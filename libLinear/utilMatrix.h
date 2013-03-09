/*
 * utilMatrix.h
 *
 *  Created on: Apr 12, 2010
 *      Author: abhinavdevireddy
 */

#ifndef UTILMATRIX_H_
#define UTILMATRIX_H_

class utilMatrix {
public:

	utilMatrix(int rank) :
		rank(rank) {
		//Initialize the data pointer using the rank
		data = new double[rank * rank];

		//Set all the diagonal elements to 1
		for (int i = 1; i <= rank; i++)
			for (int j = 1; j <= rank; j++)
				(i == j) ? setElement(i, j, (double) 1.0) : setElement(i, j,
						(double) 0.0);
	}

	utilMatrix(double dataArray[], int rank) :
		rank(rank) {
		//Initialize the data pointer using the rank
		data = new double[rank * rank];

		//Set all the elements from the array
		for (int i = 0; i < rank * rank; i++)
			data[i] = dataArray[i];
	}

	~utilMatrix() {
		delete [] data;
	}

	utilMatrix inverse() {
		utilMatrix output = utilMatrix(rank);
		for (int i = 1; i <= rank; i++)
			for (int j = 1; j <= rank; j++)
				output.setElement(i, j, cofactor(i, j));
		return output.transpose();
	}

	double determinant() {
		if (rank == 2)
			return getElement(1, 1) * getElement(2, 2) - getElement(2, 1)
					* getElement(1, 2);
		else {
			double output = 0.0;
			for (int i = 1; i <= rank; i++)
				output += getElement(i, 1) * cofactor(i, 1);
			return output;
		}
	}

	double* getData() {
		return data;
	}

private:

	void setElement(int row, int column, double element) {
		data[arrayIdx(row, column)] = element;
	}

	double getElement(int row, int column) {
		return data[arrayIdx(row, column)];
	}

	string toString() {
		ostringstream output("");
		for (int i = 1; i <= rank; i++) {
			for (int j = 1; j <= rank; j++) {
				output << getElement(i, j) << "\t\t";
			}
			output << "\n";
		}
		return output.str();
	}

	utilMatrix operator/(double rhs) { //Scalar divide with a float
		utilMatrix outputMatrix = utilMatrix(rank);
		for (int i = 1; i <= rank; i++)
			for (int j = 1; j <= rank; j++)
				outputMatrix.setElement(i, j, getElement(i, j) / rhs);
		return outputMatrix;
	}

	utilMatrix operator *(double rhs) {
		utilMatrix outputMatrix = utilMatrix(rank);
		for (int i = 1; i <= rank; i++)
			for (int j = 1; j <= rank; j++)
				outputMatrix.setElement(i, j, getElement(i, j) * rhs);
		return outputMatrix;
	}

	utilMatrix transpose() {
		utilMatrix outputMatrix = utilMatrix(rank);
		for (int i = 1; i <= rank; i++)
			for (int j = 1; j <= rank; j++)
				outputMatrix.setElement(i, j, getElement(j, i));
		return outputMatrix;
	}

	double cofactor(int row, int column) {
		//Cofactor = (-1)^(i+j) * (determinant of the minor matrix)
		double output = pow(-1, row + column)
				* subMatrix(row, column).determinant();
		return output;
	}

	utilMatrix subMatrix(int row, int column) {
		if (rank == 2)
			return utilMatrix(1) * getElement(2, 2);
		else {
			utilMatrix outputMatrix = utilMatrix(rank - 1);
			int colCount = 1, rowCount = 1;
			for (int i = 1; i <= rank; i++)
				if (i != row) {
					colCount = 1;
					for (int j = 1; j <= rank; j++)
						if (j != column) {
							outputMatrix.setElement(rowCount, colCount,
									getElement(i, j));
							colCount++;
						}
					rowCount++;
				}
			return outputMatrix;
		}
	}

	//The array that will hold all the data in the matrix
	double* data;

	//Rank dosen't change for a matrix
	const int rank;

	//Translate i,j positions into indices for the array
	int arrayIdx(int row, int column) {
		return ((row - 1) * (rank)) + (column - 1);
	}
};
#endif /* UTILMATRIX_H_ */
