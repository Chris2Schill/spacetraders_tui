#pragma once

#include <string_view>
#include <entt/entt.hpp>

#include "engine/core/uuid.h"

class Entity;

class Scene {
public:
    Scene();

    void renderScene(/*Camera*/);

    Entity createEntityWithUUID(UUID uuid, const std::string& name);
    Entity createEntity(const std::string& name);

    Entity createBasicEntity(const std::string& name);

    Entity getPrimaryCameraEntity();


    template<typename... Components>
    auto view() {
        return registry.view<Components...>();
    }

    void startRuntime();
    void stopRuntime();

    void onUpdateSimulation(double dt);
    void onUpdateRuntime(double dt);

    Entity getEntityByUUID(UUID uuid);
    Entity findEntityByName(std::string_view name);

    friend class Entity;

private:
    entt::registry registry;
    std::unordered_map<UUID, entt::entity> entityMap;
    bool is_running = false;
    bool is_paused = false;
};
