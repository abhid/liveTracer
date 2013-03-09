/*
 * Scene.h
 * Author: abhinavdevireddy
 */

#ifndef SCENE_H_
#define SCENE_H_

#include <vector>
#include "Triangle.h"
#include "Sphere.h"
#include "Shading.h"
#include "Texture.h"
#include "Quad.h"
#include "Camera.h"
#include "Light.h"

using namespace std;

class Scene {
	static const int DEFAULT_DIVISION_ANGLE = 60;
public:
	Scene();
	~Scene();
	void AddTriangle(Triangle* newTriangle);
	void AddSphere(Sphere* newSphere);
	void AddQuad(Quad* newQuad);
	void AddCamera(Camera* newCamera);
	void AddLight(Light* newLight);

	vector <Object*> GenerateTracerList();
	vector <Triangle*> GenerateRasterizerList();
	vector <Object*> GenerateOGLList();

	string getInfo();

	vector<Triangle*> TesselateSpheres();
	vector<Triangle*> TesselateQuads();
	vector <Triangle*> triangleList;
	vector <Quad*> quadList;
	vector <Sphere*> sphereList;
	vector <Camera*> cameraList;
	vector <Light*> lightList;
	Vector* ambientLight;
	Vector* sceneUp;
};

#endif /* SCENE_H_ */
