#pragma once

#include <vector>
#include <glm/vec2.hpp>

#include "drawable.h"
#include "input/mouse.h"

namespace Drawables
{

    struct Rectangle : public Drawable
    {
        Rectangle();
        Rectangle(float width, float height);
        Rectangle(float width, float height, glm::vec4 color);
        Rectangle(float xpos, float ypos, float width, float height);
        Rectangle(float xpos, float ypos, float zpos, float width, float height);
        Rectangle(const Framebuffer* fb);

        float width;
        float height;
        unsigned int texture;
        float lineWidth;
        std::string textureName;


        void draw() const;
        void draw(const Shader& shader) const;
        Rectangle& setFill(bool fill);
        void setXPosition(float x);
        void setYPosition(float y);
        void setZPosition(float z);
        void setPosition(float x, float y);
        void setPosition(float x, float y, float z);
        void setPosition(glm::vec3 pos);
        void setPosition(glm::vec2 pos);
        void setLineWidth(float lw);
        void setSize(float w, float h);
        void setWidth(float w);
        void setHeight(float h);
        void bindTexture(std::string textureFile);
        void setTexture(unsigned int tex) { texture = tex; }

        float bottom() const { return position.y-height/2.0;}
        float top() const { return position.y+height/2.0;}
        float left() const { return position.x-width/2.0;}
        float right() const { return position.x+width/2.0;}

        bool wasClicked(input::Mouse::Event e) const
        { 
            return e.xpos >= left() && e.xpos <= right() &&
                   e.ypos >= bottom() && e.ypos <= top();
        }

    };


    enum
    {
        NO_FILL = 0,
        FILL
    };

    template<typename T>
    Rectangle& getBorderAround(T drawable, glm::vec4 color, bool fill = false)
    {
        static Drawables::Rectangle border;
        
        border.setFill(fill);
        border.setLineWidth(2);
        border.setColor(color);
        border.setSize(drawable.width+3.0*3, drawable.height+3.0*3);
        border.setPosition(drawable.position);

        return border;
    }

} // end namespace Drawables
