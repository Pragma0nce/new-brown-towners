#include "Grenade.h"
#include "Explosion.h"
#include "Projectile.h"
#include "Level.h"
#include <iostream>
using namespace std;



void Grenade::fire(float power)
{
	Projectile *bullet = new Projectile();
	bullet->create("grenade.png", graphics->getPosition().x + 10, graphics->getPosition().y, level->world, 20, 20, DYNAMIC, level, CIRCLE);
	bullet->physics->getBody()->ApplyLinearImpulse(b2Vec2(cos(getFireAngle()) * power*3, sin(getFireAngle()) * power*3), bullet->physics->getBody()->GetWorldCenter(), true);
	bullet->physics->getBody()->GetFixtureList()[0].SetFriction(1);
	bullet->physics->getBody()->GetFixtureList()[0].SetDensity(0.1);
	bullet->physics->getBody()->GetFixtureList()[0].SetRestitution(0.3);
	bullet->physics->getBody()->GetFixtureList()[0].SetSensor(false);
	bullet->physics->getBody()->ResetMassData();
	bullet->hasFuse = true;
	bullet->setOwner(this);

	level->AddEntity(bullet);
}





Grenade::Grenade()
{
}


Grenade::~Grenade()
{
}
