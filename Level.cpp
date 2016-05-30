#include "Level.h"
#include "Block.h"
#include "Button.h"
#include <stdio.h>
#include "Grenade.h"
#include "Shotgun.h"
#include "Explosion.h"
#include <fstream>
#include "NetworkPlayer.h"
#include <iostream>
#include "ComputerPlayer.h"

using namespace std;

const int TURN_TIME=7;

int curTeam;
sf::Font font;

sf::View GUI(sf::FloatRect(300, 300, 800, 600));

Level::Level()
{
	srand(time(NULL));
	canScroll = false;
	click = b2Vec2(0, 0);
	release = b2Vec2(0, 0);
	gameMode = MODE_NONE;

	font.loadFromFile("calibri.ttf");
}

void Level::AddEntity(Entity *entity)
{
	buffer.push_back(entity);
}


void Level::LoadLevel()
{
	int x=0;
	int y=0;
	string line;
	fstream myfile("map.txt");
	if (myfile.is_open()){
		while (getline(myfile, line))
		{
			for (int i = 0; i < line.length(); i++){
				if (line[i] == '1')
				{
					PlaceBlock(i*16, y, DIRT);
				}
				else if (line[i] == '2')
				{
					PlaceBlock(i * 16, y, GRASS);
				}
			}

			y += 16;
		}
		myfile.close();
	}
	else cout << "Unable to open file";


}

void Level::PlaceBlock(float x, float y, BLOCK_TYPE type)
{
	int size = 16;

	Block *block = new Block();

	//int X = (std::floor(x / size) * size)+size/2;
	//int Y = (std::floor(y / size) * size)+size/2;
	string pic = "g1.png";

	if (type == DIRT){
		int dec = rand() % 3 + 1;


		switch (dec)
		{
		case 1: pic = "g1.png"; break;
		case 2: pic = "g2.png"; break;
		case 3: pic = "g3.png"; break;
		}
	}
	else if (type == GRASS)
	{
		int dec = rand() % 2 + 1;

		switch (dec)
		{
		case 1: pic = "f1.png"; break;
		case 2: pic = "f2.png"; break;
		}
	}

	block->create(pic, x, y, world, size, size, STATIC, this,BOX);

	AddEntity(block);
}

void Level::startMenu()
{
	vector<Entity*> gui;

	Button bStart;
	bStart.create("singleplayer.png", 200, 200, world, 200, 30, STATIC, this, BOX);
	bStart.setAction(BUTTON_TYPE::AI);
	gui.push_back(&bStart);

	Button bVersus;
	bVersus.create("versus.png", 200, 250, world, 200, 30, STATIC, this, BOX);
	bVersus.setAction(BUTTON_TYPE::SINGLE);
	gui.push_back(&bVersus);

	Button bHost;
	bHost.create("host.png", 200, 400, world, 200, 60, STATIC, this, BOX);
	bHost.setAction(BUTTON_TYPE::HOST);
	gui.push_back(&bHost);

	Button bJoin;
	bJoin.create("join.png", 400, 400, world, 200, 60, STATIC, this, BOX);
	bJoin.setAction(BUTTON_TYPE::JOIN);
	gui.push_back(&bJoin);

	while (window->isOpen() && gameMode==MODE_NONE) 
	{

		
		window->clear();

		for (std::vector<Entity*>::iterator it = gui.begin(); it != gui.end(); ++it)
		{
			(*it)->update(window);
			window->draw(*(*it)->graphics);
		}
		
		sf::Event event;
		while (window->pollEvent(event))
		{
			for (std::vector<Entity*>::iterator it = gui.begin(); it != gui.end(); ++it)
			{
				(*it)->getInput(&event);
			}
		}

		
		window->display();

	}

	// IF ITS A NETWORKED GAME. ESTABLISH CONNECTION
	if (gameMode == MODE_MULTIPLAYER)
		waitForConnection();
}

