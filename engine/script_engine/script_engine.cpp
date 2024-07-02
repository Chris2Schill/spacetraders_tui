#include "engine/script_engine/script_engine.h"

#include "engine/core/log.h"
#include "engine/script_engine/components_lua_bindings.h"
#include "engine/script_engine/entt_dispatcher_lua_bindings.hpp"
#include "engine/script_engine/entt_registry_lua_bindings.hpp"
#include "engine/script_engine/glm_lua_bindings.h"
#include "engine/script_engine/imgui_lua_bindings.h"
#include "engine/script_engine/log_bindings.h"
#include "engine/input/input_system.h"
#include <filesystem>

// struct ScriptClass {
//     std::string script_file;
// };

struct ScriptInstance {
    ScriptInstance(const std::string& script_file, sol::table& self, Entity entity, sol::state* lua,
                   entt::registry& reg, Scene* scene)
        : lua(lua), entity(entity), scene(scene), script_file(script_file), reg(&reg), self(self) {

        env = sol::environment(*lua, sol::create, lua->globals());
        reload();
        last_modified = std::filesystem::last_write_time(script_file);
    }
    ~ScriptInstance() {
        if (hooks.destroy.valid()) {
            hooks.destroy(self, env);
        }
        self.abandon();
        LOG_CORE_TRACE("Destroyed ScriptInstance: EntityId={}", entity.getUUID());
    }

    void invoke_init() {
        if (hooks.init.valid()) {
            hooks.init(self, env);
        }
    }
    void invoke_start() {
        if (hooks.start.valid()) {
            // if (!started) {
                hooks.start(self, env);
                started = true;
            // }
        } else {
            LOG_CORE_WARN("No start function for {}", script_file);
        }
    }
    void invoke_update(double dt) { hooks.update(self, dt, env); }
    void invoke_stop() {
        if (hooks.stop.valid()) {
            // if (started) {
                hooks.stop(self, env);
                started = false;
            // }
        }
    }
    void invoke_on_hover_enter() {
        if (hooks.on_hover_enter.valid()) {
            hooks.on_hover_enter(self, env);
        }
    }
    void invoke_on_hover_leave() {
        if (hooks.on_hover_leave.valid()) {
            hooks.on_hover_leave(self, env);
        }
    }
    void invoke_on_scrolled(InputSystem::MouseScroll val) {
        if (hooks.on_scrolled.valid()) {
            hooks.on_scrolled(self, val, env);
        }
    }

    void reload() {
        LOG_CORE_TRACE("Loading script for instance: {}", script_file);
        self = lua->safe_script_file(script_file, env);

        self["entity"] = std::ref(entity);
        self["scene"] = std::ref(*scene);

        hooks.init = self["init"];
        hooks.start = self["start"];
        hooks.update = self["update"];
        hooks.stop = self["stop"];
        hooks.destroy = self["destroy"];
        hooks.on_hover_enter = self["on_hover_enter"];
        hooks.on_hover_leave = self["on_hover_leave"];
        hooks.on_scrolled = self["on_scrolled"];

        sol::set_environment(env, hooks.init);
        sol::set_environment(env, hooks.start);
        sol::set_environment(env, hooks.update);
        sol::set_environment(env, hooks.stop);
        sol::set_environment(env, hooks.destroy);

        sol::set_environment(env, hooks.on_hover_enter);
        sol::set_environment(env, hooks.on_hover_leave);
        sol::set_environment(env, hooks.on_scrolled);
    }

    void reload_if_modified() {
        auto last_write_time = std::filesystem::last_write_time(script_file);
        if (last_write_time > last_modified) {
            LOG_CORE_INFO("RELOADING LUA: {}", script_file);
            last_modified = last_write_time;
            reload();
            invoke_init();
            invoke_start();
        }
    }

    struct hooks {
        sol::safe_function init;
        sol::safe_function start;
        sol::safe_function update;
        sol::safe_function stop;
        sol::safe_function destroy;

        sol::safe_function on_hover_enter;
        sol::safe_function on_hover_leave;
        sol::safe_function on_scrolled;
    } hooks;

    sol::state* lua;
    Entity entity;
    Scene* scene = nullptr;
    std::string script_file;
    entt::registry* reg = nullptr;
    sol::environment env;
    sol::table& self;
    std::filesystem::file_time_type last_modified = std::filesystem::file_time_type::min();
    bool hovered = false;
    bool started = false;
};

void my_panic(sol::optional<std::string> maybe_msg) {}

struct ScriptEngineData {
    sol::state lua;
    Scene* scene = nullptr;
    std::unordered_map<UUID, Ref<ScriptInstance>> entity_instances;
    entt::dispatcher dispatcher;
};
static ScriptEngineData* s_Data = nullptr;

static sol::table getEntityInstance(UUID uuid) { return s_Data->entity_instances[uuid]->self; }

