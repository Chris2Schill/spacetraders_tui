#pragma once

#include <entt/entt.hpp>
#include "scene.h"
#include "components.h"

class Entity {

public:
    Entity() = default;
    Entity(entt::entity handle, Scene* scene);

    template<typename T, typename... Args>
    T& addComponent(Args&&... args) {
        assert(!hasComponent<T>());
        T& component = scene->registry.emplace<T>(entity_handle, std::forward<Args>(args)...);
        return component;
    }

    bool operator==(const Entity& other) const
    {
        return entity_handle == other.entity_handle && scene == other.scene;
    }

    bool operator!=(const Entity& other) const
    {
        return !(*this == other);
    }

    template<typename T>
    bool hasComponent() {
        return scene->registry.try_get<T>(entity_handle);
    }

    template<typename T>
    T& getComponent() {
        assert(hasComponent<T>());
        return scene->registry.get<T>(entity_handle);
    }

    template<typename T>
    T& removeComponent() {
        assert(hasComponent<T>());
        return scene->registry.remove<T>(entity_handle);
    }

    UUID getUUID() { return getComponent<IDComponent>().uuid; }

    operator bool() const { return entity_handle != entt::null; }
    operator entt::entity() const { return entity_handle; }
    operator uint32_t() const { return (uint32_t)entity_handle; }

private:
    entt::entity entity_handle = {entt::null};
    Scene* scene = nullptr;
};
