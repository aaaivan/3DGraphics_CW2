#include "GameManager.h"
#include "Globals.h"
#include <algorithm>

GameManager::GameManager():
ball(BALL_RADIUS,
	{BALL_INIT_POSITION_X, BALL_RADIUS, BALL_INIT_POSITION_Z},
	BALL_LINEAR_SPEED,
	BALL_ANGULAR_SPEED),
horizontalSlider(Slider::Orientation::HORIZONTAL, SLIDER_LENGTH, SLIDER_THICKNESS),
verticalSlider(Slider::Orientation::VERTICAL, SLIDER_THICKNESS, SLIDER_LENGTH),
scoreString("Score: "), endOfGame(false), points(0), attemptsLeft(MAX_BALL_THROWS){
	walls.push_back(Wall(
		SIDE_WALL_LENGTH,
		WALL_HEIGHT,
		{ -FRONT_WALL_LENGTH / 2, WALL_HEIGHT / 2, -SIDE_WALL_LENGTH / 2 },
		90));
	walls.push_back(Wall(
		FRONT_WALL_LENGTH,
		WALL_HEIGHT,
		{ 0, WALL_HEIGHT / 2, -SIDE_WALL_LENGTH },
		0));
	walls.push_back(Wall(
		SIDE_WALL_LENGTH,
		WALL_HEIGHT,
		{ FRONT_WALL_LENGTH / 2, WALL_HEIGHT / 2, -SIDE_WALL_LENGTH / 2 },
		270));
	walls[1].addTarget(FRONT_WALL_LENGTH / 2 - 1.2f * TARGET30_SIZE, WALL_HEIGHT/2 - 1.2f * TARGET30_SIZE, Target::Points::THIRTY, &targetsLeft);
	walls[1].addTarget(-FRONT_WALL_LENGTH / 2 + 1.2f * TARGET30_SIZE, WALL_HEIGHT/2 - 1.2f * TARGET30_SIZE, Target::Points::THIRTY, &targetsLeft);
	walls[1].addTarget(FRONT_WALL_LENGTH / 2 - 1.2f * TARGET30_SIZE, -WALL_HEIGHT/2 + 1.2f * TARGET30_SIZE, Target::Points::THIRTY, &targetsLeft);
	walls[1].addTarget(-FRONT_WALL_LENGTH / 2 + 1.2f * TARGET30_SIZE, -WALL_HEIGHT/2 + 1.2f * TARGET30_SIZE, Target::Points::THIRTY, &targetsLeft);
	walls[1].addTarget(FRONT_WALL_LENGTH *0.22f, 0, Target::Points::TWENTY, &targetsLeft);
	walls[1].addTarget(-FRONT_WALL_LENGTH * 0.22f, 0, Target::Points::TWENTY, &targetsLeft);
	walls[1].addTarget(0, WALL_HEIGHT * 0.22f, Target::Points::TEN, &targetsLeft);
	walls[1].addTarget(0, -WALL_HEIGHT * 0.22f, Target::Points::TEN, &targetsLeft);
}

void GameManager::loadTextures() {
	Ball::loadTexture();
	Wall::loadTexture();
	Slider::loadTextures();
}

void GameManager::unloadTextures(){
	Ball::unloadTexture();
	Wall::unloadTexture();
	Slider::unloadTextures();
}

Slider* GameManager::hSlider() {
	return &horizontalSlider;
}

Slider* GameManager::vSlider() {
	return &verticalSlider;
}

void GameManager::shootBall(){
	if (attemptsLeft == 0)
		return;
	if (ball.shoot(horizontalSlider.getValue(), verticalSlider.getValue(0,0.5f)))
		attemptsLeft--;
}

void GameManager::update(GLfloat time){
	if (!endOfGame) {
		ball.update(time);
		for (Wall& w : walls) {
			GLint pointsGained = 0;
			if (w.checkCollision(&ball, &pointsGained)) {
				ball.reset();
				if (pointsGained > 0) {
					points += pointsGained;
					targetsLeft--;
				}
				if (targetsLeft == 0) {
					scoreString = "You Won! Score: ";
					endOfGame = true;
				}
				else if (attemptsLeft == 0) {
					scoreString = "You Lost! Score: ";
					endOfGame = true;
				}
			}
		}
	}
}

void GameManager::drawScene() {
	for (Wall &w : walls)
		w.draw();
	ball.draw();
}

void GameManager::drawGUI(GLint windowW, GLint windowH) {
	setOrthographicProjection(windowW, windowH);
	glDisable(GL_DEPTH_TEST);
	glDisableClientState(GL_NORMAL_ARRAY);

	//draw score message
	glColor3f(0.6f, 0, 0);
	std::string message = scoreString + std::to_string(points);
	char* str = &message[0];
	size_t l=strlen(str);
	glRasterPos2f(windowW * 0.5f - l * 4.8f, windowH * 0.88f);
	writeBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, str);
	//draw attempts left message
	message = "Attempts left: " + std::to_string(attemptsLeft);
	str = &message[0];
	l = strlen(str);
	glRasterPos2f(windowW * 0.5f - l * 4.8f, windowH * 0.88-25.0f);
	writeBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, str);
	glColor3f(1, 1, 1);
	//draw sliders
	GLfloat scale = std::min(static_cast<float>(windowW) / WINDOW_WIDTH, static_cast<float>(windowH) / WINDOW_HEIGHT);
	verticalSlider.draw(SLIDER_POSITION_X * scale, SLIDER_POSITION_Y * scale, scale);
	horizontalSlider.draw(SLIDER_POSITION_Y * scale, SLIDER_POSITION_X * scale, scale);

	glEnable(GL_DEPTH_TEST);
	glEnableClientState(GL_NORMAL_ARRAY);
	setPerspectiveProjection();
}

void GameManager::writeBitmapString(void* font, char* str) {
	char* c;
	for (c = str; *c != '\0'; c++)
		glutBitmapCharacter(font, *c);
}

void GameManager::setOrthographicProjection(GLint windowW, GLint windowH){
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, windowW, 0, windowH);
	glMatrixMode(GL_MODELVIEW);
}

void GameManager::setPerspectiveProjection(){
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}