#pragma once

#include <entt/entt.hpp>

#include "engine/core/uuid.h"

class Entity;

class Scene {
public:
    Scene();

    void renderScene(/*Camera*/){}

    Entity createEntityWithUUID(UUID uuid, const std::string& name);
    Entity createEntity(const std::string& name);

    Entity getPrimaryCameraEntity();


    template<typename... Components>
    auto view() {
        return registry.view<Components...>();
    }

    friend class Entity;

private:
    entt::registry registry;
    std::unordered_map<UUID, entt::entity> entityMap;
};
