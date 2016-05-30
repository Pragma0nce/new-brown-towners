#include "ComputerPlayer.h"
#include "Weapon.h"
#include "Level.h"
#include <iostream>
#include <random>
#include <cmath>
using namespace std;


ComputerPlayer::ComputerPlayer()
{
	hasObjective = false;
}

void ComputerPlayer::startTurn()
{
	Player::startTurn();
	weaponPower = 0;

	canFire = false;
	hasObjective = false;
}

void ComputerPlayer::receiveCommands()
{
	if (!hasObjective && myTurn)
	{
		// I can see the enemy so I use a shotgun or SMG
		for (std::vector<Player*>::iterator it = enemyTeam->teamList.begin(); it != enemyTeam->teamList.end(); ++it){
			ComputerVision vision;
			level->world->RayCast(&vision, physics->getBody()->GetPosition(), (*it)->physics->getBody()->GetPosition());


			if (vision.canSeeEnemy())
			{
				int choice = rand() % 2 + 2;
				switchWeapon(choice);
				if ((*it)->graphics->getPosition().x < graphics->getPosition().x)
				{
					changeDirection(LEFT);
					weapon->setAngle(atan2(physics->getBody()->GetPosition().y - (*it)->physics->getBody()->GetPosition().y, physics->getBody()->GetPosition().x - (*it)->physics->getBody()->GetPosition().x));
				}
				else
				{
					changeDirection(RIGHT);
					weapon->setAngle(atan2((*it)->physics->getBody()->GetPosition().y - physics->getBody()->GetPosition().y, (*it)->physics->getBody()->GetPosition().x - physics->getBody()->GetPosition().x));
				}

				//graphics->setPosition(owner->graphics->getPosition().x + cos(owner->getFireAngle()) * 150, owner->graphics->getPosition().y + sin(owner->getFireAngle()) * 150);
				cout << "SHOOTING " << (*it)->getName() << endl << endl << endl;


				wait.restart();
				canFire = true;
				hasObjective = true;
				break;
			}
		}

		// There must be terrain blocking my view. So I will use my rocket launcher
		if (hasObjective == false){
			for (std::vector<Player*>::iterator it = enemyTeam->teamList.begin(); it != enemyTeam->teamList.end(); ++it)
			{

				{
					// Create a random unform distribution
					std::random_device rd;
					std::mt19937 gen(rd());
					std::uniform_real_distribution<> choice(1.f, 2.5f);

					float num = choice(gen);

					switchWeapon(1);
					if ((*it)->graphics->getPosition().x < graphics->getPosition().x)
					{
						changeDirection(LEFT);
						weapon->setAngle(atan2((physics->getBody()->GetPosition().y + (*it)->physics->getBody()->GetPosition().y)*num, physics->getBody()->GetPosition().x - (*it)->physics->getBody()->GetPosition().x));
					}
					else
					{
						changeDirection(RIGHT);
						weapon->setAngle(atan2((*it)->physics->getBody()->GetPosition().y - physics->getBody()->GetPosition().y, (*it)->physics->getBody()->GetPosition().x - physics->getBody()->GetPosition().x));
					}

					float distance = abs((*it)->graphics->getPosition().x - graphics->getPosition().x);

					//cout << "Choice" << choice(gen) << endl;
					//system("pause");


					if (num >= 1.2)
						num = 1.2;
					weaponPower = ((distance / 1920)*(2.5 - num));


					wait.restart();
					canFire = true;
					hasObjective = true;
					break;

				}
			}
		}
	}

	if (canFire && myTurn &&hasObjective &&wait.getElapsedTime().asSeconds() >= 0.5)
	{
		//c//out << "POWA!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! ===== " << weaponPower << endl;
		//system("pause");
		weapon->fire(weaponPower);
		canFire = false;
	}
}


void ComputerPlayer::setOpponents(Team *team)
{
	enemyTeam = team;
}

ComputerPlayer::~ComputerPlayer()
{
}
