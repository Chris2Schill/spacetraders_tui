#include "tape.h"

#include "colors.h"
#include "window.h"
#include "logger.h"

#if defined(__arm__)
    #define hdd window
#endif

namespace Drawables
{
    
Tape::Builder& Tape::Builder::position(float posx, float posy, float posz)
{
    position_ = glm::vec3(posx, posy, posz); 
    return *this; 
}
Tape::Builder& Tape::Builder::size(float width, float height)
{
    width_ = width;
    height_ = height;
    return *this; 
}
Tape::Builder& Tape::Builder::up(glm::vec3 up)
{
    up_ = up;
    return *this; 
}
Tape::Builder& Tape::Builder::minValue(float val)
{
    minValue_ = val;
    return *this; 
}
Tape::Builder& Tape::Builder::maxValue(float val)
{
    maxValue_ = val;
    return *this; 
}
Tape::Builder& Tape::Builder::tickSchema(TickSchema schema)
{
    tickSchema_ = schema;
    return *this; 
}
Tape::Builder& Tape::Builder::value(float val)
{
    value_ = val;
    return *this; 
}
Tape::Builder& Tape::Builder::fontScale(float fontScale)
{
    fontScale_ = fontScale;
    return *this; 
}
Tape::Builder& Tape::Builder::showNegativesAsPositives(bool negsAsPos)
{
    showNegativesAsPositives_ = negsAsPos;
    return *this; 
}
Tape::Builder& Tape::Builder::showNegatives(bool show)
{
    showNegatives_ = show;
    return *this; 
}

std::shared_ptr<Tape> Tape::Builder::build()
{
    auto tape =  std::make_shared<Tape>(position_, width_, height_, up_, minValue_,
                                  maxValue_, fontScale_, showNegativesAsPositives_, showNegatives_, tickSchema_); 
    tape->setValue(value_);
    return tape;
}

Tape::Tape(glm::vec3 position, float width, float height, glm::vec3 up,
     float minVal, float maxVal, float fontScale, bool showNegativesAsPositives, bool showNegatives, TickSchema ts)
    : position_(position),
    width_(width),
    height_(height),
    up_(up),
    minValue_(minVal),
    maxValue_(maxVal),
    fontScale_(fontScale),
    showNegativesAsPositives_(showNegativesAsPositives),
    showNegatives_(showNegatives),
    tickSchema_(ts),
    homeplate_(position.x,position.y, width*0.8, width),
    border_(position.x, position.y, position.z, width, height),
    indicationText_(Text("0", position.x,position.y, fontScale, WHITE)),
    numberText_(Text("0", 0, 0, fontScale, GREEN))
{
    assert(minValue_ < maxValue_);
    for (auto& rect : tickSchema_.ticks)
    {
        rect.setColor(GREEN); 
    }
    
    glm::vec3 normOutScreen(0, 0, 1);


    // Rotate the homeplate because by default its pointed down
    // and justify the text
    //
    const float rotationDeg = tickSchema_.alignment == LEFT_JUSTIFIED
                        ? 90.0f
                        : tickSchema_.alignment == RIGHT_JUSTIFIED
                            ?  -90.0f
                            : 0;
    homeplate_.rotate2D(rotationDeg);
}

float Tape::valueToOffsetFromCurrentValue(float val)
{
    float spaceBetweenTicks = height_ / tickSchema_.numTicks;

    float pctOfInterval = (val)/tickSchema_.tickValueInterval;
    return pctOfInterval*spaceBetweenTicks;
}

void Tape::draw(Shader& basicShader, Shader& textShader)
{
    auto projection = hdd::getOrtho();

    // Draw the border as a stencil
    Renderer::beginDefiningStencil();
    border_.setFill(true);
    border_.setColor(BLACK);
    border_.draw(basicShader);
    Renderer::endDefiningStencil();

    // Ticks
    float spaceBetweenTicks = height_ / tickSchema_.numTicks;
    float downValue = fmod(value_, tickSchema_.tickValueInterval*tickSchema_.ticks.size());
    float upValue = tickSchema_.tickValueInterval - downValue;
    float upTickOffset = valueToOffsetFromCurrentValue(upValue);
    float downTickOffset = valueToOffsetFromCurrentValue(downValue);

    for (const auto& range : testRanges)
    {
        if (*range.active)
        {
            float height = spaceBetweenTicks*(range.lowerValue - range.upperValue);
            float offset = position_.y-downTickOffset+(spaceBetweenTicks*((range.lowerValue+range.upperValue)/2.0));
            testRange.setSize(width_, height);
            testRange.setPosition(position_.x, offset);
            testRange.setColor(range.color);
            testRange.draw(basicShader);
        }
    }

    for (int i = 0, k = 0; i < tickSchema_.numTicks+4; i+=tickSchema_.ticks.size(), k++)
    {
        // bool skipUp = false;
        // bool skipDown = false;
        // if (k % tickSchema_.textDisplayInterval == 0)
        // {
        //     float textValue = value_-downValue-(k*tickSchema_.tickValueInterval);
        //     if (textValue < 0.0 && !showNegatives_) { skipUp = true; }
        // }
        // else if (k % tickSchema_.textDisplayInterval == tickSchema_.textDisplayInterval-1) // special case here
        // {
        //     float textValue = value_-downValue+((k+1)*tickSchema_.tickValueInterval);
        // }

        const auto& rect = tickSchema_.ticks[k % tickSchema_.ticks.size()];

        const float x_offset = tickSchema_.alignment == LEFT_JUSTIFIED
                            ? -width_/2.0+rect.width/2.0
                            : tickSchema_.alignment == RIGHT_JUSTIFIED
                                ? width_/2.0-rect.width/2.0
                                : 0;

        basicShader.bind();

        const float downOffset = position_.y-downTickOffset-k*spaceBetweenTicks;
        auto transform = projection * glm::translate(glm::mat4(1), glm::vec3(position_.x+x_offset, downOffset, 0.0f));
        basicShader.setUniformMatrix4fv("u_Projection", transform);
        rect.draw(basicShader);

        float upOffset = position_.y+upTickOffset+k*spaceBetweenTicks;
        transform = projection * glm::translate(glm::mat4(1), glm::vec3(position_.x+x_offset, upOffset-spaceBetweenTicks, 0.0f));
        basicShader.setUniformMatrix4fv("u_Projection", transform);
        rect.draw(basicShader);

        // Draw the text based on the interval
        if (k % tickSchema_.textDisplayInterval == 0)
        {
            float textValue = value_-downValue-(k*tickSchema_.tickValueInterval);
            if (textValue < 0.0 && !showNegatives_) { continue; }
            if (showNegativesAsPositives_) { textValue = std::abs(textValue); }
            numberText_.setText(textValue);
            numberText_.setPosition(position_.x, downOffset);
            numberText_.draw(textShader);

        }
        else if (k % tickSchema_.textDisplayInterval == tickSchema_.textDisplayInterval-1) // special case here
        {
            float textValue = value_-downValue+((k+1)*tickSchema_.tickValueInterval);
            if (textValue < 0.0 && !showNegatives_) { continue; }
            if (showNegativesAsPositives_) { textValue = std::abs(textValue); }
            numberText_.setText(textValue);
            numberText_.setPosition(position_.x, upOffset);
            numberText_.draw(textShader);
        }
    }
    basicShader.bind();
    basicShader.setUniformMatrix4fv("u_Projection", projection); // return the projection back to normal ortho


    // Draw the border
    border_.setFill(false);
    border_.setColor(WHITE);
    border_.setLineWidth(2);
    border_.draw(basicShader);
    Renderer::clearStencil();

    // Now we need a new stencil for the homeplate indicator
    Renderer::beginDefiningStencil();
    homeplate_.setFill(true);
    homeplate_.setColor(BLACK);
    homeplate_.draw(basicShader);
    Renderer::endDefiningStencil();
    GL_CALL(glLineWidth(4));
    homeplate_.setFill(false);
    homeplate_.setColor(WHITE);
    homeplate_.draw(basicShader);


    indicationText_.setText((int)value_);
    indicationText_.draw(textShader);
    Renderer::clearStencil();
}

void Tape::setPosition(float x, float y, float z)
{
    setPosition(glm::vec3(x,y,z));
}
void Tape::setPosition(glm::vec3 vec)
{
    position_ = vec;
    border_.setPosition(vec);
}
void Tape::setMinValue(float value)
{
    minValue_ = value;
}
void Tape::setMaxValue(float value)
{
    maxValue_ = value;
}
void Tape::setSize(float width, float height)
{
    width_ = width;
    height_ = height;
}
void Tape::setValue(float value)
{
    //assert(value >= minValue_ && value <= maxValue_);
    value_ = value;
}


} // end namespace Drawables
