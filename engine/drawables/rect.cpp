#include "rect.h"
#include "window.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "logger.h"
#include "event_bus.h"

/*
 * This is the layout of the vertices.
 * When set to fill(the default mode)
 * it only renders triangles using the 
 * outer rect vertices. When fill is set
 * false, it will draw 4 trapezoids using the 
 * inner vertices
 *
 *   3                      2
 *    -----------------------
 *    |  7               6  | 
 *    |   ---------------   |
 *    |   |             |   |
 *    |   |             |   |
 *    |   |             |   |
 *    |   |             |   |
 *    |   ---------------   |
 *    |  4               5  |
 *    -----------------------
 *   0                      1
 *
 */

namespace Drawables
{

Rectangle::Rectangle(const Framebuffer* fb)
    : Rectangle(window::center().x, window::center().y, fb->getWidth(), fb->getHeight())
{
    texture = fb->getColorBuffer();
    vertices[0].texCoords = { 0, 0 };
    vertices[1].texCoords = { 1, 0 };
    vertices[2].texCoords = { 1, 1 };
    vertices[3].texCoords = { 0, 1 };
    updateVertexBuffer();
}

Rectangle::Rectangle()
    : Rectangle(window::center().x, window::center().y)
{}

Rectangle::Rectangle(float width, float height)
    : Rectangle(window::center().x, window::center().y, width, height)
{}
Rectangle::Rectangle(float width, float height, glm::vec4 color)
    : Rectangle(window::center().x, window::center().y, width, height)
{ setColor(color); }

Rectangle::Rectangle(float xpos, float ypos, float width, float height)
    : Rectangle(xpos, ypos, 0.0f, width, height)
{}

Rectangle::Rectangle(float xPos, float yPos, float zpos, float width, float height)
    : Drawable(glm::vec3(xPos, yPos, zpos)),
    width(width),
    height(height),
    lineWidth(5),
    textureName(""),
    texture(0)
{
    float xPosLeft = xPos - width / 2;
    float yPosBottom = yPos - height / 2;

    glm::vec3 normOutScreen(0, 0, 1);

    vertices =
    {
        // OuterRect
        { glm::vec3(xPosLeft, yPosBottom, zpos),              normOutScreen,  glm::vec4(1.0, 1.0, 1.0, 1.0), glm::vec2(0,1)}, // bottom left
        { glm::vec3(xPosLeft+width, yPosBottom, zpos),        normOutScreen,  glm::vec4(1.0, 1.0, 1.0, 1.0), glm::vec2(1,1)}, // bottom right
        { glm::vec3(xPosLeft+width, yPosBottom+height, zpos), normOutScreen,  glm::vec4(1.0, 1.0, 1.0, 1.0), glm::vec2(1,0)}, // top right
        { glm::vec3(xPosLeft, yPosBottom+height, zpos),       normOutScreen,  glm::vec4(1.0, 1.0, 1.0, 1.0), glm::vec2(0,0)},  // top left

        // Inner rect
        { glm::vec3(xPosLeft+lineWidth, yPosBottom+lineWidth, zpos),              normOutScreen,  glm::vec4(1.0, 1.0, 1.0, 1.0), glm::vec2(0,1)},
        { glm::vec3(xPosLeft+width-lineWidth, yPosBottom+lineWidth, zpos),        normOutScreen,  glm::vec4(1.0, 1.0, 1.0, 1.0), glm::vec2(1,1)},
        { glm::vec3(xPosLeft+width-lineWidth, yPosBottom+height-lineWidth, zpos), normOutScreen,  glm::vec4(1.0, 1.0, 1.0, 1.0), glm::vec2(1,0)},
        { glm::vec3(xPosLeft+lineWidth, yPosBottom+height-lineWidth, zpos),       normOutScreen,  glm::vec4(1.0, 1.0, 1.0, 1.0), glm::vec2(0,0)} 
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

void Rectangle::draw() const
{
    if (texture != 0)
    {
        draw(Renderer::getTextureShader());
    }
    else
    {
        draw(Renderer::getBasicShader());
    }
}

void Rectangle::draw(const Shader& shader) const
{
    if (texture != 0)
    {
        GL_CALL(glBindTexture(GL_TEXTURE_2D, texture));
    }

    Renderer::draw(*vertexArray, *indexBuffer, shader);
}

Rectangle& Rectangle::setFill(bool fill)
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

void Rectangle::setSize(float w, float h)
{
    width = w;
    height = h;
    setPosition(position);
}

void Rectangle::setWidth(float w)
{
    width = w; 
    setPosition(position);
}

void Rectangle::setHeight(float h)
{
    height = h;
    setPosition(position);
}

void Rectangle::setXPosition(float x)
{
    setPosition(x, position.y, position.z); 
}
void Rectangle::setYPosition(float y)
{
    setPosition(position.x, y, position.z);    
}
void Rectangle::setZPosition(float z)
{
    setPosition(position.x, position.y, z);    
}
void Rectangle::setPosition(float x, float y)
{
    setPosition(x, y, position.z);
}
void Rectangle::setPosition(float x, float y, float z)
{
    float xPosLeft = x - width / 2;
    float yPosBottom = y - height / 2;

    vertices[0].position = glm::vec3(xPosLeft, yPosBottom, z);
    vertices[1].position = glm::vec3(xPosLeft+width, yPosBottom, z);
    vertices[2].position = glm::vec3(xPosLeft+width, yPosBottom+height, z);
    vertices[3].position = glm::vec3(xPosLeft, yPosBottom+height, z);
    vertices[4].position = glm::vec3(xPosLeft+lineWidth, yPosBottom+lineWidth, z);
    vertices[5].position = glm::vec3(xPosLeft+width-lineWidth, yPosBottom+lineWidth, z);
    vertices[6].position = glm::vec3(xPosLeft+width-lineWidth, yPosBottom+height-lineWidth, z);
    vertices[7].position = glm::vec3(xPosLeft+lineWidth, yPosBottom+height-lineWidth, z);

    position.x = x;
    position.y = y;
    position.z = z;
    updateVertexBuffer();
}
void Rectangle::setPosition(glm::vec3 pos)
{
    setPosition(pos.x, pos.y, pos.z);
}
void Rectangle::setPosition(glm::vec2 pos)
{
    setPosition(pos.x, pos.y, position.z);
}
void Rectangle::setLineWidth(float lw)
{
    lineWidth = lw;
    setPosition(position);
}

void Rectangle::bindTexture(std::string textureFile)
{
    static const std::string TEXTURES_DIR = Renderer::RESOURCE_DIR+std::string("/textures/");

    int w, h, nrChannels;
    std::string texName = TEXTURES_DIR+textureFile;
    // GL_CALL(glEnable(GL_TEXTURE_2D));
    if (!texture)
    {
        GL_CALL(glGenTextures(1, &texture));
    }
    if (texName != textureName)
    {
        auto data = stbi_load(texName.c_str(), &w, &h, &nrChannels, 0);

        GL_CALL(glActiveTexture(GL_TEXTURE0));
        GL_CALL(glBindTexture(GL_TEXTURE_2D, texture));
        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        if (data)
        {
            auto format = nrChannels == 3 ? GL_RGB : GL_RGBA;
            GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, data));
            GL_CALL(glGenerateMipmap(GL_TEXTURE_2D));

            LOG(INFO) << "Loaded texture: " << textureFile << " - width = " << w << ", height = " << h << ", nrChannels " << nrChannels;
            stbi_image_free(data);
            textureName = texName;
        }
        else { LOG(ERROR) << "Failed to load texture."; }
    }

    GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
}

} // end namespace Drawables
