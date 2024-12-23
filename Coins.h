#pragma once
#include "Object.h"

class Coins :
    public Object
{
    void Begin() override;
    void Update(float deltaTime) override;
    void Render(Renderer& renderer) override;

private:
    Animation animation;
};


