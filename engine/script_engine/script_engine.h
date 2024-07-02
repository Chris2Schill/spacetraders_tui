#pragma once

#include <engine/core/base.h>
#include <engine/scene/entity.h>

#define SOL_EXCEPTIONS_SAFE_PROPAGATION 1
#include <sol/forward.hpp>
#include <sol/sol.hpp>

class ScriptEngine {
public:
    static void init();

    static void on_runtime_start(Scene* scene);
    static void on_runtime_stop(Scene* scene);

    static void shutdown();
    static void on_init_entity(Entity e);
    static void on_start_entity(Entity e);
    static void on_update_entity(Entity e, double dt);
    static void on_stop_entity(Entity e);
    static void on_destroy_entity(Entity e);
    static void on_hover_entity(Entity e, bool hovered);
    static void update_dispatcher();
    static Scene* get_scene();

    static void load_entity_classes(const std::string& dir);

    static void safe_script_file_global(const std::string& script_file);
};
