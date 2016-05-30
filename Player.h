#pragma once
#include <SFML\Graphics.hpp>
#include "Entity.h"
#include <string>

using namespace std;

class Weapon;
class b2World;

// for networking
enum PACKET_TYPE
{
	P_MOVEMENT,
	P_AIM,
	P_FIRE
};



class Player : public Entity{
protected:

	Weapon *weapon;


	bool powering;
	sf::Clock power;

	// lel . this is terrible
	sf::Text name;
	sf::Font font;
	sf::RectangleShape rect;
	sf::Clock jumpTime;

	bool myTurn;
	bool usedAction;

	int health;

public:

	
	void create(std::string image, float x, float y, b2World *world, float width, float height, BODY_TYPE physicsType, Level *l, BODY_SHAPE shape);
	virtual void update(sf::RenderWindow *window);
	virtual void getInput(sf::Event *event);

	void setWeapon(Weapon *weapon);
	void switchWeapon(int key);

	void setName(string n){ name.setString(n);};

	virtual void startTurn();
	void endTurn();

	string getName(){ return name.getString(); };

	virtual void receiveCommands();
	void drawGUI(sf::RenderWindow *window);
	
	ENTITY_TYPE getType();

	void damage(int hp){ health -= hp; };
	int getHealth(){ return health; };

	// Collision based classes
	void checkCollision(Entity *other);


	void destroy();

	Player();
	~Player();
};

