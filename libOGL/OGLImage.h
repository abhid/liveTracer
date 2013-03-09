/*
 * OGLImage.h
 * Author: abhinavdevireddy
 */

#ifndef OGLIMAGE_H_
#define OGLIMAGE_H_

#include <SFML/Window.hpp>

class OGLImage {
public:

	OGLImage(string sceneFile, float nx, float ny) {
		Parser imgParser = Parser(sceneFile, nx, ny);
				cout << "=================================" << "\n\tOpenGL Live Renderer"
				<< "\n=================================" << "\nimgWd: "
				<< imgParser.imgWd << "\timgHt:" << imgParser.imgHt
				<< "\n=================================\n";

		m_imgScene = imgParser.getScene();
		m_curCamera = m_imgScene.cameraList[0];
		m_objectList = m_imgScene.GenerateOGLList();

		//OpenGL Code goes in here

		// Create the main window
		    sf::Window App(sf::VideoMode(nx, ny, 32), "SFML OpenGL");

		    // Create a clock for measuring time elapsed
		    sf::Clock Clock;

		    // Set color and depth clear value
		    glClearDepth(1.f);
		    glClearColor(0.f, 0.f, 0.f, 0.f);

		    // Enable Z-buffer read and write
		    glEnable(GL_DEPTH_TEST);
		    glDepthMask(GL_TRUE);

		    //Setup viewport matrix
		    glViewport(0, 0, nx, ny);

		    // Setup a perspective projection
		    glMatrixMode(GL_PROJECTION);
		    glLoadIdentity();
		    gluPerspective(90.f, 1.f, 1.f, 500.f);

		    //Setup a modelview matrix so that you can do transforms
		    glMatrixMode(GL_MODELVIEW);
		    glLoadIdentity();
	        gluLookAt( m_curCamera->m_camPos->X(), m_curCamera->m_camPos->Y(), m_curCamera->m_camPos->Z(), m_curCamera->m_viewDir->X(), m_curCamera->m_viewDir->Y(), m_curCamera->m_viewDir->Z(), m_curCamera->m_camUp->X(), m_curCamera->m_camUp->Y(), m_curCamera->m_camUp->Z());


//		    gluLookAt( m_curCamera->m_camPos->X(), m_curCamera->m_camPos->Y(), m_curCamera->m_camPos->Z(), m_curCamera->m_viewDir->X(), m_curCamera->m_viewDir->Y(), m_curCamera->m_viewDir->Z(), m_curCamera->m_camUp->X(), m_curCamera->m_camUp->Y(), m_curCamera->m_camUp->Z());

		    // Start game loop
		    while (App.IsOpened())
		    {
		        // Process events
		        sf::Event Event;
		        while (App.GetEvent(Event))
		        {
		            // Close window : exit
		            if (Event.Type == sf::Event::Closed)
		                App.Close();

		            // Escape key : exit
		            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))
		                App.Close();

		            // Resize event : adjust viewport
		            if (Event.Type == sf::Event::Resized)
		                glViewport(0, 0, Event.Size.Width, Event.Size.Height);

		            //W
		            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::W)) {
		            	m_curCamera->moveForward();
				        gluLookAt( m_curCamera->m_camPos->X(), m_curCamera->m_camPos->Y(), m_curCamera->m_camPos->Z(), m_curCamera->m_viewDir->X(), m_curCamera->m_viewDir->Y(), m_curCamera->m_viewDir->Z(), m_curCamera->m_camUp->X(), m_curCamera->m_camUp->Y(), m_curCamera->m_camUp->Z());
		            }

		            //A
		            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::A)) {
		            	m_curCamera->strafeLeft();
				        gluLookAt( m_curCamera->m_camPos->X(), m_curCamera->m_camPos->Y(), m_curCamera->m_camPos->Z(), m_curCamera->m_viewDir->X(), m_curCamera->m_viewDir->Y(), m_curCamera->m_viewDir->Z(), m_curCamera->m_camUp->X(), m_curCamera->m_camUp->Y(), m_curCamera->m_camUp->Z());
		            }

		            //S
		            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::S)) {
		            	m_curCamera->moveBackward();
				        gluLookAt( m_curCamera->m_camPos->X(), m_curCamera->m_camPos->Y(), m_curCamera->m_camPos->Z(), m_curCamera->m_viewDir->X(), m_curCamera->m_viewDir->Y(), m_curCamera->m_viewDir->Z(), m_curCamera->m_camUp->X(), m_curCamera->m_camUp->Y(), m_curCamera->m_camUp->Z());
		            }

		            //D
		            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::D)) {
		            	m_curCamera->strafeRight();
				        gluLookAt( m_curCamera->m_camPos->X(), m_curCamera->m_camPos->Y(), m_curCamera->m_camPos->Z(), m_curCamera->m_viewDir->X(), m_curCamera->m_viewDir->Y(), m_curCamera->m_viewDir->Z(), m_curCamera->m_camUp->X(), m_curCamera->m_camUp->Y(), m_curCamera->m_camUp->Z());
		            }

		            //I
		            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::I)) {
		            	cout << "Cam position:" << m_curCamera->m_camPos->toString() << endl
		            			<< "Cam direction: " << m_curCamera->m_viewDir->toString() << endl
		            			<< "Up vector: " << m_curCamera->m_camUp->toString() << endl;
		            }
		        }

		        // Set the active window before using OpenGL commands
		        // It's useless here because active window is always the same,
		        // but don't forget it if you use multiple windows or controls
		        App.SetActive();

		        // Clear color and depth buffer
		        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		        DrawAxes();
		        // Finally, display rendered frame on screen
		        App.Display();
		    }

		//End of OpenGL Code
	}

