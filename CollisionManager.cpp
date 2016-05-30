#include "CollisionManager.h"
#include "Entity.h"
#include <iostream>
using namespace std;

CollisionManager::CollisionManager()
{
}


void CollisionManager::BeginContact(b2Contact* contact)
{
	cout << "COLLISION" << endl;

	Entity* entityA = (Entity*)contact->GetFixtureA()->GetBody()->GetUserData();
	Entity* entityB= (Entity*)contact->GetFixtureB()->GetBody()->GetUserData();

	entityA->checkCollision(entityB);
	entityB->checkCollision(entityA);
}

void CollisionManager::EndContact(b2Contact* contact)
{
	Entity* entityA = (Entity*)contact->GetFixtureA()->GetBody()->GetUserData();
	Entity* entityB = (Entity*)contact->GetFixtureB()->GetBody()->GetUserData();

	entityA->endCollision(entityB);
	entityB->endCollision(entityA);
}

CollisionManager::~CollisionManager()
{
}
