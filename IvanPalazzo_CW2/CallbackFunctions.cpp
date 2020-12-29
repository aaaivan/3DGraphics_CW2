#include "GameManager.h"
#include "Props.h"
#include "Skybox.h"
#include "Lighting.h"
#include "CallbackFunctions.h"
#include "Globals.h"
#include <cmath>

GameManager* gameManager = nullptr;
Props props; //plants, flowers and grass
Skybox skybox(SKYBOX_SIZE, SKYBOX_ROTATION_SPEED);
GLint windowW = 0, windowH = 0;
GLboolean followBall = false; //toggle between fixed and moving camera

void setup(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	
	//create main menu
	createMenu();

	//load all textures
	Skybox::loadTexture();
	Props::loadTextures();
	GameManager::loadTextures();

	gameManager = new GameManager();

	//set flags for drawing statements
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	//enable alpha test to ignore transparent pixels
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0);
	//enable alpha blending for transparency
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Cull back faces
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	//set material properties
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, Lighting::m_ambientAndDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, Lighting::m_specular);
	//set lighting properties
	glEnable(GL_LIGHTING);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Lighting::l_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Lighting::spot_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, Lighting::spot_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, Lighting::spot_position);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, Lighting::spot_angle);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, Lighting::spot_quadAtten);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Lighting::spot_direction);
}

void createMenu(void) {
	glutCreateMenu(mainMenu);
	glutAddMenuEntry("Restart", 0); //restart game
	glutAddMenuEntry("Quit", 1); //quit application
	//menu attached to right mouse click
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void mainMenu(GLint option) {
	switch (option)
	{
	case 0:
		delete gameManager;
		//create new instance of GameManager to reset the game
		gameManager = new GameManager();
		break;
	case 1:
		//release memory and exit application
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

//drawign routine
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	if (followBall) {//moving camera
		//calculate position of the ball relative to its starting position
		std::vector<GLfloat> relPos = gameManager->ballPtr()->relToInitPosition();
		//reposition the spotlight manually as lights are not moved by transformations
		GLfloat lightRelPos[4] = {
			Lighting::spot_position[0] - relPos[0],
			Lighting::spot_position[1] - relPos[1],
			Lighting::spot_position[2] - relPos[2],
			1
		};
		glLightfv(GL_LIGHT0, GL_POSITION, lightRelPos);
		//translate the whole world to bring the ball back directly in front of the camera
		glTranslatef(-relPos[0], -relPos[1], -relPos[2]);
	}
	//position camera
	gluLookAt(0, 1, 0, 0, 1, -1, 0, 1, 0);

	skybox.draw();
	gameManager->drawScene();
	props.draw();
	gameManager->drawGUI(windowW, windowH);

	glutSwapBuffers();
}

//reshape window
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

//read input from the keyboard
void keyboard(unsigned char key, GLint x, GLint y) {
	switch (key)
	{
	case ' ': //shoot the ball
		gameManager->shootBall();
		break;
	case 'f'://change camera view
		followBall = !followBall;
		break;
	default:
		break;
	}
}

//read input from the keyboard
void special(GLint key, GLint x, GLint y) {
	switch (key)
	{
	case GLUT_KEY_UP: //move vertical slider up
		gameManager->moveSlider(SLIDER_INCREMENT, Slider::Orientation::VERTICAL);
		break;
	case GLUT_KEY_LEFT: //move horizontal slider left
		gameManager->moveSlider(-SLIDER_INCREMENT, Slider::Orientation::HORIZONTAL);
		break;
	case GLUT_KEY_DOWN: //move vertical slider up
		gameManager->moveSlider(-SLIDER_INCREMENT, Slider::Orientation::VERTICAL);
		break;
	case GLUT_KEY_RIGHT: //move horizontal slider right
		gameManager->moveSlider(SLIDER_INCREMENT, Slider::Orientation::HORIZONTAL);
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

//update scene
void update(GLint index) {
	gameManager->update(FRAME_DURATION/1000.0f);
	skybox.update(FRAME_DURATION / 1000.0f);

	glutPostRedisplay();
	glutTimerFunc(FRAME_DURATION, update, 0);
}
