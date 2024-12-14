#pragma once
#include <SFML/Graphics.hpp>

class Camera
{
public:
    Camera(float zoomLevel = 1.0f); // Constructor with a default zoom level
    sf::View GetView(sf::Vector2u windowSize);
  
    float zoomLevel; // Zoom level of the camera
    sf::Vector2f position;
};