void Level::waitForConnection()
{
	if (socket.bind(63000) != sf::Socket::Done)
	{
		cout << "SOCKET COULD NOT BIND" << endl;
		system("pause");
	}

	sf::Packet packet;

	if (isHost){
		packet << "CONNECTED";
		socket.send(packet, otherIP, 63000);
	}
	else
	{
		cout << "WAITING FOR CONNECTION ........................" << endl;
		unsigned short port = 63000;
		socket.receive(packet, sf::IpAddress(otherIP), port);
		
		string message = "NOPE";
		if (packet >> message)
		{
			if (message == "CONNECTED")
			{
				cout << "CONNECTION SUCCESSFULL";
			}
		}
	}

}

void Level::Run()
{
	// Create and set the window
	window = new sf::RenderWindow(sf::VideoMode(800, 600, 32), "Worms");
	window->setFramerateLimit(60);

	// Prepare the world 
	b2Vec2 Gravity(0.f, 9.8f);
	//world = new b2World(Gravity);
	world = new b2World(Gravity);

	// GO TO THE MENU
	startMenu();

	// Create and set the view
	// a 300x200 rectangle centered on the point (350, 300).
	view = new sf::View(sf::Vector2f(300, 300), sf::Vector2f(800, 600));
	window->setView(*view);

	// create a background
	//texture.loadFromFile("back.jpg");
	//background.setTexture(texture);
	//background.setPosition(0, -500);
	
	
	// Create a contact listener
	contactListener = new CollisionManager();
	world->SetContactListener(contactListener);
	
	//----------------------------------------------------//
	//				GAME LOGIC							  //
	//----------------------------------------------------//
	// Setting up the teams and starting position
	float startX, startY, otherX, otherY;

	if (isHost){
		startX = 100;
		startY = 100;
		otherX = 1200;
		otherY = 100;
	}
	else
	{
		startX = 1200;
		startY = 100;
		otherX = 100;
		otherY = 100;
	}

	Player *player1 = new Player();
	player1->create("player.png", startX, startY, world, 20, 30, DYNAMIC,this,BOX);
	player1->setName("Bianca");
	entities.push_back(player1);

	Player *player2 = new Player();
	player2->create("player.png", startX+300, startY, world, 20, 30, DYNAMIC, this, BOX);
	player2->setName("Henri");
	entities.push_back(player2);

	if (isHost || gameMode != MODE_MULTIPLAYER){
		team1.loadPlayer(player1);
		team1.loadPlayer(player2);
	}
	else
	{
		team2.loadPlayer(player1);
		team2.loadPlayer(player2);
	}
	

	// CHOOSING ENEMY COMPOSITION BASED ON GAME MODE
	switch (gameMode)
	{
		case MODE_MULTIPLAYER:
		{
			NetworkPlayer *player1B = new NetworkPlayer();
			player1B->create("player2.png", otherX, otherY, world, 20, 30, DYNAMIC, this, BOX);
			player1B->setName("Enemy 1");
			entities.push_back(player1B);

			NetworkPlayer *player2B = new NetworkPlayer();
			player2B->create("player2.png", otherX+300, otherY, world, 20, 30, DYNAMIC, this, BOX);
			player2B->setName("Enemy 2");
			entities.push_back(player2B);

			if (isHost){
				team2.loadPlayer(player1B);
				team2.loadPlayer(player2B);
			}
			else
			{
				team1.loadPlayer(player1B);
				team1.loadPlayer(player2B);
			}
			break;
		}

		case MODE_SINGEPLAYER:
		{
			ComputerPlayer *player1B = new ComputerPlayer();
			player1B->create("player2.png", 1200, 100, world, 20, 30, DYNAMIC, this, BOX);
			player1B->setName("Kobus");
			player1B->setOpponents(&team1);
		    entities.push_back(player1B);

			ComputerPlayer *player2B = new ComputerPlayer();
			player2B->create("player2.png", 1500, 100, world, 20, 30, DYNAMIC, this, BOX);
			player2B->setName("Kevin");
			player2B->setOpponents(&team1);
			entities.push_back(player2B); 

			team2.loadPlayer(player1B);
			team2.loadPlayer(player2B);
			break;
		}
		
	}



	

	Terrain *terrain = new Terrain();
	Terrain *terrain2 = new Terrain();
	Terrain *terrain3 = new Terrain();
	Terrain *terrain4 = new Terrain();

	terrain->create("ground.png", 952, 625, world, 2024, 50, STATIC,this,BOX);
	terrain2->create("ground.png", -20-15 ,0, world, 50, 1200, STATIC,this,BOX);
	terrain3->create("ground.png", 1920+15, 0, world, 50, 1200, STATIC, this,BOX);
	terrain4->create("ground.png", 952, -600, world, 2024, 50, STATIC, this, BOX);

	entities.push_back(terrain);
	entities.push_back(terrain2);
	entities.push_back(terrain3);
	entities.push_back(terrain4);

	//Weapon *weapon = new Weapon();
	//weapon->create("launcher.png",player->graphics->getPosition().x, player->graphics->getPosition().y, world, 40, 20, DYNAMIC,this,BOX);
	//weapon->setOwner(player);
	//entities.push_back(weapon);

	//Shotgun *weapon = new Shotgun();
	//weapon->create("shotgun.png",player1->graphics->getPosition().x+10, player1->graphics->getPosition().y+10, world, 50, 20, DYNAMIC,this,BOX);
	//weapon->setOwner(player1);
	//entities.push_back(weapon);

	LoadLevel();

	// ONLY START THE GAME AFTER THE LEVEL LOADS
	curTeam = 1;
	//PlaceBlock(0, 592);

	// IF IM THE HOST - CREATE A SERVER

	Update();

}

