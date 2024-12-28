#include "Camera.h"

Camera::Camera(float zoomLevel) : zoomLevel(zoomLevel) {}

// based on the window size, getting the current view of the camera 
sf::View Camera::GetView(sf::Vector2u windowSize)
{
    // aspect ratio of the window calculated  
    float aspect = (float)windowSize.x / (float)windowSize.y;
    // According to current aspect ratio, adjust the view size to maintain the aspect ratio
    if (aspect < 1.0f) 
    {
        viewSize = sf::Vector2f(zoomLevel, zoomLevel / aspect);
    }
    else
    {
        viewSize = sf::Vector2f(zoomLevel * aspect, zoomLevel);
    }

    // Return the view with the current position and calculated size
    return sf::View(position, viewSize);
}

// Get the current size of the view
sf::Vector2f Camera::GetViewSize()
{
    return viewSize;
}

// Get the UI view, has a fixed size for consistent UI scaling ( text position and size rendering made easier )
sf::View Camera::GetUIView()
{
    // Calculate the aspect ratio of the current view size
    float aspect = viewSize.x / viewSize.y;

    // Adjust the view size to have a fixed width (100) while maintaining the aspect ratio
    viewSize = sf::Vector2f(100.f, 100.f / aspect);

    // Return the UI view with the adjusted size and a default position
    return sf::View(sf::Vector2f(), viewSize);
}
