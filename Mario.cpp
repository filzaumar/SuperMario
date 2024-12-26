#pragma once
#include "Mario.h"
#include"Enemy.h"
#include "Resources.h"
#include"Physics.h"
#include "Map.h"
#include"Animation.h"
#include"Renderer.h"
#include "Camera.h"
#include"Game.h"
#include "Object.h"
#include "Coins.h"
#include <box2d/b2_body.h>
#include<box2d/b2_polygon_shape.h>
#include<box2d/b2_circle_shape.h>
#include<box2d/b2_fixture.h>
#include <box2d/b2_math.h> 
#include<iostream>

#define M_PI 3.142f

const float movementSpeed = 5.0f; //for camera basically to see tile map
const float jumpVelocity = 8.0f; //jump velocity


bool Mario::isCollidingWithCoin(Coins& coin)
{
   float distance = std::sqrt(std::pow(position.x - coin.body->GetPosition().x, 2) +
      std::pow(position.y - coin.body->GetPosition().y, 2));
  
      return distance < 0.5f;  // CHECKK !! (radius of Mario + coin)
}

bool Mario::isCollidingWithEnemy(Enemy& enemy)
{
    float distance = std::sqrt(std::pow(position.x - enemy.body->GetPosition().x, 2) +
        std::pow(position.y - enemy.body->GetPosition().y, 2));

    return distance < 1.057f;  // CHECKK !! (radius of Mario + coin)
}
void Mario::Begin()
 {
    //Running animation for mario
    runAnimation = Animation(
        { AnimFrame(0.1f, Resources::textures["run3.png"]),
          AnimFrame(0.1f, Resources::textures["run2.png"]),
          AnimFrame(0.1f, Resources::textures["run1.png"])
        } , 0.3f); 


    //Dynamic body physics
    b2BodyDef bodyDef{};
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(position.x, position.y);
    bodyDef.fixedRotation=true;
    body = Physics::world.CreateBody(&bodyDef);

    b2PolygonShape shape{};
    shape.SetAsBox(0.4f, 0.43125f);
    b2FixtureDef fixtureDef{};
    fixtureDef.shape = &shape;
    fixtureDef.friction = 0.0f;
    fixtureDef.density = 1.0f;
    body->CreateFixture(&fixtureDef);

    b2CircleShape circleShape{};
    circleShape.m_radius=0.3f;
    circleShape.m_p.Set(0.0f, -0.5f);
    fixtureDef.shape = &circleShape;
    body->CreateFixture(&fixtureDef); 

    circleShape.m_p.Set(0.0f, 0.35f); //neeche wala fixture
    body->CreateFixture(&fixtureDef);

    shape.SetAsBox(0.4f, 0.2f, b2Vec2(0.0f, 1.0f), 0.0f);
    fixtureDef.userData.pointer = (uintptr_t)this;
    fixtureDef.isSensor=true;
    body->CreateFixture(&fixtureDef);
    

    // Load font
     
    if (!font.loadFromFile("resources/font/Arialn.ttf"))
    {
        std::cerr << "Failed to load font" << std::endl;
    }
    else {
        std::cout << "Font loaded successfully!" << std::endl;
    }
    // Set up the text object for displaying the coin count
    coinText.setFont(font);
    coinText.setCharacterSize(5.f); // Font size
    coinText.setFillColor(sf::Color::Cyan); // Text color
    coinText.setPosition(3.5f, 14.5f); // Position on screen (top-left corner)
}

void Mario::Update(float deltaTime, std::vector<Object*>& objects)
{
    if (isDead) {
        body->SetLinearVelocity(b2Vec2(0, 0));  // Stop movement
        return;
    }
    float move = movementSpeed;
    runAnimation.Update(deltaTime);
   
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        move *= 2;

    b2Vec2 velocity = body->GetLinearVelocity();
    velocity.x = 0.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        velocity.x += move;
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        velocity.x -= move;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up ) && isGrounded)
        velocity.y = -jumpVelocity;

    body->SetLinearVelocity(velocity);
   
    textureToDraw = runAnimation.GetTexture();
    if (velocity.x < 0.0f)
        isFacingLeft = true;
    else if (velocity.x > 0.0f)
        isFacingLeft = false;
    else
        textureToDraw = Resources::textures["mario.png"];
    if (!isGrounded)
        textureToDraw = Resources::textures["jump.png"];


    position = sf::Vector2f(body->GetPosition().x, body->GetPosition().y);
    angle = body->GetAngle() * 180.f / M_PI;


    //Coin collection

        for (auto& obj : objects) {
       // Check if the object is a coin
        Coins* coin = dynamic_cast<Coins*>(obj);
           if (coin && !coin->collected && isCollidingWithCoin(*coin)) {
               coin->Collect();  
               coinCount++;      // Increase coin counter
               std::cout << "COLLISIONNNNN: Coin collected! Total: " << coinCount << std::endl;
         }
       }
       
        
    // Enemy collision check
        for (auto& obj : objects) {
            Enemy* enemy = dynamic_cast<Enemy*>(obj);
            if (enemy && !enemy->isDead && isCollidingWithEnemy(*enemy)) {
                // Get positions to check if Mario is above enemy
                float marioBottom = position.y + 0.43125f;  // Using your box dimensions
                float enemyTop = enemy->body->GetPosition().y - 0.5f;  // Using enemy box height

                // If Mario is above the enemy
                if (marioBottom < enemyTop) {
                   // enemy->Die();  // Kill enemy
                    // Add jump boost
                    b2Vec2 vel = body->GetLinearVelocity();
                    vel.y = -jumpVelocity / 2;  // Small bounce
                    body->SetLinearVelocity(vel);
                }
                else {
                    Die();  // Kill Mario
                }
                std::cout << "Collision with enemy!" << std::endl;
            }
        }

    
        // Remove collected coins
        objects.erase(
            std::remove_if(
                objects.begin(),
                objects.end(),
                [](Object* obj) {
                    Coins* coin = dynamic_cast<Coins*>(obj);
                    if (coin && coin->collected) {
                     
                        delete coin; // Free memory
                        return true; // Remove from objects
                    }
                    return false;
                }),
            objects.end());
      
        coinText.setString("Coins: " + std::to_string(coinCount));
}


void Mario::Draw(Renderer& renderer)
{
    renderer.Draw(textureToDraw
        //Resources::textures["mario.png"]
        , position, sf::Vector2f(isFacingLeft ? -1.0f : 1.0f, 1.5625f), angle);

    // Draw the coin counter text
    renderer.DrawText(coinText);
}
// Add the Die function
void Mario::Die()
{
    if (!isDead) {
        isDead = true;
        std::cout << "Mario died!" << std::endl;
        // Optional: Play death animation
        textureToDraw = Resources::textures["dead.png"];  // Or use a death texture if you have one
        body->SetLinearVelocity(b2Vec2(0, +5));  // Small jump on death
    }
}


void Mario::OnBeginContact()
{
    isGrounded++;  // changed instead of bool so that when we enter tile, then enter next tile, we can still jump as grounded =1 instead of false
    std::cout << "OBC" << std::endl;
}

void Mario::OnEndContact()
{
    if (isGrounded>0)
    isGrounded--;
}
