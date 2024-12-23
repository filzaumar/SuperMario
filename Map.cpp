#include "Map.h"
#include"Physics.h"
#include"Coins.h"
#include<SFML/Graphics.hpp>
#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include "../../../../../../../vcpkg/installed/x64-windows/include/box2d/b2_math.h"

Map::Map(float cellSize): cellSize(cellSize) , grid()
{
}

void Map::CreateCheckerBoard(size_t width, size_t height)
{
	grid = std::vector(width, std::vector(height,0));
	bool last=0;

	for (auto& column : grid)
	{
		for (auto& cell:column )
		{
			cell = !last;
			last = cell;
		}
		if (width%2 == 0)
		{
			last = !last;
		}
	}
}

void Map::Draw(Renderer& renderer)
{
	int x = 0;
	for (const auto& column : grid)
	{
		int y = 0;
		for (const auto& cell : column)
		{
			if (cell)
			{
				renderer.Draw(Resources::textures["brick.png"],
					sf::Vector2f(cellSize * x + cellSize / 2.0f,
						cellSize * y + cellSize / 2.0f),
					sf::Vector2f(cellSize, cellSize));
			}
			y++;
		}
		x++;
	}
}

/*sf::Vector2f Map::InitFromImage(const sf::Image& image, std::vector<Object*>& objects)
{
	objects.clear();
	grid.clear();
	grid = std::vector(image.getSize().x, std::vector(image.getSize().y,0));

	sf::Vector2f marioPosition;

	sf::Color color = image.getPixel( x,y);

	for (size_t x = 0; x < grid.size(); x++)
	{
		for (size_t y = 0; y < grid[x].size() ; y++)
		{
			std::cout << "Processing pixel at (" << x << ", " << y << ") with color: "
				<< (int)color.r << ", " << (int)color.g << ", " << (int)color.b << std::endl;

			sf::Color color = image.getPixel(x, y);
			if (color == sf::Color::Black)
			{
				grid[x][y] = 1;
				//Static body physics
				b2BodyDef bodyDef{};
				bodyDef.position.Set(cellSize * x + cellSize / 2.0f,
					cellSize * y + cellSize / 2.0f);
				b2Body* body = Physics::world.CreateBody(&bodyDef);
				b2PolygonShape shape{};
				shape.SetAsBox(cellSize / 2.f, cellSize / 2.f);
				body->CreateFixture(&shape, 0.0f);
			}
			//else if (color == sf::Color::Red)
			//{
		 	//marioPosition = sf::Vector2f(cellSize * x + cellSize / 2.0f,
			//		cellSize * y + cellSize / 2.0f);
			//}
			if (color.r > 200 && color.g < 50 && color.b < 50) {
				marioPosition = sf::Vector2f(cellSize * x + cellSize / 2.0f,
					cellSize * y + cellSize / 2.0f);
			}

			else if (color == sf::Color::Yellow)
			{
				Object* coin = new Coins();
				coin->position = sf::Vector2f(cellSize * x + cellSize / 2.0f,
					cellSize * y + cellSize / 2.0f);
				objects.push_back(coin);
			}

		}
		std::cout << "Grid size: " << grid.size() << " x " << grid[0].size() << std::endl;
	}
	*/
#include <cmath> // For std::abs()

	// Function to check if two colors are close enough within a tolerance range
bool isColorCloseTo(const sf::Color& color, const sf::Color& targetColor, int tolerance = 10)
{
	return (std::abs(color.r - targetColor.r) <= tolerance) &&
		(std::abs(color.g - targetColor.g) <= tolerance) &&
		(std::abs(color.b - targetColor.b) <= tolerance);
}

// Example usage inside your Map initialization method:
sf::Vector2f Map::InitFromImage(const sf::Image& image, std::vector<Object*>& objects) {
	objects.clear();
	grid.clear();

	grid = std::vector(image.getSize().x, std::vector(image.getSize().y, 0));
	sf::Vector2f marioPosition;

	for (size_t x = 0; x < grid.size(); x++) {
		for (size_t y = 0; y < grid[x].size(); y++) {
			sf::Color color = image.getPixel(x, y);

			std::cout << "Processing pixel at (" << x << ", " << y << ") with color: "
				<< (int)color.r << ", " << (int)color.g << ", " << (int)color.b << std::endl;

			if (color == sf::Color::Black) {
				grid[x][y] = 1;
				// Static body physics for blocks
				b2BodyDef bodyDef{};
				bodyDef.position.Set(cellSize * x + cellSize / 2.0f, cellSize * y + cellSize / 2.0f);
				b2Body* body = Physics::world.CreateBody(&bodyDef);
				b2PolygonShape shape{};
				shape.SetAsBox(cellSize / 2.f, cellSize / 2.f);
				body->CreateFixture(&shape, 0.0f);
			}
			else if (isColorCloseTo(color, sf::Color::Red)) {
				marioPosition = sf::Vector2f(cellSize * x + cellSize / 2.0f, cellSize * y + cellSize / 2.0f);
			}
			else if (isColorCloseTo(color, sf::Color::Yellow)) {
				Object* coin = new Coins();
				coin->position = sf::Vector2f(cellSize * x + cellSize / 2.0f, cellSize * y + cellSize / 2.0f);
				objects.push_back(coin);
				std::cout << "Coin created at position (" << coin->position.x << ", " << coin->position.y << ")" << std::endl;  // Debug message
			}
			else if (isColorCloseTo(color, sf::Color(250, 0, 0))) {
				// Handle color close to Red (250, 0, 0)
				std::cout << "Recognized color close to red at (" << x << ", " << y << ")" << std::endl;
			}
			else if (color == sf::Color::White) {
				// Empty space
			}
			else {
				std::cerr << "Unrecognized color at (" << x << ", " << y << "): "
					<< (int)color.r << ", " << (int)color.g << ", " << (int)color.b << std::endl;
			}
		}
	}
	return marioPosition;
}

	

// Debugging output
	

	//if (marioPosition == sf::Vector2f(0.0f, 0.0f)) 
		//std::cerr << "Warning: No spawn point found in map.png! Defaulting to (0, 0)." << std::endl;
	
//	else 
	//	std::cout << "Spawn point found at (" << marioPosition.x << ", " << marioPosition.y << ")" << std::endl;
	//}

