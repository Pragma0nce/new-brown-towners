#include "Team.h"
#include <iostream>
using namespace std;

Team::Team()
{
	numPlayers = 0;
	curPlayer = -1;
}


void Team::loadPlayer(Player *player)
{
	teamList.push_back(player);
	current = player;
	numPlayers++;
	curPlayer++;
}
void Team::startTurn()
{

	cout << "There are " << numPlayers <<" in this team. " << "It is now player " << curPlayer << endl;
	current->startTurn();
}

void Team::endTurn()
{
	if (!teamList.empty()){

		for (auto it = teamList.begin(); it != teamList.end();)
		{
			if ((*it)->getHealth() <= 0)
			{
				Player *entity = (*it);
				it = teamList.erase(it);
				entity->destroy();
				numPlayers -= 1;
			}
			else
			{
				++it;
			}
		}

			current->endTurn();
			curPlayer++;

			if (curPlayer >= numPlayers)
			{
				curPlayer = 0;
			}

			current = teamList[curPlayer];
	}


}

Team::~Team()
{
}
