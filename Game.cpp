#include "Game.h"
#include "Resources.h"
#include "Map.h"
#include "Mario.h"

#include<filesystem>
#include<iostream>

Map map(16.0f); //map with cell size 
Camera camera(250.f); // Create the camera with a zoom level
Mario mario;




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
    mario.position = map.InitFromImage(image);  
   
}

void Update(float deltaTime)
{
    mario.Update(deltaTime);
    camera.position = mario.position;   
}

void Render(Renderer& renderer)
{
    map.Draw(renderer);
}