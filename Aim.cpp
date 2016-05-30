#include "Aim.h"


Aim::Aim()
{
}

void Aim::create(std::string image, float x, float y, b2World *world, float width, float height, BODY_TYPE physicsType, Level *l, BODY_SHAPE shape)
{
	Entity::create(image, x, y, world, width, height, physicsType, l, shape);
}
void Aim::update(sf::RenderWindow *window)
{
	Entity::update(window);
	
	if (owner->getOwner()->getDir() == RIGHT)
		graphics->setPosition(owner->graphics->getPosition().x + cos(owner->getFireAngle()) * 150, owner->graphics->getPosition().y + sin(owner->getFireAngle()) * 150);
	else
		graphics->setPosition(owner->graphics->getPosition().x  - cos(owner->getFireAngle()) * 150, owner->graphics->getPosition().y - sin(owner->getFireAngle()) * 150);

}

void Aim::setOwner(Weapon *o)
{
	owner = o;
}
void Aim::getInput(sf::Event *event)
{

}

ENTITY_TYPE Aim::getType()
{
	return AIM;
}

void Aim::checkCollision(Entity *other)
{

}

Aim::~Aim()
{
}
