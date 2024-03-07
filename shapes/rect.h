#pragma once

#include <vector>
#include <glm/vec2.hpp>

#include "shape.h"

namespace Shapes
{

    // Will give you a centered rectangle
    std::shared_ptr<Shape> createRectangle(float width, float height);

    // This overload allows you to specify a x,y location 
    std::shared_ptr<Shape> createRectangle(float xPos, float yPos, float width, float height);

} // end namespace Shapes