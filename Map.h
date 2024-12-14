#pragma once
#include <vector>
#include"Renderer.h"
#include"Resources.h"
#include<SFML/Graphics.hpp>
class Map
{
public:
	Map(float cellSize = 32.0f);
	void CreateCheckerBoard(size_t width, size_t height);
	void Draw(Renderer& renderer);
	void InitFromImage(const sf::Image& image);

	std::vector<std::vector<int>> grid;
	float cellSize;

};

