#include "NetworkPlayer.h"
#include <SFML\Network.hpp>
#include "Level.h"
#include <iostream>
using namespace std;

NetworkPlayer::NetworkPlayer()
{
	//if (socket.bind(sf::Socket::AnyPort) != sf::Socket::Done)
	//{
	//	cout << "SOCKET COULD NOT BIND" << endl;
	//	system("pause");
	//}

	//cout << "port " << socket.getLocalPort() << endl;
	//system("pause");
}

void NetworkPlayer::update(sf::RenderWindow *window)
{
	graphics->setPosition(SCALE * physics->getPositionX(), SCALE * physics->getPositionY());
	graphics->setRotation(physics->getRotation() * 180 / b2_pi);

	if (health <= 0)
	{
		graphics->setScale(2, 0.5);
		health = 0;
	}

	receiveCommands();
	drawGUI(window);
}

void NetworkPlayer::receiveCommands()
{
	if (myTurn){
		//socket.setBlocking(false);

		unsigned short port = 63000;

		sf::Packet packet;
		level->socket.receive(packet, sf::IpAddress(level->otherIP), port);

		//sf::UdpSocket sock;
		//sf::Packet packet;
		//packet << P_MOVEMENT << graphics->getPosition().x << graphics->getPosition().y;
		//sock.send(packet, "127.0.0.1", socket.getLocalPort());


		int type;

		if (packet >> type)
		{
			switch (type)
			{
			case P_MOVEMENT:

				float x,y;
				packet >> x;
				packet >> y;

				physics->getBody()->SetTransform(b2Vec2(x, y), physics->getBody()->GetAngle());
				graphics->setPosition(SCALE * physics->getPositionX(), SCALE * physics->getPositionY());
				graphics->setRotation(physics->getRotation() * 180 / b2_pi);

				cout << "X: " << graphics->getPosition().x << endl;
				cout << "Y: " << graphics->getPosition().y << endl;
				//system("pause");
				break;
			}
		}
		else
		{
			cout << "ERROR" << endl;
		}


	}
}

void NetworkPlayer::getInput(sf::Event *event)
{
}



NetworkPlayer::~NetworkPlayer()
{
}
