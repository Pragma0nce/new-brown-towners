#pragma once
#include "Entity.h"
#include "Weapon.h"

class Aim :
	public Entity
{
private:
	Weapon *owner;
public:

	void create(std::string image, float x, float y, b2World *world, float width, float height, BODY_TYPE physicsType, Level *l, BODY_SHAPE shape);
	void update(sf::RenderWindow *window);
	void getInput(sf::Event *event);
	void checkCollision(Entity *other);

	void setOwner(Weapon *weapon);

	ENTITY_TYPE getType();


	Aim();
	~Aim();
};

