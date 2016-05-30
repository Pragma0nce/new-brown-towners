#include "Explosion.h"
#include "Level.h"
#include "Block.h"

#include <iostream>
using namespace std;


void Explosion::create(std::string image, float x, float y, b2World *world, float width, float height, BODY_TYPE physicsType, Level *l, BODY_SHAPE shape)
{
	Entity::create(image, x, y, world, width, height, physicsType, l, shape);
	physics->getBody()->GetFixtureList()[0].SetSensor(true);
	size = width;
	timer.restart();
}
void Explosion::update(sf::RenderWindow *window)
{
	if (timer.getElapsedTime().asSeconds() >= 0.1)
		destroy();
}
void Explosion::getInput(sf::Event *event)
{

}

ENTITY_TYPE Explosion::getType()
{
	return EXPLOSION;
}

float applyBlastImpulse(b2Body* body, b2Vec2 blastCenter, b2Vec2 applyPoint, float blastPower) {
	b2Vec2 blastDir = applyPoint - blastCenter;
	float distance = blastDir.Normalize();
	//ignore bodies exactly at the blast point - blast direction is undefined
	if (distance == 0)
	{
		cout << "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF" << endl;
		//return;
	}
		
	float invDistance = 1 / distance;
	float impulseMag = blastPower * invDistance * invDistance;
	body->ApplyLinearImpulse(impulseMag * blastDir, applyPoint, true);

	return impulseMag;
}


// Collision based classes
void Explosion::checkCollision(Entity *other)
{
	if (other->getType() == BLOCK)
	{
		Block * block = dynamic_cast<Block*>(other);
		block->changeBody = true;
	}

	if (other->getType() != EXPLOSION){
		float power = applyBlastImpulse(other->physics->getBody(), physics->getBody()->GetWorldCenter(), other->physics->getBody()->GetWorldCenter(), size/30);

		if (other->getType() == PLAYER){
			Player *player = (Player*)other;
			player->damage(power);
			//cout << "Blast impulse applied to PLAYER " << endl;
			//c//out << "POWERL " << power << endl;
			//system("pause");
		}
	}
}

void Explosion::endCollision(Entity *other)
{

}

void Explosion::destroy()
{
	Entity::destroy();

}

Explosion::Explosion()
{
}


Explosion::~Explosion()
{
}
