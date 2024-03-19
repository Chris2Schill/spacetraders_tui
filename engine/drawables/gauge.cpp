#include "gauge.h"

#include <sstream>
#include <iomanip>
#include <cassert>
#include <iostream>
#include <cmath>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <cmath>

#include "circle.h"
#include "window.h"
#include "logger.h"
#include "colors.h"

#if defined(__arm__)
    #define hdd window
#endif

namespace Drawables
{

Shader& Gauge::getBorderShader()
{
    static Shader s = Shader::create(OPENGL_VERSION)
                             .vertexShader("ring_vertex.shader")
                             .fragmentShader("ring_fragment.shader")
                             .build();

    return s;
}

Gauge::Builder::Builder()
    : precision_(0),
      showIndicator_(true),
      showBorder_(true),
      showReading_(true),
      xpos_(window::center().x),
      ypos_(window::center().y),
      minValue_(0),
      borderWidth_(0.0),
      maxValue_(100),
      rotation_(0.0),
      rotateTickText_(false)
{}
Gauge::Builder& Gauge::Builder::percentOfCircle(const float percent)
{
    percentOfCircle_ = percent;
    return *this;
}
Gauge::Builder& Gauge::Builder::radius(const float r)
{
    radius_ = r;
    return *this;
}
Gauge::Builder& Gauge::Builder::minValue(const float val)
{
    minValue_ = val;
    return *this;
}
Gauge::Builder& Gauge::Builder::maxValue(const float val)
{
    maxValue_ = val;
    return *this;
}
Gauge::Builder& Gauge::Builder::tickSchema(const Gauge::TickSchema ts)
{
    ts_ = ts;
    return *this;
}
Gauge::Builder& Gauge::Builder::position(const float xpos, const float ypos)
{
    xpos_ = xpos;
    ypos_ = ypos;
    return *this;
}
Gauge::Builder& Gauge::Builder::rotation(const float rotation)
{
    rotation_ = rotation;
    return *this;
}
Gauge::Builder& Gauge::Builder::precision(const float precision)
{
    precision_ = precision;
    return *this;
}
Gauge::Builder& Gauge::Builder::borderWidth(const float borderWidth)
{
    borderWidth_ = borderWidth;
    return *this;
}
Gauge::Builder& Gauge::Builder::showIndicator(const bool show)
{
    showIndicator_ = show;
    return *this;
}
Gauge::Builder& Gauge::Builder::showBorder(const bool show)
{
    showBorder_ = show;
    return *this;
}
Gauge::Builder& Gauge::Builder::showReading(const bool show)
{
    showReading_ = show;
    return *this;
}
Gauge::Builder& Gauge::Builder::tickTextScale(const float scale)
{
    tickTextScale_ = scale;
    return *this;
}
Gauge::Builder& Gauge::Builder::rotateTickText(const bool rot)
{
    rotateTickText_ = rot;
    return *this;
}
std::shared_ptr<Gauge> Gauge::Builder::build()
{
    return std::make_shared<Drawables::Gauge>(radius_, percentOfCircle_, minValue_, maxValue_,
                                             ts_, xpos_, ypos_, rotation_, borderWidth_, precision_,
                                             showIndicator_, showBorder_, showReading_, tickTextScale_, rotateTickText_);
}

Gauge::Gauge(float radius, float percentOfCircle, float min, float max,
             TickSchema ticks, float xpos, float ypos, float rotation, float borderWidth, int precision,
             bool showIndicator, bool showBorder, bool showReading, float tickTextScale, bool rotateTickText)
    : radius_(radius),
    minValue_(min),
    maxValue_(max),
    worldPosX_(xpos),
    worldPosY_(ypos),
    rotation_(rotation),
    currentValue_(0.0f),
    percentOfCircle_(percentOfCircle),
    tickSchema_(ticks),
    border_(radius*2.0, radius*2.0),
    indicator_(window::center().x, window::center().y,radius*0.05),
    reading(Text("0.0", radius*0.85, -radius*0.8, 0.00875f*radius, WHITE)),
    // tickText(Text("0", 0, 0, 0.00075*radius, WHITE)),
    tickText(Text("0", 0, 0, tickTextScale, WHITE)),
    precision_(precision),
    borderWidth_(borderWidth),
    showIndicator_(showIndicator),
    showBorder_(showBorder),
    showReading_(showReading),
    rotateTickText_(rotateTickText)
{
    assert(minValue_ < maxValue_);
    assert(percentOfCircle_ >= 0.0 && percentOfCircle_ <= 1.0);
    
    // Pull out center of circle using GL_TRIANGLE_FAN to create indicator shape
    indicator_.vertices[0].position.y = window::center().y-radius;
    indicator_.updateVertexBuffer();

    updateTextReading();
}

void Gauge::setPercent(float percent)
{
    assert(percent >= 0.0 && percent <= 100.0);
    currentValue_ = percentToValue(percent);

    updateTextReading();
}

void Gauge::setValue(float value)
{
    assert (value >= minValue_ && value <= maxValue_); 
    currentValue_ = value;

    updateTextReading();
}

void Gauge::updateTextReading()
{
    std::stringstream ss;
    if (precision_ > 0)
    {
        ss << std::fixed << std::setprecision(precision_) << currentValue_;
    }
    else
    {
        ss << std::round(currentValue_);
    }
    reading.setText(ss.str());
}

void Gauge::draw(Shader& basicShader, Shader& textShader)
{
    auto projection = window::getOrtho();
    glm::mat4 modelToWorld = glm::translate(glm::mat4(1), glm::vec3(worldPosX_, worldPosY_, 0)) * 
                             glm::rotate(glm::mat4(1), glm::radians(rotation_), glm::vec3(0.0f,0.0f,-1.0f));

    // Ticks
    assert(tickSchema_.ticks.size() == tickSchema_.translationFromCenterOffset.size());
    basicShader.bind();
    basicShader.setUniform1f("u_UseUniformColor", true);
    for (int i = 0; i < tickSchema_.numTicks;)
    {
        for (unsigned j = 0; j < tickSchema_.ticks.size() && i < tickSchema_.numTicks; ++j, ++i)
        {
            // We use "blank" ticks to help us format unique looking gauges. In these cases, dont try to draw these ticks
            if (tickSchema_.ticks[j].width == 0 && tickSchema_.ticks[j].height == 0) { continue; }

            // calculate the rotation from 0 for this tick
            float rotation = percentOfCircle_*360.0 / (tickSchema_.numTicks-1) * i;

            // Pick which color the tick will be based on schema
            glm::vec4& c = rotation < tickSchema_.angleToTransitionToColor2
                            ? tickSchema_.colors[0]
                            : rotation< tickSchema_.angleToTransitionToColor3
                                ? tickSchema_.colors[1]
                                : tickSchema_.colors[2];

            // Set the color
            basicShader.bind();
            basicShader.setUniform4f("u_Color", c.r,c.g,c.b,c.a);

            // Get the rectangle obj and draw it
            const auto& rect = tickSchema_.ticks[j];
            auto model = projection * modelToWorld *  
                glm::rotate(glm::mat4(1), glm::radians(rotation), glm::vec3(0, 0, -1)) *
                glm::translate(glm::mat4(1), glm::vec3(0, -radius_ + rect.height/2.0*1.15 + tickSchema_.translationFromCenterOffset[j], 0));
            basicShader.setUniformMatrix4fv("u_Projection", model);
            rect.draw(basicShader);

            // tick text
            if (tickSchema_.tickTextInterval > 0 && i % tickSchema_.tickTextInterval == 0 && 
                (percentOfCircle_ == 1.0 && tickSchema_.numTicks % 2 != 0 && i < tickSchema_.numTicks-1)) // don't draw the last one if it would overlap with first
            {
                float tickValue = (maxValue_ - minValue_)/tickSchema_.numTicks * i;
                textShader.bind();
                model = projection * modelToWorld *  
                    glm::rotate(glm::mat4(1), glm::radians(rotation), glm::vec3(0, 0, -1)) *
                    glm::translate(glm::mat4(1), glm::vec3(0, -radius_ + rect.height/2.0*4 + tickSchema_.translationFromCenterOffset[j], 0)) *
                    glm::rotate(glm::mat4(1), glm::radians(rotateTickText_ ? 180.0f : -rotation-rotation_), glm::vec3(0, 0, -1));
                textShader.setUniformMatrix4fv("u_Projection", model);
                tickText.setText(std::round(tickValue));
                tickText.setColor(c);
                tickText.draw(textShader);
            }
        }
    }

    // Border
    if (showBorder_)
    {
        static const float target_width = window::WIDTH;
        static const float target_height = window::HEIGHT;
        float V = (float)window::WIDTH / (float)window::HEIGHT;
        float A = target_width/target_height;

        float radius;
        glm::vec2 translation;
        if (V >= A)
        {
            radius = radius_ / window::WIDTH;
            translation = glm::vec2(worldPosX_*2.0/window::WIDTH, worldPosY_*2.0/window::HEIGHT/V);
        }
        else 
        {
            radius = radius_ / window::WIDTH * V/A;
            translation = glm::vec2(worldPosX_*2.0/window::WIDTH*V/A, worldPosY_*2.0/window::HEIGHT/A);
        }

        // LOG(DEBUG) << "WIDTH = " << window::WIDTH;
        // LOG(DEBUG) << "HEIGHT = " << window::HEIGHT;

        auto transform = projection * modelToWorld;

        auto& borderShader = getBorderShader();
        borderShader.bind();
        borderShader.setUniformMatrix4fv("u_Projection", transform);
        borderShader.setUniform4f("u_Color1", tickSchema_.colors[0].r, tickSchema_.colors[0].g, tickSchema_.colors[0].b, tickSchema_.colors[0].a);
        borderShader.setUniform4f("u_Color2", tickSchema_.colors[1].r, tickSchema_.colors[1].g, tickSchema_.colors[1].b, tickSchema_.colors[1].a);
        borderShader.setUniform4f("u_Color3", tickSchema_.colors[2].r, tickSchema_.colors[2].g, tickSchema_.colors[2].b, tickSchema_.colors[2].a);
        borderShader.setUniform1f("u_Radius",    radius);
        borderShader.setUniform1f("u_LineWidth", borderWidth_ == 0.0 ? radius*0.13 : borderWidth_);
        borderShader.setUniform1f("u_PercentOfCircle", percentOfCircle_);
        borderShader.setUniform1f("u_TransitionAngle1", glm::radians(tickSchema_.angleToTransitionToColor2));
        borderShader.setUniform1f("u_TransitionAngle2", glm::radians(tickSchema_.angleToTransitionToColor3));
        borderShader.setUniform2f("u_Translation", translation.x, translation.y);
        borderShader.setUniform1f("u_Rotation", glm::radians(rotation_));
        borderShader.setUniform2f("u_Resolution", window::WIDTH, window::HEIGHT);
        border_.draw(borderShader);
    }

    // Indicator
    if (showIndicator_)
    {
        basicShader.bind();
        auto transform = projection * modelToWorld *
            glm::rotate(glm::mat4(1), glm::radians(percentOfCircle_*360.0f/100.0f* valueToPercent(currentValue_)), glm::vec3(0,0,-1));
        basicShader.setUniform1i("u_UseUniformColor", true);
        basicShader.setUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
        basicShader.setUniformMatrix4fv("u_Projection", transform);
        indicator_.draw(basicShader);
    }

    // Text
    if (showReading_)
    {
        auto transform = projection * modelToWorld;
        textShader.bind();
        textShader.setUniformMatrix4fv("u_Projection", transform);
        reading.draw(textShader);
    }

    // Reset the shaders back to default
    projection = hdd::getOrtho();
    basicShader.bind();
    basicShader.setUniformMatrix4fv("u_Projection", projection);
    basicShader.setUniform1f("u_UseUniformColor", false);
    textShader.bind();
    textShader.setUniformMatrix4fv("u_Projection", projection);

}


} // end namespace Drawables
