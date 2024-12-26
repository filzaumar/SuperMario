#include "Enemy.h"
#include "box2d/b2_shape.h"
#include"box2d/box2d.h"

Enemy::Enemy(const sf::Vector2f& position)
{
}

void Enemy::Begin()
{
    animation = Animation({ AnimFrame(1.f, Resources::textures["enemy.png"])
        //AnimFrame(0.2f, Resources::textures["c4.png"]) ,
        //AnimFrame(0.2f, Resources::textures["c3.png"]) ) 
        }, 1.f);

    // Coin physics body
    b2BodyDef bodyDef;
    bodyDef.position.Set(position.x, position.y);
    bodyDef.type = b2_dynamicBody;
    bodyDef.fixedRotation = true;
    body = Physics::world.CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(0.5f, 0.5f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.0f;
    body->CreateFixture(&fixtureDef);


    // Add a sensor on top of the enemy to detect player hits
    //b2PolygonShape topSensor;
    //topSensor.SetAsBox(0.4f, 0.1f, b2Vec2(0.0f, -0.5f), 0);  // Thin box on top

    //b2FixtureDef sensorDef;
    //sensorDef.shape = &topSensor;
    //sensorDef.isSensor = true;  // Make it a sensor so it only detects contact
    //topSensorFixture = body->CreateFixture(&sensorDef);
}

void Enemy::Update(float deltaTime)
{
    animation.Update(deltaTime);

    if (isDead) return;

    // Move Goomba
    b2Vec2 velocity = body->GetLinearVelocity();
    velocity.x = direction * moveSpeed;  // Move left or right
    body->SetLinearVelocity(velocity);

  






     // Track time since last direction change
    static float timeSinceLastChange = 0;
    timeSinceLastChange += deltaTime;

    // Check side collisions
    bool hitWall = false;
    for (b2ContactEdge* edge = body->GetContactList(); edge; edge = edge->next) {
        if (!edge->contact->IsTouching()) continue;

        // Get collision normal (direction of impact)
        b2WorldManifold worldManifold;
        edge->contact->GetWorldManifold(&worldManifold);

        // If collision is from side (x > 0.5 means mostly horizontal)
        if (std::abs(worldManifold.normal.x) > 0.5f) {
            hitWall = true;
            break;
        }
    }

    // Change direction if hit wall and enough time passed
    if (hitWall && timeSinceLastChange > 0.5f) {  // Only change every 0.5 seconds
        direction *= -1;
        timeSinceLastChange = 0;  // Reset timer
    }

    // Update render position
    position = sf::Vector2f(body->GetPosition().x, body->GetPosition().y);
}



void Enemy::Render(Renderer& renderer)
{
    if (isDead) return;
    renderer.Draw(animation.GetTexture(), position, sf::Vector2f(1.f, 1.f));
}


void Enemy::OnCollision(void* other)
{
    std::cout << "Collision Detected!" << std::endl;
    // Check if collision is with the top sensor
    for (b2ContactEdge* edge = body->GetContactList(); edge; edge = edge->next) {
        if (edge->contact->GetFixtureA() == topSensorFixture ||
            edge->contact->GetFixtureB() == topSensorFixture) {
         //   Die();
            return;
        }
    }
}
