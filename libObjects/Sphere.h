/*
 * Sphere.h
 *
 *  Created on: Mar 12, 2010
 *      Author: abhinavdevireddy
 */

#ifndef SPHERE_H_
#define SPHERE_H_

#include <algorithm>
#include <cmath>
#include "Object.h"

class Sphere: public Object {
public:
	Sphere(Vector* center, double radius, Shading* sphShade) :
		m_center(center), m_radius(radius), m_shading(sphShade) {
		m_texture = NULL;
	}

	Sphere(Vector* center, double radius, Texture* sphTexture) :
		m_center(center), m_radius(radius), m_texture(sphTexture) {
		m_shading = NULL;
	}

	~Sphere() {
		delete m_center;
		delete m_shading;
		delete m_texture;
	}

	bool intersect(Ray& inRay) {
		float A = pow(inRay.r_direction.Length(), 2);
		Vector radVec = inRay.r_origin - (*m_center);
		float B = 2 * (inRay.r_direction.Dot(radVec));
		float C = pow((inRay.r_origin - *m_center).Length(), 2) - m_radius
				* m_radius;
		float discr = B * B - 4.0 * A * C;

		if (discr > 0.0) {
			return true;
		} else
			return false;
	}

	bool intersect(Ray& inRay, vector<Light*> lightList, HitStruct& output, Vector* ambientLight) {
		float A = pow(inRay.r_direction.Length(), 2);
		Vector radVec = inRay.r_origin - (*m_center);
		float B = 2 * (inRay.r_direction.Dot(radVec));
		float C = pow((inRay.r_origin - *m_center).Length(), 2) - m_radius
				* m_radius;
		float discr = B * B - 4.0 * A * C;
		float t;

		if (discr > 0.0) {
			float t1 = (-1 * B - sqrt(discr)) / (2.0 * A);
			float t2 = (-1 * B + sqrt(discr)) / (2.0 * A);
			t = min(t1, t2);
		} else
			return false;

		output.distance = t;
		output.intersectPoint = (inRay.r_direction * t) + (inRay.r_origin);
		output.normal = (output.intersectPoint - (*m_center)) / m_radius;
		Vector colorMult = Vector(ambientLight->X(), ambientLight->Y(), ambientLight->Z());

		if (m_shading) {
			output.color.X() = m_shading->m_color->X();
			output.color.Y() = m_shading->m_color->Y();
			output.color.Z() = m_shading->m_color->Z();
			for (int i = 0; i < (int) lightList.size(); i++) {
				Vector* cl = lightList[i]->m_color;
				Vector n = output.normal;
				Vector* l = &(lightList[i]->m_position->operator -(output.intersectPoint)).Normalize();

				colorMult.X() = colorMult.X() + cl->X() * max(0.0, n.Dot(*l));
				colorMult.Y() = colorMult.X() + cl->Y() * max(0.0, n.Dot(*l));
				colorMult.Z() = colorMult.X() + cl->Z() * max(0.0, n.Dot(*l));

				if (!m_shading->lambertian) {
					Vector h = (inRay.r_origin + *l).Normalize();
					colorMult.X() = colorMult.X() + m_shading->m_specular->X() * pow(h.Dot(n), m_shading->m_exponent);
					colorMult.Y() = colorMult.Y() + m_shading->m_specular->Y() * pow(h.Dot(n), m_shading->m_exponent);
					colorMult.Z() = colorMult.Z() + m_shading->m_specular->Z() * pow(h.Dot(n), m_shading->m_exponent);
				}
			}
			output.color.X() = output.color.X() * colorMult.X();
			output.color.Y() = output.color.Y() * colorMult.Y();
			output.color.Z() = output.color.Z() * colorMult.Z();
		}

		else if (m_texture) {
			//All the mapping info to go from texture to object
			Vector map = output.intersectPoint - (*m_center);
			float theta = acos(map.Z() / m_radius);
			float phi = atan2(map.Y(), map.X());
			if (phi < 0.0)
				phi += 2 * M_PI;
			float u = floor((phi / (2 * M_PI)) * m_texture->texWidth);
			float v = floor(((M_PI - theta) / M_PI) * m_texture->texHeight);

			Vector bumpNormal = Vector();
			if ((((3 * v * m_texture->texWidth) + (u * 3)) < (3*m_texture->texWidth*m_texture->texHeight)) && (((3 * v * m_texture->bumpWidth) + (u * 3)) < (3*m_texture->bumpWidth*m_texture->bumpHeight))) {
			//Get the color data from the texture
			output.color.X() = (float) (m_texture->texData[(int) ((3 * v * m_texture->texWidth) + (u * 3))]) / 255.0;
			output.color.Y() = (float) (m_texture->texData[(int) ((3 * v * m_texture->texWidth) + (u * 3) + 1)]) / 255.0;
			output.color.Z() = (float) (m_texture->texData[(int) ((3 * v * m_texture->texWidth) + (u * 3) + 2)]) / 255.0;

			//Get the normal data from the bump map
			bumpNormal.X() = (float) (m_texture->bumpData[(int) ((3 * v * m_texture->bumpWidth) + (u * 3))]) / 255.0;
			bumpNormal.Y() = (float) (m_texture->bumpData[(int) ((3 * v * m_texture->bumpWidth) + (u * 3) + 1)]) / 255.0;
			bumpNormal.Z() = (float) (m_texture->bumpData[(int) ((3 * v * m_texture->bumpWidth) + (u * 3) + 2)]) / 255.0;
			}
			else cerr << "Error while getting texture / bump data\n";
			//Setting the normal from the bump normal
			output.normal.X() = output.normal.X() * fabs(bumpNormal.X());
			output.normal.Y() = output.normal.Y() * fabs(bumpNormal.Y());
			output.normal.Z() = output.normal.Z() * fabs(bumpNormal.Z());
			output.normal = output.normal.Normalize();
			//TODO: Figure out how to get bump maps to work

			// Color is now applied to the sphere from the texture. Now use light to shade it
			for (int i = 0; i < (int) lightList.size(); i++) {
				Vector* cl = lightList[i]->m_color;
				Vector* l = &(lightList[i]->m_position->operator -(output.intersectPoint)).Normalize();
				//Set the lighting from all the lights using the texture and bump map
				colorMult.X() = colorMult.X() + cl->X() * max(0.0, output.normal.Dot(*l));
				colorMult.Y() = colorMult.Y() + cl->Y() * max(0.0, output.normal.Dot(*l));
				colorMult.Z() = colorMult.Z() + cl->Z() * max(0.0, output.normal.Dot(*l));
			}
			output.color.X() = output.color.X() * colorMult.X();
			output.color.Y() = output.color.Y() * colorMult.Y();
			output.color.Z() = output.color.Z() * colorMult.Z();
		}
		return true;
	}

