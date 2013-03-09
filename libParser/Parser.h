/*
 * Parser.h
 * Author: abhinavdevireddy
 */

#ifndef PARSER_H_
#define PARSER_H_

#include "Scene.h"
#include <string>
#include <fstream>

class Parser {
public:
	Parser(string filePath, double imgWd, double imgHt);
	~Parser();
	Scene getScene();
	double imgHt;
	double imgWd;
private:
	Scene m_scene;
};

#endif /* PARSER_H_ */
