#pragma once
#include <SFML/Graphics.hpp>
#include<iostream>

struct AnimFrame {
	AnimFrame(float time = 0.0f, sf::Texture texture= sf::Texture() ): time(time), texture(texture) {}
	float time; // time for when animation is playing
	sf::Texture texture;

};
class Animation
{
private:
	float time = 0.0f;
	float length;
	std::vector<AnimFrame> frames;
	
public:
	Animation(std::vector<AnimFrame> frames = {}, float length = 0.0f) :frames(frames), length(length) {}
	sf::Vector2f position;
	sf::Texture GetTexture();
	void Update(float deltaTime);
	
};

