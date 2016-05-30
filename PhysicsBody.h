#pragma once

#include <Box2D/Box2D.h>

enum BODY_TYPE{
	STATIC,
	DYNAMIC,
	KINEMATIC
};

enum BODY_SHAPE
{
	CIRCLE,
	BOX
};
const int SCALE = 30;

class PhysicsBody
{
private:
	b2BodyDef definition;
	//b2PolygonShape shape;
	//b2CircleShape shape;
	b2FixtureDef fixture;
	b2PolygonShape box;
	b2CircleShape circle;

	b2Body* body;
	b2World *world;


public:
	PhysicsBody(float x, float y, float width, float height, b2World *w, BODY_TYPE type, BODY_SHAPE shape);

	void setFriction(float f);
	void setDensity(float d);

	float getPositionX();
	float getPositionY();

	b2Body *getBody();

	void addPolygonFixture(float width, float height, float originX, float originY, bool isSensor);
	float getRotation();


	~PhysicsBody();
};

