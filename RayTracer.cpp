/*
 * RayTracer.cpp
 * Author: abhinavdevireddy
 * The rayTracer class that performs all the heavy work of the ray tracer. Shoots rays, Checks intersections and sets pixel values
 */


#ifndef RAYTRACER_H_
#define RAYTRACER_H_

#include "Parser.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include "Image.h"
#include <pthread.h>

using namespace std;

static pthread_mutex_t mutexSetPixel;

class RayTracer {

	struct threadData {
		int tid;
		int imgWd;
		int imgHt;
		int startWd;
		int endWd;
		int startHt;
		int endHt;
		vector<Light*> lightList;
		Vector* ambientLight;
		Camera* curCam;
		vector<Object*> objectList;
		Image* outputImage;
	};

public:
	int NUM_THREADS;
	string toString(int a);
	static void* subTrace(void*);

	//Use for single image generation
	RayTracer(string sceneFile, int imgWd, int imgHt, string outputFile,
			int threadCount) :
		NUM_THREADS(threadCount) {
		//Parse the scenefile
		Parser imgParser = Parser(sceneFile, imgWd, imgHt);
		cout << "=================================" << "\n\tRayTracer"
				<< "\n=================================" << "\nimgWd: "
				<< imgParser.imgWd << "\timgHt:" << imgParser.imgHt
				<< "\n=================================\n";
		//Get the scene
		Scene imgScene = imgParser.getScene();
		//Print info about the scene
		cout << imgScene.getInfo() << endl;

		//Create NUM_THREADS thread ids
		pthread_t threadID[NUM_THREADS];
		threadData subtraceData[NUM_THREADS];
		pthread_mutex_init(&mutexSetPixel, NULL);
		pthread_attr_t threadAttr;
		pthread_attr_init(&threadAttr);
		pthread_attr_setdetachstate(&threadAttr, PTHREAD_CREATE_JOINABLE);
		void* status;

		for (int i = 0; i < NUM_THREADS; i++)
			subtraceData[i] = threadData();

		//Get the current camera
		for (int camCount = 0; camCount < (int) imgScene.cameraList.size(); camCount++) {
			//Get the current camera
			Camera* curCam = imgScene.cameraList[camCount];
			//Create the output file
			string curImage = outputFile;
			Image outputImage = Image(curImage.append(toString(camCount + 1)),
					imgWd, imgHt);
			//Get the list of objects to be raytraced
			vector<Object*> objList = imgScene.GenerateTracerList();

			//Thread argument setup
			int htDiv = imgHt / NUM_THREADS; //Subdivide the problem by height

			cout << "Creating " << NUM_THREADS << " threads..." << endl;
			for (int i = 0; i < NUM_THREADS; i++) {
				subtraceData[i].imgWd = imgWd;
				subtraceData[i].imgHt = imgHt;
				subtraceData[i].imgWd = imgWd;
				subtraceData[i].curCam = curCam;
				subtraceData[i].objectList = objList;
				subtraceData[i].outputImage = &outputImage;
				subtraceData[i].lightList = imgScene.lightList;
				subtraceData[i].ambientLight = imgScene.ambientLight;
				subtraceData[i].tid = i;
				subtraceData[i].startWd = 0;
				subtraceData[i].endWd = imgWd;
				subtraceData[i].startHt = htDiv * i;
				subtraceData[i].endHt = htDiv * (i + 1);
				pthread_create(&threadID[i], &threadAttr, subTrace,
						(void*) &subtraceData[i]);
			}

			//Wait for all the threads to finish and write the image
			pthread_attr_destroy(&threadAttr);
			for (int i = 0; i < NUM_THREADS; i++)
				pthread_join(threadID[i], &status);
			outputImage.writeImage();
		}

		pthread_exit(NULL);
	}

	//Use for stop motion type image generation
	RayTracer(string sceneFile, int imgWd, int imgHt, string outputFile,
			int threadCount, int imgCount, int startImg, int endImg,
			int moonSph) :
		NUM_THREADS(threadCount) {
		int MAX_ITERATIONS = imgCount;
		int START_NUM = startImg;
		int END_NUM = endImg;
		int MOON_SPH = moonSph;

		//Parse the scenefile
		Parser imgParser = Parser(sceneFile, imgWd, imgHt);
		cout << "=================================" << "\n\tRayTracer"
				<< "\n=================================" << "\nimgWd: "
				<< imgParser.imgWd << "\timgHt:" << imgParser.imgHt
				<< "\n=================================\n";
		//Get the scene
		Scene imgScene = imgParser.getScene();
		//Print info about the scene
		cout << imgScene.getInfo() << endl;
		//Create NUM_THREADS thread ids
		pthread_t threadID[NUM_THREADS];
		threadData subtraceData[NUM_THREADS];
		pthread_mutex_init(&mutexSetPixel, NULL);
		pthread_attr_t threadAttr;
		pthread_attr_init(&threadAttr);
		pthread_attr_setdetachstate(&threadAttr, PTHREAD_CREATE_JOINABLE);
		void* status;
		for (int i = 0; i < NUM_THREADS; i++)
			subtraceData[i] = threadData();

		for (int l = START_NUM; l < END_NUM; l++) {
			float angInc = 360 / MAX_ITERATIONS;
			if (l == START_NUM)
				imgScene.sphereList[MOON_SPH]->ApplyTransform(GMatrix::yRotate(l * angInc));
			imgScene.sphereList[MOON_SPH]->ApplyTransform(GMatrix::yRotate(angInc));

			//Get the current camera
			for (int camCount = 0; camCount < (int) imgScene.cameraList.size(); camCount++) {
				//Get the current camera
				Camera* curCam = imgScene.cameraList[camCount];
				//Create the output file
				string curImage = outputFile;
				Image outputImage = Image(curImage.append(toString(l + 1)),
						imgWd, imgHt);
				//Get the list of objects to be raytraced
				vector<Object*> objList = imgScene.GenerateTracerList();

				//Thread argument setup
				int htDiv = imgHt / NUM_THREADS;

				cout << "Creating " << NUM_THREADS << " threads..." << endl;
				for (int i = 0; i < NUM_THREADS; i++) {
					subtraceData[i].imgWd = imgWd;
					subtraceData[i].imgHt = imgHt;
					subtraceData[i].imgWd = imgWd;
					subtraceData[i].curCam = curCam;
					subtraceData[i].objectList = objList;
					subtraceData[i].outputImage = &outputImage;
					subtraceData[i].lightList = imgScene.lightList;
					subtraceData[i].ambientLight = imgScene.ambientLight;
					subtraceData[i].tid = i;
					subtraceData[i].startWd = 0;
					subtraceData[i].endWd = imgWd;
					subtraceData[i].startHt = htDiv * i;
					subtraceData[i].endHt = htDiv * (i + 1);
					pthread_create(&threadID[i], &threadAttr, subTrace, (void*) &subtraceData[i]);
				}

				//Wait for all the threads to finish and write the image
				pthread_attr_destroy(&threadAttr);
				for (int i = 0; i < NUM_THREADS; i++)
					pthread_join(threadID[i], &status);
				outputImage.writeImage();
			}
		} //END: Rotation of Moon loop
		pthread_exit(NULL);
	}


