#pragma once

#include <vector>
#include <glm/vec2.hpp>

#include "drawable.h"

namespace Drawables
{

    struct Triangle : public Drawable
    {
        Triangle(); // equilateral
        Triangle(float width); // equilateral
        Triangle(float width, float height);
        Triangle(float xpos, float ypos, float width); //equilateral
        Triangle(float xpos, float ypos, float width, float height);
        Triangle(float xpos, float ypos, float zpos, float width, float height);

        float width;
        float height;
        unsigned int texture;

        void draw(const Shader& shader) const;
        void setXPosition(float x);
        void setYPosition(float y);
        void setZPosition(float z);
        void setPosition(float x, float y, float z = 0.0f);
        void setPosition(glm::vec3 pos);
        void setPosition(glm::vec2 pos);
        void setSize(float w, float h);
        void setWidth(float w);
        void setHeight(float h);
        float getHeightOffset() const;

        float bottom() const { return position.y-height/2.0;}
        float top() const { return position.y+height/2.0;}
        float left() const { return position.x-width/2.0;}
        float right() const { return position.x+width/2.0;}
    };

} // end namespace Drawables
