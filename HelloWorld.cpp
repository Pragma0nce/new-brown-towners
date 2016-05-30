
#include "Level.h"
#include <fstream>
#include <iostream>
#include <SFML\Main.hpp>
#include <SFML/Network.hpp>
using namespace std;


void sendPacket()
{
	sf::UdpSocket socket;
	//if (socket.bind(54001) != sf::Socket::Done)
	//{
	//	cout << "Could not bind" << endl;
	//}
	sf::Packet packet;
	packet << "Boo!";
	socket.send(packet, "127.0.0.1", 54000);
}

int main()
{
	Level level;
	level.Run();

	// bind the socket to a port

	sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Worms");
	window.setFramerateLimit(60);

	//while (window.isOpen()){

	//
	//}


	sf::UdpSocket socket;
	if (socket.bind(54000) != sf::Socket::Done)
	{
		// error...
	}

	sendPacket();
	sf::Packet packet;
	std::string text;
	unsigned short port = 53000;

	socket.receive(packet, sf::IpAddress("127.0.0.1"), port);

	if (packet >> text)
	{
		cout << text << endl;
	}
	else
	{
		cout << "ERROR" << endl;
	}

	system("pause");
}
