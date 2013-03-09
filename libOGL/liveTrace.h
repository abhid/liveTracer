/*
 * liveTrace.h
 *
 *  Created on: May 8, 2010
 *      Author: abhinavdevireddy
 */

#ifndef LIVETRACE_H_
#define LIVETRACE_H_

#include <SFML/Window.hpp>
#include "RayTracer.cpp"
#include "Texture.h"

class liveTrace {
public:
	bool screenRefresh;
	string sceneFilename;
	int imgWd;
	int imgHt;
	int camCount;
	int threadCount;
	GLuint textureId;
	float* imageData;
	float curMoonPos;
	float displayLevel;

	liveTrace(string scenefile, int imgWd, int imgHt, int threadCount) :
		sceneFilename(scenefile), imgWd(imgWd), imgHt(imgHt), threadCount(
				threadCount) {

		imageData = new float[imgWd * imgHt * 3];
		curMoonPos = 0.0;
		displayLevel = 1.0;
		loadTexture();

		sf::Window App(sf::VideoMode(imgWd, imgHt, 32), "Live Ray Tracer");
		App.SetFramerateLimit(3);

		// Create a clock for measuring time elapsed
		sf::Clock Clock;

		// Set color and depth clear value
		glClearDepth(1.f);
		glClearColor(0.5f, 0.5f, 0.5f, 0.f);

		// Enable Z-buffer read and write
		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);

		//Setup viewport matrix
		glViewport(0, 0, imgWd, imgHt);

		// Setup a perspective projection
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(90.f, 1.f, 1.f, 500.f);

		//Setup a modelview matrix so that you can do transforms
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		// Start game loop
		while (App.IsOpened()) {
			// Process events
			sf::Event Event;
			while (App.GetEvent(Event)) {
				// Close window : exit
				if (Event.Type == sf::Event::Closed)
					App.Close();

				// Escape key : exit
				if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code
						== sf::Key::Escape))
					App.Close();

				// Resize event : adjust viewport
				if (Event.Type == sf::Event::Resized) {
					glViewport(0, 0, Event.Size.Width, Event.Size.Height);
					screenRefresh = true;
				}

				//R
				if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code
						== sf::Key::R)) {
					screenRefresh = true;
				}

				//L
				if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code
						== sf::Key::L)) {
					loadTexture();
					screenRefresh = true;
				}
				//C
				if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code
						== sf::Key::C)) {
					displayLevel = 10;
					camCount++;
					loadTexture();
					screenRefresh = true;
				}
				//N
				if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code
						== sf::Key::N)) {
					curMoonPos += 10;
					displayLevel = 10;
					loadTexture();
					screenRefresh = true;
				}
				//P
				if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code
						== sf::Key::P)) {
					curMoonPos -= 10;
					displayLevel = 10;
					loadTexture();
					screenRefresh = true;
				}
				//I
				if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code
						== sf::Key::I)) {
					char buf[20];
					time_t curTime = time(NULL);
					strftime(buf, 20, "live-%m%d-%H%M", localtime(&curTime));
					Image::Write(buf, imgWd, imgHt, imageData);
				}
				//H
				if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code
						== sf::Key::H)) {
					cout << endl << endl
							<< "======================================" << endl
							<< "          Live Renderer Help          " << endl
							<< "======================================" << endl
							<< "Esc\tExit" << endl
							<< "R\tRefresh the screen" << endl
							<< "L\tLoad the texture and refresh the screen" << endl
							<< "C\tToggle between cameras" << endl
							<< "N\tShow the next image in the series" << endl
							<< "P\tShow the previous image in the series" << endl
							<< "I\tWrite the image to disk" << endl
							<< "H\tShow this help menu" << endl;
				}
			}
			App.SetActive();
			redrawScreen();
			if (displayLevel > 1) {
				displayLevel--;
				loadTexture();
			}
			App.Display();
		}
	}

	void loadTexture() {
		Matrix moonRot = GMatrix::zRotate(curMoonPos);
		RayTracer* liveTracer = new RayTracer(sceneFilename, imgWd/displayLevel, imgHt/displayLevel, imageData, threadCount, moonRot, 1, camCount);
		screenRefresh = true;
		delete liveTracer;
	}

	void redrawScreen() {
		if (screenRefresh) {

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			glEnable(GL_TEXTURE_2D);
			glGenTextures(1, &textureId);
			glBindTexture(GL_TEXTURE_2D, textureId);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

			gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, imgWd/displayLevel, imgHt/displayLevel, GL_RGB, GL_FLOAT, imageData);

			glPushMatrix();
			glLoadIdentity();
			glMatrixMode(GL_PROJECTION);
			glPushMatrix();
			glLoadIdentity();

			glBegin(GL_QUADS);
			glNormal3f(0.0, 0.0, 1.0);

			glTexCoord2f(0.0, 0.0);
			glVertex3f(-1.0, -1.0, -1.0);

			glTexCoord2f(1.0, 0.0);
			glVertex3f(1.0, -1.0, -1.0);

			glTexCoord2f(1.0, 1.0);
			glVertex3f(1.0, 1.0, -1.0);

			glTexCoord2f(0.0, 1.0);
			glVertex3f(-1.0, 1.0, -1.0);
			glEnd();

			glPopMatrix();
			glMatrixMode(GL_MODELVIEW);
			glPopMatrix();
			screenRefresh = false;

			glDisable(GL_TEXTURE_2D);
		}
	}
};

#endif /* LIVETRACE_H_ */
