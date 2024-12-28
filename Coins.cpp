#include "Coins.h"
#include "box2d/b2_shape.h"
#include"box2d/box2d.h"

Coins::Coins(const sf::Vector2f& position)
{
	this->position = position;
}

void Coins::Begin()
{
	animation = Animation({ AnimFrame( 0.2f, Resources::textures["c5.png"]),
		AnimFrame(0.2f, Resources::textures["c4.png"]) ,
		AnimFrame(0.2f, Resources::textures["c3.png"]) ,
		AnimFrame(0.2f, Resources::textures["c2.png"]) ,
		AnimFrame(0.2f, Resources::textures["c1.png"]) }, 1.f);

    // Coin physics body
    b2BodyDef bodyDef{};
    bodyDef.position.Set(position.x, position.y);
    bodyDef.type = b2_staticBody;
    body = Physics::world.CreateBody(&bodyDef);
	  
}

void Coins::Update(float deltaTime) // Update animation frames for movement of enemy
{
	animation.Update(deltaTime);
    
}

void Coins::Render(Renderer& renderer) // Render enemy
{
	renderer.Draw(animation.GetTexture(), position, sf::Vector2f(1.f, 1.f));
}
