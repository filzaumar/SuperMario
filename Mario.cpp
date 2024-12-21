#include "Mario.h"
#include "Resources.h"

const float movementSpeed = 3.0f; //for camera basically to see tile map

void Mario::Begin()
{
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
        position.x += move * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        position.x -= move * deltaTime;
    }
   /* 
   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        position.y -= move * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        position.y += move * deltaTime;
    }
    */
}

void Mario::Draw(Renderer& renderer)
{
    renderer.Draw(Resources::textures["mario.png"], position, sf::Vector2f(1.0f, 1.5625f));
}
