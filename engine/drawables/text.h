#pragma once

#include <memory>
#include <map>
#include <sstream>
#include <string>

#include <engine/renderer/renderer.h>
// #include "renderer/vertex_buffer_layout.h"
// #include "vertex_array.h"
#include "rect.h"

extern std::string FONT_FILEPATH;

namespace Drawables
{

struct Character
{
    unsigned int textureId;  // ID handle of the glyph texture
    glm::ivec2   size;       // Size of glyph
    glm::ivec2   bearing;    // Offset from baseline to left/top of glyph
    long advance;    // Offset to advance to next glyph
};

std::map<char, Character>& getCharacterMap();


class Text
{

    std::shared_ptr<VertexBuffer> vb;
    std::shared_ptr<VertexArray> va;
    std::shared_ptr<VertexBufferLayout> vbl;
    std::string text;
    float scale;
    float spacing;
    glm::vec4 color;
    std::map<char, Character>& characterMap;
        
public:
    static float DEFAULT_SPACING;

    Text() : characterMap(getCharacterMap()){}
    Text(std::string textStr, float x, float y, float s, glm::vec4 color);
    Text(std::string textStr, float x, float y, float s, glm::vec4 color, std::map<char, Character>& characters);

    glm::vec3 position;

    Text& operator=(const Text& other)
    {
        if (&other == this) return *this;

        vb = other.vb;
        va = other.va;
        vbl = other.vbl;
        text = other.text;
        scale = other.scale;
        color = other.color;
        characterMap = other.characterMap;
        position = other.position;
        spacing = other.spacing;

        return *this; 
    }
    

    inline void setText(std::string str) { text = str; }
    inline void setXPosition(float x) { position.x = x; }
    inline void setYPosition(float y) { position.y = y; }
    inline void setZPosition(float z) { position.z = z; }
    inline void setPosition(float x, float y) { position.x = x; position.y = y; }
    inline void setPosition(glm::vec3 pos) { position = pos; }
    inline void setScale(float s) { scale = s; }
    inline void setColor(glm::vec4 c) { color = c; }
    inline float bottom() { return position.y - getHeight()/2.0;}
    inline float top() { return position.y + getHeight()/2.0;}
    inline float left() { return position.x - getWidth()/2.0;}
    inline float right() { return position.x + getWidth()/2.0;}
    inline glm::vec4 getColor() const { return color;}
    inline const std::string& getText() const { return text; }


    template<typename T>
    void setText(T integral)
    {
        std::stringstream ss;
        ss << integral;
        text = ss.str();
    }

    float getWidth() const;
    float getHeight() const;

    void draw() const;
    void draw(Shader& s) const;

    void drawAsLabel(Shader& basicShader, Shader& textShader) const;
};

template<typename T>
Rectangle& getSizeableBorderAround(T drawable, glm::vec4 color, bool fill, float padding)
{
    static Drawables::Rectangle rect;
    
    rect.setFill(fill);
    rect.setLineWidth(2);
    rect.setColor(color);
    rect.setSize(drawable.getWidth()+padding, drawable.getHeight()+padding*1.5);
    rect.setPosition(drawable.position.x, drawable.position.y);

    return rect;

}


template<>
Rectangle& getBorderAround<Drawables::Text>(Drawables::Text drawable, glm::vec4 color, bool fill);

}// end namespace Drawables