	void ApplyTransform(Matrix transformMatrix) {
		m_center = &(transformMatrix * *m_center);
	}

	void OGLRender() {

	}

	string toString() {
		ostringstream output("");
		output << "Sphere:\t";
		output << "Center: " << m_center->toString() << "\t" << "Radius: "
				<< m_radius << "\n";
		output << "\n";
		return output.str();
	}

	vector<Triangle*> Tesselate() {
		int incAngle = 10; //Set this somewhere
		int iterations = 360 / incAngle;
		double divAngle = incAngle * M_PI / 180.0;

		double* center = m_center->GetArray();
		double v1[4];
		double v2[4];
		double v3[4];
		double v4[4];

		vector<Triangle*> output;
		double azi = 0.0, ele = 0.0;
		for (int i = 0; i < iterations; i++, azi += divAngle) {
			for (int j = 0; j < iterations; j++, ele += divAngle) {
				v1[0] = center[0] + m_radius * cos(ele) * sin(azi);
				v1[1] = center[1] + m_radius * sin(ele) * cos(azi);
				v1[2] = center[2] + m_radius * cos(azi);
				v1[3] = 1;
				v2[0] = center[0] + m_radius * cos(ele + divAngle) * sin(azi);
				v2[1] = center[1] + m_radius * cos(ele + divAngle) * sin(azi);
				v2[2] = center[2] + m_radius * cos(azi);
				v2[3] = 1;
				v3[0] = center[0] + m_radius * cos(ele) * sin(azi + divAngle);
				v3[1] = center[1] + m_radius * cos(ele) * sin(azi + divAngle);
				v3[2] = center[2] + m_radius * cos(azi + divAngle);
				v3[3] = 1;
				v4[0] = center[0] + m_radius * cos(ele + divAngle) * sin(azi
						+ divAngle);
				v4[1] = center[1] + m_radius * cos(ele + divAngle) * sin(azi
						+ divAngle);
				v4[2] = center[2] + m_radius * cos(azi + divAngle);
				v4[3] = 1;
				output.push_back(new Triangle(new Vector(v1, 4), new Vector(v2,
						4), new Vector(v3, 4), m_shading));
				output.push_back(new Triangle(new Vector(v2, 4), new Vector(v4,
						4), new Vector(v3, 4), m_shading));
			}
		}

		return output;
	}

	Vector* m_center;
	double m_radius;
	Shading* m_shading;
	Texture* m_texture;
};

#endif /* SPHERE_H_ */
