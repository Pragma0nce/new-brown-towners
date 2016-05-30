#pragma once
#include "Player.h"
#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>

class NetworkPlayer :
	public Player
{
private:
	sf::UdpSocket socket;
	int senderPort;
public:

	void update(sf::RenderWindow *window);
	void receiveCommands();
	void getInput(sf::Event *event);

	NetworkPlayer();
	~NetworkPlayer();
};

