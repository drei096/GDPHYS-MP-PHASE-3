#include "RectPrism.h"

RectPrism::RectPrism()
{
}

void RectPrism::addForceAtPoint(PhysVector point, PhysVector f)
{
	accumulatedForce = accumulatedForce + f;
	accumulatedTorque = accumulatedTorque + PhysVector::crossProductF(point, f);
}

void RectPrism::updateRectPos()
{
	points.at(0) = (Utils::rotatePoint(ul, rotation) + position);
	points.at(1) = (Utils::rotatePoint(ur, rotation) + position);
	points.at(2) = (Utils::rotatePoint(lr, rotation) + position);
	points.at(3) = (Utils::rotatePoint(ll, rotation) + position);
}
