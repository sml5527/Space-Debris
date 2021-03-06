#include "Projectile.h"
//constructor
Projectile::Projectile(vector3 pos, vector3 trg, float spd, float massIn)
{
	//initialize variables with given values
	origin = pos;
	position = 0;
	target = trg;
	speed = spd;
	mass = massIn;
	currentLocation = origin;

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

	currentLocation = travelVector;

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

vector3 Projectile::getVelocity()
{
	vector3 velocity = target - origin;
	velocity = glm::normalize(velocity);
	return velocity * speed;

}

vector3 Projectile::getCurrentLocation()
{
	return currentLocation;
}

float Projectile::getMass()
{
	return mass;
}

void Projectile::changeVelocity(vector3 newVelocity, vector3 newOrigin)
{
	position = 0;
	origin = newOrigin;
	target = origin + glm::normalize(newVelocity) * 10.0f;
	speed = 10;
}
