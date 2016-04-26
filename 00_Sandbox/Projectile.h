#ifndef _PROJECTILE_H_
#define _PROJECTILE_H_

#include "RE\ReEngAppClass.h"
#include "RE\ReEng.h"
#include <SFML\Graphics.hpp>
#include "MyBoundingObjectClass.h"

class Projectile
{
private:
	vector3 origin; //coordinates of the projectile's original position
	float position; //0-1 value of how close the projectile is to its target
	vector3 target; //coordinates of projectile's target
	float speed; //how fast the projectile is moving
	float travelTime; //how long it should take the projectile to move the distance between its origin and its target
	matrix4 projMatrix = IDENTITY_M4; //model matrix for the projectile
	bool targetReached = false; //if the projectile has reached its target yet

public:
	//constructor; takes starting position, target position, and projectile speed
	Projectile(vector3 pos, vector3 trg, float spd);

	//move the projectile towards its target
	void moveProjectile(float timeSpan);

	//get functions
	matrix4 getMatrix();
	bool isTargetReached();
};

#endif // !_PROJECTILE_H_

