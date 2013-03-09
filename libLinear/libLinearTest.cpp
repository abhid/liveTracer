/*
 * libLinearTest.cpp
 *
 *  Created on: Apr 12, 2010
 *      Author: abhinavdevireddy
 */

#include "GMatrix.h"

int main(int argc, char** argv) {
	cout << "Testing the Vector classes..." << endl;
	Vector v1 = Vector();
	Vector v2 = Vector(1.0, 2.0, 3.0);
	Vector v3 = Vector(2.0, 4.0, 8.0, 1.0);
	double vArr[] = {1.0, 3.0, 5.0, 1.0};
	Vector v4 = Vector(vArr, 3);
	Vector v5 = Vector(vArr, 4);
	Vector v6 = Vector(-4, 2, 0);
	Vector v7 = Vector(0.0, 0.0, 0.0, 1.0);
	Vector v8 = Vector(2.0, 1.0, 2.0);
	Vector v9 = Vector(2.0/3.0, 1.0/3.0, 2.0/3.0);
	Vector v10 = Vector(3.0, 6.0, 11.0);
	Vector v11 = Vector(-1.0, -2.0, -5.0);
	Vector v12 = Vector(2.0, 4.0, 6.0);
	Vector v13 = Vector(1.0, 2.0, 4.0);
	if (v4 != v5)
		cout << "Vector > Array Constructor : FAILED" << endl;
	if (v7 != v1)
		cout << "Vector > Equality testing : FAILED" << endl;
	if( v3.Dot(v2) != 34.0 )
		cout << "Vector > Dot Product : FAILED" << endl;
	if (v3.Cross(v2) != v6)
		cout << "Vector > Cross Product : FAILED" << endl;
	if (v8.Normalize() != v9)
		cout << "Vector > Normalize : FAILED" << endl;
	if (v2 + v3 != v10)
		cout << "Vector > Addition Op : FAILED" << endl;
	if (v2 - v3 != v11)
		cout << "Vector > Subtraction Op : FAILED" << endl;
	if (v2*2 != v12)
		cout << "Vector > Multiply Op : FAILED" << endl;
	if (v3/2 != v13)
		cout << "Vector > Division Op : FAILED" << endl;

	cout << "Testing the Matrix classes..." << endl;
	double matrixArr[] = {0.0, 1.0, 3.0, 1.0, 5.0, 0.0, 8.0, 6.0, 9.0, 10.0, 0.0, 12.0, 13.0, 14.0, 15.0, 0.0};
	Matrix m1 = Matrix();
	Matrix m2 = Matrix(matrixArr);
	cout << m2.toString() << endl;
	cout << "Determinant: " << m2.Determinant() << endl;
	cout << "Inverse:" << endl << m2.Inverse().toString() << endl;

	cout << "Testing the GMatrix class..." << endl;


	cout << "Testing the Ray class..." << endl;
}
