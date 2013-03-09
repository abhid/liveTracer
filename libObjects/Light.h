/*
 * Light.h
 * Author: abhinavdevireddy
 */

#ifndef LIGHT_H_
#define LIGHT_H_

#include "Vector.h"
#include "Object.h"

class Light {
public:
	Light(Vector* position, Vector* color) {
		m_position = position;
		m_color = color;
	}

	~Light() {
		delete m_position;
		delete m_color;
	}
Vector* m_position;
Vector* m_color;
};

#endif /* LIGHT_H_ */
