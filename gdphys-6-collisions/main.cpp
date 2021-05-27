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
    sf::Texture shurikenTexture;
    sf::Sprite shurikenSprite;

    Utils::offset = PhysVector(0, 250);

    
    //CIRCLE1
    
    CircleRB circle1;
    circle1.name = "circle1";
    circle1.mass = 50.0f;
    circle1.damping = 1.0f;
    circle1.radius = 20.0f;
    circle1.ParticleType = 2;

    sf::CircleShape circle1Shape(circle1.radius);
    circle1Shape.setFillColor(sf::Color::White);
    circle1Shape.setOrigin(circle1Shape.getRadius(), circle1Shape.getRadius());

    PhysVector renderPoint1 = circle1.toRenderPoint();
    circle1.position = PhysVector(350, 100);
    circle1.initialPos = circle1.position;

    RenderParticle circle1Particle = RenderParticle(&circle1, &circle1Shape);

    circle1.addForce(PhysVector(100000, 0));
    
    renderParticles.push_back(&circle1Particle);
    pWorld.addParticle(&circle1);

    //RECT 3
    RectPrism* rect3 = new RectPrism();
    rect3->name = "Rectangle3";
    rect3->mass = 50.0f;
    rect3->damping = 1.0f;
    rect3->radius = 25;
    rect3->ParticleType = 3;

    rect3->width = 80;
    rect3->height = 40;
    rect3->rotation = -(45 * (180 / PI));

    rect3->ul = PhysVector(-rect3->width / 2, rect3->height / 2);
    rect3->ll = PhysVector(-rect3->width / 2, -rect3->height / 2);
    rect3->ur = PhysVector(rect3->width / 2, rect3->height / 2);
    rect3->lr = PhysVector(rect3->width / 2, -rect3->height / 2);

    sf::RectangleShape rect3Shape(sf::Vector2f(rect3->width, rect3->height));
    rect3Shape.setFillColor(sf::Color::Blue);
    rect3Shape.setOrigin(sf::Vector2f(rect3->width / 2, rect3->height / 2));
    rect3Shape.setRotation(rect3->rotation);

    PhysVector renderPoint5 = rect3->toRenderPoint();
    rect3->position = PhysVector(350, 0);
    rect3->initialPos = rect3->position;

    RenderParticle rectangle3Particle = RenderParticle(rect3, &rect3Shape);
    renderParticles.push_back(&rectangle3Particle);

    rect3->points.push_back(Utils::rotatePoint(rect3->ul, rect3->rotation) + rect3->position);
    rect3->points.push_back(Utils::rotatePoint(rect3->ur, rect3->rotation) + rect3->position);
    rect3->points.push_back(Utils::rotatePoint(rect3->lr, rect3->rotation) + rect3->position);
    rect3->points.push_back(Utils::rotatePoint(rect3->ll, rect3->rotation) + rect3->position);

    rect3->addForce(PhysVector(50000, 0));
    pWorld.addParticle(rect3);

    //CIRCLE2
    CircleRB circle2;
    circle2.name = "circle2";
    circle2.mass = 50.0f;
    circle2.damping = 1.0f;
    circle2.radius = 20.0f;
    circle2.ParticleType = 2;

    sf::CircleShape circle2Shape(circle2.radius);
    circle2Shape.setFillColor(sf::Color::White);
    circle2Shape.setOrigin(circle2Shape.getRadius(), circle2Shape.getRadius());

    PhysVector renderPoint2 = circle2.toRenderPoint();
    circle2.position = PhysVector(600, 100);
    circle2.initialPos = circle2.position;

    RenderParticle circle2Particle = RenderParticle(&circle2, &circle2Shape);

    circle2.addForce(PhysVector(-100000, 0));

    renderParticles.push_back(&circle2Particle);
    pWorld.addParticle(&circle2);
   

    //CIRCLE3
    CircleRB circle3;
    circle3.name = "circle3";
    circle3.mass = 50.0f;
    circle3.damping = 1.0f;
    circle3.radius = 20.0f;
    circle3.ParticleType = 2;

    sf::CircleShape circle3Shape(circle3.radius);
    circle3Shape.setFillColor(sf::Color::White);
    circle3Shape.setOrigin(circle3Shape.getRadius(), circle3Shape.getRadius());

    PhysVector renderPoint6 = circle3.toRenderPoint();
    circle3.position = PhysVector(600, 0);
    circle3.initialPos = circle3.position;

    RenderParticle circle3Particle = RenderParticle(&circle3, &circle3Shape);

    circle3.addForce(PhysVector(-50000, 0));

    renderParticles.push_back(&circle3Particle);
    pWorld.addParticle(&circle3);

   

    /////////////////////////////////////////////////////////////////////////////////////

    //RECT 1
    RectPrism* rect1 = new RectPrism();
    rect1->name = "Rectangle1";
    rect1->mass = 50.0f;
    rect1->damping = 1.0f;
    rect1->radius = 25;
    rect1->ParticleType = 3;

    rect1->width = 80;
    rect1->height = 40;
    rect1->rotation = -(45 * (180/PI));

    rect1->ul = PhysVector(-rect1->width / 2, rect1->height / 2);
    rect1->ll = PhysVector(-rect1->width / 2, -rect1->height / 2);
    rect1->ur = PhysVector(rect1->width / 2, rect1->height / 2);
    rect1->lr = PhysVector(rect1->width / 2, -rect1->height / 2);

    sf::RectangleShape rect1Shape(sf::Vector2f(rect1->width, rect1->height));
    rect1Shape.setFillColor(sf::Color::Red);
    rect1Shape.setOrigin(sf::Vector2f(rect1->width / 2, rect1->height / 2));
    rect1Shape.setRotation(rect1->rotation);

    PhysVector renderPoint3 = rect1->toRenderPoint();
    rect1->position = PhysVector(350, -150);
    rect1->initialPos = rect1->position;
    
    RenderParticle rectangle1Particle = RenderParticle(rect1, &rect1Shape);
    renderParticles.push_back(&rectangle1Particle);

    rect1->points.push_back(Utils::rotatePoint(rect1->ul, rect1->rotation) + rect1->position);
    rect1->points.push_back(Utils::rotatePoint(rect1->ur, rect1->rotation) + rect1->position);
    rect1->points.push_back(Utils::rotatePoint(rect1->lr, rect1->rotation) + rect1->position);
    rect1->points.push_back(Utils::rotatePoint(rect1->ll, rect1->rotation) + rect1->position);

    rect1->addForce(PhysVector(100000, 0));
    pWorld.addParticle(rect1);

    //RECT2
    RectPrism* rect2 = new RectPrism();
    rect2->name = "Rectangle2";
    rect2->mass = 50.0f;
    rect2->damping = 1.0f;
    rect2->radius = 25;
    rect2->ParticleType = 3;
    
    rect2->width = 80;
    rect2->height = 40;
    rect2->rotation = 45 * (180 / PI);

    rect2->ul = PhysVector(-rect2->width / 2, rect2->height / 2);
    rect2->ll = PhysVector(-rect2->width / 2, -rect2->height / 2);
    rect2->ur = PhysVector(rect2->width / 2, rect2->height / 2);
    rect2->lr = PhysVector(rect2->width / 2, -rect2->height / 2);

    sf::RectangleShape rect2Shape(sf::Vector2f(rect2->width, rect2->height));
    rect2Shape.setFillColor(sf::Color::Blue);
    rect2Shape.setOrigin(sf::Vector2f(rect2->width / 2, rect2->height / 2));
    rect2Shape.setRotation(rect2->rotation);

    PhysVector renderPoint4 = rect2->toRenderPoint();
    rect2->position = PhysVector(600, -150);
    rect2->initialPos = rect2->position;

    RenderParticle rectangle2Particle = RenderParticle(rect2, &rect2Shape);
    renderParticles.push_back(&rectangle2Particle);

    rect2->points.push_back(Utils::rotatePoint(rect2->ul, rect2->rotation) + rect2->position);
    rect2->points.push_back(Utils::rotatePoint(rect2->ur, rect2->rotation) + rect2->position);
    rect2->points.push_back(Utils::rotatePoint(rect2->lr, rect2->rotation) + rect2->position);
    rect2->points.push_back(Utils::rotatePoint(rect2->ll, rect2->rotation) + rect2->position);

    rect2->addForce(PhysVector(-10000, 0));
    pWorld.addParticle(rect2);

    
    

    
    
    
    PhysVector temp(0, 0);

    
    
    /////////////////////////////////////////////////////////////////////
    

    sf::Clock clock;
    sf::Time timeSinceLast = sf::Time::Zero;

    while (1) {

        timeSinceLast += clock.restart();

        if (timeSinceLast > TimePerFrame) {

            timeSinceLast -= TimePerFrame;


            pWorld.update(TimePerFrame.asMilliseconds() / 1000.0f);

            /*
            rect1->points.at(0) = (Utils::rotatePoint(rect1->ul, rect1->rotation) + rect1->position);
            rect1->points.at(1) = (Utils::rotatePoint(rect1->ur, rect1->rotation) + rect1->position);
            rect1->points.at(2) = (Utils::rotatePoint(rect1->lr, rect1->rotation) + rect1->position);
            rect1->points.at(3) = (Utils::rotatePoint(rect1->ll, rect1->rotation) + rect1->position);

            rect2->points.at(0) = (Utils::rotatePoint(rect2->ul, rect2->rotation) + rect2->position);
            rect2->points.at(1) = (Utils::rotatePoint(rect2->ur, rect2->rotation) + rect2->position);
            rect2->points.at(2) = (Utils::rotatePoint(rect2->lr, rect2->rotation) + rect2->position);
            rect2->points.at(3) = (Utils::rotatePoint(rect2->ll, rect2->rotation) + rect2->position);

            rect3->points.at(0) = (Utils::rotatePoint(rect3->ul, rect3->rotation) + rect3->position);
            rect3->points.at(1) = (Utils::rotatePoint(rect3->ur, rect3->rotation) + rect3->position);
            rect3->points.at(2) = (Utils::rotatePoint(rect3->lr, rect3->rotation) + rect3->position);
            rect3->points.at(3) = (Utils::rotatePoint(rect3->ll, rect3->rotation) + rect3->position);
            */

            //PhysVector renderPoint1 = circle1.toRenderPoint();
            //circle1Shape.setPosition(renderPoint1.x, renderPoint1.y);
            //PhysVector renderPoint2 = circle2.toRenderPoint();
            //circle2Shape.setPosition(renderPoint2.x, renderPoint2.y);
            //PhysVector renderPoint3 = rect1.toRenderPoint();
            //rect1Shape.setPosition(renderPoint3.x, renderPoint3.y);
            //PhysVector renderPoint4 = rect2.toRenderPoint();
            //rect2Shape.setPosition(renderPoint4.x, renderPoint4.y);
            //PhysVector renderPoint5 = rect3.toRenderPoint();
            //rect3Shape.setPosition(renderPoint5.x, renderPoint5.y);
            //PhysVector renderPoint6 = circle3.toRenderPoint();
            //circle3Shape.setPosition(renderPoint6.x, renderPoint6.y);
            
            //PhysVector renderPoint2 = bullet2.toRenderPoint();
            //bullet2.particleShape.setPosition(renderPoint2.x, renderPoint2.y);

 

            window.pollEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();

            window.clear();

            //shurikenPos = Utils::p6ToSFMLPoint(bullet.position);
            //shurikenSprite.setPosition(shurikenPos.x, shurikenPos.y);
            
            //shurikenSprite.setRotation(bullet.rotation * (180)/acos(-1.0));

            //float rad_Angle1 = atan2f(bullet2.position.y - bullet.position.y, bullet2.position.x - bullet.position.x);
            
            //float deg = rad_Angle1 * (180 / PI);

            

            
                //window.draw(shurikenSprite);
            for (std::list<RenderParticle*>::iterator i = renderParticles.begin(); i != renderParticles.end(); i++)
            {
                (*i)->draw(&window);
            }
                //window.draw(bullet.particleShape);
                //window.draw(bullet2.particleShape);
                
            
                

            window.display();

            //cout << bullet.velocity.x << ", " << bullet.velocity.y << endl;


            
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