#pragma once

#include <memory>
#include <string>
#include <vector>
#include <renderer/renderer.h>

#include "drawables/rect.h"
#include "drawables/circle.h"
#include "drawables/text.h"



namespace Drawables
{

class Gauge
{
public:

    struct TickSchema
    {
        std::vector<Rectangle> ticks; std::string schema = "1"; std::vector<float> translationFromCenterOffset = { 0.0f };
        int numTicks;
        std::vector<glm::vec4> colors;
        float angleToTransitionToColor2;
        float angleToTransitionToColor3;
        int tickTextInterval;
    };

    class Builder
    {
        Gauge::TickSchema ts_;
        float percentOfCircle_;
        float minValue_;
        float maxValue_;
        float currentValue_;
        float radius_;
        float xpos_;
        float ypos_;
        float rotation_;
        float precision_;
        float borderWidth_;
        bool showIndicator_;
        bool showBorder_;
        bool showReading_;
        float tickTextScale_;
        bool rotateTickText_;
    public:
        Builder();
        Builder& percentOfCircle(const float percent);
        Builder& radius(const float radius);
        Builder& minValue(const float minVal);
        Builder& maxValue(const float maxVal);
        Builder& tickSchema(const Gauge::TickSchema ts);
        Builder& position(const float xpos, const float ypos);
        Builder& precision(const float precision);
        Builder& borderWidth(const float borderWidth);
        Builder& showIndicator(const bool show);
        Builder& showBorder(const bool show);
        Builder& showReading(const bool show);
        Builder& rotation(float rot);
        Builder& tickTextScale(const float scale);
        Builder& rotateTickText(const bool rot);
        std::shared_ptr<Gauge> build();
    };
private:

    Rectangle border_;
    Circle indicator_; // Using a circle (GL_TRIANGLE_FAN) with its center point translated out from the center
    TickSchema tickSchema_;
    Drawables::Text reading;
    Drawables::Text tickText;
    int precision_;

    // How far around the gauge outline should wrap. 100% means full circle
    float percentOfCircle_;

    float worldPosX_;
    float worldPosY_;
    float rotation_;
    float minValue_;
    float maxValue_;
    float currentValue_;
    float radius_;
    float borderWidth_;
    bool showIndicator_;
    bool showBorder_;
    bool showReading_;
    bool rotateTickText_;


    float percentToValue(float percent)
    {
        return (percent/100) * (maxValue_-minValue_) + minValue_;
    }

    float valueToPercent(float value)
    {
        return (value - minValue_) / (maxValue_-minValue_) * 100;
    }
public:

    Gauge(float radius, float percentOfCircle, float min, float max, TickSchema ticks, float xpos, float ypos, float rotation, float borderWidth, int precision, bool showIndicator, bool showBorder, bool showReading, float tickTextScale, bool rotateTickText);

    void setPosition(float x, float y)
    {
        worldPosX_ = x; 
        worldPosY_ = y;
    }
    float getRadius() { return radius_; }
    void setPosition(glm::vec2 pos) { worldPosX_ = pos.x, worldPosY_ = pos.y; }
    glm::vec2 getPosition() { return glm::vec2(worldPosX_, worldPosY_);}
    void setPercent(float percent);
    void setValue(float value);
    void updateTextReading();
    void overrideText(std::string text) { reading.setText(text);}
    void setRotation(float rotDeg) { rotation_ = rotDeg; }
    void draw(Shader& shader, Shader& textShader);

    static Shader& getBorderShader();
};


} // end namespace Drawables
