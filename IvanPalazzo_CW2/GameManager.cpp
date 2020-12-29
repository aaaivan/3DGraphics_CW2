#include "GameManager.h"
#include "Globals.h"
#include <algorithm>

//constructor: initialize all the game objects and variables 
GameManager::GameManager():
ball(BALL_RADIUS,
	{BALL_INIT_POSITION_X, BALL_RADIUS, BALL_INIT_POSITION_Z},
	BALL_LINEAR_SPEED,
	BALL_ANGULAR_SPEED),
horizontalSlider(Slider::Orientation::HORIZONTAL, SLIDER_LENGTH, SLIDER_THICKNESS),
verticalSlider(Slider::Orientation::VERTICAL, SLIDER_THICKNESS, SLIDER_LENGTH),
scoreString("Score: "), endOfGame(false), points(0), attemptsLeft(MAX_BALL_THROWS){
	//create walls
	walls.push_back(Wall(
		SIDE_WALL_LENGTH + WALL_THICKNESS,
		WALL_HEIGHT,
		{ -FRONT_WALL_LENGTH / 2, WALL_HEIGHT / 2, -(SIDE_WALL_LENGTH + WALL_THICKNESS) / 2 },
		90));
	walls.push_back(Wall(
		FRONT_WALL_LENGTH,
		WALL_HEIGHT,
		{ 0, WALL_HEIGHT / 2, -SIDE_WALL_LENGTH },
		0));
	walls.push_back(Wall(
		SIDE_WALL_LENGTH + WALL_THICKNESS,
		WALL_HEIGHT,
		{ FRONT_WALL_LENGTH / 2, WALL_HEIGHT / 2, -(SIDE_WALL_LENGTH + WALL_THICKNESS) / 2 },
		270));
	//add targets to the wall at the back
	walls[1].addTarget(FRONT_WALL_LENGTH / 2 - 1.2f * TARGET30_SIZE, WALL_HEIGHT/2 - 1.2f * TARGET30_SIZE, Target::Points::THIRTY, &targetsLeft);
	walls[1].addTarget(-FRONT_WALL_LENGTH / 2 + 1.2f * TARGET30_SIZE, WALL_HEIGHT/2 - 1.2f * TARGET30_SIZE, Target::Points::THIRTY, &targetsLeft);
	walls[1].addTarget(FRONT_WALL_LENGTH / 2 - 1.2f * TARGET30_SIZE, -WALL_HEIGHT/2 + 1.2f * TARGET30_SIZE, Target::Points::THIRTY, &targetsLeft);
	walls[1].addTarget(-FRONT_WALL_LENGTH / 2 + 1.2f * TARGET30_SIZE, -WALL_HEIGHT/2 + 1.2f * TARGET30_SIZE, Target::Points::THIRTY, &targetsLeft);
	walls[1].addTarget(FRONT_WALL_LENGTH *0.22f, 0, Target::Points::TWENTY, &targetsLeft);
	walls[1].addTarget(-FRONT_WALL_LENGTH * 0.22f, 0, Target::Points::TWENTY, &targetsLeft);
	walls[1].addTarget(0, WALL_HEIGHT * 0.22f, Target::Points::TEN, &targetsLeft);
	walls[1].addTarget(0, -WALL_HEIGHT * 0.22f, Target::Points::TEN, &targetsLeft);
}

//load textures for rendering
void GameManager::loadTextures() {
	Ball::loadTexture();
	Wall::loadTexture();
	Slider::loadTextures();
}

//delete textures from memory
void GameManager::unloadTextures(){
	Ball::unloadTexture();
	Wall::unloadTexture();
	Slider::unloadTextures();
}

//move th evertical and horizontal slider
void GameManager::moveSlider(GLfloat amount, Slider::Orientation orientation){
	if (!endOfGame) {
		if (orientation == Slider::Orientation::HORIZONTAL)
			horizontalSlider.changeValue(amount);
		else
			verticalSlider.changeValue(amount);
	}
}

Ball const* GameManager::ballPtr() const {
	return &ball;
}

//shoot the ball if the game is not over
void GameManager::shootBall(){
	if (endOfGame)
		return;
	if (ball.shoot(horizontalSlider.getValue(), verticalSlider.getValue(0,0.5f)))
		attemptsLeft--;
}

//update scene
void GameManager::update(GLfloat time){
	if (!endOfGame) {
		ball.update(time);
		//check collision with the walls
		for (Wall& w : walls) {
			GLint pointsGained = 0;
			if (w.checkCollision(&ball, &pointsGained)) {//collision detected
				ball.reset();
				if (pointsGained > 0) {//target hit
					points += pointsGained;
					targetsLeft--;
				}
				if (targetsLeft == 0) {//all targets have been hit
					scoreString = "You Won! Score: ";
					endOfGame = true;
				}
				else if (attemptsLeft == 0) {//no attempts left: game over
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
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glDisableClientState(GL_NORMAL_ARRAY);

	//draw score message
	glColor3f(0, 0, 0);
	std::string message = scoreString + std::to_string(points);
	char* str = &message[0];
	size_t l=strlen(str);
	glRasterPos2f(windowW * 0.5f - l * 4.8f, windowH * 0.85f);
	writeBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, str);
	//draw attempts left message
	message = "Attempts left: " + std::to_string(attemptsLeft);
	str = &message[0];
	l = strlen(str);
	glRasterPos2f(windowW * 0.5f - l * 4.8f, windowH * 0.85-25.0f);
	writeBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, str);
	glColor3f(1, 1, 1);
	//draw sliders
	GLfloat scale = std::min(static_cast<float>(windowW) / WINDOW_WIDTH, static_cast<float>(windowH) / WINDOW_HEIGHT);
	verticalSlider.draw(SLIDER_POSITION_X * scale, SLIDER_POSITION_Y * scale, scale);
	horizontalSlider.draw(SLIDER_POSITION_Y * scale, SLIDER_POSITION_X * scale, scale);

	glEnable(GL_DEPTH_TEST);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnable(GL_LIGHTING);
	setPerspectiveProjection();
}

//display string on the scene
void GameManager::writeBitmapString(void* font, char* str) {
	char* c;
	for (c = str; *c != '\0'; c++)
		glutBitmapCharacter(font, *c);
}

//swich to orthographic projection
void GameManager::setOrthographicProjection(GLint windowW, GLint windowH){
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, windowW, 0, windowH);
	glMatrixMode(GL_MODELVIEW);
}

//swich to perspective projection
void GameManager::setPerspectiveProjection(){
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}