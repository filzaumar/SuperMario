#pragma once
#include"Object.h"
#include<SFML/Graphics.hpp>
#include<box2d/b2_body.h>
#include"Renderer.h"
#include"Physics.h"
#include "Animation.h"
#include"Map.h"
#include"Coins.h"
class Mario: public ContactListener, public Object
{
private:
	b2Body* body{};
	size_t isGrounded = 0;
	bool isFacingLeft = false;
	Animation runAnimation;
	sf::Texture textureToDraw{};
	bool isCollidingWithCoin(Coins& coin);


public:
	void Begin();
	void Update(float deltaTime, std::vector<Object*>& objects);
	void Draw(Renderer&);
	sf::Vector2f position{};
	float angle{};
	sf::Text coinText;
	sf::Font font;
	int coinCount = 0;

	void OnBeginContact()override;
	void OnEndContact()override;
};

