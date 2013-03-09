/*
 * Rasterizer.cpp
 * Author: abhinavdevireddy
 */

#include "Parser.h"
#include "GMatrix.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include "Image.h"
#include <vector>
#include "Camera.h"
#include "Vertex.h"

using namespace std;

class Rasterizer {
public:
	Rasterizer(string sceneFile, int imgWd, int imgHt, string outputFile) {
		Parser imgParser = Parser(sceneFile, imgWd, imgHt);
		cout << "=================================" << "\n\tRasterizer"
				<< "\n=================================" << "\nimgWd: "
				<< imgParser.imgWd << "\timgHt:" << imgParser.imgHt
				<< "\n=================================\n";
		Scene imgScene = imgParser.getScene();
		cout << imgScene.getInfo() << endl;
	}
};
