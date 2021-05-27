#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <cstdlib>
#include <vector>
#include <ctime>
#include "PhysVector.h"
#include "PhysParticle.h"
#include "../Utils.h"
#include "PhysicsWorld.h"
#include "DragForceGenerator.h"
#include "ForceGenerator.h"
#include "ForceRegistry.h"
#include "GravityForceGenerator.h"
#include "Springs/AnchoredSpring.h"
#include "Springs/BungeeSpring.h"
#include "Collision/ParticleContact.h"
#include "Collision/ContactResolver.h"
#include "Links/ParticleLink.h"
#include "Links/Rod.h"
#include "Rigidbodies/CircleRB.h"
#include "Rigidbodies/RectPrism.h"

class RenderParticle
{
public:
	PhysParticle* referenceParticle;
	sf::Shape* particleShape;

public:
	RenderParticle(PhysParticle* p, sf::Shape* s) : referenceParticle(p), particleShape(s) {}
	void draw(sf::RenderWindow* window);
};

