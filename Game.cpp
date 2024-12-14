#include "Game.h"


sf::Texture texture;

void Begin()
{
    // Load the texture
    if (!texture.loadFromFile("brick.png"))
    {
        std::cerr << "Failed to load texture." << std::endl;
        exit(-1); // Exit the program if texture loading fails
    }
    std::cout << "Loaded texture. Size: " << texture.getSize().x << " x " << texture.getSize().y << std::endl;
}

void Update(float deltaTime)
{
    // Placeholder for updating game logic
}

void Render(Renderer& renderer)
{
    // Set position to (300, 200)
    sf::Vector2f position(300.f, 200.f);

    // Scale the texture to 200x200 pixels (larger than its original size)
    sf::Vector2f size(16.f, 16.f);

    // Draw the texture with the new position and size
    renderer.Draw(texture, position, size);
    // Draw the texture at position (200, 200) and scale it to its original size
  //  renderer.Draw(texture, sf::Vector2f(200.f, 200.f), sf::Vector2f(texture.getSize().x, texture.getSize().y));
}