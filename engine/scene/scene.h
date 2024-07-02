#pragma once

#include <string_view>
#include <queue>
#include <entt/entt.hpp>

#include "engine/core/base.h"
#include "engine/core/uuid.h"
#include "engine/input/coordinate_conversions.h"

class Entity;

struct SceneData;

class Scene {
public:
    Scene();

    void renderScene(Entity camera);

    Entity createEntityWithUUID(UUID uuid, const std::string& name);
    Entity createEntity(const std::string& name);
    Entity createEntityActor(const std::string& name, const std::string& script);

    Entity createBasicEntity(const std::string& name);

    void destroyEntity(Entity e);

    Entity getPrimaryCameraEntity();


    template<typename... Components>
    auto view() {
        return registry.view<Components...>();
    }

    void startRuntime();
    void stopRuntime();

    void step(double dt);

    void onUpdateWindow();
    void onUpdateSimulation(double dt);
    void onUpdateRuntime(double dt);

    Entity getEntityByUUID(UUID uuid);
    Entity findEntityByName(std::string_view name);

    friend class Entity;
    friend class ScriptEngine;

    void init_script(entt::registry& reg, entt::entity entity);
    void release_script(entt::registry& reg, entt::entity entity);

    bool isRunning() const { return is_running; }

    double deltaTime() const;

    // TODO: Move
    Coord<WorldSpace> get_mouse_position();

private:

    entt::registry registry;
    std::unordered_map<UUID, entt::entity> entityMap;
    std::queue<Entity> toBeDestroyed;
    bool is_running = false;
    bool is_paused = true;

    Ref<SceneData> pData;
};
