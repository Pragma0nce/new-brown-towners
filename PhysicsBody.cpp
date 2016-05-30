#include "PhysicsBody.h"
#include "string"
#include <iostream>
using namespace std;

PhysicsBody::PhysicsBody(float x, float y, float width, float height, b2World *w, BODY_TYPE type, BODY_SHAPE s)
{
	cout << "GOT HERE" << endl;
	// Assign the world
	world = w;

	// Position the body
	definition.position = b2Vec2(x / SCALE, y / SCALE);

	// Define the type of body
	switch (type)
	{
		case STATIC: definition.type = b2_staticBody; break;
		case DYNAMIC: definition.type = b2_dynamicBody; break;
		case KINEMATIC: definition.type = b2_kinematicBody; break;
	}

	// Add the body to the world
	body = world->CreateBody(&definition);


	// Set the shape
	switch (s)
	{
	case BOX:
		box.SetAsBox((width / 2) / SCALE, (height / 2) / SCALE);
		fixture.shape = &box;
		break;
	case CIRCLE:
		circle.m_p.Set(0, 0); //position, relative to body position
		circle.m_radius = width/2/SCALE; //radius
		fixture.shape = &circle;
		break;
	}

	//shape.SetAsBox((width / 2) / SCALE, (height / 2) / SCALE); // Creates a box shape. 
	fixture.density = 0.7f;  // Sets the density of the body
	fixture.restitution = 0.1;

	cout << "PHYSICS_WIDTH: " << width / 2 / SCALE << endl;

	fixture.friction = 1.f;
	//fixture.shape = &shape; // Sets the shape
	body->CreateFixture(&fixture); // Apply the fixture definition

}

void PhysicsBody::addPolygonFixture(float width, float height, float originX, float originY, bool isSensor)
{
	b2PolygonShape polygonShape;
	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &polygonShape;
	myFixtureDef.density = 1;
	polygonShape.SetAsBox(width, height, b2Vec2(originX, originY), 0);
	myFixtureDef.isSensor = true;

	b2Fixture* newFixture = body->CreateFixture(&myFixtureDef);
	newFixture->SetUserData((void*)1);
}


float PhysicsBody::getPositionX()
{
	return body->GetPosition().x;
}
float PhysicsBody::getPositionY()
{
	return body->GetPosition().y;
}

b2Body *PhysicsBody::getBody()
{
	return body;
}

void PhysicsBody::setFriction(float f)
{
	fixture.density = f;
}
void PhysicsBody::setDensity(float d)
{
	fixture.density = d;
}

float PhysicsBody::getRotation()
{
	return body->GetAngle();
}

PhysicsBody::~PhysicsBody()
{
}
