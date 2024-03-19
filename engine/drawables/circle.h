#pragma once

#include "drawable.h"

namespace Drawables
{

struct Circle : public Drawable
{
    Circle(float xPos, float yPos, float radius, float percentDrawn=1.0, unsigned int smoothness = 100);

    float radius;

    void draw() const;
    void draw(const Shader& shader) const;

    void setRadius(float rad);
    void setXPosition(float xPos);
    void setPosition(float xPos, float yPos);
    void setPosition(glm::vec2 pos);
    void setPosition(glm::vec3 pos);
    unsigned int smoothness;
    float percentDrawn;

    float bottom() const { return position.y - radius/2.0; }
    float top() const { return position.y + radius/2.0; }
    float left() const { return position.x - radius/2.0; }
    float right() const { return position.x + radius/2.0; }
};



} // end namespace Drawables
