/*
 * Scene.cpp
 * Author: abhinavdevireddy
 */

#include "Scene.h"

Scene::Scene() {
	triangleList.clear();
	cameraList.clear();
	lightList.clear();
	sphereList.clear();
	quadList.clear();
}

Scene::~Scene() {
}

void Scene::AddTriangle(Triangle* newTriangle) {
	triangleList.push_back(newTriangle);
}

void Scene::AddLight(Light* newLight) {
	lightList.push_back(newLight);
}

void Scene::AddCamera(Camera* newCamera) {
	cameraList.push_back(newCamera);
}

void Scene::AddSphere(Sphere* newSphere) {
	sphereList.push_back(newSphere);
}

void Scene::AddQuad(Quad* newQuad) {
	quadList.push_back(newQuad);
}

string Scene::getInfo() {
	stringstream output;
	output << "Triangles: " << (int) triangleList.size() << endl << "Spheres: "
			<< (int) sphereList.size() << endl << "Quads: "
			<< (int) quadList.size() << endl << "Cameras: "
			<< (int) cameraList.size() << endl << "Lights: "
			<< lightList.size();
	return output.str();
}

vector<Object*> Scene::GenerateTracerList() {
	vector<Object*> tracerList;
	tracerList.clear();
	int triSize = triangleList.size();
	int quadSize = quadList.size();
	int sphSize = sphereList.size();
	//Not implemented yet
	for (int i = 0; i < triSize; i++)
		tracerList.push_back(triangleList[i]);
	for (int i = 0; i < quadSize; i++) {
		vector<Triangle*> tesselateList = TesselateQuads();
		for (int j = 0; j <(int) tesselateList.size(); j++)
			tracerList.push_back(tesselateList[j]);
	}
	//Implemented
	for (int i = 0; i < sphSize; i++)
		tracerList.push_back(sphereList[i]);
	return tracerList;
}

vector<Triangle*> Scene::GenerateRasterizerList() {
	vector<Triangle*> rasterList;
	rasterList.clear();
	int triSize = triangleList.size();
	int quadSize = quadList.size();
	int sphSize = sphereList.size();
	for (int i = 0; i < triSize; i++)
		rasterList.push_back(triangleList[i]);
	for (int i = 0; i < quadSize; i++) {
		vector<Triangle*> tesselateList = TesselateQuads();
		for (int j = 0; j <(int) tesselateList.size(); j++)
			rasterList.push_back(tesselateList[j]);
	}
	for (int i = 0; i < sphSize; i++) {
		vector<Triangle*> tesselateList = TesselateSpheres();
		for (int j = 0; j <(int) tesselateList.size(); j++)
			rasterList.push_back(tesselateList[j]);
	}
	return rasterList;
}

vector<Object*> Scene::GenerateOGLList() {
	vector<Object*> OGLList;
	OGLList.clear();
	int triSize = triangleList.size();
	int quadSize = quadList.size();
	int sphSize = sphereList.size();
	for (int i = 0; i < triSize; i++)
		OGLList.push_back(triangleList[i]);
	for (int i = 0; i < quadSize; i++) {
		OGLList.push_back(quadList[i]);
	}
	for (int i = 0; i < sphSize; i++) {
		vector<Triangle*> tesselateList = TesselateSpheres();
		for (int j = 0; j <(int) tesselateList.size(); j++)
			OGLList.push_back(tesselateList[j]);
	}
	return OGLList;
}

vector<Triangle*> Scene::TesselateSpheres() {
	vector<Triangle*> outputList;
	outputList.clear();

	int size = sphereList.size();
	vector<Triangle*> tesselateList;

	for (int i = 0; i < size; i++) {
		tesselateList.clear();
		Sphere* curSph = sphereList[i];
		tesselateList = curSph->Tesselate();
		int triCount = tesselateList.size();
		for (int j = 0; j < triCount; j++) {
			outputList.push_back(tesselateList[j]);
		}
	}
	return outputList;
}

vector<Triangle*> Scene::TesselateQuads() {
	vector<Triangle*> outputList;
	outputList.clear();

	int size = quadList.size();
	vector<Triangle*> tesselateList;

	for (int i = 0; i < size; i++) {
		tesselateList.clear();
		Quad* curQuad = quadList[i];
		tesselateList = curQuad->Tesselate();
		int triCount = tesselateList.size();
		for (int j = 0; j < triCount; j++) {
			outputList.push_back(tesselateList[j]);
		}
	}
	return outputList;
}
