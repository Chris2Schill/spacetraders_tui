#pragma once

#include <string>
#include <vector>
#include "renderer/shader.h"
#include "text.h"

namespace Drawables
{


class MultiLineText
{
    std::vector<Text> texts;
    float fontScale;
    glm::vec3 position;
    glm::vec4 color;
    std::string rawText;
    float width;
    float height;

public:   
    MultiLineText(std::string text, float xpos, float ypos, float fontScale, glm::vec4 color);

    void setText(std::string text);
    void setPosition(glm::vec2 xy);
    float getWidth() const { return width; };
    float getHeight() const { return height; };
    void updateDimensions();

    
    void draw();
    void draw(Shader& textShader);
};

} // end namespace Drawables
