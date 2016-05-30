#include "Weapon.h"
#include "Projectile.h"
#include "Level.h"
#include <iostream>
#include "Aim.h"
using namespace std;


Weapon::Weapon()
{
}


Weapon::~Weapon()
{
}


void Weapon::create(std::string image, float x, float y, b2World *world, float width, float height, BODY_TYPE physicsType, Level *l, BODY_SHAPE shape)
{
	Entity::create(image, x, y, world, width, height, physicsType,l,shape);
	dir = RIGHT;

	physics->getBody()->GetFixtureList()->SetSensor(true);
	physics->getBody()->SetGravityScale(0);
	physics->getBody()->SetFixedRotation(false);

	float fireAngle = 0;
	

	// SETUP THE AIM

	aim = new Aim();
	aim->create("aim.png", graphics->getPosition().x, graphics->getPosition().y, world, 32, 32, KINEMATIC, level, CIRCLE);
	aim->physics->getBody()->GetFixtureList()[0].SetSensor(true);
	aim->setOwner(this);
	level->AddEntity(aim);

}

void Weapon::fire(float power)
{
	Projectile *bullet = new Projectile();
	bullet->create("ball.png", graphics->getPosition().x, graphics->getPosition().y, level->world, 20, 20, DYNAMIC, level, CIRCLE);

	if (owner->getDir() == RIGHT)
		bullet->physics->getBody()->ApplyLinearImpulse(b2Vec2(cos(getFireAngle()) * (power)*5, sin(getFireAngle()) * (power)*5), bullet->physics->getBody()->GetWorldCenter(), true);
	else if (owner->getDir() == LEFT)
		bullet->physics->getBody()->ApplyLinearImpulse(-b2Vec2(cos(getFireAngle()) * (power)* 5, sin(getFireAngle()) * (power)* 5), bullet->physics->getBody()->GetWorldCenter(), true);

	bullet->physics->getBody()->GetFixtureList()[0].SetFriction(1);
	bullet->physics->getBody()->GetFixtureList()[0].SetDensity(4);
	bullet->physics->getBody()->ResetMassData();
	bullet->shouldFollow(true);

	bullet->setOwner(this);

	level->AddEntity(bullet);
}

void Weapon::setOwner(Player *player)
{
	owner = player;
	player->setWeapon(this);
}

void Weapon::setAim(DIRECTION dir)
{
	if (dir ==UP)
	fireAngle += 0.05;
	else
	if (dir == DOWN)
		fireAngle -= 0.05;

	cout << "ANGLE: " << fireAngle * 180 / b2_pi << endl;

	if (fireAngle * 180 / b2_pi <= -90){
		fireAngle = -90*b2_pi/180;
	}
	else 	if (fireAngle * 180 / b2_pi >= 90){
		fireAngle = 90 * b2_pi / 180;
	}
}

void Weapon::update(sf::RenderWindow *window)
{
	b2Vec2 ownerPos(owner->physics->getBody()->GetPosition().x, owner->physics->getBody()->GetPosition().y);

	physics->getBody()->SetTransform(ownerPos, fireAngle);
	graphics->setPosition(SCALE * physics->getPositionX(), SCALE * physics->getPositionY());
	graphics->setRotation(physics->getRotation() * 180 / b2_pi);

	if (dir == RIGHT && owner->getDir() == LEFT){
		changeDirection(LEFT);
	}
	else if (dir == LEFT && owner->getDir() == RIGHT){
		changeDirection(RIGHT);
	}

	// DRAW THE AIM 

}
void Weapon::getInput(sf::Event *event)
{

}

ENTITY_TYPE Weapon::getType()
{
	return WEAPON;
}

// Collision based classes
void Weapon::checkCollision(Entity *other)
{

}

void Weapon::destroy()
{
	aim->destroy();
	Entity::destroy();
}