#include "multi_line_text.h"

#include <sstream>

const float MLT_PADDING = 3;

namespace Drawables
{


MultiLineText::MultiLineText(std::string text, float xpos, float ypos, float fontScale, glm::vec4 color)
    : fontScale(fontScale)
    , position(xpos, ypos, 0)
    , rawText(text)
    , color(color)
    , width(0)
{
    setText(text);
}

void MultiLineText::setText(std::string text)
{
    rawText = text;
    std::stringstream ss(rawText);
    std::string segment;
    std::vector<std::string> seglist;

    texts.clear();
    while(std::getline(ss, segment, '\n'))
    {
        texts.push_back(Text(segment, 0, 0, fontScale, color));
    }

    setPosition({position.x, position.y});
    updateDimensions();
}

void MultiLineText::setPosition(glm::vec2 xy)
{
    position.x = xy.x;
    position.y = xy.y;

    texts[0].setPosition(position.x, position.y);
    for (unsigned i = 1; i < texts.size(); ++i)
    {
        texts[i].setPosition(texts[i-1].left()+texts[i].getWidth()/2.0, texts[i-1].position.y-texts[0].getHeight()-MLT_PADDING);
    }
}

void MultiLineText::draw()
{
    for (auto& text : texts)
    {
        text.draw(Renderer::getTextShader());
    }
}

void MultiLineText::draw(Shader& textShader)
{
    for (auto& text : texts)
    {
        text.draw(textShader);
    }
}

void MultiLineText::updateDimensions()
{
    float w = 0;
    float h = 0;
    for (const auto& t : texts)
    {
        w = std::max(w, t.getWidth());
        h += t.getHeight();
    }
    h += MLT_PADDING*(texts.size()-1);

    width = w;
    height = h;
}

} // end namespace Drawables
