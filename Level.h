#pragma once
#include <vector>
#include <SFML\Graphics.hpp>
#include "Level.h"
#include <Box2D/Box2D.h>
#include "Player.h"
#include "Terrain.h"
#include "CollisionManager.h"
#include "Weapon.h"
#include "Team.h"
#include <SFML\Network.hpp>
using namespace std;

enum BLOCK_TYPE
{
	DIRT,
	GRASS
};

enum GAME_MODE
{
	MODE_NONE,
	MODE_SINGEPLAYER,
	MODE_VERSUS,
	MODE_MULTIPLAYER
};

class Level
{
private:
	void emptyBuffer();
	sf::Texture texture;
	sf::Sprite background;

	b2Vec2 click;
	b2Vec2 release;
	b2Vec2 diff;
	bool canScroll;


	Player *currentPlayer;


	// Teams
	Team team1;
	Team team2;

	sf::Clock turnTime;

public:
	// for networked game
	string otherIP;
	bool isHost;
	sf::UdpSocket socket;

	void waitForConnection();

	
	GAME_MODE gameMode;



	float timeLeft;

	sf::View *view;
	Level();

	vector<Entity*> entities;
	vector<Entity*> buffer;

	b2World *world;
	CollisionManager *contactListener;
	sf::RenderWindow *window;


	void startMenu();

	void Run();
	void Update();
	
	void centerView(float x, float y);

	void LoadLevel();

	void AddEntity(Entity *entity);

	void PlaceBlock(float x, float y, BLOCK_TYPE type);

	~Level();
};

