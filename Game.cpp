#include "Game.h"
#include "Resources.h"
#include "Map.h"

#include<filesystem>
#include<iostream>

Map map(16.0f);
// Create the camera with a zoom level
Camera camera(250.f);
const float movementSpeed = 180.0f; //for camera basically to see tile map


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

    sf::Image image;
    image.loadFromFile("resources/image/map.png");
    map.InitFromImage(image);

    camera.position= sf::Vector2f(160.0f, 160.0f);
   
   
}

void Update(float deltaTime)
{
    float move = movementSpeed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
        move*=2;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        camera.position.x += move * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        camera.position.x -= move * deltaTime;
    }
}

void Render(Renderer& renderer)
{
    map.Draw(renderer);
    /*
    // Set position to (300, 200)
    sf::Vector2f position;

    // Scale the texture to 200x200 pixels (larger than its original size)
    sf::Vector2f size(16.f, 16.f);

    // Draw the texture with the new position and size
    renderer.Draw(Resources::textures["mario.png"], position, size);
    */
}