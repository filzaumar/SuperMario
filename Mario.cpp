#include "Mario.h"
#include "Resources.h"
#include"Physics.h"
#include <box2d/b2_body.h>
#include<box2d/b2_polygon_shape.h>
#include<box2d/b2_fixture.h>

#define M_PI 3.142f

const float movementSpeed = 3.0f; //for camera basically to see tile map

void Mario::Begin()
{
    //Dynamic body physics
    b2BodyDef bodyDef{};
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(position.x, position.y);
    body = Physics::world.CreateBody(&bodyDef);
    b2PolygonShape shape{};
    shape.SetAsBox(0.5f, 0.78125f);
    b2FixtureDef fixtureDef{};
    fixtureDef.shape = &shape;
    fixtureDef.friction = 0.3f;
    fixtureDef.density = 1.0f;
    body->CreateFixture(&fixtureDef);
}

void Mario::Update(float deltaTime)
{
	float move = movementSpeed;


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
        move *= 2;
    }
    /*
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        position.x += move * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        position.x -= move * deltaTime;
    }
    
   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        position.y -= move * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        position.y += move * deltaTime;
    }
    */
    position = sf::Vector2f(body->GetPosition().x, body->GetPosition().y);
    angle = body->GetAngle() * 180.f/M_PI;
}

void Mario::Draw(Renderer& renderer)
{
    renderer.Draw(Resources::textures["mario.png"], position, sf::Vector2f(1.0f, 1.5625f), angle);
}
