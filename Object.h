#pragma once
#include"Renderer.h"
#include"Animation.h"
#include"Resources.h"

class Object
{
private:

public:
	virtual void Begin(){}
	virtual void Update(float deltaTime){}
	virtual void Render(Renderer& renderer){}

	sf::Vector2f position{};
	float angle{};
};

