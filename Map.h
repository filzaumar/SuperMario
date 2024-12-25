#pragma once
#include <vector>
#include <iostream>
#include"Renderer.h"
#include"Resources.h"
#include"Object.h"
#include"Enemy.h"
#include<SFML/Graphics.hpp>
class Map
{
public:
	Map(float cellSize = 32.0f);
	void CreateCheckerBoard(size_t width, size_t height);
	void Draw(Renderer& renderer);
	sf::Vector2f InitFromImage(const sf::Image& image, std::vector<Object*>&objects);

	std::vector<std::vector<int>> grid;
	float cellSize;

};

