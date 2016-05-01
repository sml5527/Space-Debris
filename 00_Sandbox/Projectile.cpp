#include "Projectile.h"
//constructor
Projectile::Projectile(vector3 pos, vector3 trg, float spd)
{
	//initialize variables with given values
	origin = pos;
	position = 0;
	target = trg;
	speed = spd;

	//find travelTime
	travelTime = glm::distance(origin, target);
	
	//create the projMatrix using the current position
	projMatrix = glm::translate(origin);
}

//move the projectile toward its target; takes how much time has passed since the last move
void Projectile::moveProjectile(float timeSpan)
{
	//set the projectile to its origin
	projMatrix = glm::translate(origin);

	//increment position by the percent of travelTime that has passed
	//the time moved between calls should equal timeSpan * speed
	//if position passes 1, set it to 1, and set targetReached to true
	position += (timeSpan * speed) / travelTime;
	std::cout << position;
	if (position > 1)
	{
		position = 1;
		targetReached = true;
	}

	//use lerp to find the projectile's current location if position is <1
	//otherwise the projectile's current location is equal to its target
	vector3 travelVector;
	if (position < 1)
	{
		travelVector = glm::lerp(origin, target, position);
	}
	else
	{
		travelVector = target;
	}

	//translate the projectile matrix by its travelVector
	projMatrix = glm::translate(travelVector);
}

//get the position matrix of the projectile
matrix4 Projectile::getMatrix()
{
	return projMatrix;
}

//get whether the projectile has reached its target
bool Projectile::isTargetReached()
{
	return targetReached;
}
