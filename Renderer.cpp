/*
 * Renderer.cpp
 * Author: abhinavdevireddy
 * The main file that parses the arguments and calls the specified renderer
 * #############################################
 * ## Program for CS 5631 : Computer Graphics ##
 * ##  at the University of Minnesota Duluth  ##
 * #############################################
 */

#include <iostream>
#include <cstdlib>
#include <string>
#include "RayTracer.cpp"
#include "Rasterizer.cpp"
#include "OGLImage.h"
#include <getopt.h>
#include "liveTrace.h"

using namespace std;

/**
 * Function that shows the help menu
 */
void ShowHelp() {
	cout << "USAGE:" << endl
			<< "Renderer [OPTIONS]" << endl << endl
			<< "List of valid options: " << endl
			<< "r\tRenderer : [RAY/RAST/OGL]" << endl
			<< "s\tScenefile" << endl
			<< "h\tHeight of the image" << endl
			<< "w\tWidth of the image" << endl
			<< "o\tBase output file" << endl
			<< "t\tThread count" << endl
			<< "g\tGenerate a sequence of images for rotation" << endl
				<< "   n\tNumber of images to generate" << endl
				<< "   b\tStarting number of image in sequence" << endl
				<< "   e\tEnding number of image in sequence" << endl
			<< "l\tEnable live ray tracing" << endl
			<< "?\tShow the help menu" << endl;
}

/**
 * The main function that runs the specified renderer
 */
int main(int argc, char** argv) {
	bool rFlag = false, tFlag = false, hFlag = false, wFlag = false, sFlag = false, oFlag = false, gFlag = false, help = false, nFlag = false, bFlag = false, eFlag = false, lFlag = false;
	char option;

	string renderer;
	int threadCount = 1;
	int imgHt = 800;
	int imgWd = 600;

	string sceneFilename;
	string outputImg;
	//Special options when generating sequences of images
	int imageCount = 1;
	int beginImage = 0;
	int endImage = 1;
	int MOON_SPH = 1;

	while ((option = getopt(argc, argv, "r:t:h:w:s:o:g?n:b:e:l")) != -1) {
		switch (option) {
		case 'r':
			renderer = optarg;
			rFlag = true;
			break;
		case 't':
			threadCount = atoi(optarg);
			tFlag = true;
			break;
		case 'h':
			imgHt = atoi(optarg);
			hFlag = true;
			break;
		case 'w':
			imgWd = atoi(optarg);
			wFlag = true;
			break;
		case 's':
			sceneFilename = optarg;
			sFlag = true;
			break;
		case 'o':
			outputImg = optarg;
			oFlag = true;
			break;
		case 'g':
			gFlag = true;
			break;
		case '?':
			help = true;
			break;
		case 'n':
			imageCount = atoi(optarg);
			nFlag = true;
			break;
		case 'b':
			beginImage = atoi(optarg);
			bFlag = true;
			break;
		case 'e':
			endImage = atoi(optarg);
			eFlag = true;
			break;
		case 'l':
			lFlag = true;
			break;
		}
	}

	if (help) {
		ShowHelp();
		exit(0);
	}

	if (!(rFlag && hFlag && wFlag && sFlag && oFlag) && !(rFlag && hFlag && wFlag && sFlag && lFlag)) {
		ShowHelp();
		exit(0);
	}

	//Pick which renderer to use
	if (renderer == "OGL") {
		//OpenGL Rendering
		OGLImage(sceneFilename, imgWd, imgHt);
	}
	else if (renderer == "RAY") {
		//Raytracer Rendering
		if (gFlag) {
			//Generate multiple ray traced images
			if (nFlag && bFlag && eFlag)
				RayTracer(sceneFilename, imgWd, imgHt, outputImg, threadCount, imageCount, beginImage, endImage, MOON_SPH);
		}
		else if (lFlag) {
			//Open the live ray tracer
			liveTrace(sceneFilename, imgWd, imgHt, threadCount);
		}
		else
			//Open the regular ray tracer and output the images
			RayTracer(sceneFilename, imgWd, imgHt, outputImg, threadCount);
	}
	else if (renderer == "RAST") {
		//Rasterizer Rendering
		Rasterizer(sceneFilename, imgWd, imgHt, outputImg);
	}
}
