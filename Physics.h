#pragma once
#include <box2d/b2_world.h>
#include <box2d/b2_draw.h>
#include<box2d/b2_world_callbacks.h>
#include<box2d/b2_contact.h>
#include "Renderer.h"

class MyDebugDraw;

class ContactListener {
public:
    virtual void OnBeginContact() = 0;
    virtual void OnEndContact() = 0;
};

class MyGlobalContactListener : public b2ContactListener {
public:
	void BeginContact(b2Contact* contact) override; 
	void EndContact(b2Contact* contact) override;   
};

class Physics
{
public:
	static b2World world; //basically world that shows all physics
	static void Init();
	static void Update(float deltaTime);

	static void DebugDraw(Renderer& renderer);
	static MyDebugDraw* debugDraw;
};

