#pragma once
#include <Box2D\Box2D.h>
#include <SFML\Graphics.hpp>
#include "PhysicsBody.h"

enum ENTITY_TYPE
{
	TERRAIN,
	PLAYER,
	WEAPON,
	PROJECTILE,
	BLOCK,
	GRENADE,
	EXPLOSION,
	AIM,
	BUTTON
};

enum DIRECTION{
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class Level;

class Entity 
{
protected:
	sf::Texture texture;
	DIRECTION dir;
	Level *level;

	bool isAlive;

public:
	PhysicsBody *physics;
	sf::Sprite *graphics;

	DIRECTION getDir(){ return dir; };
	void changeDirection(DIRECTION d)
	{
		dir = d;
		graphics->setScale(-graphics->getScale().x, graphics->getScale().y);
	}

	virtual void create(std::string image, float x, float y, b2World *world, float width, float height, BODY_TYPE physicsType, Level *l, BODY_SHAPE shape);
	virtual void update(sf::RenderWindow *window)=0;
	virtual void getInput(sf::Event *event)=0;
	virtual void destroy();

	bool isDead();

	virtual ENTITY_TYPE getType()=0;

	Entity();
	~Entity();

	virtual void checkCollision(Entity *other)=0;
	virtual void endCollision(Entity *other);
};

