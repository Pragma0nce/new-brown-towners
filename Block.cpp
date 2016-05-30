#include "Block.h"


void Block::create(std::string image, float x, float y, b2World *world, float width, float height, BODY_TYPE physicsType, Level *l, BODY_SHAPE shape)
{
	Entity::create(image, x, y, world, width, height, physicsType, l, shape);
	changeBody = false;
	isDynamic = false;

	physics->getBody()->GetFixtureList()[0].SetDensity(1);
	physics->getBody()->GetFixtureList()[0].SetRestitution(0.2);
	physics->getBody()->ResetMassData();

	timer.restart();
}

void applyBlastImpulseB(b2Body* body, b2Vec2 blastCenter, b2Vec2 applyPoint, float blastPower) {
	b2Vec2 blastDir = applyPoint - blastCenter;
	float distance = blastDir.Normalize();
	//ignore bodies exactly at the blast point - blast direction is undefined
	if (distance == 0)
		return;
	float invDistance = 1 / distance;
	float impulseMag = blastPower * invDistance * invDistance;
	body->ApplyLinearImpulse(impulseMag * blastDir, applyPoint,true);
}

void Block::update(sf::RenderWindow *window)
{
	Entity::update(window);
	if (changeBody)
	{
		physics->getBody()->SetType(b2_dynamicBody);
		changeBody = false;
		isDynamic = true;

		applyBlastImpulseB(physics->getBody(), blast->physics->getBody()->GetWorldCenter(), physics->getBody()->GetWorldCenter(), 2);

		timer.restart();
	}

	if (isDynamic && physics->getBody()->GetLinearVelocity().y >= 0 && physics->getBody()->GetLinearVelocity().y <=0.1 && timer.getElapsedTime().asSeconds() >= 1)
	{
		destroy();
	}
}
void Block::getInput(sf::Event *event)
{

}

ENTITY_TYPE Block::getType()
{
	return BLOCK;
}



// Collision based classes
void Block::checkCollision(Entity *other)
{
	if (other->getType() == EXPLOSION)
	{
	
		//physics->getBody()->ApplyLinearImpulse(b2Vec2(cos(5) *1, sin(5) * 1), physics->getBody()->GetWorldCenter(), true);
		changeBody = true;
		blast = other;
	}
}

void Block::destroy()
{
	Entity::destroy();
}

Block::Block()
{
}


Block::~Block()
{
}
