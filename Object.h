#pragma once
#include"Renderer.h"
#include"Animation.h"
#include"Resources.h"
#include"Physics.h"

class Object
{
private:
	
public:
	sf::Vector2f position{};
	float angle{};

	virtual void Begin() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render(Renderer& renderer) = 0;

	virtual ~Object() = default;
};

