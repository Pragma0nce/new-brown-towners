#pragma once
#include <Box2D\Box2D.h>

class CollisionManager : public b2ContactListener
{
private:
public:
	CollisionManager();
	~CollisionManager();

	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
};

