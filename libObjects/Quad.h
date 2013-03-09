/*
 * Quad.h
 *
 *  Created on: Apr 14, 2010
 *      Author: abhinavdevireddy
 */

#ifndef QUAD_H_
#define QUAD_H_

class Quad: public Object {
public:
	static const int VERTEX_COUNT = 4;

	Quad(Vector* pt1, Vector* pt2, Vector* pt3, Vector* pt4,
			Shading* quadShading) {
		m_vertex[0] = pt1;
		m_vertex[1] = pt2;
		m_vertex[2] = pt3;
		m_vertex[3] = pt4;
		m_shading = quadShading;
	}
	Quad(Vector* pt1, Vector* pt2, Vector* pt3, Vector* pt4,
			Texture* quadTexture) {
		m_vertex[0] = pt1;
		m_vertex[1] = pt2;
		m_vertex[2] = pt3;
		m_vertex[3] = pt4;
		m_texture = quadTexture;
	}

	~Quad() {
		delete []m_vertex;
		delete m_shading;
		delete m_texture;
	}

	bool intersect(Ray& inRay) {
			return true;
	}

	bool intersect(Ray& inRay, vector<Light*> lightList, HitStruct& output, Vector* ambientLight) {
		return true;
	}

	void ApplyTransform(Matrix transformMatrix) {

	}

	void OGLRender() {
		cout << "Rendering a quad" << endl;
		cout << m_vertex[0]->toString() << endl;
		glBegin( GL_QUADS);
		glVertex3f(m_vertex[0]->X(), m_vertex[0]->Y(), m_vertex[0]->Z());
		glVertex3f(m_vertex[1]->X(), m_vertex[1]->Y(), m_vertex[1]->Z());
		glVertex3f(m_vertex[2]->X(), m_vertex[2]->Y(), m_vertex[2]->Z());
		glVertex3f(m_vertex[3]->X(), m_vertex[3]->Y(), m_vertex[3]->Z());
		glEnd();
	}

	string toString() {
		ostringstream output("");
		output << "Quad:\t";
		for (int i = 0; i < VERTEX_COUNT; i++)
			output << (m_vertex[i])->toString() << "\t";
		output << "\n";
		return output.str();
	}

	vector<Triangle*> Tesselate() {
		vector<Triangle*> output;
		return output;
	}

private:
	Vector* m_vertex[VERTEX_COUNT];

};

#endif /* QUAD_H_ */
