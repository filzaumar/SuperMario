#pragma once
#include <box2d/b2_world.h>

class Physics
{
public:
	static b2World world; //basically world that shows all physics
	static void Init();
	static void Update(float deltaTime);
};

