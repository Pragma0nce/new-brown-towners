#pragma once
#include <Box2D\Box2D.h>

class ComputerVision : public b2RayCastCallback
{
private:
	bool hasLOS; // has line of sight on enemy
public:
	float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction);

	bool canSeeEnemy(){ return hasLOS; };

	ComputerVision();
	~ComputerVision();
};

