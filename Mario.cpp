#include "Mario.h"

const float movementSpeed = 180.0f; //for camera basically to see tile map

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
}
