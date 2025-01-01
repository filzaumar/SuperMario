#pragma once

#include<SFML/Graphics.hpp>
#include<box2d/b2_polygon_shape.h>
#include<box2d/b2_circle_shape.h>
#include<box2d/b2_fixture.h>
#include<box2d/b2_body.h>
#include <box2d/b2_math.h>
#include<iostream>

#include"Object.h"
#include"Renderer.h"
#include"Physics.h"
#include "Animation.h"
#include"Map.h"
#include"Coins.h"
#include"Enemy.h"
#include "Resources.h"
#include "Camera.h"
#include"Game.h"


class Mario: public ContactListener
{
private:
	b2Body* body{};
	Animation runAnimation;
	sf::Texture textureToDraw{};
	bool isFacingLeft = false;
	bool isCollidingWithCoin(Coins& coin);
	bool isCollidingWithEnemy(Enemy& enemy);
	size_t isGrounded = 0;	
	int coinCount = 0;

public:
	sf::Vector2f position{};
	bool isDead = false;
	float angle{};
	std::string currentTextureName;

	void Begin();
	void Update(float deltaTime, std::vector<Object*>& objects);
	void Draw(Renderer&);
	void Die();
	int getCoinCount();
		
	void OnBeginContact()override;
	void OnEndContact()override;
};

