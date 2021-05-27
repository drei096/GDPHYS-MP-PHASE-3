#pragma once
#include<list>
#include"PhysParticle.h"
#include "ForceRegistry.h"
#include "GravityForceGenerator.h"
#include "Collision/ParticleContact.h"
#include "Collision/ContactResolver.h"
#include <vector>
#include "Links/ParticleLink.h"
#include "Rigidbodies/CircleRB.h"
#include "Rigidbodies/RectPrism.h"
#include "../Utils.h"


using namespace std;

class PhysicsWorld
{
public:
	ForceRegistry registry;
	list <PhysParticle*> particles;
	list <ParticleLink*> links;

	//Change Gravity Value here
	PhysVector gravity = PhysVector(0, 0);  // 20m/s2 down

	vector<ParticleContact*> contacts;

public:
	void addParticle(PhysParticle* particle);
	void update(float time);
	void addContact(PhysParticle* p1, PhysParticle* p2, float restitution, PhysVector collisionNormal);

protected:
	GravityForceGenerator Gravity = GravityForceGenerator();
	void updateParticleList();
	ContactResolver contactResolver = ContactResolver(20);

	void generateContacts();
	void getOverlaps();

	//generating contacts for both particles
	void generateParticleContacts(PhysParticle* a, PhysParticle* b);
	//generating contacts if 1 or both are RB's
	void generateRigidbodyContacts(PhysParticle* a, PhysParticle* b);

	//processing contacts
	void processRigidBodyContact1(RectPrism* a, RectPrism* b);
	void processRigidBodyContact2(RectPrism* a, PhysParticle* b);
};

