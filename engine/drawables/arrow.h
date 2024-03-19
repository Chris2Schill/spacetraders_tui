#pragma once

#include <vector>
#include <glm/vec2.hpp>

#include "window.h"
#include "drawable.h"
#include "triangle.h"
#include "rect.h"
#include "colors.h"
#include "logger.h"

namespace Drawables
{

    struct Arrow
    {
        Arrow(Triangle head, Rectangle stem, bool hasTail = 0)
            : Arrow(head, stem, {window::center().x, window::center().y, 0}, hasTail)
        {
        }
        Arrow(Triangle head, Rectangle stem, glm::vec3 position, bool hasTail = 0)
            : head(head)
            , stem(stem)
            , position(position)
            , currentRotationDeg(0.0f)
            , tail(stem.width)
            , hasTail(hasTail)
        {
            setPosition(position);
            tail.setColor(glm::vec4(0,0,0,0));
        }
        // Arrow(glm::vec3 position, glm::vec2 dimensions)
        Arrow(float headWidth, float stemWidth, float stemHeight)
            : head(headWidth)
            , stem(stemWidth, stemHeight)
            , position({0,0,0})
            , currentRotationDeg(0.0f)
            , tail(stemWidth)
            , hasTail(false)
        {
            setPosition(position);
        }

        glm::vec3 position;
        Triangle head;
        Rectangle stem;
        Triangle tail;

        float currentRotationDeg;
        bool hasTail;

        float getWidth() const { return std::max(head.width, stem.width); }
        float getHeight() const { return head.height + stem.height; }

        glm::mat4 getRotationMatrix(float deg) const { return glm::mat4(1); }

        void setColor(glm::vec4 color)
        {
            head.setColor(color);
            stem.setColor(color);
        }

        void setXPosition(float xpos) { setPosition({xpos, position.y, position.z}); }
        void setYPosition(float ypos) { setPosition({position.x, ypos, position.z}); }
        void setPosition(float xpos, float ypos) { setPosition({xpos, ypos, position.z}); }

        float calcHeightAvg() const { return (stem.height+head.height)/2.0f;}
        float calcHeightOffset() const { return calcHeightAvg() - (stem.height/2.0f); }

        void setPosition(glm::vec3 pos)
        {
            position = pos;
            head.setPosition(pos);
            stem.setPosition(pos);
            tail.setPosition(pos);

            stem.setYPosition(pos.y-calcHeightOffset());
            head.setYPosition(stem.position.y+getHeadOffset());
            tail.setYPosition(stem.position.y+getTailOffset());

            // A total hack
            float tmp = currentRotationDeg;
            currentRotationDeg = 0;
            setRotation2D(tmp);
        }

        float getHeadOffset() const { return stem.height/2+head.height/2; }
        float getTailOffset() const { return -stem.height/2+tail.height/2; }

        void setRotation2D(float deg)
        {
            float diff = currentRotationDeg - deg;
            if (diff != 0)
            {
                currentRotationDeg = deg;
                // sorry for this. its confusing becuase i wanted the center of the arrow
                // to be the actual center and becuase its made up of two objects there are some
                // calculations
                
                // move stem back into normal pos before centering
                stem.position.y += calcHeightOffset();
                stem.rotate2D(diff); // do the rotation

                // position and rotate the head based off this new position and the rotation
                head.setPosition(stem.position.x+(stem.height/2)*cos(glm::radians(90+currentRotationDeg)),
                                 stem.position.y+(stem.height/2)*sin(glm::radians(90+currentRotationDeg)));
                head.rotate2D(-currentRotationDeg);

                // position and rotate the tail based off this new position and the rotation
                float offset = tail.getHeightOffset()+1;
                tail.setPosition(stem.position.x-(stem.height/2+offset)*cos(glm::radians(90+currentRotationDeg)),
                                 stem.position.y-(stem.height/2+offset)*sin(glm::radians(90+currentRotationDeg)));
                tail.rotate2D(-currentRotationDeg);

                // put the stem back
                stem.position.y -= calcHeightOffset();
                stem.updateVertexBuffer();
            }
        }

        void draw(const Shader& shader) const
        {
            head.draw(shader);
            if (hasTail)
            {
                Renderer::beginDefiningStencil();
                tail.draw(shader);
                Renderer::endDefiningStencil();
                Renderer::setStencilAsExclusionMask();
            }
            stem.draw(shader);
            Renderer::clearStencil();
        }
    };

} // end namespace Drawables
