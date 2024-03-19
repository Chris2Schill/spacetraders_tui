#pragma once

#include <vector>
#include <glm/vec3.hpp>

#include "drawable.h"

namespace Drawables
{

    struct Homeplate : public Drawable
    {
        Homeplate();
        Homeplate(float width, float height);
        Homeplate(float xpos, float ypos, float width, float height);
        Homeplate(float xpos, float ypos, float zpos, float width, float height);

        float width;
        float height;

        void draw(const Shader& shader) const;
        void setFill(bool fill);
        void setXPosition(float x);
        void setYPosition(float y);
        void setZPosition(float z);
        void setPosition(float x, float y, float z = 0.0f);
        void setPosition(glm::vec3 pos);
        void setPosition(glm::vec2 pos);
        void setSize(float w, float h);
        void setWidth(float w);
        void setHeight(float h);

        float bottom() const { return position.y-height/2.0;}
        float top() const { return position.y+height/2.0;}
        float left() const { return position.x-width/2.0;}
        float right() const { return position.x+width/2.0;}
    };

} // end namespace Drawables