private:
	vector<Object*> m_objectList;
	Camera* m_curCamera;
	Scene m_imgScene;

	void RenderObjects() {
		for (int i = 0; i < (int)m_objectList.size(); i++) {
			m_objectList[i]->OGLRender();
		}
	}

	void DrawAxes() {
		glBegin(GL_LINES);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(250.0, 0.0, 0.0);


		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 250.0, 0.0);


		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 250.0);

		//CUBE

		glBegin(GL_QUADS);
			glColor3f(1.0, 1.0, 1.0);
		    glVertex3f(-5.f, -5.f, -5.f);
		    glVertex3f(-5.f,  5.f, -5.f);
		    glVertex3f( 5.f,  5.f, -5.f);
		    glVertex3f( 5.f, -5.f, -5.f);

		    glVertex3f(-5.f, -5.f, 5.f);
		    glVertex3f(-5.f,  5.f, 5.f);
		    glVertex3f( 5.f,  5.f, 5.f);
		    glVertex3f( 5.f, -5.f, 5.f);

		    glVertex3f(-5.f, -5.f, -5.f);
		    glVertex3f(-5.f,  5.f, -5.f);
		    glVertex3f(-5.f,  5.f,  5.f);
		    glVertex3f(-5.f, -5.f,  5.f);

		    glVertex3f(5.f, -5.f, -5.f);
		    glVertex3f(5.f,  5.f, -5.f);
		    glVertex3f(5.f,  5.f,  5.f);
		    glVertex3f(5.f, -5.f,  5.f);

		    glVertex3f(-5.f, -5.f,  5.f);
		    glVertex3f(-5.f, -5.f, -5.f);
		    glVertex3f( 5.f, -5.f, -5.f);
		    glVertex3f( 5.f, -5.f,  5.f);

		    glVertex3f(-5.f, 5.f,  5.f);
		    glVertex3f(-5.f, 5.f, -5.f);
		    glVertex3f( 5.f, 5.f, -5.f);
		    glVertex3f( 5.f, 5.f,  5.f);

		glEnd();


		//END OF CUBE

		glEnd();
	}
};
#endif /* OGLIMAGE_H_ */
