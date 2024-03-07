#pragma once

#include <vector>
#include <cstdint>
#include "render_object.h"

struct Entity
{
    uint64_t              id;
    // Transform             transform;
    std::vector<Vertex>   vertices;
    std::vector<uint32_t> indices;
};

struct World
{
    std::vector<Entity> entities;
};

std::vector<RenderCommand> generate_render_commands(const World& world)
{
    std::vector<RenderCommand> cmds;
    for (const auto& objs : world.entities)
    {
        // cmds.emplace_back(obsj)
    }

    return cmds;
}
