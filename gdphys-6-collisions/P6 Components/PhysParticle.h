#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include"PhysVector.h"

using namespace std;
class PhysParticle
{
public:
	string name;
	float mass;
	float radius;
	float restitution = 1;
	sf::Clock timer;
	PhysVector position = PhysVector(0, 0);
	PhysVector velocity = PhysVector(0, 0);
	PhysVector acceleration = PhysVector(0, 0);
	PhysVector totalVelocity = PhysVector(0, 0);
	PhysVector initialPos = PhysVector(0, 0);

	int ParticleType;

	bool isFinished = false;
	//EDIT DAMPING VALUE HERE
	float damping;
	float angularDamping = 0.9f;
	float angularVelocity = 0;
	float rotation = 0;

public:
	void update(float time);
	float measureTime();
	bool getIsDestroyed();
	void setIsDestroyed();
	void addForce(PhysVector f);
	void resetForce();
	PhysParticle();
	PhysVector toRenderPoint();
	virtual void addForceAtPoint(PhysVector point, PhysVector f) = 0;
	float momentOfInertia();
	int getParticleType();


private:
	void updatePos(float time);
	void updateVelocity(float time);
	//void updateDestroyed();

protected:
	bool isDestroyed = false;
	PhysVector accumulatedForce = PhysVector(0, 0);
	float accumulatedTorque = 0;

};

