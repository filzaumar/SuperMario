#pragma once
#include<unordered_map> //more efficiency than ordered map
#include<SFML/Graphics.hpp>

class Resources
{
public:
	static std::unordered_map< std::string, sf::Texture> textures;

};