void Level::Update()
{
	release = b2Vec2(view->getCenter().x, view->getCenter().y);
	
	//team1.startTurn();
	

	// WAIT FOR START SIGNAL BEFORE BEGINNING
	if (gameMode == MODE_MULTIPLAYER){
		sf::Packet packet;
		packet << "READY";
		socket.send(packet, otherIP, 63000);

		bool isReady = false;
		socket.setBlocking(false);

		while (!isReady)
		{
			sf::Packet packet;
			unsigned short port = 63000;
			socket.receive(packet, sf::IpAddress(otherIP), port);

			string message;

			if (packet >> message)
			{
				isReady = true;
			}
			else
				cout << " ... Waiting for other computer ... " << endl;
		}
	}

	team1.startTurn();
	turnTime.restart();

	while (window->isOpen())
	{
		timeLeft = TURN_TIME - turnTime.getElapsedTime().asSeconds();

		if (timeLeft <= 0)
		{
			if (curTeam == 1){
				team1.endTurn();
				team2.startTurn();
				curTeam = 2;
			}
			else if (curTeam == 2){
				team2.endTurn();
				team1.startTurn();
				curTeam = 1;
			}

			turnTime.restart();
		}

		sf::Event event;
		//release = b2Vec2(view->getCenter().x, view->getCenter().y);

		if (canScroll)
		{
			//b2Vec2 diff(sf::Mouse::getPosition(*window).x - click.x, sf::Mouse::getPosition(*window).y - click.y);
			//view->setCenter((click.x - sf::Mouse::getPosition(*window).x + preView.x), (click.y - sf::Mouse::getPosition(*window).y + preView.y));
			//diff = click - release;
			view->setCenter(release.x + (click.x - sf::Mouse::getPosition(*window).x), release.y + (click.y-sf::Mouse::getPosition(*window).y));
			cout << "X: --------------------------------------- " << sf::Mouse::getPosition(*window).x - click.x << endl;
		}

		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::MouseButtonPressed){
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					float MouseX = sf::Mouse::getPosition(*window).x;
					float MouseY = sf::Mouse::getPosition(*window).y;
					//PlaceBlock(MouseX, MouseY);
					click = b2Vec2(MouseX, MouseY);
					canScroll = true;
				}
			}

			if (event.type == sf::Event::MouseButtonReleased){
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					float MouseX = sf::Mouse::getPosition(*window).x;
					float MouseY = sf::Mouse::getPosition(*window).y;
					release = b2Vec2(view->getCenter().x, view->getCenter().y);
					canScroll = false;
				}
			}

			// MOVING THE VIEWPORT
			if (event.type == sf::Event::KeyPressed){
				if (event.key.code == sf::Keyboard::D)
				{
					view->move(10, 0);
				}
				else if (event.key.code == sf::Keyboard::A)
				{
					view->move(-10, 0);
				}
			}


			if (event.type == sf::Event::MouseWheelScrolled)
			{
				if (event.mouseWheelScroll.delta >= 1)
				{
					if (view->getSize().x >= 400)
					view->zoom(0.9f);
				}
				else if (event.mouseWheelScroll.delta <= 0)
				{
					if (view->getSize().x <=1500)
					view->zoom(1.1);
				}

				std::cout << "wheel movement: " << event.mouseWheelScroll.delta << std::endl;
				//std::cout << "mouse x: " << event.mouseWheelScroll.x << std::endl;
				//std::cout << "mouse y: " << event.mouseWheelScroll.y << std::endl;
			}

			for (std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
			{
				(*it)->getInput(&event);
			}
		}

		/** When the user left-mouse-click, add a box into the world */
		/*
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
		int MouseX = sf::Mouse::getPosition(Window).x;
		int MouseY = sf::Mouse::getPosition(Window).y;
		CreateBox(World, MouseX, MouseY);
		}*/

		/** Simulate the world */
		world->Step(1 / 60.f, 8, 3);


		//==========================================================================================================================//
		//										DRAW ON MAIN VIEW PORT                                                              //
		//==========================================================================================================================//
		// DRAW EVERYTHING
		window->clear(sf::Color(144, 195, 212,0));
		window->setView(*view);

		//window->draw(background);

		for (std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
		{
			window->draw(*(*it)->graphics);
		}

		//==========================================================================================================================//
		//										UPDATES				                                                                //
		//==========================================================================================================================//

		// UPDATE EVERYTHING
		for (std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
		{
			(*it)->update(window);
		}

		// UPDATE THE SERVER

		//==========================================================================================================================//
		//										DRAW ON GUI VIEW PORT                                                               //
		//==========================================================================================================================//
		window->setView(GUI);
		// DRAW THE TIME LEFT
		sf::Text time(std::to_string(TURN_TIME - static_cast<int>(round(turnTime.getElapsedTime().asSeconds()))), font, 30);
		time.setPosition(GUI.getCenter().x, (GUI.getCenter().y - 300));

		sf::RectangleShape cover(sf::Vector2f(100, 50));
		cover.setFillColor(sf::Color(37, 39, 61));
		cover.setPosition(GUI.getCenter().x-40, GUI.getCenter().y - 300);

		window->draw(cover);
		window->draw(time); 

		// DRAW THE BOTTOM GUI ELEMENTS


		// DRAW background

		window->display();

		emptyBuffer();

		//Window.draw(*Player.graphics);
		//Window.draw(*terrain.graphics);
		//Window.draw(*terrain2.graphics);
		//Window.draw(*weapon.graphics);


		//Player.update(&Window);
		//weapon.update(&Window);




		/*for (b2Body* BodyIterator = World.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
		{
			if (BodyIterator->GetType() == b2_dynamicBody)
			{
				sf::Sprite Sprite;
				Sprite.setTexture(BoxTexture);
				Sprite.setOrigin(8.f, 8.f);
				Sprite.setPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
				Sprite.setRotation(BodyIterator->GetAngle() * 180 / b2_pi);
				//Window.draw(Sprite);

			}
			else
			{
				//sf::Sprite GroundSprite;
				//GroundSprite.setTexture(GroundTexture);
				//GroundSprite.setOrigin(400.f, 8.f);
				//GroundSprite.setPosition(BodyIterator->GetPosition().x * SCALE, BodyIterator->GetPosition().y * SCALE);
				//GroundSprite.setRotation(180 / b2_pi * BodyIterator->GetAngle());
				//Window.draw(GroundSprite);
			}
		}
		Window.display();*/
	}
}

void Level::centerView(float x, float y)
{
	release = b2Vec2(view->getCenter().x, view->getCenter().y);
	view->setCenter(x, y);
}

void Level::emptyBuffer()
{
	for (std::vector<Entity*>::iterator it = buffer.begin(); it != buffer.end(); ++it)
	{
		entities.push_back(*it);
	}

	while (!buffer.empty())
	{
		buffer.pop_back();
	}


	// Move dead items into buffer
	for (auto it = entities.begin(); it != entities.end();)
	{
		bool bErased = false;

		if ((*it)->isDead())
		{
			Entity *entity = (*it);
			it = entities.erase(it);
			delete entity;
		}
		else
		{
			++it;
		}
	}
}
Level::~Level()
{
}
