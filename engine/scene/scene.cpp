#include "scene.h"

#include "components.h"
#include "entity.h"

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
    return Entity();
}
