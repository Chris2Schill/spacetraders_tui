#include "triangle.h"

#include <math.h>

#include "window.h"
#include "logger.h"


namespace Drawables
{

Triangle::Triangle()
    : Triangle(window::center().x, window::center().y, window::WIDTH*0.5)
{}

Triangle::Triangle(float width)
    : Triangle(window::center().x, window::center().y, width, width*sqrt(3.0)/2.0)
{}

Triangle::Triangle(float width, float height)
    : Triangle(window::center().x, window::center().y, width, height)
{}

Triangle::Triangle(float xpos, float ypos, float width)
    : Triangle(window::center().x, window::center().y, width, width*sqrt(3.0)/2.0)
{}

Triangle::Triangle(float xpos, float ypos, float width, float height)
    : Triangle(xpos, ypos, 0.0f, width, height)
{}

float Triangle::getHeightOffset() const { return width/2*sin(glm::radians(30.0f)); }// assumin equliateral for now

Triangle::Triangle(float xPos, float yPos, float zpos, float width, float height)
    : Drawable(glm::vec3(xPos, yPos, zpos)),
    width(width),
    height(height)
{
    float heightOffset = getHeightOffset();
    float xPosLeft = xPos - width / 2;
    float yPosBottom = yPos - heightOffset;

    glm::vec3 normOutScreen(0, 0, 1);

    vertices =
    {
        { glm::vec3(xPosLeft, yPosBottom, zpos),        normOutScreen,  glm::vec4(1.0, 1.0, 1.0, 1.0), glm::vec2(0,1)}, // bottom left
        { glm::vec3(xPosLeft+width, yPosBottom, zpos),  normOutScreen,  glm::vec4(1.0, 1.0, 1.0, 1.0), glm::vec2(1,1)}, // bottom right
        { glm::vec3(xPos, yPosBottom+height, zpos),     normOutScreen,  glm::vec4(1.0, 1.0, 1.0, 1.0), glm::vec2(1,0)}, // top
    };

    indices = { 0, 1, 2, };

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

void Triangle::draw(const Shader& shader) const
{
    if (texture != 0)
    {
        GL_CALL(glBindTexture(GL_TEXTURE_2D, texture));
    }

    Renderer::draw(*vertexArray, *indexBuffer, shader);
}

void Triangle::setSize(float w, float h)
{
    width = w;
    height = h;
    setPosition(position);
}

void Triangle::setWidth(float w)
{
    width = w; 
    setPosition(position);
}

void Triangle::setHeight(float h)
{
    height = h;
    setPosition(position);
}

void Triangle::setXPosition(float x)
{
    setPosition(x, position.y, position.z); 
}
void Triangle::setYPosition(float y)
{
    setPosition(position.x, y, position.z);    
}
void Triangle::setZPosition(float z)
{
    setPosition(position.x, position.y, z);    
}
void Triangle::setPosition(float x, float y, float z)
{
    float xPosLeft = x - width / 2;
    float yPosBottom = y - height / 2;

    vertices[0].position = glm::vec3(xPosLeft, yPosBottom, z);
    vertices[1].position = glm::vec3(xPosLeft+width, yPosBottom, z);
    vertices[2].position = glm::vec3(x, yPosBottom+height, z);

    position.x = x;
    position.y = y;
    position.z = z;
    updateVertexBuffer();
}
void Triangle::setPosition(glm::vec3 pos)
{
    setPosition(pos.x, pos.y, pos.z);
}
void Triangle::setPosition(glm::vec2 pos)
{
    setPosition(pos.x, pos.y, position.z);
}

} // end namespace Drawables
