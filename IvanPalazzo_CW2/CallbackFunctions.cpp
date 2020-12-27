#include "GameManager.h"
#include "Props.h"
#include "Skybox.h"
#include "CallbackFunctions.h"
#include "Globals.h"
#include <cmath>

GameManager* gameManager = nullptr;
Props props;
Skybox skybox(SKYBOX_SIZE, SKYBOX_ROTATION_SPEED);
GLint windowW = 0, windowH = 0;
void setup(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	createMenu();

	Skybox::loadTexture();
	Props::loadTextures();
	GameManager::loadTextures();
	gameManager = new GameManager();

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
		delete gameManager;
		gameManager = new GameManager();
		break;
	case 1:
		delete gameManager;
		GameManager::unloadTextures();
		Props::unloadTextures();
		Skybox::unloadTexture();
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

	skybox.draw();
	gameManager->drawScene();
	props.draw();
	gameManager->drawGUI(windowW, windowH);

	glutSwapBuffers();
}

void reshape(GLint w, GLint h) {
	GLdouble aspect = static_cast<float>(w) / h;
	GLdouble defaultAspect = static_cast<float>(WINDOW_WIDTH) / WINDOW_HEIGHT;
	windowW = w;
	windowH = h;

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (aspect >= defaultAspect)
		glFrustum(-1 / defaultAspect * aspect, 1 / defaultAspect * aspect, -1 / defaultAspect, 1 / defaultAspect, 1, 0.75f*SKYBOX_SIZE);
	else
		glFrustum(-1, 1, -1 / aspect, 1 / aspect, 1, 0.75f * SKYBOX_SIZE);
	glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, GLint x, GLint y) {
	switch (key)
	{
	case ' ': //move car forward
		gameManager->shootBall();
		break;
	default:
		break;
	}
}

void special(GLint key, GLint x, GLint y) {
	switch (key)
	{
	case GLUT_KEY_UP: //move car forward
		gameManager->vSlider()->increase(SLIDER_INCREMENT);
		break;
	case GLUT_KEY_LEFT: //rotate car anticlockwise
		gameManager->hSlider()->decrease(SLIDER_INCREMENT);
		break;
	case GLUT_KEY_DOWN: //move car backwards
		gameManager->vSlider()->decrease(SLIDER_INCREMENT);
		break;
	case GLUT_KEY_RIGHT: //rotate car clockwise
		gameManager->hSlider()->increase(SLIDER_INCREMENT);
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void update(GLint index) {
	gameManager->update(FRAME_DURATION/1000.0f);
	skybox.Update(FRAME_DURATION / 1000.0f);
	glutPostRedisplay();
	glutTimerFunc(FRAME_DURATION, update, 0);
}
