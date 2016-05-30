#include "SMG.h"
#include "Projectile.h"
#include "Level.h"
#include <iostream>
using namespace std;


SMG::SMG()
{
}

void SMG::create(std::string image, float x, float y, b2World *world, float width, float height, BODY_TYPE physicsType, Level *l, BODY_SHAPE shape)
{
	Weapon::create(image, x, y, world, width, height, physicsType, l, shape);
	numBullets = 0;
	rot.restart();
}

void SMG::update(sf::RenderWindow *window)
{
	Weapon::update(window);
	float powerMult = 1;
	
	int test = (rand() % 2 + 1);

	if (rot.getElapsedTime().asSeconds() >= 0.1f && numBullets > 0){
		Projectile *bullet = new Projectile();
		bullet->create("bullet.png", graphics->getPosition().x, graphics->getPosition().y, level->world, 4, 4, DYNAMIC, level, CIRCLE);
		bullet->physics->getBody()->GetFixtureList()[0].SetFriction(1);
		bullet->physics->getBody()->GetFixtureList()[0].SetDensity(2);
		bullet->physics->getBody()->SetGravityScale(0);
		bullet->physics->getBody()->ResetMassData();
		bullet->setExplosionSize(10);
		bullet->setOwner(this);


		level->AddEntity(bullet);
		numBullets -= 1;

		if (test == 1)
			fireAngle -= 0.01;
		else
			fireAngle += 0.01;

		if (owner->getDir() == RIGHT)
			bullet->physics->getBody()->ApplyLinearImpulse(b2Vec2(cos(getFireAngle())*powerMult, sin(getFireAngle())*powerMult), bullet->physics->getBody()->GetWorldCenter(), true);
		else if (owner->getDir() == LEFT)
			bullet->physics->getBody()->ApplyLinearImpulse(-b2Vec2(cos(getFireAngle())*powerMult, sin(getFireAngle())*powerMult), bullet->physics->getBody()->GetWorldCenter(), true);


		rot.restart();

	}
}

void SMG::fire(float power)
{
	numBullets = 20;
	/*
	srand(time(NULL));
	const double PI = 3.141592653589793238463;
	Projectile *bullet[5];

	for (int i = 0; i < 5; i++)
	{
		float angleDiff = 2 * i * b2_pi / 180;

		bullet[i] = new Projectile();
		bullet[i]->create("bullet.png", graphics->getPosition().x, graphics->getPosition().y, level->world, 8, 8, DYNAMIC, level, CIRCLE);

		if (owner->getDir() == RIGHT)
			bullet[i]->physics->getBody()->ApplyLinearImpulse(b2Vec2(cos(getFireAngle() + angleDiff), sin(getFireAngle() + angleDiff)), bullet[i]->physics->getBody()->GetWorldCenter(), true);
		else if (owner->getDir() == LEFT)
			bullet[i]->physics->getBody()->ApplyLinearImpulse(-b2Vec2(cos(getFireAngle() - angleDiff), sin(getFireAngle() - angleDiff)), bullet[i]->physics->getBody()->GetWorldCenter(), true);

		bullet[i]->physics->getBody()->GetFixtureList()[0].SetFriction(1);
		bullet[i]->physics->getBody()->GetFixtureList()[0].SetDensity(0.1);
		bullet[i]->physics->getBody()->SetGravityScale(0);
		bullet[i]->setExplosionSize(30);
		level->AddEntity(bullet[i]);
	}*/
}


SMG::~SMG()
{
}
