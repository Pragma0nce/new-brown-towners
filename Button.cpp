#include "Button.h"
#include "Level.h"
#include <iostream>
using namespace std;

Button::Button()
{
}


void Button::update(sf::RenderWindow *window)
{
	Entity::update(window);
}
void Button::getInput(sf::Event *event)
{
	if (event->type == sf::Event::MouseButtonReleased)
	{
		if ((sf::Mouse::getPosition(*level->window).x >= graphics->getPosition().x - graphics->getGlobalBounds().width / 2 && sf::Mouse::getPosition(*level->window).x <= graphics->getPosition().x + graphics->getGlobalBounds().width / 2)
			&& (sf::Mouse::getPosition(*level->window).y >= graphics->getPosition().y - graphics->getGlobalBounds().height / 2 && sf::Mouse::getPosition(*level->window).y <= graphics->getPosition().y + graphics->getGlobalBounds().height / 2)
			)
		{
			// This means i am clicked
			string ip;
			switch (action)
			{
			case HOST:
				cout << "HOST IP: ";
				cin >> ip;
				level->otherIP = ip;
				level->gameMode = MODE_MULTIPLAYER;
				level->isHost = true;
				break;
			case AI:
				level->gameMode = MODE_SINGEPLAYER;
				break;

			case JOIN:
				cin >> ip;
				level->otherIP = ip;
				level->gameMode = MODE_MULTIPLAYER;
				level->isHost = false;
			}

		}
	}
}
ENTITY_TYPE Button::getType()
{
	return BUTTON;
}
void Button::checkCollision(Entity *other)
{

}

Button::~Button()
{
}
