#include "Game.h"
#include "Resources.h"
#include<filesystem>
#include<iostream>


void Begin()
{
    // Load the texture
    for (auto& file : std::filesystem::directory_iterator("./resources/textures/"))
    {
        if (file.is_regular_file() && file.path().extension() == ".png" || file.path().extension()==".jpg")
        {
            Resources::textures[file.path().filename().string()].loadFromFile(file.path().string());
        }

    }
   
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
    renderer.Draw(Resources::textures["mario.png"], position, size);
    // Draw the texture at position (200, 200) and scale it to its original size
  //  renderer.Draw(texture, sf::Vector2f(200.f, 200.f), sf::Vector2f(texture.getSize().x, texture.getSize().y));
}