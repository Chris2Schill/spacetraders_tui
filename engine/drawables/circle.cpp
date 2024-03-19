#include "circle.h"

#include "window.h"
#include <renderer/renderer.h>
#include "colors.h"

namespace Drawables
{

Circle::Circle(float xPos, float yPos, float radius, float percentDrawn, unsigned int smoothness)
    : Drawable(glm::vec3(xPos, yPos, 0.0f)),
    radius(radius),
    smoothness(smoothness),
    percentDrawn(percentDrawn)
{
    assert(smoothness > 0);
    assert(percentDrawn >= 0.0f && percentDrawn <= 1.0f);

    // Using GL_TRIANGLE_FAN to draw, so first point is the center
    Vertex centerPoint = { glm::vec3(xPos,yPos,0), glm::vec3(0,0,1), WHITE };
    vertices.push_back(centerPoint);
    indices.push_back(0);

    float increment = 2*M_PI / smoothness;
    // first point is bottom of circle
    float currVertexPos = 0 - (2*M_PI / 4.0);
    for (unsigned int i = 0; i <= smoothness*percentDrawn; ++i)
    {
        Vertex v;
        v.position = glm::vec3(xPos + cos(currVertexPos)*radius, yPos + sin(currVertexPos)*radius, 0.0f);
        v.color = WHITE;
        v.normal = glm::vec3(0, 0, 1);
        vertices.push_back(v);

        indices.push_back(i+1);

        currVertexPos -= increment;
    }

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

    vertexBuffer->unbind();
    vertexArray->unbind();
    indexBuffer->unbind();
}

void Circle::setRadius(float rad)
{
    radius = rad;
    setPosition(position);
}

void Circle::setXPosition(float xPos)
{
    setPosition(glm::vec3(xPos, position.y, position.z));
}

void Circle::setPosition(float xPos, float yPos)
{
    setPosition(glm::vec2(xPos, yPos));
}

void Circle::setPosition(glm::vec2 pos)
{
    setPosition({pos.x, pos.y, position.z});
}

void Circle::setPosition(glm::vec3 pos)
{
    position = pos;
    vertices[0].position = position;

    float increment = 2*M_PI / smoothness;
    // first point is bottom of circle
    float currVertexPos = 0 - (2*M_PI / 4.0);
    for (unsigned int i = 0; i <= smoothness*percentDrawn; ++i)
    {
        vertices[i+1].position = glm::vec3(position.x + cos(currVertexPos)*radius, position.y + sin(currVertexPos)*radius, 0.0f);
        currVertexPos -= increment;
    }
    updateVertexBuffer();
}

void Circle::draw() const
{
    draw(Renderer::getBasicShader());
}

void Circle::draw(const Shader& shader) const
{
    Renderer::drawTriangleFan(*vertexArray, *indexBuffer, shader);
}

} // end namespace Drawables
