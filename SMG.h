#pragma once
#include "Weapon.h"

class SMG : public Weapon
{
private:
	sf::Clock rot;
	int numBullets;
public:

	void create(std::string image, float x, float y, b2World *world, float width, float height, BODY_TYPE physicsType, Level *l, BODY_SHAPE shape);
	void fire(float power);
	void update(sf::RenderWindow *window);

	SMG();
	~SMG();
};

