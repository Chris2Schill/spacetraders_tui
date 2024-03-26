#pragma once

#include <engine/core/base.h>

#define SOL_EXCEPTIONS_SAFE_PROPAGATION 1

#include <sol/forward.hpp>
#include <sol/sol.hpp>
#include <engine/scene/entity.h>

// class LuaScript
// {
//     Ref<sol::protected_function> on_start;
//     Ref<sol::protected_function> on_update;
// };

class ScriptEngine {
public:
    static void init();

    static void on_runtime_start(Scene* scene);
    static void on_runtime_stop(Scene* scene);

    static void shutdown();
    static void on_create_entity(Entity e);
    static void on_update_entity(Entity e, double dt);
    static Scene* get_scene();

    static void load_entity_classes();
    static bool class_exists(const std::string& class_name);
};
