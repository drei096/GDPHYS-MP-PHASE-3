#include "RenderParticle.h"

void RenderParticle::draw(sf::RenderWindow* window)
{
	if (!referenceParticle->getIsDestroyed())
	{
		PhysVector v = referenceParticle->toRenderPoint();
		particleShape->setPosition(v.x, v.y);

		window->draw(*particleShape);
	}
}
