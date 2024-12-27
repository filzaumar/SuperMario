#include "Camera.h"

Camera::Camera(float zoomLevel) : zoomLevel(zoomLevel) {}

sf::View Camera::GetView(sf::Vector2u windowSize)
{
	float aspect = (float)windowSize.x / (float)windowSize.y;

	if (aspect < 1.0f)
	{
		viewSize = sf::Vector2f(zoomLevel, zoomLevel / aspect);
	}
	else
	{
		viewSize = sf::Vector2f(zoomLevel * aspect, zoomLevel);
	}


	return sf::View(position, viewSize);
}

sf::Vector2f Camera::GetViewSize()
{
	return viewSize;
}



sf::View Camera::GetUIView()
{
	//float aspect = View.x / .y;
	return sf::View();
}
