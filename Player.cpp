#include "Player.h"
#include <iostream>
#include "Level.h"
#include "Weapon.h"
#include "Shotgun.h"
#include "Projectile.h"
#include "Explosion.h"
#include "Grenade.h"
#include "SMG.h"

using namespace std;

Player::Player()
{
}

void Player::startTurn()
{
	level->centerView(graphics->getPosition().x, graphics->getPosition().y);
	level->view->setSize(800, 600);

	usedAction = false;

	myTurn = true;
}

void Player::endTurn()
{
	myTurn = false;

	if (weapon != NULL)
		weapon->destroy();

	weapon = NULL;
}

void Player::create(std::string image, float x, float y, b2World *world, float width, float height, BODY_TYPE physicsType, Level *l, BODY_SHAPE shape)
{
	Entity::create(image, x, y, world, width, height, physicsType,l,shape);

	physics->getBody()->SetFixedRotation(true);
	physics->getBody()->GetFixtureList()[0].SetDensity(1);
	physics->getBody()->GetFixtureList()[0].SetFriction(0.2);
	physics->getBody()->GetFixtureList()[0].SetRestitution(0.3);
	physics->getBody()->ResetMassData();

	dir = RIGHT;
	powering = false;
	myTurn = false;

	// SETTING UP THE NAME AND HEALTH
	if (!font.loadFromFile("calibri.ttf"))
	{
		// error...
	}

	name.setScale(0.7, 0.7);
	name.setFont(font);
	name.setString("Default");

	rect.setFillColor(sf::Color(176, 81, 102));
	rect.setOutlineColor(sf::Color::White);
	rect.setOutlineThickness(1);
	rect.setSize(sf::Vector2f(60, 30));

	health = 100;

	/*texture.loadFromFile(image);

	graphics = new sf::Sprite(texture);
	physics = new PhysicsBody(x, y, 32, 40, world, DYNAMIC);

	physics->getBody()->SetFixedRotation(true);
	physics->getBody()->SetUserData(this);

	//add foot sensor fixture

	physics = new PhysicsBody(x, y, graphics->getGlobalBounds().width, graphics->getGlobalBounds().height, world, DYNAMIC);
	physics->getBody()->SetFixedRotation(true);
	physics->getBody()->SetUserData(this);

	physics->addPolygonFixture(0.3f, 0.3f, 0, 0.2, true);


	graphics->setOrigin(84.f, 99.f);
	graphics->setScale(0.2f, 0.2f);
	graphics->setPosition(SCALE * physics->getPositionX(), SCALE * physics->getPositionY());
	graphics->setRotation(physics->getRotation() * 180 / b2_pi);*/
}

void Player::switchWeapon(int key)
{
	if (weapon != NULL)
		weapon->destroy();

	switch (key)
	{
		case 1: weapon = new Weapon();
				weapon->create("launcher.png", graphics->getPosition().x + 10, graphics->getPosition().y, level->world, 50, 20, DYNAMIC, level, BOX);
				break;

		case 2: weapon = new Shotgun();
				weapon->create("shotgun.png", graphics->getPosition().x + 10, graphics->getPosition().y + 10, level->world, 50, 20, DYNAMIC, level, BOX);
				break;

		case 3: weapon = new SMG();
				weapon->create("smg.png", graphics->getPosition().x + 10, graphics->getPosition().y + 10, level->world, 50, 20, DYNAMIC, level, BOX);
				break;
		case 4: weapon = new Grenade();
				weapon->create("grenade.png", graphics->getPosition().x + 10, graphics->getPosition().y + 10, level->world, 20, 20, DYNAMIC, level, BOX);
				break;

	}

	weapon->setOwner(this);
	level->AddEntity(weapon);

}

void Player::getInput(sf::Event *event)
{
	if (myTurn){

		if (event->type == sf::Event::KeyReleased)
		{
			if (event->key.code == sf::Keyboard::Left || event->key.code == sf::Keyboard::Right){
				b2Vec2 vel = physics->getBody()->GetLinearVelocity();
				vel.x = 0;

				physics->getBody()->SetLinearVelocity(vel);
			}
			else if (event->key.code == sf::Keyboard::Space)
			{
				if (weapon != NULL && !usedAction){
					if (powering == true){

						float p = power.getElapsedTime().asSeconds();

						cout << p << " Seconds" << endl;

						if (p >= 3)
							p = 3;


						weapon->fire(p);
						usedAction = true;
						powering = false;
					}
				}
			}
		}
		else if (event->type == sf::Event::KeyPressed)
		{
			if (event->key.code == sf::Keyboard::Return && jumpTime.getElapsedTime().asSeconds() >= 2){
				b2Vec2 vel = physics->getBody()->GetLinearVelocity();
				vel.y = -8;

				physics->getBody()->SetLinearVelocity(vel);
				jumpTime.restart();

			}

			// FIRE
			else if (event->key.code == sf::Keyboard::Space && !usedAction)
			{
				if (powering == false){
					power.restart();
					powering = true;
				}

			}
			// CHANGE WEAPON
			else if (event->key.code == sf::Keyboard::Num1)
				switchWeapon(1);
			else if (event->key.code == sf::Keyboard::Num2)
				switchWeapon(2);
			else if (event->key.code == sf::Keyboard::Num3)
				switchWeapon(3);
			else if (event->key.code == sf::Keyboard::Num4)
				switchWeapon(4);

		}
	}
}

