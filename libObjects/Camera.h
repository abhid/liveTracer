/*
 * Camera.h
 * Author: abhinavdevireddy
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include "Ray.h"
#include "GMatrix.h"

class Camera {
public:

	Camera(Vector* position, Vector* view_dir, double near, double far, double fov, double imgWd, double imgHt, Vector* camUp) : m_camPos(position), m_viewDir(view_dir), m_camUp(camUp), m_camfov(fov), img_ht(imgHt), img_wd(imgWd), m_near(fabs(near)), m_far(far) {

		w = m_viewDir->operator *(-1.0);
		u = m_camUp->Cross(w);
		v = w.Cross(u);

		u = u.Normalize();
		v = v.Normalize();
		w = w.Normalize();

		Matrix m1 = Matrix();
		m1.SetColumn(*m_camPos, 4);
		Matrix m2 = Matrix();
		m2.SetColumn(u, 1);
		m2.SetColumn(v, 2);
		m2.SetColumn(w, 3);
		m = m1*m2;

		fov = m_camfov * M_PI / 180.0;
		t = tan(fov / 2) * m_near;			//No need for fabs as we already used it in initialization
		r = img_wd / img_ht * t;
		b = -t;
		l = -r;

	}

	~Camera() {
		// DO NOT DELETE ANY DATA MEMBERS
//		delete m_camPos;
//		delete m_viewDir;
//		delete m_camUp;
	}

	Ray generateRay(float px, float py) {
		px = l + ((r - l)*(px + 0.5)/ img_wd);
		py = b + ((t - b)*(py + 0.5)/ img_ht);
		Vector rayShoot = Vector(px, py, m_near*-1.0);	//Important : Note the -1.0 for the correct direction of the plane
		Vector s = m * rayShoot;
		s = s.Normalize();
		Ray output = Ray();
		output.r_direction.X() = s.X();
		output.r_direction.Y() = s.Y();
		output.r_direction.Z() = s.Z();
		output.r_origin.X() = m_camPos->X();
		output.r_origin.Y() = m_camPos->Y();
		output.r_origin.Z() = m_camPos->Z();
		return output;
	}

	Matrix generate_M_cam() {
		return GMatrix::M_Cam(m_camPos->X(), m_camPos->Y(), m_camPos->Z());
	}

	void moveForward() {
		m_camPos->X() = m_camPos->X() + w.X()*-1.0;
		m_camPos->Y() = m_camPos->Y() + w.Y()*-1.0;
		m_camPos->Z() = m_camPos->Z() + w.Z()*-1.0;
	}

	void moveBackward() {
		m_camPos->X() = m_camPos->X() + w.X();
		m_camPos->Y() = m_camPos->Y() + w.Y();
		m_camPos->Z() = m_camPos->Z() + w.Z();
	}

	void strafeLeft() {
		m_camPos->X() = m_camPos->X() + u.X()*-1.0;
		m_camPos->Y() = m_camPos->Y() + u.Y()*-1.0;
		m_camPos->Z() = m_camPos->Z() + u.Z()*-1.0;
	}

	void strafeRight() {
	m_camPos->X() = m_camPos->X() + u.X();
	m_camPos->Y() = m_camPos->Y() + u.Y();
	m_camPos->Z() = m_camPos->Z() + u.Z();
	}

	Vector w;		//Camera basis
	Vector u;		//Camera basis
	Vector v;		//Camera basis
	Matrix m;		//Camera matrix

	Vector* m_camPos;	//Camera position
	Vector* m_viewDir;	//Camera viewing direction
	Vector* m_camUp;
	double m_camfov;	//FOV of camera in degrees

	//Image constraints
	double img_ht;		//Ht of image
	double img_wd;		//Wd of image
	double m_near;		//Near plane of the image
	double m_far;		//Far plane of the world

	double fov, t, r, b, l;	//FOV in radians, top, bottom, right, bottom and left of the image
};

#endif /* CAMERA_H_ */
