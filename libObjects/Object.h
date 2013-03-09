/*
 * Shape.h
 * Author: abhinavdevireddy
 */

#ifndef SHAPE_H_
#define SHAPE_H_

#include "HitStruct.h"
#include "Ray.h"
#include "Matrix.h"
#include "Shading.h"
#include "Texture.h"
#include "Light.h"
#include "SFML/Window.hpp"

class Object {
public:
	//Intersect with a Ray : For the rayTracer
	virtual bool intersect(Ray& inRay) = 0;
	virtual bool intersect(Ray& inRay, vector<Light*> lightList, HitStruct& output, Vector* ambientLight) = 0;

	//Apply a transformation matrix to the object
	virtual void ApplyTransform(Matrix transformMatrix) = 0;

	//Render the object in the OpenGL Window : For the OGL Rendering
	virtual void OGLRender() = 0;

	//String representation of the object
	virtual string toString() = 0;

	Shading* m_shading;
	Texture* m_texture;
};
#endif /* SHAPE_H_ */
