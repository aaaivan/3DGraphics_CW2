#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H
#include "Wall.h"
#include "Ball.h"
#include "Slider.h"
#include <GL/freeglut.h>
#include <string>


class GameManager {
	std::vector<Wall> walls;
	Ball ball;
	GLint points, targetsLeft, attemptsLeft;
	Slider horizontalSlider;
	Slider verticalSlider;
	std::string scoreString;
	GLboolean endOfGame;
public:
	GameManager();
	static void loadTextures();
	static void unloadTextures();
	Slider* hSlider();
	Slider* vSlider();
	void shootBall();
	void update(GLfloat time);
	void drawScene();
	void drawGUI(GLint windowW, GLint windowH);
private:
	void writeBitmapString(void* font, char* str);
	void setOrthographicProjection(GLint windowW, GLint windowH);
	void setPerspectiveProjection();
};

#endif // !GAME_MANAGER_H
