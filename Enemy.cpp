#include "Enemy.h"
#include "box2d/b2_shape.h"
#include"box2d/box2d.h"

Enemy::Enemy(const sf::Vector2f& position)
{
}

void Enemy::Begin()
{
    animation = Animation({ AnimFrame(0.3f, Resources::textures["enemy.png"]),
        AnimFrame(0.3f, Resources::textures["enemy2.png"])}
        , 0.6f);

    // Enemy physics body
    b2BodyDef bodyDef;
    bodyDef.position.Set(position.x, position.y);
    bodyDef.type = b2_dynamicBody;
    bodyDef.fixedRotation = true;
    body = Physics::world.CreateBody(&bodyDef);

    b2CircleShape shape;
    shape.m_radius = 0.5f;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.0f;
    body->CreateFixture(&fixtureDef);

}

void Enemy::Update(float deltaTime)
{
    animation.Update(deltaTime);

    // Move Enemy
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

        // Check direction of impact
        b2WorldManifold worldManifold;
        edge->contact->GetWorldManifold(&worldManifold);

        // Check if collision is horizontal
        if (std::abs(worldManifold.normal.x) > 0.5f) {
            hitWall = true;
            break;
        }
    }

    // Change direction if hit a wall and time > 0.5
    if (hitWall && timeSinceLastChange > 0.5f) {  
        direction *= -1;
        timeSinceLastChange = 0; 
    }

    // render position updated
    position = sf::Vector2f(body->GetPosition().x, body->GetPosition().y);
}



void Enemy::Render(Renderer& renderer)
{
    renderer.Draw(animation.GetTexture(), position, sf::Vector2f(1.f, 1.f));
}
