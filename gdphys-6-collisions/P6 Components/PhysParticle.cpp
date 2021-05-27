#include "PhysParticle.h"
#include "../Utils.h"
#include <iostream>
#include "Rigidbodies/CircleRB.h"
#include "Rigidbodies/RectPrism.h"
using namespace std;

void PhysParticle::update(float time)
{
	if (mass == 0)
	{
		return;
	}
	updatePos(time);
	updateVelocity(time);
	resetForce();
}

void PhysParticle::updatePos(float time)
{
	position = position + (velocity * time) + ((acceleration * powf(time, 2)) * (1 / 2));
	//compute rotation similar to above, but w/o acc
	rotation = rotation + angularVelocity * time;
}

void PhysParticle::updateVelocity(float time)
{
	//setting acceleration
	acceleration = acceleration + accumulatedForce * (1 / mass);

	velocity = velocity + acceleration * time;
	//velocity with damping
	velocity = velocity * powf(damping, time);

	float mI = momentOfInertia();
	angularVelocity = angularVelocity + (-accumulatedTorque) * ((float)1 / mI) * time;
	angularVelocity = angularVelocity * powf(angularDamping, time);

	//calculate total velocity over the sim
	totalVelocity = totalVelocity + velocity;
}

//DEPRECATED
float PhysParticle::measureTime()
{
	sf::Clock clock;
	sf::Time elapsed = clock.getElapsedTime();
	return elapsed.asSeconds() * 1000;
}

bool PhysParticle::getIsDestroyed()
{
	return isDestroyed;
}

void PhysParticle::setIsDestroyed()
{
	isDestroyed = true;
}

void PhysParticle::addForce(PhysVector f)
{
	accumulatedForce = accumulatedForce + f;
}

void PhysParticle::resetForce()
{
	accumulatedForce = PhysVector(0, 0);
	accumulatedTorque = 0;
	acceleration = PhysVector(0, 0);
}

PhysParticle::PhysParticle()
{
}

PhysVector PhysParticle::toRenderPoint()
{
	return Utils::p6ToSFMLPoint(position);
}

void PhysParticle::addForceAtPoint(PhysVector point, PhysVector f)
{
	/*
	accumulatedForce = accumulatedForce + f;
	accumulatedTorque = accumulatedTorque + PhysVector::crossProductF(point, f);
	*/
}

float PhysParticle::momentOfInertia()
{
	return ((float)2/5) * mass * (radius * radius);
}

int PhysParticle::getParticleType()
{
	return this->ParticleType;
}






