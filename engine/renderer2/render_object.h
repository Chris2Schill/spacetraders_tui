#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "render_command.h"

struct Material
{

};

struct RenderObject
{
    Material material;

    std::vector<RenderCommand> renderCommands;
};
