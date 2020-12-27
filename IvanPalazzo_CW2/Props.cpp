#include "Props.h"
#include "Globals.h"

Props::Props():
grass(FRONT_WALL_LENGTH, SIDE_WALL_LENGTH), plants() {
	plants.push_back(Plant(PALM_WIDTH, PALM_HEIGHT, { -FRONT_WALL_LENGTH / 2 + 0.1f, PALM_HEIGHT / 2, -2.7f }, 90, Plant::Type::PALM));
	plants.push_back(Plant(PALM_WIDTH, PALM_HEIGHT, { -FRONT_WALL_LENGTH / 2 + 0.1f, PALM_HEIGHT / 2, -3.5f }, 90, Plant::Type::PALM));
	plants.push_back(Plant(PALM_WIDTH, PALM_HEIGHT, { -FRONT_WALL_LENGTH / 2 + 0.1f, PALM_HEIGHT / 2, -4.3f }, 90, Plant::Type::PALM));
	plants.push_back(Plant(PALM_WIDTH, PALM_HEIGHT, { -FRONT_WALL_LENGTH / 2 + 0.1f, PALM_HEIGHT / 2, -5.1f }, 90, Plant::Type::PALM));
	plants.push_back(Plant(PALM_WIDTH, PALM_HEIGHT, { -FRONT_WALL_LENGTH / 2 + 0.1f, PALM_HEIGHT / 2, -5.9f }, 90, Plant::Type::PALM));
	plants.push_back(Plant(PALM_WIDTH, PALM_HEIGHT, { -FRONT_WALL_LENGTH / 2 + 0.1f, PALM_HEIGHT / 2, -6.7f }, 90, Plant::Type::PALM));
	plants.push_back(Plant(PALM_WIDTH, PALM_HEIGHT, { -FRONT_WALL_LENGTH / 2 + 0.1f, PALM_HEIGHT / 2, -7.5f }, 90, Plant::Type::PALM));
	plants.push_back(Plant(PALM_WIDTH, PALM_HEIGHT, { FRONT_WALL_LENGTH / 2 - 0.1f, PALM_HEIGHT / 2, -2.7f }, 270, Plant::Type::PALM));
	plants.push_back(Plant(PALM_WIDTH, PALM_HEIGHT, { FRONT_WALL_LENGTH / 2 - 0.1f, PALM_HEIGHT / 2, -3.5f }, 270, Plant::Type::PALM));
	plants.push_back(Plant(PALM_WIDTH, PALM_HEIGHT, { FRONT_WALL_LENGTH / 2 - 0.1f, PALM_HEIGHT / 2, -4.3f }, 270, Plant::Type::PALM));
	plants.push_back(Plant(PALM_WIDTH, PALM_HEIGHT, { FRONT_WALL_LENGTH / 2 - 0.1f, PALM_HEIGHT / 2, -5.1f }, 270, Plant::Type::PALM));
	plants.push_back(Plant(PALM_WIDTH, PALM_HEIGHT, { FRONT_WALL_LENGTH / 2 - 0.1f, PALM_HEIGHT / 2, -5.9f }, 270, Plant::Type::PALM));
	plants.push_back(Plant(PALM_WIDTH, PALM_HEIGHT, { FRONT_WALL_LENGTH / 2 - 0.1f, PALM_HEIGHT / 2, -6.7f }, 270, Plant::Type::PALM));
	plants.push_back(Plant(PALM_WIDTH, PALM_HEIGHT, { FRONT_WALL_LENGTH / 2 - 0.1f, PALM_HEIGHT / 2, -7.5f }, 270, Plant::Type::PALM));
	plants.push_back(Plant(FLOWER_WIDTH, FLOWER_HEIGHT, { -3.5f, FLOWER_HEIGHT / 2, -SIDE_WALL_LENGTH + 0.1f }, 0, Plant::Type::YELLOW_FLOWER));
	plants.push_back(Plant(FLOWER_WIDTH, FLOWER_HEIGHT, { -2.5f, FLOWER_HEIGHT / 2, -SIDE_WALL_LENGTH + 0.1f }, 0, Plant::Type::YELLOW_FLOWER));
	plants.push_back(Plant(FLOWER_WIDTH, FLOWER_HEIGHT, { -1.5f, FLOWER_HEIGHT / 2, -SIDE_WALL_LENGTH + 0.1f }, 0, Plant::Type::YELLOW_FLOWER));
	plants.push_back(Plant(FLOWER_WIDTH, FLOWER_HEIGHT, { -0.5f, FLOWER_HEIGHT / 2, -SIDE_WALL_LENGTH + 0.1f }, 0, Plant::Type::YELLOW_FLOWER));
	plants.push_back(Plant(FLOWER_WIDTH, FLOWER_HEIGHT, { 0.5, FLOWER_HEIGHT / 2, -SIDE_WALL_LENGTH + 0.1f }, 0, Plant::Type::YELLOW_FLOWER));
	plants.push_back(Plant(FLOWER_WIDTH, FLOWER_HEIGHT, { 1.5, FLOWER_HEIGHT / 2, -SIDE_WALL_LENGTH + 0.1f }, 0, Plant::Type::YELLOW_FLOWER));
	plants.push_back(Plant(FLOWER_WIDTH, FLOWER_HEIGHT, { 2.5, FLOWER_HEIGHT / 2, -SIDE_WALL_LENGTH + 0.1f }, 0, Plant::Type::YELLOW_FLOWER));
	plants.push_back(Plant(FLOWER_WIDTH, FLOWER_HEIGHT, { 3.5, FLOWER_HEIGHT / 2, -SIDE_WALL_LENGTH + 0.1f }, 0, Plant::Type::YELLOW_FLOWER));
	plants.push_back(Plant(FLOWER_WIDTH, FLOWER_HEIGHT, { -3, FLOWER_HEIGHT / 2, -SIDE_WALL_LENGTH + 0.1f }, 0, Plant::Type::ORANGE_FLOWER));
	plants.push_back(Plant(FLOWER_WIDTH, FLOWER_HEIGHT, { -2, FLOWER_HEIGHT / 2, -SIDE_WALL_LENGTH + 0.1f }, 0, Plant::Type::ORANGE_FLOWER));
	plants.push_back(Plant(FLOWER_WIDTH, FLOWER_HEIGHT, { -1, FLOWER_HEIGHT / 2, -SIDE_WALL_LENGTH + 0.1f }, 0, Plant::Type::ORANGE_FLOWER));
	plants.push_back(Plant(FLOWER_WIDTH, FLOWER_HEIGHT, { 0, FLOWER_HEIGHT / 2, -SIDE_WALL_LENGTH + 0.1f }, 0, Plant::Type::ORANGE_FLOWER));
	plants.push_back(Plant(FLOWER_WIDTH, FLOWER_HEIGHT, { 1, FLOWER_HEIGHT / 2, -SIDE_WALL_LENGTH + 0.1f }, 0, Plant::Type::ORANGE_FLOWER));
	plants.push_back(Plant(FLOWER_WIDTH, FLOWER_HEIGHT, { 2, FLOWER_HEIGHT / 2, -SIDE_WALL_LENGTH + 0.1f }, 0, Plant::Type::ORANGE_FLOWER));
	plants.push_back(Plant(FLOWER_WIDTH, FLOWER_HEIGHT, { 3, FLOWER_HEIGHT / 2, -SIDE_WALL_LENGTH + 0.1f }, 0, Plant::Type::ORANGE_FLOWER));
}

void Props::loadTextures(){
	Plant::loadTextures();
	Grass::loadTexture();
}

void Props::unloadTextures(){
	Plant::unloadTextures();
	Grass::unloadTexture();
}

void Props::draw(){
	grass.draw();
	for (Plant& p : plants)
		p.draw();
}
