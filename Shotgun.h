#pragma once
#include "Weapon.h"
class Shotgun :
	public Weapon
{
public:

	//void create(std::string image, float x, float y, b2World *world, float width, float height, BODY_TYPE physicsType, Level *l, BODY_SHAPE shape);
	//void update(sf::RenderWindow *window);
	//void getInput(sf::Event *event);

	void fire(float power);

	//ENTITY_TYPE getType();
	//void checkCollision(Entity *other);


	//void destroy();
	Shotgun();
	~Shotgun();
};

