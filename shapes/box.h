#pragma once

#include <vector>

#include "shape.h"

namespace Shapes
{

    // Will give you a centered rectangle
    std::shared_ptr<Shape> createBox(float width, float height, float depth);

    // This overload allows you to specify a x,y location 
    std::shared_ptr<Shape> createBox(float xPos, float yPos, float zPos,
                                     float width, float height, float depth);

} // end namespace Shapes