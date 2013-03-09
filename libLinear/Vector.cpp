/*
 * Vector.cpp
 * Author: Abhi Devireddy
 * Abstract Vector class for representing any 3D or 4D vectors
 */

#include "Vector.h"

/**
 * Constructors
 */
Vector::Vector() {
	for (int i = 0; i < 3; i++)
		data[i] = 0;
	data[3] = 1;
}

Vector::Vector(double x, double y, double z, double w) {
	data[0] = x;
	data[1] = y;
	data[2] = z;
	data[3] = w;
}

Vector::Vector(double x, double y, double z) {
	data[0] = x;
	data[1] = y;
	data[2] = z;
	data[3] = 1;
}

Vector::Vector(double* dataArray, int arrayLength) {
	data[3] = 1;
	for (int i = 0; i < arrayLength; i++)
		data[i] = dataArray[i];
}

Vector::~Vector() {
}
/**
 * Returns the length of the Vector
 * @return Returns a floating point value of the length of the Vector
 */
double Vector::Length() {
	double output = 0;
	for (int i = 0; i < 3; i++)
		output += data[i] * data[i];
	return (double) (sqrt(output));
}

double Vector::Length4() {
	double output = 0;
	for (int i = 0; i < 4; i++)
		output += data[i] * data[i];
	return (double) (sqrt(output));
}

/**
 * Returns the Unit Vector associated with the given Vector
 * @return Returns a Vector of length 1 and in the same direction as the original
 */
Vector Vector::Normalize() {
	if (Length() != 0) {
		return Vector(X(), Y(), Z()) / Length();
	} else return Vector(X(), Y(), Z());
}

/**
 * Dot product with another Vector
 * @param vec2 The 2nd Vector in the dot product
 * @return The floating point value of the dot product of the vectors
 */
double Vector::Dot(Vector& vec2) {
	double output = 0.0;
	double* vec2Arr = vec2.GetArray();
	for (int i = 0; i < 3; i++)
		output += data[i] * vec2Arr[i];
	return output;
}

double Vector::Dot4(Vector& vec2) {
	double output = 0.0;
	double* vec2Arr = vec2.GetArray();
	for (int i = 0; i < 4; i++)
		output += data[i] * vec2Arr[i];
	return output;
}

/**
 * Cross product with another Vector
 * @param vec2 The 2nd Vector in the cross product
 * @return The result of the cross product of the 2 vectors
 */
Vector Vector::Cross(Vector vec2) {
	double newArray[3];
	double* vec2Arr = vec2.GetArray();
	newArray[0] = data[1] * vec2Arr[2] - data[2] * vec2Arr[1];
	newArray[1] = data[2] * vec2Arr[0] - data[0] * vec2Arr[2];
	newArray[2] = data[0] * vec2Arr[1] - data[1] * vec2Arr[0];
	return Vector(newArray, 3);
}

/**
 * toString() : Converts the Vector into a string
 * @return The string representation of the Vector : ax + by + cz
 */
string Vector::toString() {
	ostringstream output("");
	output << "(";
	for (int i = 0; i < 4; i++) {
		output << sgn(data[i]) << fabs(data[i]);
		if (i < 3)
			output << ",";
	}
	output << ")";
	return output.str();
}

/**
 * Addition Operator
 * @operator Adds vectors component wise
 * @return Returns the Vector sum of the 2 vectors
 */
Vector Vector::operator+(Vector& rhs) {
	double newArray[3];
	double* rhsArr = rhs.GetArray();
	for (int i = 0; i < 3; i++)
		newArray[i] = data[i] + rhsArr[i];
	return Vector(newArray, 3);
}

/**
 * Subtraction Operator
 * @operator Subtracts vectors component wise
 * @return Returns the Vector difference of the 2 vectors
 */
Vector Vector::operator-(Vector& rhs) {
	double newArray[3];
	double* rhsArr = rhs.GetArray();
	for (int i = 0; i < 3; i++)
		newArray[i] = data[i] - rhsArr[i];
	return Vector(newArray, 3);
}

/**
 * Multiplication Operator
 * @operator Multiplies vectors component wise
 */
Vector Vector::operator*(double rhs) {
	double newArray[3];
	for (int i = 0; i < 3; i++)
		newArray[i] = data[i] * rhs;
	return Vector(newArray, 3);
}

/**
 * Division Operator
 * @operator Divides the vector component wise
 * @return Returns the Vector divided by the input
 */
Vector Vector::operator/(double rhs) {
	double newArray[3];
	for (int i = 0; i < 3; i++)
		newArray[i] = data[i] / rhs;
	return Vector(newArray, 3);
}

/**
 * Equate operator
 * @operator Assigns the value of the second Vector to the first
 */
void Vector::operator=(Vector rhs) {
	double* rhsArr = rhs.GetArray();
	for (int i = 0; i < 4; i++)
		data[i] = rhsArr[i];
}

/**
 * Equality operation
 * @operator Checks for equality of the 2 vectors
 * @return Returns true if the vectors are the same, else false
 */
bool Vector::operator==(Vector rhs) {
	double* rhsArr = rhs.GetArray();
	for (int i = 0; i < 3; i++)
		if (data[i] == rhsArr[i])
			return false;
	return true;
}

/**
 * Inequality operation
 * @operator Checks for inequality of the 2 vectors
 * @return Returns false if the 2 vectors are the same, else true
 */
bool Vector::operator!=(Vector& rhs) {
	double* rhsArr = rhs.GetArray();
	for (int i = 0; i < 3; i++)
		if (data[i] != rhsArr[i])
			return true;
	return false;
}

Vector Vector::Homogenize() {
	double newVec[4];
	for (int i = 0; i < 4; i++)
		newVec[i] = data[i] / W();
	return Vector(newVec, 4);
}
