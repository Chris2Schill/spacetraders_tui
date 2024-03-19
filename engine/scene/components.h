#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include "engine/core/uuid.h"
#include "engine/scene/scene_camera.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>


struct RigidBodyComponent {};

struct CameraComponent {
    SceneCamera camera;
    // int camera;
};

struct TagComponent{
    std::string tag;
};

struct IDComponent{
    UUID uuid;
};

struct TransformComponent{
    glm::vec3 translation  = { 0,0,0};
    glm::vec3 rotation = {0,0,0};
    glm::vec3 scale = {1,1,1};

    TransformComponent() = default;
    TransformComponent(const TransformComponent&) = default;
    TransformComponent(const glm::vec3& translation)
        : translation(translation) {}

    glm::mat4 getTransform() const
    {
        glm::mat4 rotation = glm::toMat4(glm::quat(rotation));

        return glm::translate(glm::mat4(1.0f), translation)
            * rotation
            * glm::scale(glm::mat4(1.0f), scale);
    }

    const glm::vec3& getPosition() { return translation; }
};

template<typename... Args>
struct ComponentGroup
{
};

using AllComponents = ComponentGroup<TagComponent, TransformComponent,
                                     RigidBodyComponent, CameraComponent>;
