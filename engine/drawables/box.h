#pragma once

#include <vector>

#include "drawable.h"

namespace Drawables
{
    struct Box : public Drawable
    {
        Box(float width, float height, float depth);
        Box(float xpos, float ypos, float zpos, float width, float height, float depth);
           
        glm::vec3 position;
        float width;
        float height;
        float depth;
        
        void draw(const Shader& shader) const;
    };

} // end namespace Drawables
