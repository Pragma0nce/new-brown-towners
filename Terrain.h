#pragma once

#include <SFML\Graphics.hpp>
#include "Entity.h"

class Terrain : public Entity
{
private:
	//sf::Texture texture;
public:
	//PhysicsBody *physics;
	//sf::Sprite *graphics;

	void create(std::string image, float x, float y, b2World *world, float width, float height, BODY_TYPE physicsType, Level *l, BODY_SHAPE shape);
	void update(sf::RenderWindow *window);
	void getInput(sf::Event *event);

	ENTITY_TYPE getType();

	// Collision based classes
	void checkCollision(Entity *other);
	void destroy();

	Terrain();
	~Terrain();
};

