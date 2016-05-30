#pragma once
#include "Entity.h"
#include "Weapon.h"

class Projectile :
	public Entity
{
private:
	bool canExplode;
	bool hasExploded;

	float explosionSize;
	b2Vec2 colPos;

	bool follow;

	sf::Clock safeZone;
	sf::Clock fuse;

	Weapon *owner;

public:
	bool hasFuse;

	void create(std::string image, float x, float y, b2World *world, float width, float height, BODY_TYPE physicsType, Level *l, BODY_SHAPE shape);
	void update(sf::RenderWindow *window);
	void getInput(sf::Event *event);

	void shouldFollow(bool b){ follow = b; };

	void explode();
	void setExplosionSize(float p);

	void setOwner(Weapon *o){ owner = o; };
	Weapon *getOwner(){ return owner; };

	ENTITY_TYPE getType();

	// Collision based classes
	void checkCollision(Entity *other);
	void destroy();

	Projectile();
	~Projectile();
};

