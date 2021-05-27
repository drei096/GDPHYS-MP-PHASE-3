#pragma once
//#include "../PhysicsWorld.h"
#include "../PhysParticle.h"
//#include "../PhysVector.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include "../../Utils.h"
class RectPrism : public PhysParticle
{
public:
	RectPrism();
	void addForceAtPoint(PhysVector point, PhysVector f);
	float width;
	float height;
	std::vector<PhysVector> points;

	PhysVector ul = PhysVector(0,0);
	PhysVector ll = PhysVector(0,0);
	PhysVector ur = PhysVector(0,0);
	PhysVector lr = PhysVector(0,0);

	void updateRectPos();
};

