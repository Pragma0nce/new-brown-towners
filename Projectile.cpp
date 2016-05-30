#include "Projectile.h"
#include "Explosion.h"
#include "Entity.h"
#include "Level.h"
#include <iostream>
using namespace std;

Projectile::Projectile()
{
}


Projectile::~Projectile()
{
}


void Projectile::setExplosionSize(float p)
{
	explosionSize = p;
}

void Projectile::create(std::string image, float x, float y, b2World *world, float width, float height, BODY_TYPE physicsType, Level *l, BODY_SHAPE shape)
{
	Entity::create(image, x, y, world, width, height, physicsType,l,shape);
	safeZone.restart();

	physics->getBody()->GetFixtureList()[0].SetSensor(true);
	physics->getBody()->GetFixtureList()[0].SetDensity(0.4);
	physics->getBody()->SetGravityScale(2);
	physics->getBody()->SetBullet(true);
	physics->getBody()->ResetMassData();

	level->view->setSize(800*1.5, 600*1.5);

	follow = false;
	explosionSize = 150;
	canExplode = false;
	hasExploded = false;
	hasFuse = false;
}

void Projectile::update(sf::RenderWindow *window)
{
	graphics->setPosition(SCALE * physics->getPositionX(), SCALE * physics->getPositionY());
	graphics->setRotation(physics->getRotation() * 180 / b2_pi);

	if (follow)
		level->centerView(graphics->getPosition().x, graphics->getPosition().y);
	//level->view->setSize(800, 600);

	physics->getBody()->SetTransform(physics->getBody()->GetPosition(), atan2(physics->getBody()->GetLinearVelocity().y, physics->getBody()->GetLinearVelocity().x));

	//if (owner->getOwner()->getDir() == RIGHT){
		//graphics->setPosition(owner->graphics->getPosition().x + cos(owner->getFireAngle()) * 150, owner->graphics->getPosition().y + sin(owner->getFireAngle()) * 150);
		//physics->getBody()->set
	//}
	//else
		//graphics->setPosition(owner->graphics->getPosition().x - cos(owner->getFireAngle()) * 150, owner->graphics->getPosition().y - sin(owner->getFireAngle()) * 150);

	if (canExplode)
		explode();
}

void Projectile::explode()
{
	if (canExplode && !hasFuse)
	{
		if (explosionSize != 0){
			Explosion *explosion = new Explosion();
			explosion->create("explosion.png", colPos.x*SCALE, colPos.y*SCALE, level->world, explosionSize, explosionSize, DYNAMIC, level, CIRCLE);
			level->AddEntity(explosion);
		}

		canExplode = false;
		hasExploded = true;
		destroy();
	}

	/*
	if (hasFuse && canExplode)
	{
		physics->getBody()->GetFixtureList()[0].SetSensor(false);
	}*/

	if (hasFuse && fuse.getElapsedTime().asSeconds() >=2)
	{

		Explosion *explosion = new Explosion();
		explosion->create("explosion.png", colPos.x*SCALE, colPos.y*SCALE, level->world, explosionSize, explosionSize, DYNAMIC, level, CIRCLE);
		level->AddEntity(explosion);

		canExplode = false;
		hasExploded = true;
		destroy();
	}
}


void Projectile::getInput(sf::Event *event)
{

}


ENTITY_TYPE Projectile::getType()
{
	return PROJECTILE;
}

// Collision based classes
void Projectile::checkCollision(Entity *other)
{
	if (other->physics->getBody()->GetUserData() != owner->getOwner() && other->getType() != WEAPON && other->getType() != PROJECTILE && other->getType() != EXPLOSION && other->getType() != AIM){
		if (!hasExploded){
			colPos = physics->getBody()->GetPosition();
	
			if (canExplode == false)
				fuse.restart();

			canExplode = true;
		}

		
	}
}

void Projectile::destroy()
{
	Entity::destroy();
};