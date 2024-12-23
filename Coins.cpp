#include "Coins.h"

void Coins::Begin()
{
	animation = Animation({ AnimFrame( 0.2f, Resources::textures["c5.png"]),
		AnimFrame(0.2f, Resources::textures["c4.png"]) ,
		AnimFrame(0.2f, Resources::textures["c3.png"]) ,
		AnimFrame(0.2f, Resources::textures["c2.png"]) ,
		AnimFrame(0.2f, Resources::textures["c1.png"]) }, 1.f);
}

void Coins::Update(float deltaTime)
{
	animation.Update(deltaTime);
}

void Coins::Render(Renderer& renderer)
{
	renderer.Draw(animation.GetTexture(), position, sf::Vector2f(1.f, 1.f));
}
