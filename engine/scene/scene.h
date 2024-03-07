#pragma once

#include <entt/entt.hpp>

#include "engine/core/uuid.h"

class Entity;

class Scene {
public:

    void renderScene(/*Camera*/){}

    Entity createEntityWithUUID(UUID uuid, const std::string& name);
    Entity createEntity(const std::string& name);

    Entity getPrimaryCameraEntity();

    friend class Entity;

private:
    entt::registry registry;
    std::unordered_map<UUID, entt::entity> entityMap;
};
