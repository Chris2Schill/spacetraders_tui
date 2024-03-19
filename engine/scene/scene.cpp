#include "scene.h"

#include "components.h"
#include "entity.h"

Scene::Scene()
{
    auto ent = createEntity("PrimaryCamera");
    auto& cam = ent.addComponent<SceneCamera>();
    cam.SetPerspective(90, 0.5, 200);
    cam.SetViewportSize(500, 500);
}

Entity Scene::createEntityWithUUID(UUID uuid, const std::string& name) {
    Entity e = {registry.create(),this};
    e.addComponent<IDComponent>(uuid);
    e.addComponent<TransformComponent>();
    auto& tag = e.addComponent<TagComponent>();
    tag.tag = name.empty() ? "Entity" : name;
    entityMap[uuid] = e;
    return e;
}

Entity Scene::createEntity(const std::string& name)
{
    return createEntityWithUUID(UUID(), name);
}

Entity Scene::getPrimaryCameraEntity()
{
    auto view = registry.view<SceneCamera, TagComponent>();
    for (auto ent : view) {
        auto& tag = view.get<TagComponent>(ent);
        if (tag.tag == "PrimaryCamera") {
            return Entity{ent, this};
        }
    }
    throw std::runtime_error("Could not find primary camera entity");
}