	//Use for the live ray tracer
	RayTracer(string sceneFile, int imgWd, int imgHt, float* imageData, int threadCount, Matrix moonRot, int MOON_SPH, int camSelect) : NUM_THREADS(threadCount) {
		//Parse the scenefile
		Parser imgParser = Parser(sceneFile, imgWd, imgHt);
		//Get the scene
		Scene imgScene = imgParser.getScene();
		//Rotate the moon
		imgScene.sphereList[MOON_SPH]->ApplyTransform(moonRot);
		Image outputImage = Image("dummyOut", imgWd, imgHt);
		//Create NUM_THREADS thread ids
		pthread_t threadID[NUM_THREADS];
		threadData subtraceData[NUM_THREADS];
		pthread_mutex_init(&mutexSetPixel, NULL);
		pthread_attr_t threadAttr;
		pthread_attr_init(&threadAttr);
		pthread_attr_setdetachstate(&threadAttr, PTHREAD_CREATE_JOINABLE);
		void* status;

		for (int i = 0; i < NUM_THREADS; i++)
			subtraceData[i] = threadData();

		Camera* curCam = imgScene.cameraList[camSelect%imgScene.cameraList.size()];
		//Get the list of objects to be raytraced
		vector<Object*> objList = imgScene.GenerateTracerList();

		//Thread argument setup
		int htDiv = imgHt / NUM_THREADS; //Subdivide the problem by height

		cout << "Creating " << NUM_THREADS << " threads..." << endl;
		for (int i = 0; i < NUM_THREADS; i++) {
			subtraceData[i].imgWd = imgWd;
			subtraceData[i].imgHt = imgHt;
			subtraceData[i].imgWd = imgWd;
			subtraceData[i].curCam = curCam;
			subtraceData[i].objectList = objList;
			subtraceData[i].outputImage = &outputImage;
			subtraceData[i].lightList = imgScene.lightList;
			subtraceData[i].ambientLight = imgScene.ambientLight;
			subtraceData[i].tid = i;
			subtraceData[i].startWd = 0;
			subtraceData[i].endWd = imgWd;
			subtraceData[i].startHt = htDiv * i;
			subtraceData[i].endHt = htDiv * (i + 1);
			pthread_create(&threadID[i], &threadAttr, subTrace,
					(void*) &subtraceData[i]);
		}

		//Wait for all the threads to finish and write the image
		pthread_attr_destroy(&threadAttr);
		for (int i = 0; i < NUM_THREADS; i++)
			pthread_join(threadID[i], &status);

		//Return the image data
		outputImage.getOGLData(imageData);
		objList.clear();
	}

	~RayTracer() {
	}
};

void* RayTracer::subTrace(void* subtracerData) {
	struct threadData *curData;
	curData = (struct threadData*) subtracerData;
	cout << "Created thread " << curData->tid << endl;

	//For every pixel, shoot a ray and test intersection with every object. Upon intersection set the color
	for (int i = curData->startWd; i < curData->endWd; i++) {
		for (int j = curData->startHt; j < curData->endHt; j++) {
			Ray curRay = curData->curCam->generateRay(i, j);
			float minDist = 100000;
			for (int k = 0; k < (int) curData->objectList.size(); k++) {
				HitStruct curHit = HitStruct();
				if (curData->objectList[k]->intersect(curRay, curData->lightList, curHit, curData->ambientLight)) {
					if (curHit.distance > 1.0 && curHit.distance < minDist) {
						minDist = curHit.distance;
						pthread_mutex_lock(&mutexSetPixel);
						curData->outputImage->setPixel(i, j, &curHit.color);
						pthread_mutex_unlock(&mutexSetPixel);
					}
				}
			}
		}
	}
	cout << "Exiting thread " << curData->tid << endl;
	pthread_exit(NULL);
}

string RayTracer::toString(int a) {
	ostringstream oss;
	oss << a;
	return oss.str();
}


#endif /* RAYTRACER_H_ */
