#include "Terrain.h"
#include <iostream>

using namespace std;

Terrain::Terrain()
{
}

void Terrain::create(std::string image, float x, float y, b2World *world, float width, float height, BODY_TYPE physicsType, Level *l, BODY_SHAPE shape)
{
	Entity::create(image, x, y, world,width,height,physicsType,l,shape);

	/*
	texture.loadFromFile(image);

	graphics = new sf::Sprite(texture);
	physics = new PhysicsBody(x, y, 1920, 128, world, STATIC);

	physics->getBody()->SetFixedRotation(true);
	physics->getBody()->SetUserData(this);
	physics = new PhysicsBody(x, y, 200, 100, world, DYNAMIC);
	physics->getBody()->SetFixedRotation(true);
	physics->getBody()->SetUserData(this);


	graphics->setOrigin(960, 64);
	graphics->setPosition(SCALE * physics->getPositionX(), SCALE * physics->getPositionY());
	graphics->setRotation(physics->getRotation() * 180 / b2_pi);*/
}

void Terrain::getInput(sf::Event *event)
{

}

void Terrain::checkCollision(Entity *other)
{

}

ENTITY_TYPE Terrain::getType()
{
	return TERRAIN;
}


void Terrain::update(sf::RenderWindow *window)
{
	//graphics->setPosition(SCALE * physics->getPositionX(), SCALE * physics->getPositionY());
	//graphics->setRotation(physics->getRotation() * 180 / b2_pi);


}

void Terrain::destroy()
{
	Entity::destroy();

}

Terrain::~Terrain()
{
}