ENTITY_TYPE Player::getType()
{
	return PLAYER;
}

void Player::checkCollision(Entity *other)
{

	if (other->getType() == EXPLOSION)
	{
		Explosion *exp = dynamic_cast<Explosion*>(other);
		health -= exp->getSize()/4;
	}
}

void Player::setWeapon(Weapon *w)
{
	weapon = w;
}

void Player::drawGUI(sf::RenderWindow *window)
{
	// UPDATE THE NAME POSTION
	name.setPosition(graphics->getPosition().x - 25, graphics->getPosition().y - 80);
	rect.setPosition(graphics->getPosition().x - 30, graphics->getPosition().y - 80);

	// DRAW THE NAME
	sf::RectangleShape rect2;
	rect2.setFillColor(sf::Color(156, 76, 93));
	rect2.setOutlineColor(sf::Color::White);
	rect2.setOutlineThickness(1);
	rect2.setSize(sf::Vector2f(60, 20));

	rect2.setPosition(graphics->getPosition().x - 30, graphics->getPosition().y - 45);

	sf::Text name2;
	name2.setScale(0.7, 0.7);
	name2.setFont(font);
	name2.setString(std::to_string(health));

	name2.setPosition(graphics->getPosition().x - 17, graphics->getPosition().y - 50);
	window->draw(rect);
	window->draw(rect2);
	window->draw(name);
	window->draw(name2);
}

void Player::receiveCommands()
{
	if (myTurn){
		// Check if the keyboard right key is pressed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			// physics: if it is pressed change the velocity of the object, so that it moves to the right.
			b2Vec2 vel = physics->getBody()->GetLinearVelocity();
			vel.x = 5;

			physics->getBody()->SetLinearVelocity(vel);

			// Change the direction flag so that the player sprite faces the other direction.

			if (dir == LEFT){
				changeDirection(RIGHT);
			}

			level->centerView(graphics->getPosition().x, graphics->getPosition().y);


		}
		// Check if the keyboard left key is pressed
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			// physics if it is pressed change the velocity of the object, so that it moves to the right.
			b2Vec2 vel = physics->getBody()->GetLinearVelocity();
			vel.x = -5;
			physics->getBody()->SetLinearVelocity(vel);

			//// Change the direction flag so that the player sprite faces the other direction.
			if (dir == RIGHT){
				changeDirection(LEFT);
			}

			level->centerView(graphics->getPosition().x, graphics->getPosition().y);
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			// physics if it is pressed change the velocity of the object, so that it moves to the right.
			//weapon->physics->getBody()->SetTransform(weapon->physics->getBody()->GetPosition(), 20);
			if (weapon != NULL){
				if (dir == RIGHT)
					weapon->setAim(DOWN);
				else if (dir == LEFT)
					weapon->setAim(UP);
			}


		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			// physics if it is pressed change the velocity of the object, so that it moves to the right.
			//weapon->physics->getBody()->SetTransform(weapon->physics->getBody()->GetPosition(), 20);
			if (weapon != NULL){
				if (dir == RIGHT)
					weapon->setAim(UP);
				else if (dir == LEFT)
					weapon->setAim(DOWN);
			}
		}
	}


}

void Player::update(sf::RenderWindow *window)
{	// Update the graphical representation so that is the same position as the physics counter part.
	graphics->setPosition(SCALE * physics->getPositionX(), SCALE * physics->getPositionY());
	graphics->setRotation(physics->getRotation() * 180 / b2_pi);

	if (health <= 0)
	{
		graphics->setScale(2, 0.5);
		health = 0;
	}

	sf::Packet packet;
	packet << P_MOVEMENT << physics->getBody()->GetPosition().x << physics->getBody()->GetPosition().y;
	level->socket.send(packet, sf::IpAddress(level->otherIP), (unsigned short)(63000));


	receiveCommands();
	drawGUI(window);
}

void Player::destroy()
{
	Entity::destroy();
	//delete graphics;
	//delete physics;
}

Player::~Player()
{
}
