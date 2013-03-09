/*
 * HVector.h
 * Author: Abhi Devireddy
 * A homoegenous Vector class that contains a 4D Vector
 */

#ifndef VECTOR_H_
#define VECTOR_H_

#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>
#include <sstream>

using namespace std;

class Vector {
public:
	//Constructors
	Vector ();											//Generates origin (0, 0, 0, 1)
	Vector (double x, double y, double z, double w);	//Generates (x, y, z, w)
	Vector (double x, double y, double z);				//Generates (x, y, z, 1)
	Vector (double* dataArray, int ArrayLen);
	~Vector();

	//Get the length of the vector
	double Length();
	double Length4();

	//Get the unit vector
	Vector Normalize();

	//Get the co-ordinates array
	double* GetArray() { return data; }

	//Dot product
	double Dot(Vector& vec2);
	double Dot4(Vector& vec2);

	//Cross product
	Vector Cross(Vector vec2);
	//Vector as a string representation
	string toString();
	//Vector operations
	Vector operator+(Vector& rhs);				//Add 2 vectors
	Vector operator-(Vector& rhs);				//Subtract 2 vectors
	Vector operator*(double rhs);				//Scalar Multiplication
	Vector operator/(double rhs);				//Scalar Division

	void operator=(Vector rhs);					//Assignment operator
	bool operator==(Vector rhs);					//Equality operator
	bool operator!=(Vector& rhs);					//Inequality operator

	//Individual element accessors
	double& X() { return data[0]; }
	double& Y() { return data[1]; }
	double& Z() { return data[2]; }
	double& W() { return data[3]; }

	//Homogenize the vector
	Vector Homogenize();

private:
	//Array with all the 4 components of the vector
	double data[4];

	//Signum function
	char sgn(double t) {
		return t<0 ? '-' : '+';
	}
};


#endif /* VECTOR_H_ */
