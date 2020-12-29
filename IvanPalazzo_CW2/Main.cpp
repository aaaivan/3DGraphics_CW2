#include <iostream>
#include "Globals.h"
#include "CallbackFunctions.h"

int main(int argc, char** argv){
	//print controls to the consols
	std::cout << "**********FOOTBALL GAME: CONTROLS**********\n"
		<< "->Right button (mouse): main menu. Use it to restart the game or quit.\n"
		<< "->Arrow keys: aim ball up/down and left/right\n"
		<< "->Space bar: throw ball\n"
		<< "->F key: toggle camera view\n"
		<< std::endl;
	
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

	//function to update scene
	glutTimerFunc(FRAME_DURATION, update, 0);

	glutMainLoop();
}
