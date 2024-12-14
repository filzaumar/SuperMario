#include "Renderer.h"
#include <iostream>

// Constructor
Renderer::Renderer(sf::RenderTarget& target) : target(target) {}

// Draw Method
void Renderer::Draw(const sf::Texture& texture, const sf::Vector2f& position, const sf::Vector2f& size)
{
    sprite.setTexture(texture);

    // Set origin
    sprite.setOrigin((sf::Vector2f)texture.getSize() / 2.0f);

    // Set position and scale based on arguments
    sprite.setPosition(position);
    sprite.setScale(size.x / texture.getSize().x, size.y / texture.getSize().y);

    // Draw the sprite on the target
    target.draw(sprite);
}

