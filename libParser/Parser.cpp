/*
 * Parser.cpp
 * Author: abhinavdevireddy
 */

#include "Parser.h"

#define ARGS_PER_LINE 25

Parser::Parser(string filename, double imgWd, double imgHt) :
	imgHt(imgHt), imgWd(imgWd) {

	m_scene = Scene();

	fstream sceneFile(filename.c_str(), fstream::in);
	if (!sceneFile.is_open()) {
		cout << "Error opening Scenefile. Check filename and try again.\n";
		exit(1);
	}

	while (!sceneFile.eof()) {
		string tempLine;
		getline(sceneFile, tempLine);
		istringstream curLine(tempLine);
		string lineArgs[ARGS_PER_LINE];
		//Extract all the different values in the given line
		for (int i = 0; i < ARGS_PER_LINE; i++)
			curLine >> lineArgs[i];

		//If the line is a shape
		if (lineArgs[0].compare("shape") == 0) {

			//If the line is a sphere
			if (lineArgs[1].compare("sphere") == 0) {
				Sphere* newSphere;
				Shading* sphShading;
				Texture* sphTexture;

				if (lineArgs[6].compare("lambertian") == 0)
					sphShading = new Shading(new Vector(atof(lineArgs[7].c_str()), atof(lineArgs[8].c_str()), atof(lineArgs[9].c_str())), NULL, 0);
				else if (lineArgs[6].compare("phong") == 0)
					sphShading = new Shading(new Vector(atof(lineArgs[7].c_str()), atof(lineArgs[8].c_str()), atof(lineArgs[9].c_str())), new Vector(atof(lineArgs[10].c_str()), atof(lineArgs[11].c_str()), atof(lineArgs[12].c_str())), atof(lineArgs[13].c_str()));
				else if (lineArgs[6].compare("texture") == 0) {
					sphTexture = new Texture(lineArgs[7].c_str(), lineArgs[8].c_str());
				}
				else sphShading = new Shading(new Vector(1.0, 1.0, 1.0), NULL, 0);

				if (lineArgs[6].compare("texture") != 0) {
					//If it is shading and not a texture
					newSphere = new Sphere(new Vector(atof(lineArgs[2].c_str()), atof(lineArgs[3].c_str()), atof(lineArgs[4].c_str())), atof(lineArgs[5].c_str()), sphShading);
				}
				else {
					//If it is a texture
					newSphere = new Sphere(new Vector(atof(lineArgs[2].c_str()), atof(lineArgs[3].c_str()), atof(lineArgs[4].c_str())), atof(lineArgs[5].c_str()), sphTexture);
				}

				m_scene.AddSphere(newSphere);
			}
			//If the line is a box
			else if (lineArgs[1].compare("box") == 0) {
				double u1 = atof(lineArgs[2].c_str());
				double u2 = atof(lineArgs[3].c_str());
				double u3 = atof(lineArgs[4].c_str());
				double v1 = atof(lineArgs[5].c_str());
				double v2 = atof(lineArgs[6].c_str());
				double v3 = atof(lineArgs[7].c_str());

				Vector* pt[] = { new Vector(u1, u2, u3),
						new Vector(v1, u2, u3),
						new Vector(v1, u2, v3),
						new Vector(u1, u2, v3),
						new Vector(u1, v2, u3),
						new Vector(v1, v2, u3),
						new Vector(v1, v2, v3),
						new Vector(u1, v2, v3) };

				Shading* quadShading;
				Texture* quadTexture;

				if (lineArgs[8].compare("lambertian") == 0) {
					quadShading = new Shading(new Vector(atof(lineArgs[9].c_str()), atof(lineArgs[10].c_str()), atof(lineArgs[11].c_str())), NULL, 0);
				}
				else if (lineArgs[8].compare("phong") == 0) {
					quadShading = new Shading(new Vector(atof(lineArgs[9].c_str()), atof(lineArgs[10].c_str()), atof(lineArgs[11].c_str())), new Vector(atof(lineArgs[12].c_str()), atof(lineArgs[13].c_str()), atof(lineArgs[14].c_str())), atof(lineArgs[15].c_str()));
				} else if (lineArgs[8].compare("texture") == 0) {
					quadTexture = new Texture(lineArgs[9].c_str(), lineArgs[10].c_str());
				} else {
					quadShading = new Shading(new Vector(1.0, 1.0, 1.0), NULL, 0);
				}

				if (quadTexture == NULL) {
					m_scene.AddQuad(new Quad(pt[0], pt[3], pt[2], pt[1], quadShading));
					m_scene.AddQuad(new Quad(pt[4], pt[5], pt[6], pt[7], quadShading));
					m_scene.AddQuad(new Quad(pt[6], pt[5], pt[1], pt[2], quadShading));
					m_scene.AddQuad(new Quad(pt[4], pt[7], pt[3], pt[0], quadShading));
					m_scene.AddQuad(new Quad(pt[7], pt[6], pt[2], pt[3], quadShading));
					m_scene.AddQuad(new Quad(pt[5], pt[4], pt[0], pt[1], quadShading));
				}
				else {
					m_scene.AddQuad(new Quad(pt[0], pt[3], pt[2], pt[1], quadTexture));
					m_scene.AddQuad(new Quad(pt[4], pt[5], pt[6], pt[7], quadTexture));
					m_scene.AddQuad(new Quad(pt[6], pt[5], pt[1], pt[2], quadTexture));
					m_scene.AddQuad(new Quad(pt[4], pt[7], pt[3], pt[0], quadTexture));
					m_scene.AddQuad(new Quad(pt[7], pt[6], pt[2], pt[3], quadTexture));
					m_scene.AddQuad(new Quad(pt[5], pt[4], pt[0], pt[1], quadTexture));
				}
			}

			//If the shape is a triangle
			else if (lineArgs[1].compare("triangle") == 0) {
				Vector* pt[] = {new Vector(atof(lineArgs[2].c_str()), atof(lineArgs[3].c_str()), atof(lineArgs[4].c_str())),
								new Vector(atof(lineArgs[5].c_str()), atof(lineArgs[6].c_str()), atof(lineArgs[7].c_str())),
								new Vector(atof(lineArgs[8].c_str()), atof(lineArgs[9].c_str()), atof(lineArgs[10].c_str())) };
				Shading* triShading;
				Texture* triTexture;
				if (lineArgs[11].compare("lambertian") == 0)
					triShading = new Shading(new Vector(atof(lineArgs[12].c_str()), atof(lineArgs[13].c_str()), atof(lineArgs[14].c_str())), NULL, 0);
				else if (lineArgs[11].compare("phong") == 0)
					triShading = new Shading(new Vector(atof(lineArgs[12].c_str()), atof(lineArgs[13].c_str()), atof(lineArgs[14].c_str())), new Vector(atof(lineArgs[15].c_str()), atof(lineArgs[16].c_str()), atof(lineArgs[17].c_str())), atof(lineArgs[18].c_str()));
				else if (lineArgs[11].compare("texture") == 0)
					triTexture = new Texture(lineArgs[12].c_str(), lineArgs[13].c_str());

				if (triTexture == NULL)
					m_scene.AddTriangle(new Triangle(pt[0], pt[1], pt[2], triShading));
				else m_scene.AddTriangle(new Triangle(pt[0], pt[1], pt[2], triTexture));
			}
		}

		//If the line is a light
		else if (lineArgs[0].compare("light") == 0) {
			m_scene.AddLight(new Light(new Vector(atof(lineArgs[1].c_str()), atof(lineArgs[2].c_str()), atof(lineArgs[3].c_str())), new Vector(atof(lineArgs[4].c_str()), atof(lineArgs[5].c_str()), atof(lineArgs[6].c_str()))));
		}

		//If the line is ambient light
		else if (lineArgs[0].compare("ambient") == 0) {
			m_scene.ambientLight = new Vector(atof(lineArgs[1].c_str()), atof(lineArgs[2].c_str()), atof(lineArgs[3].c_str()));
		}

		//If the line is a camera
		else if (lineArgs[0].compare("camera") == 0) {
			Vector* position = new Vector(atof(lineArgs[1].c_str()), atof(lineArgs[2].c_str()), atof(lineArgs[3].c_str()));
			Vector* viewOrient = new Vector(atof(lineArgs[5].c_str()), atof(lineArgs[6].c_str()), atof(lineArgs[7].c_str()));

			double near = atof(lineArgs[8].c_str());
			double far = atof(lineArgs[9].c_str());
			double fov = atof(lineArgs[10].c_str());

			Camera* newCamera;

			if (lineArgs[4].compare("lookatpt") == 0) {
				Vector* viewDir = new Vector();
				viewDir = &viewOrient->operator -(* position);
				newCamera = new Camera(position, &viewDir->Normalize(), near, far, fov, imgWd, imgHt, m_scene.sceneUp);
			} else if (lineArgs[4].compare("viewdir") == 0) {
				newCamera = new Camera(position, &viewOrient->Normalize(), near, far, fov, imgWd, imgHt, m_scene.sceneUp);
			}
			m_scene.AddCamera(newCamera);
		}

		//Needs to be before the cameras
		else if (lineArgs[0].compare("up") == 0) {
			m_scene.sceneUp = new Vector(atof(lineArgs[1].c_str()), atof(lineArgs[2].c_str()), atof(lineArgs[3].c_str()));
		}
	}
	sceneFile.close();
}

Scene Parser::getScene() {
	return m_scene;
}

Parser::~Parser() {
	for (int i = 0; i < (int)m_scene.triangleList.size(); i++)
		delete m_scene.triangleList[i];
	for (int i = 0; i < (int)m_scene.cameraList.size(); i++)
			delete m_scene.cameraList[i];
	for (int i = 0; i < (int)m_scene.sphereList.size(); i++)
			delete m_scene.sphereList[i];
	for (int i = 0; i < (int)m_scene.quadList.size(); i++)
			delete m_scene.quadList[i];
	for (int i = 0; i < (int)m_scene.lightList.size(); i++)
			delete m_scene.lightList[i];

	delete m_scene.ambientLight;
	delete m_scene.sceneUp;

}
