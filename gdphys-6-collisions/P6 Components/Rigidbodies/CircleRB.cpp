#include "CircleRB.h"

CircleRB::CircleRB()
{
	this->ParticleType = 1;
}

void CircleRB::addForceAtPoint(PhysVector point, PhysVector f)
{
	accumulatedForce = accumulatedForce + f;
	accumulatedTorque = accumulatedTorque + PhysVector::crossProductF(point, f);
}
