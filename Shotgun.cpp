#include "Shotgun.h"
#include "Projectile.h"
#include "Level.h"
#include <iostream>
#include <math.h>
using namespace std;

Shotgun::Shotgun()
{
}

void Shotgun::fire(float power)
{
	srand(time(NULL));
	const double PI = 3.141592653589793238463;
	Projectile *bullet[5];

	for (int i = 0; i < 5; i++)
	{
		float angleDiff = 2*i * b2_pi / 180;
		cout << "ANGLE DIFF ================================ " << angleDiff << endl;

		bullet[i] = new Projectile();
		bullet[i]->create("bullet.png", graphics->getPosition().x , graphics->getPosition().y, level->world, 8, 8, DYNAMIC, level, CIRCLE);

		if (owner->getDir() == RIGHT)
			bullet[i]->physics->getBody()->ApplyLinearImpulse(b2Vec2(cos(getFireAngle() + angleDiff) , sin(getFireAngle() + angleDiff) ), bullet[i]->physics->getBody()->GetWorldCenter(), true);
		else if (owner->getDir() == LEFT)
			bullet[i]->physics->getBody()->ApplyLinearImpulse(-b2Vec2(cos(getFireAngle() - angleDiff) , sin(getFireAngle() - angleDiff) ), bullet[i]->physics->getBody()->GetWorldCenter(), true);

		bullet[i]->physics->getBody()->GetFixtureList()[0].SetFriction(1);
		bullet[i]->physics->getBody()->GetFixtureList()[0].SetDensity(0.1);
		bullet[i]->physics->getBody()->SetGravityScale(0);
		bullet[i]->physics->getBody()->ResetMassData();
		bullet[i]->setOwner(this);
		bullet[i]->setExplosionSize(20);
		level->AddEntity(bullet[i]);
	}

}

Shotgun::~Shotgun()
{
}
