#include "CallbackFunctions.h"
#include "Globals.h"
#include <cmath>
#include "GameManager.h"

GameManager gameManager;

void setup(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	createMenu();
	GameManager::loadTextures();
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Cull the back faces of the sphere.
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void createMenu(void) {
	glutCreateMenu(mainMenu);
	glutAddMenuEntry("Restart", 0);
	glutAddMenuEntry("Quit", 1);
	//menu attached to right mouse click
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void mainMenu(GLint option) {
	switch (option)
	{
	case 0:
		//restart;
		break;
	case 1:
		exit(0);
		break;
	default:
		break;
	}
}


void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0, 1, 0, 0, 1, -1, 0, 1, 0);

	gameManager.draw();

	glutSwapBuffers();
}

void reshape(GLint w, GLint h) {
	GLdouble aspect = static_cast<float>(w) / h;
	GLdouble defaultAspect = static_cast<float>(WINDOW_WIDTH) / WINDOW_HEIGHT;

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (aspect >= defaultAspect)
		glFrustum(-1 / defaultAspect * aspect, 1 / defaultAspect * aspect, -1 / defaultAspect, 1 / defaultAspect, 1, 50);
	else
		glFrustum(-1, 1, -1 / aspect, 1 / aspect, 1, 50);
	glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, GLint x, GLint y) {

}

void special(GLint key, GLint x, GLint y) {

}

void update(GLint index) {

}
