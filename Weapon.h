#pragma once
#include "Entity.h"
#include "Player.h"

class Aim;

class Weapon :
	public Entity
{

protected:
	Player *owner;
	float fireAngle;
	Aim *aim;


public:

	float getFireAngle(){ return fireAngle; };
	virtual void fire(float power);


	virtual void create(std::string image, float x, float y, b2World *world, float width, float height, BODY_TYPE physicsType, Level *l, BODY_SHAPE shape);
	virtual void update(sf::RenderWindow *window);
	virtual void getInput(sf::Event *event);

	void setAim(DIRECTION dir);
	void setAngle(float angle){ fireAngle = angle; };

	void setOwner(Player *player);
	Player *getOwner(){ return owner; };

	virtual ENTITY_TYPE getType();

	// Collision based classes
	virtual void checkCollision(Entity *other);

	virtual void destroy();

	Weapon();
	~Weapon();
};

