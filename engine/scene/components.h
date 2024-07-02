#pragma once

#include "engine/core/uuid.h"
#include "engine/core/log.h"
#include "engine/scene/scene_camera.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/io.hpp>
#include <sol/sol.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>
#include <sstream>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

struct RigidBodyComponent {};

struct CameraComponent {
    // SceneCamera camera;
    sf::View view;
    static constexpr auto in_place_delete = true;
};

struct TagComponent {
    std::string tag;

    static constexpr auto in_place_delete = true;
};

struct PriorityComponent {
    int priority;
    static constexpr auto in_place_delete = true;
};

struct IDComponent {
    UUID uuid;

    static constexpr auto in_place_delete = true;
};

struct CircleComponent {
    CircleComponent() = default;

    CircleComponent(float radius) :shape(radius) {  }
    CircleComponent(float radius, int pointCount) : shape(radius, pointCount) {  }

    sf::CircleShape shape;
    glm::vec4 fillColor = {255,255,255,255};
    glm::vec4 outlineColor {255,255,255,255};
    static constexpr auto in_place_delete = true;
};

// struct RectComponent {
//     glm::vec2 dimensions;
// };

struct SpriteComponent {
    SpriteComponent() = default;
    SpriteComponent(const std::string& filename) {
        texture = create_ref<sf::Texture>();
        if (texture->loadFromFile(filename)) {
            texture->setSmooth(true);
            sprite = create_ref<sf::Sprite>(*texture);
        }
        else {
            LOG_CORE_ERROR("Failed to load sprite file: {}", filename);
        }
    }
    Ref<sf::Sprite>  sprite;
    Ref<sf::Texture> texture;
    glm::vec2        dimensions{30,30};
    glm::vec4        color{255,255,255,255};
    static constexpr auto in_place_delete = true;
};

struct TransformComponent {
    glm::vec3 translation = {0, 0, 0};
    glm::vec3 rotation = {0, 0, 0};
    glm::vec3 scale = {1, 1, 1};

    TransformComponent() = default;
    TransformComponent(const TransformComponent&) = default;
    TransformComponent(const glm::vec3& translation) : translation(translation) {}

    glm::mat4 getTransform() const {
        glm::mat4 rotation = glm::toMat4(glm::quat(rotation));

        return glm::translate(glm::mat4(1.0f), translation) * rotation * glm::scale(glm::mat4(1.0f), scale);
    }

    const glm::vec3& getPosition() const { return translation; }

    [[nodiscard]] std::string to_string() const {
        std::stringstream ss;
        ss << "Translation=" << translation << ", Rotation=" << rotation << ", Scale=" << scale;
        return ss.str();
    }


    static constexpr auto in_place_delete = true;

};

template <typename... Args> struct ComponentGroup {};

struct ScriptComponent {
    std::string class_name;
    sol::table  instance;

    static constexpr auto in_place_delete = true;
};

// class ScriptableEntity;

// struct LuaScriptComponent {
//     ScriptableEntity* instance = nullptr;
//
//     std::function<ScriptableEntity*()> instantiate_script();
//     std::function<void(ScriptableEntity*)> destroy_script();
//
//     template <typename T> void bind() {
//
//         instantiate_script = []() { return static_cast<ScriptableEntity*>(new T()); };
//         destroy_script = [](LuaScriptComponent* nsc) {
//             delete nsc->instance;
//             nsc->instance = nullptr;
//         };
//     }
// };

using AllComponents = ComponentGroup<TagComponent, TransformComponent, RigidBodyComponent, CameraComponent, ScriptComponent>;
