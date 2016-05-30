#pragma once
#include "Entity.h"

enum BUTTON_TYPE{
	HOST,
	JOIN,
	SINGLE,
	AI
};

class Button :
	public Entity
{
private:
	BUTTON_TYPE action;

public:

	void update(sf::RenderWindow *window);
	void getInput(sf::Event *event);
	ENTITY_TYPE getType();
	void checkCollision(Entity *other);

	void setAction(BUTTON_TYPE a){ action = a; };

	Button();
	~Button();
};

