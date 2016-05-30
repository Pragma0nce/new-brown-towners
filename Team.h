#pragma once
#include <vector>
#include "Player.h"
using namespace std;

class Team
{
private:
	int numPlayers;
	int curPlayer;

	Player *current;
	
public:
	vector<Player*> teamList;

	void loadPlayer(Player *player);
	void startTurn();
	void endTurn();

	Team();
	~Team();
};

