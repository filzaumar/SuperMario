#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include"Renderer.h"
#include "Camera.h"
#include "Resources.h"
#include "Map.h"
#include "Mario.h"
#include "Animation.h"

#include "Physics.h"
#include<filesystem>
#include<iostream>

extern Camera camera;
extern sf::Font font;
extern sf::Text coinText;
extern sf::Text gameOverText;

void Begin();
void Update(float deltaTime);
void Render(Renderer& renderer);
void RenderUI(Renderer& renderer);


