#pragma once
#include "Object.h"

class Coins :
    public Object
{
public:
    Coins() {};
    Coins(const sf::Vector2f& position);
    b2Body* body;  // Add a body for physics
    bool collected = false;  // A flag to mark if the coin has been collected
    void Collect() { collected = true; std::cout << "COIN COLLECTED" << std::endl; }
  
  
    void Begin() override;
    void Update(float deltaTime) override;
    void Render(Renderer& renderer) override;

private:
    Animation animation;
};