void ScriptEngine::init() {
    s_Data = new ScriptEngineData();

    s_Data->lua.open_libraries();
    s_Data->lua.set_exception_handler(
        [](lua_State* L, sol::optional<const std::exception&> maybe_exception, sol::string_view description) {
            if (maybe_exception) {
                LOG_CORE_ERROR("Exception: Description - {}", description);
            }
            return sol::stack::push(L, description);
        });
    sol::state lua(sol::c_call<decltype(&my_panic), &my_panic>);

    SCION_CORE::Scripting::GLMBindings::CreateGLMBindings(s_Data->lua);
    sol_ImGui::Init(s_Data->lua);
    lua_bind_log_functions(s_Data->lua);

#define AUTO_ARG(x) decltype(x), x
    s_Data->lua.require("registry", sol::c_call<AUTO_ARG(&open_registry)>, false);
    s_Data->lua.require("dispatcher", sol::c_call<AUTO_ARG(&open_dispatcher)>, false);
#undef AUTO_ARG
    s_Data->lua["dispatcher"] = std::ref(s_Data->dispatcher);
    s_Data->lua["get_mouse_position"] = [](){
        return s_Data->scene->get_mouse_position().pos;
    };

    register_components(s_Data->lua);
}

void ScriptEngine::shutdown() { delete s_Data; }

void ScriptEngine::on_runtime_start(Scene* scene) { s_Data->scene = scene; }

void ScriptEngine::on_runtime_stop(Scene* scene) {
    s_Data->scene = nullptr;
    s_Data->entity_instances.clear();
}

void ScriptEngine::on_init_entity(Entity entity) {
    auto& sc = entity.getComponent<ScriptComponent>();

    sol::table& inst = sc.instance;

    UUID uuid = entity.getUUID();
    auto iter = s_Data->entity_instances.find(uuid);
    if (iter == s_Data->entity_instances.end()) {
        Ref<ScriptInstance> instance =
            create_ref<ScriptInstance>("/home/cschilling/spacetraders/spacetraders_tui/gui/scripts/" + sc.class_name, inst,
                    entity, &s_Data->lua, s_Data->scene->registry, s_Data->scene);

        s_Data->entity_instances[uuid] = instance;
        instance->invoke_init();
    }
}

void ScriptEngine::on_start_entity(Entity e)
{
    s_Data->entity_instances[e.getUUID()]->invoke_start();
}

void ScriptEngine::on_update_entity(Entity entity, double dt) {
    UUID uuid = entity.getUUID();

    auto iter = s_Data->entity_instances.find(uuid);
    if (iter != s_Data->entity_instances.end()) {
        Ref<ScriptInstance> instance = iter->second;
        instance->reload_if_modified();
        instance->invoke_update(dt);
    }
}

void ScriptEngine::on_stop_entity(Entity e)
{
    s_Data->entity_instances[e.getUUID()]->invoke_stop();
}

void ScriptEngine::on_destroy_entity(Entity entity) {
    auto iter = s_Data->entity_instances.find(entity.getUUID());
    if (iter != s_Data->entity_instances.end()) {
        s_Data->entity_instances.erase(iter);
    }
    // TODO: Might want to move this...
    s_Data->lua.collect_garbage();
}

void ScriptEngine::on_hover_entity(Entity e, bool hovered)
{
    auto iter = s_Data->entity_instances.find(e.getUUID());
    if (iter != s_Data->entity_instances.end()) {
        Ref<ScriptInstance> instance = iter->second;
        if (!instance->hovered && hovered) {
            instance->invoke_on_hover_enter();
        }
        else if (instance->hovered && !hovered) {

            instance->invoke_on_hover_leave();
        }

        if (hovered && ImGui::GetIO().MouseWheel != 0) {
            InputSystem::MouseScroll ms = ImGui::GetIO().MouseWheel > 0 ? InputSystem::WHEEL_UP : InputSystem::WHEEL_DOWN;
            instance->invoke_on_scrolled(ms);
        }

        instance->hovered = hovered;
    }
}

Scene* ScriptEngine::get_scene() { return s_Data->scene; }

// void ScriptEngine::load_entity_classes(const std::string& dir) {
//     std::ranges::for_each(
//         std::filesystem::directory_iterator{dir},
//         [](const std::filesystem::directory_entry& dir_entry) {
//             if (dir_entry.is_directory()) {
//                 load_entity_classes(dir_entry.path());
//             }
//
//             if (dir_entry.is_regular_file() && dir_entry.path().extension() == ".lua") {
//                 LOG_CORE_TRACE("loading {}", dir_entry.path());
//
//                 Ref<ScriptClass> sc = create_ref<ScriptClass>();
//                 sc->script_file = dir_entry.path();
//
//                 s_Data->entity_classes[dir_entry.path()] = sc;
//             }
//         });
// }

void ScriptEngine::safe_script_file_global(const std::string& script_file) {
    s_Data->lua.safe_script_file(script_file);
}

void ScriptEngine::update_dispatcher() { s_Data->dispatcher.update(); }
