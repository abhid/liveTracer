/*
 * Triangle.h
 *
 *  Created on: Mar 12, 2010
 *      Author: abhinavdevireddy
 */

#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "Object.h"

class Triangle: public Object {
public:
	static const int VERTEX_COUNT = 3;

	Triangle(Vector* pt1, Vector* pt2, Vector* pt3, Shading* triShade) {
		m_vertex[0] = pt1;
		m_vertex[1] = pt2;
		m_vertex[2] = pt3;
		m_shading = triShade;
	}

	Triangle(Vector* pt1, Vector* pt2, Vector* pt3, Texture* triTexture) {
		m_vertex[0] = pt1;
		m_vertex[1] = pt2;
		m_vertex[2] = pt3;
		m_texture = triTexture;
	}

	~Triangle() {
		delete [] m_vertex;
		delete m_shading;
		delete m_texture;
	}

	bool intersect(Ray& inRay) {
			return true;
		}

	bool intersect(Ray& inRay, vector<Light*> lightList, HitStruct& output, Vector* ambientLight) {
		//TODO Finish Triangle Intersect method
		return true;
	}

	void ApplyTransform(Matrix transformMatrix) {
		for (int i = 0; i < VERTEX_COUNT; i++) {
			m_vertex[i] = &(transformMatrix * *m_vertex[i]);
			m_vertex[i] = &m_vertex[i]->Homogenize();
		}
	}

	void OGLRender() {
		glBegin(GL_TRIANGLES);
		glVertex3f(m_vertex[0]->X(), m_vertex[0]->Y(), m_vertex[0]->Z());
		glVertex3f(m_vertex[1]->X(), m_vertex[1]->Y(), m_vertex[1]->Z());
		glVertex3f(m_vertex[2]->X(), m_vertex[2]->Y(), m_vertex[2]->Z());
		glEnd();
	}

	string toString() {
		ostringstream output("");
		output << "Triangle:\t";
		for (int i = 0; i < VERTEX_COUNT; i++)
			output << (m_vertex[i])->toString() << "\t";
		output << "\n";
		return output.str();
	}

	Vector* m_vertex[VERTEX_COUNT];
};

#endif /* TRIANGLE_H_ */
