#include "Entity.h"
#include <iostream>
#include "Level.h"
using namespace std;

Entity::Entity()
{

}

void Entity::update(sf::RenderWindow *window)
{
	graphics->setPosition(SCALE * physics->getPositionX(), SCALE * physics->getPositionY());
	graphics->setRotation(physics->getRotation() * 180 / b2_pi);
}

bool Entity::isDead()
{
	if (!isAlive)
		return true;
	else
		return false;
}

void Entity::destroy()
{
	isAlive = false;
}

void Entity::create(std::string image, float x, float y, b2World *world, float width, float height, BODY_TYPE physicsType, Level *l, BODY_SHAPE shape)
{
	// Setting up the graphics
	isAlive = true;
	level = l;
	dir = LEFT;
	texture.loadFromFile(image);

	graphics = new sf::Sprite(texture);

	float xScale = width/texture.getSize().x;
	float yScale = height/texture.getSize().y;

	cout << texture.getSize().x << xScale << endl;
	cout << texture.getSize().y << yScale << endl;

	graphics->setScale(xScale, yScale);

	graphics->setOrigin(texture.getSize().x/2,texture.getSize().y/2);
	graphics->setPosition(x, y);

	cout <<"WIDTH: " << graphics->getGlobalBounds().width << endl;
	cout <<"HEIGHT: " << graphics->getGlobalBounds().height << endl;
	cout << "ORIGIN:" << width / 2 << endl;
	cout << "ORIGIN:" << height / 2 << endl;


	// Setting up the physics
	physics = new PhysicsBody(x, y, width, height, world, physicsType,shape);	
	//physics->getBody()->SetFixedRotation(true);
	physics->getBody()->SetUserData(this);
}

void Entity::endCollision(Entity *other)
{

}
Entity::~Entity()
{
	level->world->DestroyBody(physics->getBody());
}
