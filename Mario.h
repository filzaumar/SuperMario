#pragma once
#include<SFML/Graphics.hpp>
#include"Renderer.h"
class Mario
{
private:
	b2Body* body;
public:
	void Begin();
	void Update(float deltaTime);
	void Draw(Renderer&);
	sf::Vector2f position{};
	float angle{};
};

