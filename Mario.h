#pragma once
#include<SFML/Graphics.hpp>
class Mario
{
public:
	void Update(float deltaTime);
	sf::Vector2f position{};
	float angle{};
};

