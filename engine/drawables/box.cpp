#include "box.h"
#include "window.h"
#include "colors.h"


namespace Drawables
{

Box::Box(float width, float height, float depth)
    : Box(window::center().x, window::center().y, 0.0f, width, height, depth)
{
}

Box::Box(float xpos, float ypos, float zpos, float width, float height, float depth)
    : Drawable(glm::vec3(xpos, ypos, zpos)),
    width(width),
    height(height),
    depth(depth)
{
    float xPosi = xpos - width / 2;
    float yPosi = xpos - height / 2;
    float zPosi = zpos - depth / 2;

    auto point0 = glm::vec3(-xPosi, -yPosi, zPosi);
    auto point1 = glm::vec3(xPosi, -yPosi, zPosi);
    auto point2 = glm::vec3( xPosi,  yPosi, zPosi);
    auto point3 = glm::vec3(-xPosi,  yPosi, zPosi);
    auto point4 = glm::vec3(-xPosi, -yPosi, -zPosi);
    auto point5 = glm::vec3( xPosi, -yPosi, -zPosi);
    auto point6 = glm::vec3( xPosi,  yPosi, -zPosi);
    auto point7 = glm::vec3(-xPosi,  yPosi, -zPosi);

    auto normFront = glm::vec3(0, 0, 1);
    auto normRight = glm::vec3(1, 0, 0);
    auto normUp = glm::vec3(0, 1, 0);

    vertices =
    {
        // front
        { point4, normFront, WHITE },
        { point5, normFront, WHITE },
        { point6, normFront, WHITE },
        { point6, normFront, WHITE },
        { point7, normFront, WHITE },
        { point4, normFront, WHITE },

        // back
        { point0, -normFront, WHITE },
        { point1, -normFront, WHITE },
        { point2, -normFront, WHITE },
        { point2, -normFront, WHITE },
        { point3, -normFront, WHITE },
        { point0, -normFront, WHITE },

        // left
        { point5, -normRight, WHITE },
        { point1, -normRight, WHITE },
        { point2, -normRight, WHITE },
        { point2, -normRight, WHITE },
        { point6, -normRight, WHITE },
        { point5, -normRight, WHITE },

        // right
        { point4, normRight, WHITE },
        { point0, normRight, WHITE },
        { point3, normRight, WHITE },
        { point3, normRight, WHITE },
        { point7, normRight, WHITE },
        { point4, normRight, WHITE },

        // top
        { point4, normUp, WHITE },
        { point0, normUp, WHITE },
        { point1, normUp, WHITE },
        { point1, normUp, WHITE },
        { point5, normUp, WHITE },
        { point4, normUp, WHITE },

        // bottom
        { point7, -normUp, WHITE },
        { point3, -normUp, WHITE },
        { point2, -normUp, WHITE },
        { point2, -normUp, WHITE },
        { point6, -normUp, WHITE },
        { point7, -normUp, WHITE },
    };


    const int numFaces = 6;
    const int numVerticesPerFace = 4;
    const int repeatedVertices = 12;
        
    for (int i = 0; i < numFaces * numVerticesPerFace + repeatedVertices; ++i)
    {
        indices.push_back(i);
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

    vertexArray->unbind();
    vertexBuffer->unbind();
    indexBuffer->unbind();
}

void Box::draw(const Shader& shader) const
{
    Renderer::draw(*vertexArray, *indexBuffer, shader);
}

} // end namespace Drawables
