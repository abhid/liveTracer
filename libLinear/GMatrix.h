/*
 * GMatrix.cpp
 * Static class that generates different matrices for viewing the world and transformations
 * Author: abhinavdevireddy
 */

#ifndef GMATRIX_H_
#define GMATRIX_H_

#include "Matrix.h"

class GMatrix {
public:

	/**
	 * Generate a scale transformation matrix
	 * @param xscale The x-axis scaling factor
	 * @param yscale The y-axis scaling factor
	 * @param zscale The z-axis scaling factor
	 * @return A matrix for the specified transformation
	 */
	static Matrix generateScale(double xscale, double yscale, double zscale) {
		Matrix outputMatrix = Matrix();
		outputMatrix.SetElement(1, 1, xscale);
		outputMatrix.SetElement(2, 2, yscale);
		outputMatrix.SetElement(3, 3, zscale);
		return outputMatrix;
	}

	/**
	 * Generate a rotation transformation matrix. Input angles are in degrees
	 * @param xrotate The angle for rotation in degrees
	 * @return A matrix for the specified rotation about x
	 */
	static Matrix xRotate(double xrotate) {
		xrotate = xrotate * M_PI / 180.0;
		Matrix outputMatrix = Matrix();
		if (xrotate != 0) {
			outputMatrix.SetElement(2, 2, (cos(xrotate)));
			outputMatrix.SetElement(2, 3, (-1.0 * sin(
					xrotate)));
			outputMatrix.SetElement(2, 1, (1.0));
			outputMatrix.SetElement(3, 2, (sin(xrotate)));
			outputMatrix.SetElement(3, 3, (cos(xrotate)));
		}
		return outputMatrix;
	}

	/**
	 * Generate a rotation transformation matrix. Input angles are in degrees
	 * @param yrotate The angle for rotation in degrees
	 * @return A matrix for the specified rotation about y
	 */
	static Matrix yRotate(double yrotate) {
		yrotate = yrotate * M_PI / 180.0;
		Matrix outputMatrix = Matrix();
		if (yrotate != 0) {
			outputMatrix.SetElement(1, 1, static_cast<double> (cos(yrotate)));
			outputMatrix.SetElement(1, 3, static_cast<double> (sin(yrotate)));
			outputMatrix.SetElement(3, 1, static_cast<double> (-1.0 * sin(
					yrotate)));
			outputMatrix.SetElement(3, 3, static_cast<double> (cos(yrotate)));
		}
		return outputMatrix;
	}

	/**
	 * Generate a rotation transformation matrix. Input angles are in degrees
	 * @param zrotate The angle for rotation in degrees
	 * @return A matrix for the specified rotation about z
	 */
	static Matrix zRotate(double zrotate) {
		zrotate = zrotate * M_PI / 180.0;
		Matrix outputMatrix = Matrix();
		if (zrotate != 0) {
			outputMatrix.SetElement(1, 1, static_cast<double> (cos(zrotate)));
			outputMatrix.SetElement(1, 2, static_cast<double> (-1.0 * sin(
					zrotate)));
			outputMatrix.SetElement(2, 1, static_cast<double> (sin(zrotate)));
			outputMatrix.SetElement(2, 2, static_cast<double> (cos(zrotate)));
		}
		return outputMatrix;
	}

	/**
	 * Generate a translation transformation matrix
	 * @param xtrans Translation in the x direction
	 * @param ytrans Translation in the y-direction
	 * @param ztrans Translation in the z-direction
	 * @return A matrix for the specified transformation
	 */
	static Matrix generateTranslate(double xtrans, double ytrans,
			double ztrans) {
		Matrix outputMatrix = Matrix();
		double vectorData[] = { xtrans, ytrans, ztrans, 1.0 };
		outputMatrix.SetColumn(*(new Vector(vectorData, 4)), 4);
		return outputMatrix;
	}

	/**
	 * Generate an Orthogonal Projection Matrix
	 * @param l The left end of the projection
	 * @param r The right end of the projection
	 * @param b The bottom of the projection
	 * @param t The top of the projection
	 * @param n The near of the projection
	 * @param f The far of the projection
	 */
	static Matrix M_Ortho(double nx, double ny, double fov, double n, double f) {
		fov = fov * M_PI / 180.0;
		double t = tan(fov / 2) * fabs(n);
		double r = nx / ny * t;
		double b = -t;
		double l = -r;
		double ortho[] = { 2.0 / (r - l), 0.0, 0.0, -(r + l) / (r - l), 0.0,
				2.0 / (t - b), 0.0, -(t + b) / (t - b), 0.0, 0.0,
				2.0 / (n - f), -(n + f) / (n - f), 0.0, 0.0, 0.0, 1.0 };
		return Matrix(ortho);
	}

	/**
	 *Generate the viewport matrix to go from the canonical view volume to the screen
	 */
	static Matrix M_Vp(double nx, double ny) {
		double vp[] = { nx / 2.0, 0.0, 0.0, (nx - 1) / 2.0, 0.0, ny / 2.0,
				0.0, (ny - 1) / 2.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0 };
		return Matrix(vp);
	}

	/**
	 * Generate the prespective matrix to go from a frustum to an othogonal view volume
	 */
	static Matrix M_p(double n, double f) {
		double p[] = { 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, (n + f) / n, -f, 0.0, 0.0, 1 / n, 0.0 };
		return Matrix(p);
	}

	/**
	 * Generate the camera matrix
	 */
	static Matrix M_Cam(double camx, double camy, double camz) {
		double cam[] = { 1.0, 0.0, 0.0, -1.0 * camx, 0.0, 1.0, 0.0, -1.0
				* camy, 0.0, 0.0, 1.0, -1.0 * camz, 0.0, 0.0, 0.0, 1.0 };
		return Matrix(cam);
	}
};

#endif /* GMATRIX_H_ */
