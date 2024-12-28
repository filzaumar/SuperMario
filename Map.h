#pragma once
#include<SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <box2d/b2_body.h>
#include <box2d/b2_math.h>
#include <box2d/b2_polygon_shape.h>
#include <cmath> // For std::abs()
#include <vector>
#include <iostream>

#include"Physics.h"
#include"Coins.h"
#include"Renderer.h"
#include"Resources.h"
#include"Object.h"
#include"Enemy.h"

class Map
{
public:
	Map(float cellSize = 32.0f);
	sf::Vector2f InitFromImage(const sf::Image& image, std::vector<Object*>& objects);
	std::vector<std::vector<int>> grid;
	float cellSize;

	void CreateCheckerBoard(size_t width, size_t height);
	void Draw(Renderer& renderer);
	
};

