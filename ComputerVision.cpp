#include "ComputerVision.h"
#include <iostream>
#include "Entity.h"
#include "Player.h"
using namespace std;

ComputerVision::ComputerVision()
{
	hasLOS = true;
}

float32 ComputerVision::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction)
{
	Entity *entity;

	entity = (Entity*)fixture->GetBody()->GetUserData();

	if (entity->getType() == 1)
	{
		Player *player = (Player*)entity;
		cout << "RAYCAST COLLIDED AGAINST ............................. " << player->getName()<< endl;
		
	}
	else if (entity->getType() != AIM || entity->getType() != WEAPON){
		hasLOS = false;
		cout << "RAYCAST COLLIDED AGAINST ............................. " << entity->getType() << endl;
	}

	return 1;
}

ComputerVision::~ComputerVision()
{
}
