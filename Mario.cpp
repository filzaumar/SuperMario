/* 
#include "Mario.h"
#include "Resources.h"
#include"Physics.h"
#include <box2d/b2_body.h>
#include<box2d/b2_polygon_shape.h>
#include<box2d/b2_fixture.h>
#include<iostream>
#include <box2d/b2_math.h> 

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
    fixtureDef.friction = 0.1f;
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
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        body->ApplyForceToCenter(b2Vec2(move, 0.0f), true);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        body->ApplyForceToCenter(b2Vec2(-move, 0.0f), true);
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        body->ApplyForceToCenter(b2Vec2(0.0f, -move), true);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        body->ApplyForceToCenter(b2Vec2(0.0f, move),true);
    }
    
    position = sf::Vector2f(body->GetPosition().x, body->GetPosition().y);
    angle = body->GetAngle() * 180.f/M_PI;
}

void Mario::Draw(Renderer& renderer)
{
    renderer.Draw(Resources::textures["mario.png"], position, sf::Vector2f(1.0f, 1.5625f), angle);
}
*/

#include "Mario.h"
#include "Resources.h"
#include"Physics.h"
#include <box2d/b2_body.h>
#include<box2d/b2_polygon_shape.h>
#include<box2d/b2_circle_shape.h>
#include<box2d/b2_fixture.h>
#include<iostream>
#include <box2d/b2_math.h> 

#define M_PI 3.142f

const float movementSpeed = 5.0f; //for camera basically to see tile map
const float jumpVelocity = 10.0f; //jump velocity

void Mario::Begin()
{
    //Dynamic body physics
    b2BodyDef bodyDef{};
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(position.x, position.y);
    bodyDef.fixedRotation=true;
    body = Physics::world.CreateBody(&bodyDef);

    b2PolygonShape shape{};
    shape.SetAsBox(0.45f, 0.28125f);
    b2FixtureDef fixtureDef{};
    fixtureDef.shape = &shape;
    fixtureDef.friction = 0.1f;
    fixtureDef.density = 1.0f;
    body->CreateFixture(&fixtureDef);

    b2CircleShape circleShape{};
    circleShape.m_radius=0.3f;
    circleShape.m_p.Set(0.0f, -0.5f);
    fixtureDef.shape = &circleShape;
    body->CreateFixture(&fixtureDef); 

    circleShape.m_p.Set(0.0f, 0.5f); //neeche wala fixture
    fixtureDef.userData.pointer = (uintptr_t)this;
    body->CreateFixture(&fixtureDef);

    //circleShape.m_radius = 0.3f;
    //circleShape.m_p.Set(0.0f, 0.5f);
    //fixtureDef.shape = &circleShape;
    //body->CreateFixture(&fixtureDef);

  //  isGrounded = false;
}

void Mario::Update(float deltaTime)
{
    float move = movementSpeed;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        move *= 2;

    b2Vec2 velocity = body->GetLinearVelocity();
    velocity.x = 0.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        velocity.x += move;
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        velocity.x -= move;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up ) && isGrounded)
        velocity.y = -jumpVelocity;

    body->SetLinearVelocity(velocity);
   

   // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && isGrounded)
     //   body->ApplyLinearImpulseToCenter(b2Vec2(0.0f, -jumpImpulse), true);
       // isGrounded = false;

    position = sf::Vector2f(body->GetPosition().x, body->GetPosition().y);
    angle = body->GetAngle() * 180.f / M_PI;

    //Simple Ground Check (You will need to improve this later)
    //if (body->GetLinearVelocity().y == 0) {
      //  isGrounded = true;
    //}
    //else
      //  isGrounded = false;
}

void Mario::Draw(Renderer& renderer)
{
    renderer.Draw(Resources::textures["mario.png"], position, sf::Vector2f(1.0f, 1.5625f), angle);
}

void Mario::OnBeginContact()
{
    isGrounded = true;
    std::cout << "OBC" << std::endl;
}

void Mario::OnEndContact()
{
    isGrounded = false;
}
