#include "PhysicsWorld.h"


void PhysicsWorld::addParticle(PhysParticle* particle)
{
	particles.push_back(particle);
	//uncomment if need to apply gravity to particles
	//registry.add(particle, &Gravity); 
}

void PhysicsWorld::update(float time)
{
	updateParticleList();
	registry.updateForce(time);

	for (list<PhysParticle*>::iterator i = particles.begin(); i != particles.end(); i++)
	{
		//uncomment if need to apply gravity
		//(*i)->acceleration = gravity; 
		(*i)->update(time);

		//if current updating particle is rectprism, apply this to update edge positions
		if ((*i)->ParticleType == 3)
		{
			RectPrism* rect = dynamic_cast<RectPrism*>(*i);
			rect->updateRectPos();
		}
	}

	generateContacts(); 

	if (contacts.size() > 0)
	{
		contactResolver.max_iterations = contacts.size() * 2;
		contactResolver.resolveContacts(contacts, time);
	}
}

void PhysicsWorld::addContact(PhysParticle* p1, PhysParticle* p2, float restitution, PhysVector collisionNormal)
{
	ParticleContact* toAdd = new ParticleContact();

	toAdd->particles[0] = p1;
	toAdd->particles[1] = p2;
	toAdd->restitution = restitution;
	toAdd->collisonNormal = collisionNormal;

	contacts.push_back(toAdd);
}

void PhysicsWorld::updateParticleList()
{
	particles.remove_if(
		[](PhysParticle* p)
		{
			return p->getIsDestroyed();
		}
	);
}

void PhysicsWorld::generateContacts()
{
	contacts.clear();
	getOverlaps();

	for (list<ParticleLink*>::iterator i = links.begin(); i != links.end(); i++)
	{
		ParticleContact* contact = (*i)->getContact();
		if (contact != nullptr)
		{
			contacts.push_back(contact);
		}
	}
}

void PhysicsWorld::getOverlaps()
{
	for (int i = 0; i < particles.size() - 1; i++)
	{
		list<PhysParticle*>::iterator a = next(particles.begin(), i);

		for (int h = i + 1; h < particles.size(); h++)
		{
			list<PhysParticle*>::iterator b = next(particles.begin(), h);

			//0 = Particle, 2= Circle, 3 = Rect
			if ((*a)->getParticleType() == 0 && (*b)->getParticleType() == 0)
			{
				generateParticleContacts(*a, *b); //particle contact resolution
			}
			else
			{
				generateRigidbodyContacts(*a, *b); //rigidbody contact resolution
			}
		}
	}
}

void PhysicsWorld::generateParticleContacts(PhysParticle* a, PhysParticle* b)
{
	float mag2 = (a->position - b->position).magnitudeSquared();
	float rad2 = (a->radius + b->radius) * (a->radius + b->radius);

	if (mag2 <= rad2)
	{
		PhysVector dir = a->position - b->position;
		dir.normalize();
		float r = rad2 - mag2;
		float depth = sqrt(r);

		float restitution = a->restitution;
		if (b->restitution < restitution)
			restitution = b->restitution;

		addContact(a, b, restitution, dir);
	}
}

void PhysicsWorld::generateRigidbodyContacts(PhysParticle* a, PhysParticle* b)
{
	//if particles are both particle/circle
	if (a->getParticleType() == 2 && b->getParticleType() == 2 ||
		a->getParticleType() == 2 && b->getParticleType() == 0 ||
		a->getParticleType() == 0 && b->getParticleType() == 2)
	{
		generateParticleContacts(a, b);
	}
	//if particles are both rects
	else if (a->getParticleType() == 3 && b->getParticleType() == 3)
	{
		RectPrism* rect1 = dynamic_cast<RectPrism*>(a);
		RectPrism* rect2 = dynamic_cast<RectPrism*>(b);

		processRigidBodyContact1(rect1, rect2);
	}
	//if mixed
	else
	{
		RectPrism* rect = dynamic_cast<RectPrism*>(a);
		if (rect == nullptr)
		{
			rect = dynamic_cast<RectPrism*>(b);
			processRigidBodyContact2(rect, a); //a is a particle/circle
		}
		else
		{
			processRigidBodyContact2(rect, b); //b is a particle/circle
		}
	}
}

void PhysicsWorld::processRigidBodyContact1(RectPrism* a, RectPrism* b)
{
	PhysVector temp = PhysVector(0, 0);

	std::vector<RectPrism*> rects;
	rects.push_back(a);
	rects.push_back(b);

	bool ret = true;
	for (int i = 0; i < rects.size(); i++)
	{
		for (int e1 = 0; e1 < rects[i]->points.size(); e1++)
		{
			int e2 = (e1 + 1) % rects[i]->points.size();
			PhysVector p1 = rects[i]->points[e1];
			PhysVector p2 = rects[i]->points[e2];

			PhysVector perpendicularEdge = PhysVector(p2.y - p1.y, p1.x - p2.x);

			float minA = temp.dotProduct(perpendicularEdge, rects[0]->points[0]);
			float maxA = temp.dotProduct(perpendicularEdge, rects[0]->points[0]);

			for (int h = 1; h < rects[0]->points.size(); h++)
			{
				float ftemp = temp.dotProduct(perpendicularEdge, rects[0]->points[h]);
				if (ftemp < minA)
				{
					minA = ftemp;
				}
				if (ftemp > maxA)
				{
					maxA = ftemp;
				}
			}

			//SECOND RECT
			float minB = temp.dotProduct(perpendicularEdge, rects[1]->points[0]);
			float maxB = temp.dotProduct(perpendicularEdge, rects[1]->points[0]);

			for (int h = 1; h < rects[1]->points.size(); h++)
			{
				float ftemp = temp.dotProduct(perpendicularEdge, rects[1]->points[h]);
				if (ftemp < minB)
				{
					minB = ftemp;
				}
				if (ftemp > maxB)
				{
					maxB = ftemp;
				}
			}

			if (maxA < minB || maxB < minA)
			{
				ret = false;
				break;
			}
		}
	}
	//the for loop fails to exit since a collision is detected
	if (ret)
	{
		PhysVector dir = a->position - b->position;
		dir.normalize();
		

		float restitution = a->restitution;
		if (b->restitution < restitution)
			restitution = b->restitution;

		addContact(a, b, restitution, dir);
	}
}

void PhysicsWorld::processRigidBodyContact2(RectPrism* a, PhysParticle* b)
{
	PhysVector relVector = b->position - a->position;
	float invAngle = -a->rotation;
	PhysVector locVector = Utils::rotatePoint(relVector, invAngle);

	float minX = locVector.x;
	if ((a->width / 2) < minX)
	{
		minX = a->width / 2;
	}

	float maxX = minX;
	if (maxX < -a->width / 2)
	{
		maxX = -a->width / 2;
	}

	float minY = locVector.y;
	if ((a->height / 2) < minY)
	{
		minY = a->height / 2;
	}

	float maxY = minY;
	if (maxY < -a->height / 2)
	{
		maxY = -a->height / 2;
	}

	float D_X = locVector.x - maxX;
	float D_Y = locVector.y - maxY;

	bool col = (D_X * D_X + D_Y * D_Y) <= (b->radius * b->radius);

	//collision is detected
	if (col)
	{
		PhysVector dir = a->position - b->position;
		dir.normalize();

		float restitution = a->restitution;
		if (b->restitution < a->restitution)
		{
			restitution = b->restitution;
		}

		addContact(a, b, restitution, dir);
	}
}



