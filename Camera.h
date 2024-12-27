#pragma once
#include <SFML/Graphics.hpp>

class Camera
{
    sf::Vector2f viewSize{};
public:
    Camera(float zoomLevel = 1.f); // Constructor with a default zoom level
    sf::View GetView(sf::Vector2u windowSize);
    sf::Vector2f GetViewSize();
    sf::View GetUIView();
  
    float zoomLevel; // Zoom level of the camera
    sf::Vector2f position;
};
