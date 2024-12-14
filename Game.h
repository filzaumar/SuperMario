#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include"Renderer.h"

void Begin();
void Update(float deltaTime);
void Render(  Renderer& renderer);