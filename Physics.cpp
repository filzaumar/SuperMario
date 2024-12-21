#include "Physics.h"

b2World Physics::world{ b2Vec2(0.0f,9.2f) }; //gravity

void Physics::Init()
{
}

void Physics::Update(float deltaTime)
{
	world.Step(deltaTime, 6, 2); // frame limit 60 so deltaTime is gonna be 1/60
}
