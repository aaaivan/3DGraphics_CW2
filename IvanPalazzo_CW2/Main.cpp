#include <iostream>
#include "Globals.h"
#include "CallbackFunctions.h"

int main(int argc, char** argv){

	//std::cout << "**********FOOTBALL: CONTROLS**********\n->Mouse's right button: main menu\n" <<
	//	"->WASD/Arrow keys: move/rotate car (you can select your preferred control type from the menu)" << std::endl;
	
	//initialize freeglut library
	glutInit(&argc, argv);
	//double buffer, each pixel defined by rgba value, depth test enabled
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	//window properties (size, position, name)
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(WINDOW_POS_X, WINDOW_POS_Y);
	glutCreateWindow("Footbal game");
	//display routine
	glutDisplayFunc(display);
	//window reshape routine
	glutReshapeFunc(reshape);
	//keyboard input
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);

	//setup routine
	setup();

	//animation
	glutTimerFunc(FRAME_DURATION, update, 0);

	glutMainLoop();
}
