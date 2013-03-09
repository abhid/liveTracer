/*
 * Shading.h
 * Contains all the information about shading the object
 * Author: abhinavdevireddy
 */

#ifndef SHADING_H_
#define SHADING_H_

#include "Vector.h"

class Shading {
public:

	Shading(Vector* color, Vector* specular, double exponent) {
		if (specular == NULL)
			lambertian = true;
		else
			lambertian = false;
		m_color = color;
		m_specular = specular;
		m_exponent = exponent;
	}

	~Shading() {
		delete m_color;
		delete m_specular;
	}

	Vector* m_color;
	Vector* m_specular;
	bool lambertian;
	double m_exponent;
};

#endif /* SHADING_H_ */
