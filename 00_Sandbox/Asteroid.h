#ifndef _ASTEROID_H_
#define _ASTEROID_H_

#include "RE\ReEngAppClass.h"
#include "RE\ReEng.h"
#include <SFML\Graphics.hpp>
#include "MyBoundingObjectClass.h"
#include "Projectile.h"

class Asteroid : public Projectile
{
private:

public:
	typedef Projectile super;
	//constructor; takes starting position, target position, and projectile speed
	Asteroid(vector3 pos, vector3 trg, float spd, float mass);

	//move the projectile towards its target
	void moveAsteroid(float timeSpan);

	//get functions
	matrix4 getMatrix();
	bool isTargetReached();
};

#endif // !_PROJECTILE_H_

