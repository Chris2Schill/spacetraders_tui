#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "rect.h"
#include "homeplate.h"
#include "drawables/text.h"


namespace Drawables
{
class Tape
{
public:

    enum tick_alignment
    {
        LEFT_JUSTIFIED,
        RIGHT_JUSTIFIED,
        CENTERED
    };
    struct TickSchema
    {
        std::vector<Rectangle> ticks;
        int numTicks;
        tick_alignment alignment;
        float tickValueInterval;
        int textDisplayInterval;
    };

    struct Builder
    {
        glm::vec3 position_;
        glm::vec3 up_;
        float minValue_;
        float maxValue_;
        float width_;
        float height_;
        float value_;
        float fontScale_;
        bool showNegativesAsPositives_;
        bool showNegatives_;
        TickSchema tickSchema_;

        Builder() = default;
        
        Builder& position(float posx, float posy, float posz = 0.0f);
        Builder& size(float width, float height);
        Builder& up(glm::vec3 up);
        Builder& minValue(float val);
        Builder& maxValue(float val);
        Builder& tickSchema(TickSchema schema);
        Builder& value(float val);
        Builder& fontScale(float fontScale);
        Builder& showNegativesAsPositives(bool negsAsPos);
        Builder& showNegatives(bool show);
        
        std::shared_ptr<Tape> build();
    };

    float top()    const { return border_.top();    }
    float bottom() const { return border_.bottom(); }
    float left()   const { return border_.left();   }
    float right()  const { return border_.right();   }
    float getWidth() const { return width_;}
    glm::vec3 getPosition() const { return position_;}

    Tape(glm::vec3 position, float width, float height, glm::vec3 up,
         float minVal, float maxVal, float fontScale, bool showNegativesAsPositives, bool showNegatives, TickSchema ts);

    void draw(Shader& shader, Shader& textShader);
    glm::vec3 getPosition() { return position_; }
    void setPosition(float x, float y, float z);
    void setPosition(glm::vec3 vec);
    void setMinValue(float value);
    void setMaxValue(float value);
    void setSize(float width, float height);
    void setValue(float value);

    struct TestRange
    {
        float lowerValue;
        float upperValue;
        glm::vec4 color;
        const bool* active;
    };
    void addTestRange(TestRange testRange) { testRanges.push_back(testRange); };


private:

    Tape() = delete;
    float valueToOffsetFromCurrentValue(float val);

    glm::vec3 position_;
    glm::vec3 up_;

    float minValue_;
    float maxValue_;
    float width_;
    float height_;
    float value_;
    float fontScale_;
    bool showNegativesAsPositives_;
    bool showNegatives_;
    TickSchema tickSchema_;

    std::vector<TestRange> testRanges;

    Drawables::Text indicationText_;

    Homeplate homeplate_;

    Rectangle border_;
    Drawables::Text numberText_;
    Drawables::Rectangle testRange;
};

}
