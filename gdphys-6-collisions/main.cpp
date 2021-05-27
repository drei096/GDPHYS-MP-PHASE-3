#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <cstdlib>
#include <vector>
#include <ctime>
#include "P6 components/PhysVector.h"
#include "P6 components/PhysParticle.h"
#include "Utils.h"
#include "P6 components/PhysicsWorld.h"
#include "P6 Components/DragForceGenerator.h"
#include "P6 Components/ForceGenerator.h"
#include "P6 Components/ForceRegistry.h"
#include "P6 Components/GravityForceGenerator.h"
#include "P6 Components/Springs/AnchoredSpring.h"
#include "P6 Components/Springs/BungeeSpring.h"
#include "P6 Components/Collision/ParticleContact.h"
#include "P6 Components/Collision/ContactResolver.h"
#include "P6 Components/Links/ParticleLink.h"
#include "P6 Components/Links/Rod.h"
#include "P6 Components/RenderParticle.h"
#include "P6 Components/Rigidbodies/CircleRB.h"
#include "P6 Components/Rigidbodies/RectPrism.h"

#define PI 3.14159

using namespace std;


int main()
{
    const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
    Utils utils;
    PhysicsWorld pWorld = PhysicsWorld();
    std::list <RenderParticle*> renderParticles;

    sf::RenderWindow window(sf::VideoMode(720, 500), "P6 Test");

    sf::Event event;

    Utils::offset = PhysVector(0, 250);

    /*PARTICLE TYPES
    * 0 = PARTICLE
    * 2 = CIRCLERB
    * 3 = RECTPRISM
    */
    
    //CIRCLE1 = LEFT CIRCLE AT TOP
    CircleRB circle1;
    circle1.name = "circle1";
    circle1.mass = 50.0f;
    circle1.damping = 1.0f;
    circle1.radius = 20.0f;
    circle1.ParticleType = 2;

    //CIRCLE1 SHAPE
    sf::CircleShape circle1Shape(circle1.radius);
    circle1Shape.setFillColor(sf::Color::White);
    circle1Shape.setOrigin(circle1Shape.getRadius(), circle1Shape.getRadius());

    //CIRCLE1 RENDERPOINT AND POSITION
    PhysVector renderPoint1 = circle1.toRenderPoint();
    circle1.position = PhysVector(350, 100);
    circle1.initialPos = circle1.position;

    //CIRCLE1 RENDERPARTICLE
    RenderParticle circle1Particle = RenderParticle(&circle1, &circle1Shape);

    //ADDING FORCE TO CIRCLE1
    //circle1.addForce(PhysVector(100000, 0));
    circle1.addForceAtPoint(PhysVector(0, 0), PhysVector(100000, 0));
    
    //ADDING CIRCLE1 TO RP AND PWORLD
    renderParticles.push_back(&circle1Particle);
    pWorld.addParticle(&circle1);


    //RECT 3 = LEFT RECTANGLE AT MIDDLE
    RectPrism* rect3 = new RectPrism();
    rect3->name = "Rectangle3";
    rect3->mass = 50.0f;
    rect3->damping = 1.0f;
    rect3->radius = 25;
    rect3->ParticleType = 3;

    rect3->width = 80;
    rect3->height = 40;
    rect3->rotation = -(45 * (180 / PI));

    //RECT3 CORNER POSITIONS
    rect3->ul = PhysVector(-rect3->width / 2, rect3->height / 2);
    rect3->ll = PhysVector(-rect3->width / 2, -rect3->height / 2);
    rect3->ur = PhysVector(rect3->width / 2, rect3->height / 2);
    rect3->lr = PhysVector(rect3->width / 2, -rect3->height / 2);

    //RECT3 SHAPE
    sf::RectangleShape rect3Shape(sf::Vector2f(rect3->width, rect3->height));
    rect3Shape.setFillColor(sf::Color::Blue);
    rect3Shape.setOrigin(sf::Vector2f(rect3->width / 2, rect3->height / 2));
    rect3Shape.setRotation(rect3->rotation);

    //RECT3 RENDERPOINT
    PhysVector renderPoint5 = rect3->toRenderPoint();
    rect3->position = PhysVector(350, 0);
    rect3->initialPos = rect3->position;

    //RECT3 RENDERPARTICLE
    RenderParticle rectangle3Particle = RenderParticle(rect3, &rect3Shape);
    renderParticles.push_back(&rectangle3Particle);

    //SHAPE POS FOR ROTATION
    PhysVector rect3ShapePos = Utils::p6ToSFMLPoint(rect3->position);

    //ADDING EDGES FOR COLLISION DETECTION
    rect3->points.push_back(Utils::rotatePoint(rect3->ul, rect3->rotation) + rect3->position);
    rect3->points.push_back(Utils::rotatePoint(rect3->ur, rect3->rotation) + rect3->position);
    rect3->points.push_back(Utils::rotatePoint(rect3->lr, rect3->rotation) + rect3->position);
    rect3->points.push_back(Utils::rotatePoint(rect3->ll, rect3->rotation) + rect3->position);

    //ADDING FORCE TO RECT3
    //rect3->addForce(PhysVector(50000, 0));
    //ADDING FORCE WITH POSSIBLE ROTATION
    rect3->addForceAtPoint(PhysVector(0, 0), PhysVector(50000, 0));

    //ADDING RECT3 TO PWORLD
    pWorld.addParticle(rect3);

    //////////////////////////////////////////////////////////////////////////////////////////
    //CIRCLE2 = RIGHT CIRCLE AT TOP

    CircleRB circle2;
    circle2.name = "circle2";
    circle2.mass = 50.0f;
    circle2.damping = 1.0f;
    circle2.radius = 20.0f;
    circle2.ParticleType = 2;

    //CIRCLE2 SHAPE
    sf::CircleShape circle2Shape(circle2.radius);
    circle2Shape.setFillColor(sf::Color::White);
    circle2Shape.setOrigin(circle2Shape.getRadius(), circle2Shape.getRadius());

    //CIRCLE2 RENDERPOINT
    PhysVector renderPoint2 = circle2.toRenderPoint();
    circle2.position = PhysVector(600, 100);
    circle2.initialPos = circle2.position;

    //CIRCLE2 RENDERPARTICLE
    RenderParticle circle2Particle = RenderParticle(&circle2, &circle2Shape);

    //ADDING FORCE TO CIRCLE2
    circle2.addForce(PhysVector(-100000, 0));

    //ADDING CIRCLE2 TO RP AND PWORLD
    renderParticles.push_back(&circle2Particle);
    pWorld.addParticle(&circle2);
   

    //CIRCLE3 = RIGHT CIRCLE AT MIDDLE
    CircleRB circle3;
    circle3.name = "circle3";
    circle3.mass = 50.0f;
    circle3.damping = 1.0f;
    circle3.radius = 20.0f;
    circle3.ParticleType = 2;

    //CIRCLE3 SHAPE
    sf::CircleShape circle3Shape(circle3.radius);
    circle3Shape.setFillColor(sf::Color::White);
    circle3Shape.setOrigin(circle3Shape.getRadius(), circle3Shape.getRadius());

    //CIRCLE3 RENDERPOINT
    PhysVector renderPoint6 = circle3.toRenderPoint();
    circle3.position = PhysVector(600, 0);
    circle3.initialPos = circle3.position;

    //CIRCLE3 RENDERPARTICLE
    RenderParticle circle3Particle = RenderParticle(&circle3, &circle3Shape);

    //ADDING FORCE TO CIRCLE3
    circle3.addForce(PhysVector(-50000, 0));

    //ADDING CIRCLE3 TO RP AND PWORLD
    renderParticles.push_back(&circle3Particle);
    pWorld.addParticle(&circle3);

   

    /////////////////////////////////////////////////////////////////////////////////////

    //RECT 1 = LEFT RECTANGLE AT BOTTOM
    RectPrism* rect1 = new RectPrism();
    rect1->name = "Rectangle1";
    rect1->mass = 50.0f;
    rect1->damping = 1.0f;
    rect1->radius = 25;
    rect1->ParticleType = 3;

    rect1->width = 80;
    rect1->height = 40;
    rect1->rotation = -(45 * (180/PI));

    //RECT1 EDGE POSITIONS
    rect1->ul = PhysVector(-rect1->width / 2, rect1->height / 2);
    rect1->ll = PhysVector(-rect1->width / 2, -rect1->height / 2);
    rect1->ur = PhysVector(rect1->width / 2, rect1->height / 2);
    rect1->lr = PhysVector(rect1->width / 2, -rect1->height / 2);

    //RECT1 SHAPE
    sf::RectangleShape rect1Shape(sf::Vector2f(rect1->width, rect1->height));
    rect1Shape.setFillColor(sf::Color::Red);
    rect1Shape.setOrigin(sf::Vector2f(rect1->width / 2, rect1->height / 2));
    rect1Shape.setRotation(rect1->rotation);

    //RECT1 RENDERPOINT
    PhysVector renderPoint3 = rect1->toRenderPoint();
    rect1->position = PhysVector(350, -150);
    rect1->initialPos = rect1->position;
    
    //SHAPE POS FOR ROTATION
    PhysVector rect1ShapePos = Utils::p6ToSFMLPoint(rect1->position);

    //RECT1 RENDERPARTICLE
    RenderParticle rectangle1Particle = RenderParticle(rect1, &rect1Shape);
    renderParticles.push_back(&rectangle1Particle);

    //RECT1 EDGE POSITIONS FOR COLLISION DETECTION
    rect1->points.push_back(Utils::rotatePoint(rect1->ul, rect1->rotation) + rect1->position);
    rect1->points.push_back(Utils::rotatePoint(rect1->ur, rect1->rotation) + rect1->position);
    rect1->points.push_back(Utils::rotatePoint(rect1->lr, rect1->rotation) + rect1->position);
    rect1->points.push_back(Utils::rotatePoint(rect1->ll, rect1->rotation) + rect1->position);

    //ADDING FORCE TO RECT1 AND ADDING TO PWORLD
    //rect1->addForce(PhysVector(100000, 0));
    //ADDING FORCE W/ POSSIBLE ROTATION
    rect1->addForceAtPoint(PhysVector(0, 0), PhysVector(50000, 0));

    pWorld.addParticle(rect1);


    //RECT2 = RIGHT RECTANGLE AT BOTTOM
    RectPrism* rect2 = new RectPrism();
    rect2->name = "Rectangle2";
    rect2->mass = 50.0f;
    rect2->damping = 1.0f;
    rect2->radius = 25;
    rect2->ParticleType = 3;
    
    rect2->width = 80;
    rect2->height = 40;
    rect2->rotation = 45 * (180 / PI);

    //RECT2 EDGE POSITIONS
    rect2->ul = PhysVector(-rect2->width / 2, rect2->height / 2);
    rect2->ll = PhysVector(-rect2->width / 2, -rect2->height / 2);
    rect2->ur = PhysVector(rect2->width / 2, rect2->height / 2);
    rect2->lr = PhysVector(rect2->width / 2, -rect2->height / 2);

    //RECT2 SHAPE
    sf::RectangleShape rect2Shape(sf::Vector2f(rect2->width, rect2->height));
    rect2Shape.setFillColor(sf::Color::Blue);
    rect2Shape.setOrigin(sf::Vector2f(rect2->width / 2, rect2->height / 2));
    rect2Shape.setRotation(rect2->rotation);

    //RECT2 RENDERPOINT
    PhysVector renderPoint4 = rect2->toRenderPoint();
    rect2->position = PhysVector(600, -150);
    rect2->initialPos = rect2->position;

    //RECT2 RENDERPARTICLE
    RenderParticle rectangle2Particle = RenderParticle(rect2, &rect2Shape);
    renderParticles.push_back(&rectangle2Particle);

    //SHAPE POS FOR ROTATION
    PhysVector rect2ShapePos = Utils::p6ToSFMLPoint(rect2->position);

    //RECT2 EDGE POSITIONS FOR COLLISION DETECTION
    rect2->points.push_back(Utils::rotatePoint(rect2->ul, rect2->rotation) + rect2->position);
    rect2->points.push_back(Utils::rotatePoint(rect2->ur, rect2->rotation) + rect2->position);
    rect2->points.push_back(Utils::rotatePoint(rect2->lr, rect2->rotation) + rect2->position);
    rect2->points.push_back(Utils::rotatePoint(rect2->ll, rect2->rotation) + rect2->position);

    //ADDING FORCE TO RECT2 AND ADD TO PWORLD
    //rect2->addForce(PhysVector(-50000, 0));
    //ADDING FORCE WITH POSSIBLE ROTATION
    rect2->addForceAtPoint(PhysVector(0, 0), PhysVector(-50000, 0));
    pWorld.addParticle(rect2);

    /////////////////////////////////////////////////////////////////////////////////////
    
    
    PhysVector temp(0, 0);

    
    
    /////////////////////////////////////////////////////////////////////
    

    sf::Clock clock;
    sf::Time timeSinceLast = sf::Time::Zero;

    while (1) {

        timeSinceLast += clock.restart();

        if (timeSinceLast > TimePerFrame) {

            timeSinceLast -= TimePerFrame;

            //PHYSICS WORLD UPDATE INCLUDING RECTPRISMS
            pWorld.update(TimePerFrame.asMilliseconds() / 1000.0f);

            //UPDATING ROTATION
            rect1ShapePos = Utils::p6ToSFMLPoint(rect1->position);
            rect1Shape.setPosition(rect1ShapePos.x, rect1ShapePos.y);
            rect1Shape.setRotation(rect1->rotation);

            rect2ShapePos = Utils::p6ToSFMLPoint(rect2->position);
            rect2Shape.setPosition(rect2ShapePos.x, rect2ShapePos.y);
            rect2Shape.setRotation(rect2->rotation);

            rect3ShapePos = Utils::p6ToSFMLPoint(rect3->position);
            rect3Shape.setPosition(rect3ShapePos.x, rect3ShapePos.y);
            rect3Shape.setRotation(rect3->rotation);

            //POLL EVENTS
            window.pollEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();

            window.clear();

            //RENDERING RENDERPARTICLES
            for (std::list<RenderParticle*>::iterator i = renderParticles.begin(); i != renderParticles.end(); i++)
            {
                (*i)->draw(&window);
            }
                
                
            window.display();


            
            /*
            if (bullet.position.x > bullet.initialPos.x && bullet.position.y >= bullet.initialPos.y)
            {
                break;
            }
            */
           
        }
    }

    //utils.displayDistanceTravelled(bullet);


    return 0;
}