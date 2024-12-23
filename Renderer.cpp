#include "Renderer.h"
#include <iostream>

// Constructor
Renderer::Renderer(sf::RenderTarget& target) : target(target) {}

// Draw Method
void Renderer::Draw(const sf::Texture& texture, const sf::Vector2f& position, const sf::Vector2f& size, float angle)
{
    sprite.setTexture(texture, true);

    // Set origin
    sprite.setOrigin((sf::Vector2f)texture.getSize() / 2.0f);

    // Set position and scale based on arguments
    sprite.setPosition(position);
    sprite.setRotation(angle);
    sprite.setScale(size.x / texture.getSize().x, size.y / texture.getSize().y);
    
    // Draw the sprite on the target
    target.draw(sprite);
}

