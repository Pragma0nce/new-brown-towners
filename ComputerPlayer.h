#pragma once
#include "Player.h"
#include "Team.h"
#include "ComputerVision.h"

class ComputerPlayer :
	public Player
{
private:
	bool hasObjective;
	bool canFire;

	float weaponPower;

	sf::Clock wait;
	Team *enemyTeam;
	
public:

	void setOpponents(Team *team);
	void receiveCommands();
	void getInput(sf::Event *event){};

	void startTurn();

	ComputerPlayer();
	~ComputerPlayer();
};

