#include "text.h"

#include <vector>
#include <iostream>
#include <glm/ext.hpp>

#include "ft2build.h"
#include FT_FREETYPE_H

#include "rect.h"
#include "logger.h"
#include "colors.h"

std::string FONT_FILEPATH = "telegrama_render.otf";

namespace Drawables
{

float Text::DEFAULT_SPACING = 0.0f;

void initFreetype();


std::map<char, Character>& getCharacterMap()
{
    static std::map<char, Character> charMap;
    static bool first = true;
    if (first)
    {
        // Make sure you set first to false before calling initFreeType to avoid
        // recurseive BS.. TODO: fix this lazy lazy-initializer
        first = false;

        initFreetype();
    }
    return charMap;
}

void initFreetype()
{
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        LOG(ERROR) << "ERROR::FREETYPE: Could not init FreeType Library";
    }

    FT_Face face;
    if (FT_New_Face(ft, (Renderer::RESOURCE_DIR+std::string("/fonts/")+FONT_FILEPATH).c_str(), 0, &face))
    {
        LOG(ERROR) << "ERROR::FREETYPE: Failed to load font";
    }

    FT_Set_Pixel_Sizes(face, 0, 48);

    if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
    {
        LOG(ERROR) << "ERROR::FREETYTPE: Failed to load Glyph";
    }

    GL_CALL(glPixelStorei(GL_UNPACK_ALIGNMENT, 1)); // disable byte-alignment restriction
    getCharacterMap();

    for (unsigned char c = 0; c < 255; c++)
    {
        // load character glyph 
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            LOG(ERROR) << "ERROR::FREETYTPE: Failed to load Glyph";
            continue;
        }
        // generate texture
        unsigned int texture;
        GL_CALL(glGenTextures(1, &texture));
        GL_CALL(glBindTexture(GL_TEXTURE_2D, texture));
        GL_CALL(glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_ALPHA,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_ALPHA,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        ));
        // set texture options
        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        // now store character for later use
        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };
        getCharacterMap().insert(std::pair<char, Character>(c, character));
    }
    GL_CALL(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

Text::Text(std::string textStr, float x, float y, float s, glm::vec4 color)
    : Text(textStr, x, y, s, color, getCharacterMap())
{
}

Text::Text(std::string textStr, float x, float y, float s, glm::vec4 color, std::map<char, Character>& characters)
    : text(textStr),
    scale(s),
    color(color),
    characterMap(characters),
    position(x,y,0.0f),
    spacing(DEFAULT_SPACING)
{
    std::vector<glm::vec4> vertices =
    {
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0}
    };

    vbl = std::make_shared<VertexBufferLayout>();
    vbl->push<float>(4);

    vb = std::make_shared<VertexBuffer>(&vertices[0], sizeof(glm::vec4)*vertices.size(), GL_DYNAMIC_DRAW);

    va = std::make_shared<VertexArray>();
    va->addBuffer(*vb, *vbl);
}

float Text::getWidth() const
{
    float fullWidth = 0.0;
    for (std::string::const_iterator c = text.begin(); c != text.end(); c++)
    {
        Character ch = characterMap[*c];
        fullWidth += ((ch.advance >> 6) * scale); // bitshift by 6 to get value in pixels (2^6 = 64)
    }
    if (text.size() > 0)
    {
        fullWidth += spacing * (text.size()-1);
    }

    return fullWidth;
}

float Text::getHeight() const
{
    float fullHeight = 0.0;
    for (std::string::const_iterator c = text.begin(); c != text.end(); c++)
    {
        Character ch = characterMap[*c];
        fullHeight = std::max(ch.size.y * scale, fullHeight);
    }
    return fullHeight;
}

void Text::draw() const
{
    draw(Renderer::getTextShader());
}

void Text::draw(Shader& s) const
{
    // activate corresponding render state	
    s.bind();
    s.setUniform3f("textColor", color.r, color.g, color.b);
    va->bind();

    // Calculate width/heightof full text string
    float fullWidth = 0.0;
    float fullHeight = 0.0;
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = characterMap[*c];

        fullWidth += ((ch.advance >> 6) * scale); // bitshift by 6 to get value in pixels (2^6 = 64)
        fullHeight = std::max(ch.size.y * scale, fullHeight);
    }
    if (text.size() > 0)
    {
        fullWidth += spacing * (text.size()-1);
    }

    float x = position.x - (fullWidth/2.0);
    float y = position.y - (fullHeight/2.0);

    // iterate through all characters
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = characterMap[*c];

        float xpos = x + ch.bearing.x * scale;
        float ypos = y - (ch.size.y - ch.bearing.y) * scale;

        float w = ch.size.x * scale;
        float h = ch.size.y * scale;

        // update VBO for each character
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }
        };
        // render glyph texture over quad
        GL_CALL(glBindTexture(GL_TEXTURE_2D, ch.textureId));
        // update content of VBO memory
        vb->bind();
        GL_CALL(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices));
        // vb->unbind();
        // render quad
        GL_CALL(glDrawArrays(GL_TRIANGLES, 0, 6));
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += ((ch.advance >> 6) * scale) + spacing; // bitshift by 6 to get value in pixels (2^6 = 64)
    }
    // va->unbind();
    // GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
}

void Text::drawAsLabel(Shader& basicShader, Shader& textShader) const
{
    auto& rect = getBorderAround(*this, ORANGE, FILL);
    // rect.scale({1.5, 2.0, 1.0});
    rect.draw(basicShader);
    draw(textShader);
}

template<>
Rectangle& getBorderAround<Text>(Text drawable, glm::vec4 color, bool fill)
{
    static Drawables::Rectangle rect;
    static const float PADDING = 3.0;
    
    rect.setFill(fill);
    rect.setLineWidth(2);
    rect.setColor(color);
    rect.setSize(drawable.getWidth()+PADDING, drawable.getHeight()+PADDING*1.5);
    rect.setPosition(drawable.position.x, drawable.position.y);

    return rect;
}

} // end namespace Drawables
