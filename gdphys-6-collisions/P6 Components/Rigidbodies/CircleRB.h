#pragma once
#include "../PhysicsWorld.h"
#include "../PhysParticle.h"
#include "../PhysVector.h"
#include <SFML/Graphics.hpp>
class PhysParticle;
class CircleRB : public PhysParticle
{
public:
	CircleRB();
	void addForceAtPoint(PhysVector point, PhysVector f);
};

