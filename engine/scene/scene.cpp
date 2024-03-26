#include "scene.h"

#include "components.h"
#include <iostream>
#include "engine/scene/entity.h"
#include "engine/script_engine/script_engine.h"

Scene::Scene() {
    auto ent = createEntity("PrimaryCamera");
    auto& cam = ent.addComponent<SceneCamera>();
    cam.SetPerspective(90, 0.5, 200);
    cam.SetViewportSize(500, 500);
}

Entity Scene::createEntityWithUUID(UUID uuid, const std::string& name) {
    Entity e = {registry.create(), this};
    e.addComponent<IDComponent>(uuid);
    e.addComponent<TransformComponent>();
    auto& tag = e.addComponent<TagComponent>();
    tag.tag = name.empty() ? "Entity" : name;
    entityMap[uuid] = e;
    return e;
}

Entity Scene::createEntity(const std::string& name) { return createEntityWithUUID(UUID(), name); }

Entity Scene::createBasicEntity(const std::string& name)
{
    Entity e = {registry.create(), this};
    auto uuid = UUID();
    e.addComponent<IDComponent>(uuid);
    auto& tag = e.addComponent<TagComponent>();
    tag.tag = name.empty() ? "Entity" : name;
    entityMap[uuid] = e;
    return e;
}

Entity Scene::getPrimaryCameraEntity() {
    auto view = registry.view<SceneCamera, TagComponent>();
    for (auto ent : view) {
        auto& tag = view.get<TagComponent>(ent);
        if (tag.tag == "PrimaryCamera") {
            return Entity{ent, this};
        }
    }
    throw std::runtime_error("Could not find primary camera entity");
}

void Scene::startRuntime()
{
    is_running = true;

    //start_physics();
    ScriptEngine::on_runtime_start(this);

    auto view = registry.view<ScriptComponent>();
    for (auto e : view) {
        
        Entity entity = {e, this};
        ScriptEngine::on_create_entity(entity);
    }
}

void Scene::stopRuntime()
{
    is_running = false;
    ScriptEngine::on_runtime_stop(this);
}

void Scene::onUpdateSimulation(double dt)
{
    renderScene();
}

void Scene::onUpdateRuntime(double dt)
{
    if (!is_paused) {

        auto view = registry.view<ScriptComponent>();
        for (auto e : view) {
            Entity entity = {e, this};
            ScriptEngine::on_update_entity(entity, dt);
        }
    }
}

void Scene::renderScene(/*Camera*/)
{
    // Draw ImGui Windows
    // {
    //     auto view = registry.view<ImGuiRenderComponent>();
    // }
}

Entity Scene::getEntityByUUID(UUID uuid) {
    auto iter = entityMap.find(uuid);
    if (iter == entityMap.end()) {
        std::cerr << "Could not find entity with UUID " << uuid << "\n";
        return {};
    }
    return {iter->second, this};
}

Entity Scene::findEntityByName(std::string_view name) {
    auto view = registry.view<TagComponent>();
    for (auto entity : view) {
        const TagComponent& tc = view.get<TagComponent>(entity);
        if (tc.tag == name)
            return Entity{entity, this};
    }
    return {};
}
