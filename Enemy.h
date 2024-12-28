#pragma once
#include "Object.h"

class Enemy :
    public Object
{
public:
    Enemy() {};
    Enemy(const sf::Vector2f& position);
    b2Body* body;  // Add a body for physics
    b2Fixture* topSensorFixture;
    bool collected = false;  // A flag to mark if the coin has been collected
    void Collect() { collected = true; std::cout << "COIN COLLECTED" << std::endl; }
    int direction = 1;
    float moveSpeed = 3.0f;
    bool isDead = false;

    void Begin() override;
    void Update(float deltaTime) override;
    void Render(Renderer& renderer) override;
    void OnCollision(void* other);

private:
    Animation animation;
};


























/*
#pragma once
#include "Object.h"
#include "Physics.h"
#include "Resources.h"
#include "Mario.h"
#include <box2d/b2_body.h>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include<box2d/box2d.h>

class Mario;
class Goomba : public Object {
public:

    Goomba(const sf::Vector2f& startPos)
        : position(startPos),
        isDead(false),
        direction(1),
        moveSpeed(1.0f),
        body(nullptr),
        topSensorFixture(nullptr) {
        // Load Goomba texture
        texture = &Resources::textures["goomba.png"];

        // Create Goomba physics body
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(position.x, position.y);
        bodyDef.fixedRotation = true;
        body = Physics::world.CreateBody(&bodyDef);

        // Main body shape
        b2PolygonShape boxShape{};
        boxShape.SetAsBox(0.35f, 0.35f);
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &boxShape;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.0f;
        fixtureDef.userData.pointer = (uintptr_t)this;
        body->CreateFixture(&fixtureDef);

        // Top sensor shape (for Mario bounce detection)
        b2PolygonShape sensorShape;
        sensorShape.SetAsBox(0.35f, 0.1f, b2Vec2(0.0f, 0.4f), 0.0f);
        b2FixtureDef sensorFixtureDef;
        sensorFixtureDef.shape = &sensorShape;
        sensorFixtureDef.isSensor = true;
        sensorFixtureDef.userData.pointer = (uintptr_t)this;
        topSensorFixture = body->CreateFixture(&sensorFixtureDef);
    }

    ~Goomba() {
        if (body) {
            Physics::world.DestroyBody(body);
        }
    }

    void Update(float deltaTime) override {
        if (isDead) return;

        // Move Goomba
        b2Vec2 velocity = body->GetLinearVelocity();
        velocity.x = direction * moveSpeed;
        body->SetLinearVelocity(velocity);

        // Update position for rendering
        position = sf::Vector2f(body->GetPosition().x, body->GetPosition().y);

        // Reverse direction if it hits the edge of a platform
        for (b2ContactEdge* edge = body->GetContactList(); edge; edge = edge->next) {
            if (edge->contact->IsTouching() && !edge->contact->GetFixtureA()->IsSensor() &&
                !edge->contact->GetFixtureB()->IsSensor()) {
                direction *= -1; // Reverse direction
                break;
            }
        }
    }

    void Render(Renderer& renderer) override {
        if (isDead) return;

        renderer.Draw(*texture, position, sf::Vector2f(0.7f, 0.7f));
    }

    void OnBeginContact(void* other) {
        Mario* mario = dynamic_cast<Mario*>(reinterpret_cast<Object*>(other));
        if (mario) {
            // If Mario hits the top sensor, kill Goomba
            for (b2ContactEdge* edge = body->GetContactList(); edge; edge = edge->next) {
                if ((edge->contact->GetFixtureA() == topSensorFixture ||
                    edge->contact->GetFixtureB() == topSensorFixture) &&
                    edge->contact->IsTouching()) {
                    Kill();
                    //      mario->Bounce();  // Make Mario bounce after killing Goomba
                    return;
                }
            }
            // Otherwise, Mario dies
            //mario->Die();
        }
    }

    void Kill() {
        if (!isDead) {
            isDead = true;
            body->SetEnabled(false);  // Disable the body
        }
    }

private:
    sf::Vector2f position;
    sf::Texture* texture;
    b2Body* body;
    b2Fixture* topSensorFixture; // Store the sensor fixture
    bool isDead;
    int direction;  // 1 for right, -1 for left
    float moveSpeed;
};
*/