#pragma once
#include "Entity.h"
class Explosion :
	public Entity
{
private:
	sf::Clock timer;
	int size;
public:

	void create(std::string image, float x, float y, b2World *world, float width, float height, BODY_TYPE physicsType, Level *l, BODY_SHAPE shape);
	void update(sf::RenderWindow *window);
	void getInput(sf::Event *event);

	ENTITY_TYPE getType();

	// Collision based classes
	void checkCollision(Entity *other);
	void endCollision(Entity *other);

	int getSize(){ return size; };

	void destroy();

	Explosion();
	~Explosion();
};

