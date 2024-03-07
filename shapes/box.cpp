#include "box.h"


namespace Shapes
{

std::shared_ptr<Shape> createBox(float width, float height, float depth)
{
    return createBox(0,0,0,width,height,depth);
}

std::shared_ptr<Shape> createBox(float xPos, float yPos, float zPos, float width, float height, float depth)
{
    float xPosi = xPos - width / 2;
    float yPosi = xPos - height / 2;
    float zPosi = zPos - depth / 2;

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

    const std::vector<Vertex> vertices =
    {

        // front
        { point4, normFront, glm::vec3(1, 1, 1) },
        { point5, normFront, glm::vec3(1, 1, 1) },
        { point6, normFront, glm::vec3(1, 1, 1) },
        { point6, normFront, glm::vec3(1, 1, 1) },
        { point7, normFront, glm::vec3(1, 1, 1) },
        { point4, normFront, glm::vec3(1, 1, 1) },

        // back
        { point0, -normFront, glm::vec3(1, 1, 1) },
        { point1, -normFront, glm::vec3(1, 1, 1) },
        { point2, -normFront, glm::vec3(1, 1, 1) },
        { point2, -normFront, glm::vec3(1, 1, 1) },
        { point3, -normFront, glm::vec3(1, 1, 1) },
        { point0, -normFront, glm::vec3(1, 1, 1) },

        // left
        { point5, -normRight, glm::vec3(1, 1, 1) },
        { point1, -normRight, glm::vec3(1, 1, 1) },
        { point2, -normRight, glm::vec3(1, 1, 1) },
        { point2, -normRight, glm::vec3(1, 1, 1) },
        { point6, -normRight, glm::vec3(1, 1, 1) },
        { point5, -normRight, glm::vec3(1, 1, 1) },

        // right
        { point4, normRight, glm::vec3(1, 1, 1) },
        { point0, normRight, glm::vec3(1, 1, 1) },
        { point3, normRight, glm::vec3(1, 1, 1) },
        { point3, normRight, glm::vec3(1, 1, 1) },
        { point7, normRight, glm::vec3(1, 1, 1) },
        { point4, normRight, glm::vec3(1, 1, 1) },

        // top
        { point4, normUp, glm::vec3(1, 1, 1) },
        { point0, normUp, glm::vec3(1, 1, 1) },
        { point1, normUp, glm::vec3(1, 1, 1) },
        { point1, normUp, glm::vec3(1, 1, 1) },
        { point5, normUp, glm::vec3(1, 1, 1) },
        { point4, normUp, glm::vec3(1, 1, 1) },

        // bottom
        { point7, -normUp, glm::vec3(1, 1, 1) },
        { point3, -normUp, glm::vec3(1, 1, 1) },
        { point2, -normUp, glm::vec3(1, 1, 1) },
        { point2, -normUp, glm::vec3(1, 1, 1) },
        { point6, -normUp, glm::vec3(1, 1, 1) },
        { point7, -normUp, glm::vec3(1, 1, 1) },
    };

    //const std::vector<unsigned int> indices =
    //{
    //    0, 1, 2, 3, 7, 1, 5, 4, 7, 6, 2, 4, 0, 1
    //};

    const int numFaces = 6;
    const int numVerticesPerFace = 4;
    const int repeatedVertices = 12;
        
    std::vector<unsigned int> indices;
    for (int i = 0; i < numFaces * numVerticesPerFace + repeatedVertices; ++i)
    {
        indices.push_back(i);
    }

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
