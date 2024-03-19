#pragma once

#include <vector>
#include <glm/vec2.hpp>

#include "drawable.h"
#include "window.h"

namespace Drawables
{

    struct Diamond : public Drawable
    {
        Diamond() : Diamond(window::center().x, window::center().y) {}
        Diamond(float width, float height) : Diamond(window::center().x, window::center().y, width, height) {}
        Diamond(float xpos, float ypos, float width, float height) : Diamond(xpos, ypos, 0.0f, width, height) {}

        Diamond(float xpos, float ypos, float zpos, float width, float height)
            : Drawable(glm::vec3(xpos, ypos, zpos)),
              width(width),
              height(height),
              lineWidth(5)
        {
            glm::vec3 normOutScreen(0, 0, 1);

            vertices =
            {
                // Outer diamond
                { glm::vec3(xpos-width/2, ypos, zpos),   normOutScreen,  glm::vec4(1.0, 1.0, 1.0, 1.0), glm::vec2(0,1)}, // bottom left
                { glm::vec3(xpos, ypos-height/2, zpos),  normOutScreen,  glm::vec4(1.0, 1.0, 1.0, 1.0), glm::vec2(1,1)}, // bottom right
                { glm::vec3(xpos+width/2, ypos, zpos),   normOutScreen,  glm::vec4(1.0, 1.0, 1.0, 1.0), glm::vec2(1,0)}, // top right
                { glm::vec3(xpos, ypos+height/2, zpos),  normOutScreen,  glm::vec4(1.0, 1.0, 1.0, 1.0), glm::vec2(0,0)},  // top left

                // Inner diamond
                { glm::vec3(xpos-width/2+lineWidth, ypos, zpos),   normOutScreen,  glm::vec4(1.0, 1.0, 1.0, 1.0), glm::vec2(0,1)}, // bottom left
                { glm::vec3(xpos, ypos-height/2+lineWidth, zpos),  normOutScreen,  glm::vec4(1.0, 1.0, 1.0, 1.0), glm::vec2(1,1)}, // bottom right
                { glm::vec3(xpos+width/2-lineWidth, ypos, zpos),   normOutScreen,  glm::vec4(1.0, 1.0, 1.0, 1.0), glm::vec2(1,0)}, // top right
                { glm::vec3(xpos, ypos+height/2-lineWidth, zpos),  normOutScreen,  glm::vec4(1.0, 1.0, 1.0, 1.0), glm::vec2(0,0)},  // top left
            };

            indices =
            {
                0, 1, 2,
                2, 3, 0
            };

            layout = std::make_shared<VertexBufferLayout>();
            layout->push<float>(3);
            layout->push<float>(3);
            layout->push<float>(4);
            layout->push<float>(2);

            vertexBuffer = std::make_shared<VertexBuffer>(&vertices[0],
                    sizeof(Vertex)*vertices.size());

            vertexArray = std::make_shared<VertexArray>();
            vertexArray->addBuffer(vertexBuffer, layout);

            indexBuffer = std::make_shared<IndexBuffer>(&indices[0], indices.size());

            vertexArray->unbind();
            vertexBuffer->unbind();
            indexBuffer->unbind();
        }


        void draw(const Shader& shader) const
        {
            Renderer::draw(*vertexArray, *indexBuffer, shader);
        }

        Diamond& setFill(bool fill)
        {
            if (fill)
            {
                indices = { 0, 1, 2,
                            2, 3, 0 };
                    
            }
            else
            {
                indices = { // Bottom trapezoid
                    0, 1, 4,
                    1, 5, 4,
                    
                    // Right trapezoid
                    1, 2, 5,
                    2, 6, 5,

                    // Top trapezoid
                    2, 3, 6,
                    3, 7, 6,

                    // Left trapezoid
                    3, 0, 7,
                    0, 4, 7
                    };
            }
            
            updateIndexBuffer();
            return *this;
        }

        void setXPosition(float x) { setPosition({x, position.y, position.z}); }

        void setYPosition(float y) { setPosition({position.x, y, position.z}); }

        void setZPosition(float z) { setPosition({position.x, position.y, z}); }

        void setPosition(glm::vec2 pos) { setPosition({pos.x, pos.y, position.z}); };

        void setPosition(float x, float y, float z = 0.0f) { setPosition({x,y,z}); }

        void setPosition(glm::vec3 pos)
        {
            vertices[0].position  = glm::vec3(pos.x-width/2, pos.y, pos.z),  
            vertices[1].position  = glm::vec3(pos.x, pos.y-height/2, pos.z), 
            vertices[2].position  = glm::vec3(pos.x+width/2, pos.y, pos.z),
            vertices[3].position  = glm::vec3(pos.x, pos.y+height/2, pos.z),
            vertices[4].position  = glm::vec3(pos.x-width/2+lineWidth, pos.y, pos.z),  
            vertices[5].position  = glm::vec3(pos.x, pos.y-height/2+lineWidth, pos.z), 
            vertices[6].position  = glm::vec3(pos.x+width/2-lineWidth, pos.y, pos.z),
            vertices[7].position  = glm::vec3(pos.x, pos.y+height/2-lineWidth, pos.z),

            position = pos;
            updateVertexBuffer();
        }
        void setSize(float w, float h)
        {
            width = w;
            height = h;
            setPosition(position);
        }

        float bottom() const { return position.y-height/2.0;}
        float top() const { return position.y+height/2.0;}
        float left() const { return position.x-width/2.0;}
        float right() const { return position.x+width/2.0;}

        float width;
        float height;

        float lineWidth;
    };

} // end namespace Drawables
