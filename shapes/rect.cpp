#include "rect.h"

namespace Shapes
{

std::shared_ptr<Shape> createRectangle(float width, float height)
{
    return createRectangle(0, 0, width, height);
}

std::shared_ptr<Shape> createRectangle(float xPos, float yPos, float width, float height)
{
    float xPosLeft = xPos - width / 2;
    float yPosBottom = yPos - height / 2;

    glm::vec3 normOutScreen(0, 0, 1);

    std::vector<Vertex> vertices =
    {
        // Position                                         Normal                 Color
        { glm::vec3(xPosLeft, yPosBottom, 0.0),              normOutScreen,  glm::vec3(1.0, 1.0, 1.0) },
        { glm::vec3(xPosLeft+width, yPosBottom, 0.0),        normOutScreen,  glm::vec3(1.0, 1.0, 1.0) },
        { glm::vec3(xPosLeft+width, yPosBottom+height, 0.0), normOutScreen,  glm::vec3(1.0, 1.0, 1.0) },
        { glm::vec3(xPosLeft, yPosBottom+height, 0.0),       normOutScreen,  glm::vec3(1.0, 1.0, 1.0) } 
    };

    std::vector<unsigned int> indices =
    {
        0, 1, 2,
        2, 3, 0
    };

    auto vbl = std::make_shared<VertexBufferLayout>();
    vbl->push<float>(3);
    vbl->push<float>(3);
    vbl->push<float>(3);

    auto vb = std::make_shared<VertexBuffer>(&vertices[0],
                                            sizeof(Vertex)*vertices.size());

    auto va = std::make_shared<VertexArray>();
    va->addBuffer(vb, vbl);

    auto ib = std::make_shared<IndexBuffer>(&indices[0], indices.size());

    auto shape = std::make_shared<Shape>(va, vb, vbl, ib, vertices, indices);

    va->unbind();
    vb->unbind();
    ib->unbind();

    return shape;
}

} // end namespace Shapes
