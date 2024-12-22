#pragma once
#include<SFML/Graphics.hpp>
#include<box2d/b2_body.h>
#include"Renderer.h"
#include"Physics.h"

class Mario: public ContactListener
{
private:
	b2Body* body{};
	size_t isGrounded = 0;
	bool isFacingLeft = false;
public:
	void Begin();
	void Update(float deltaTime);
	void Draw(Renderer&);
	sf::Vector2f position{};
	float angle{};

	void OnBeginContact()override;
	void OnEndContact()override;
};

