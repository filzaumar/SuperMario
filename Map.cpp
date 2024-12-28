#include "Map.h"

Map::Map(float cellSize) : cellSize(cellSize), grid()
{
}

void Map::CreateCheckerBoard(size_t width, size_t height) //Checker board created with alternating 0s and 1s
{
	grid = std::vector(width, std::vector(height, 0));
	bool last = 0;

	for (auto& column : grid)
	{
		for (auto& cell : column)
		{
			cell = !last;
			last = cell;
		}
		if (width % 2 == 0)  // If the width is even, change the pattern after each row
		{
			last = !last;
		}
	}
}
// Method to draw the grid using a renderer
void Map::Draw(Renderer& renderer)
{
	int x = 0; // x-coordinate for grid drawing
    // Loop through each column in the grid
	for (const auto& column : grid)
	{
		int y = 0; // y-coordinate for grid drawing
        // Loop through each cell in the current column
		for (const auto& cell : column)
		{
			if (cell) // If the cell is 1
			{   // Draw the texture for the brick at the calculated position
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

// Function to check if two colors are close enough within a tolerance range
bool isColorCloseTo(const sf::Color& color, const sf::Color& targetColor, int tolerance = 10)
{
	return (std::abs(color.r - targetColor.r) <= tolerance) &&
		(std::abs(color.g - targetColor.g) <= tolerance) &&
		(std::abs(color.b - targetColor.b) <= tolerance);
}
// Method to initialize the map from an image, extracting objects and grid data
sf::Vector2f Map::InitFromImage(const sf::Image& image, std::vector<Object*>& objects) {
	objects.clear();
	grid.clear();

	grid = std::vector(image.getSize().x, std::vector(image.getSize().y, 0));
	sf::Vector2f marioPosition;

	// Loop through each pixel in the image to process the map
	for (size_t x = 0; x < grid.size(); x++) {
		for (size_t y = 0; y < grid[x].size(); y++) {
			sf::Color color = image.getPixel(x, y);

			//std::cout << "Processing pixel at (" << x << ", " << y << ") with color: "
				//<< (int)color.r << ", " << (int)color.g << ", " << (int)color.b << std::endl;

			// Process different colors to set up the map
			if (color == sf::Color::Black) { // black for bricks
				grid[x][y] = 1;
			
				// Static body physics for blocks
				b2BodyDef bodyDef{};
				bodyDef.position.Set(cellSize * x + cellSize / 2.0f, cellSize * y + cellSize / 2.0f);
				b2Body* body = Physics::world.CreateBody(&bodyDef);
				b2PolygonShape shape{};
				shape.SetAsBox(cellSize / 2.f, cellSize / 2.f);
				body->CreateFixture(&shape, 0.0f);
			}
			else if (isColorCloseTo(color, sf::Color::Red)) {  // red for mario's spawn position
				marioPosition = sf::Vector2f(cellSize * x + cellSize / 2.0f, cellSize * y + cellSize / 2.0f);
			}
			else if (isColorCloseTo(color, sf::Color::Yellow)) { // yellow for coins
				Object* coin = new Coins();
				coin->position = sf::Vector2f(cellSize * x + cellSize / 2.0f, cellSize * y + cellSize / 2.0f);
				objects.push_back(coin);
				//std::cout << "Coin created at position (" << coin->position.x << ", " << coin->position.y << ")" << std::endl;  // Debug message
			}
			else if (isColorCloseTo(color, sf::Color(0, 0, 250))) { // blue for enemy
				Object* enemy = new Enemy();
				enemy->position = sf::Vector2f(cellSize * x + cellSize / 2.0f, cellSize * y + cellSize / 2.0f);
				objects.push_back(enemy);
				//std::cout << "Coin created at position (" << enemy->position.x << ", " << enemy->position.y << ")" << std::endl;  // Debug message
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