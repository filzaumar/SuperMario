#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Graphics.hpp>

class Renderer
{
private:
    sf::Sprite sprite;
public:
    explicit Renderer(sf::RenderTarget& target);
    void Draw(const sf::Texture& texture, const sf::Vector2f& position, const sf::Vector2f& size, float angle=0.0f);
    void DrawText(const sf::Text& text);
    sf::RenderTarget& target;
  
};

#endif
