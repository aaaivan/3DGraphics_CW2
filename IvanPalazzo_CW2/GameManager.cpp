#include "GameManager.h"
#include "Globals.h"
GameManager::GameManager():
ball(BALL_RADIUS,
	{BALL_INIT_POSITION_X, BALL_RADIUS, BALL_INIT_POSITION_Z},
	BALL_LINEAR_SPEED,
	BALL_ANGULAR_SPEED),
horizontalSlider(Slider::Orientation::HORIZONTAL, SLIDER_WIDTH, SLIDER_HEIGHT),
verticalSlider(Slider::Orientation::VERTICAL, SLIDER_WIDTH, SLIDER_HEIGHT) {
	points = 0;
	attemptsLeft = MAX_BALL_THROWS;
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
	walls[1].addTarget(FRONT_WALL_LENGTH / 2 - 1.2f * TARGET30_SIZE, WALL_HEIGHT/2 - 1.2f * TARGET30_SIZE, Target::Points::THIRTY);
	walls[1].addTarget(-FRONT_WALL_LENGTH / 2 + 1.2f * TARGET30_SIZE, WALL_HEIGHT/2 - 1.2f * TARGET30_SIZE, Target::Points::THIRTY);
	walls[1].addTarget(FRONT_WALL_LENGTH / 2 - 1.2f * TARGET30_SIZE, -WALL_HEIGHT/2 + 1.2f * TARGET30_SIZE, Target::Points::THIRTY);
	walls[1].addTarget(-FRONT_WALL_LENGTH / 2 + 1.2f * TARGET30_SIZE, -WALL_HEIGHT/2 + 1.2f * TARGET30_SIZE, Target::Points::THIRTY);
	walls[1].addTarget(FRONT_WALL_LENGTH *0.22f, 0, Target::Points::TWENTY);
	walls[1].addTarget(-FRONT_WALL_LENGTH * 0.22f, 0, Target::Points::TWENTY);
	walls[1].addTarget(0, WALL_HEIGHT * 0.22f, Target::Points::TEN);
	walls[1].addTarget(0, -WALL_HEIGHT * 0.22f, Target::Points::TEN);
}

void GameManager::loadTextures() {
	Ball::loadTexture();
	Wall::loadTexture();
}

void GameManager::draw() {
	for (Wall &w : walls)
		w.draw();
	ball.draw();
}
