#pragma once
#include"Renderer.h"
#include"Animation.h"
#include"Resources.h"
#include"Physics.h"

class Object
{
private:
	
public:
	virtual void Begin(){}
	virtual void Update(float deltaTime){}
	virtual void Render(Renderer& renderer){}


	virtual ~Object() = default;
	sf::Vector2f position{};
	float angle{};
};

