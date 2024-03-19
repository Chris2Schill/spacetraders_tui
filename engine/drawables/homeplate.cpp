#include "homeplate.h"

#include "window.h"
#include "colors.h"

static const float heightScale = 0.8;

namespace Drawables
{

Homeplate::Homeplate()
    : Homeplate(window::center().x, window::center().y)
{}

Homeplate::Homeplate(float width, float height)
    : Homeplate(window::center().x, window::center().y, width, height)
{}

Homeplate::Homeplate(float xpos, float ypos, float width, float height)
    : Homeplate(xpos, ypos, 0.0f, width, height)
{}

Homeplate::Homeplate(float xPos, float yPos, float zPos, float width, float height)
    : width(width),
    height(height),
    Drawable(glm::vec3(xPos, yPos, zPos))
{
    float xPosLeft = xPos - width / 2;
    float yPosBottom = yPos - height / 2;

    glm::vec3 normOutScreen(0, 0, 1);

    float mod = height*(1.0-heightScale);

    vertices =
    {
        // Position                                                Normal                 Color
        { glm::vec3(xPosLeft, yPosBottom+mod, zPos),          normOutScreen,  WHITE },
        { glm::vec3(xPos, yPosBottom, zPos),                  normOutScreen,  WHITE },
        { glm::vec3(xPosLeft+width, yPosBottom+mod, zPos),    normOutScreen,  WHITE },
        { glm::vec3(xPosLeft+width, yPosBottom+height, zPos), normOutScreen,  WHITE },
        { glm::vec3(xPosLeft, yPosBottom+height, zPos),       normOutScreen,  WHITE } 
    };

    indices =
    {
        0, 1, 2,
        0, 2, 3,
        3, 4, 0
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

void Homeplate::draw(const Shader& shader) const
{
    static const int FILL_NUM_INDICES = 9;

    // Quick and dirty way of drawing as fill or border...
    if (indices.size() == FILL_NUM_INDICES)
    {
        Renderer::draw(*vertexArray, *indexBuffer, shader);
    }
    else
    {
        Renderer::drawLines(*vertexArray, *indexBuffer, shader);
    }
}

void Homeplate::setFill(bool fill)
{
    if (fill)
    {
        indices = { 0, 1, 2,
                    0, 2, 3,
                    3, 4, 0 };
    }
    else
    {
        indices = { 0,1,
                    1,2,
                    2,3,
                    3,4,
                    4,0 };
    }
    updateIndexBuffer();
}

void Homeplate::setSize(float w, float h)
{
    width = w;
    height = h;
    setPosition(position);
}

void Homeplate::setWidth(float w)
{
    width = w; 
    setPosition(position);
}

void Homeplate::setHeight(float h)
{
    height = h;
    setPosition(position);
}

void Homeplate::setXPosition(float x)
{
    setPosition(x, position.y, position.z); 
}
void Homeplate::setYPosition(float y)
{
    setPosition(position.x, y, position.z);    
}
void Homeplate::setZPosition(float z)
{
    setPosition(position.x, position.y, z);    
}
void Homeplate::setPosition(float x, float y, float z)
{
    float xPosLeft = x - width / 2;
    float yPosBottom = y - height / 2;

    float mod = height*(1.0-heightScale);
    vertices[0].position = glm::vec3(xPosLeft, yPosBottom+mod, z);
    vertices[1].position = glm::vec3(x, yPosBottom, z);
    vertices[2].position = glm::vec3(xPosLeft+width, yPosBottom+mod, z);
    vertices[3].position = glm::vec3(xPosLeft+width, yPosBottom+height, z);
    vertices[4].position = glm::vec3(xPosLeft, yPosBottom+height, z);

    position.x = x;
    position.y = y;
    position.z = z;
    updateVertexBuffer();
}
void Homeplate::setPosition(glm::vec3 pos)
{
    setPosition(pos.x, pos.y, pos.z);
}
void Homeplate::setPosition(glm::vec2 pos)
{
    setPosition(pos.x, pos.y, position.z);
}


} // end namespace Drawables
