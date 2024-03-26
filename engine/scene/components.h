#pragma once

#include "engine/core/uuid.h"
#include "engine/scene/scene_camera.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <sol/sol.hpp>
#include <string>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

struct RigidBodyComponent {};

struct CameraComponent {
    SceneCamera camera;
    // int camera;
};

struct TagComponent {
    std::string tag;
};

struct IDComponent {
    UUID uuid;
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

    const glm::vec3& getPosition() { return translation; }
};

template <typename... Args> struct ComponentGroup {};

struct ScriptComponent {
    ScriptComponent(const std::string& class_name) : class_name(class_name) {}

    std::string class_name;

    // sol::state* lua;
    // std::string script_file;
    // time_t last_modified = 0;
    //
    // void setup(sol::state* lua_state, const std::string& script) {
    //     lua = lua_state;
    //     script_file = script;
    //     lua->set_function("getTag", [this]() { return script_file; });
    //     // (*lua)["transform"] = transform;
    //     // lua->set_function("getTransform", [this](){ return pos(); });
    //
    //     // lua->new_usertype<Transform>("Transform", "x", &Transform::x, "y",
    //     //                              &Transform::y,       // the usual
    //     //                              "z", &Transform::z); // the usual
    //
    //     // (*lua)["transform"] = std::ref(transform);
    //     reload();
    // }
    //
    // void reload() { lua->script_file(script_file); }
    //
    // // bool script_was_modified() {
    // //     struct stat sbuf;
    // //     stat(script_file.c_str(), &sbuf);
    // //     if (sbuf.st_mtime > last_modified) {
    // //         std::cout << "RELOADING LUA\n";
    // //         last_modified = sbuf.st_mtime;
    // //         return true;
    // //     }
    // //
    // //     return false;
    // // }
};

class ScriptableEntity;

struct LuaScriptComponent {
    ScriptableEntity* instance = nullptr;

    std::function<ScriptableEntity*()> instantiate_script();
    std::function<void(ScriptableEntity*)> destroy_script();

    template <typename T> void bind() {

        instantiate_script = []() { return static_cast<ScriptableEntity*>(new T()); };
        destroy_script = [](LuaScriptComponent* nsc) {
            delete nsc->instance;
            nsc->instance = nullptr;
        };
    }
};

using AllComponents = ComponentGroup<TagComponent, TransformComponent, RigidBodyComponent, CameraComponent>;
