#include "engine/script_engine/script_engine.h"

#include "engine/script_engine/glm_lua_bindings.h"
#include "engine/script_engine/imgui_lua_bindings.h"
#include <filesystem>

struct ScriptClass {
    std::string script_file;
};

// void LoadImguiBindings();
// const char* RunString(const char* szLua);
// extern lua_State* lState;
// extern std::deque<int> endStack;
// void ImEndStack(int type);




struct ScriptInstance {
    ScriptInstance(Ref<ScriptClass> script_class, Entity entity, sol::state* lua)
        : lua(lua), script_class(script_class) {
            std::cout << "Creating script instnace\n";
        reload();
    }

    void invoke_on_create() { lua->safe_script("OnCreate()", *env); }
    void invoke_on_update() { lua->safe_script("OnUpdate()", *env); }

    void reload() {
        env = create_ref<sol::environment>(*lua, sol::create, lua->globals());
        lua->safe_script_file(script_class->script_file, *env);
    }

    void reload_if_modified() {
        auto last_write_time = std::filesystem::last_write_time(script_class->script_file);
        if (last_write_time > last_modified) {
            std::cerr << "RELOADING LUA:" << script_class->script_file << "\n";
            last_modified = last_write_time;
            reload();
            invoke_on_create();
        }

    }

    sol::state* lua;
    Ref<ScriptClass> script_class;
    Ref<sol::environment> env;
    std::filesystem::file_time_type last_modified = std::filesystem::file_time_type::min();
};

void my_panic(sol::optional<std::string> maybe_msg) {}

struct ScriptEngineData {
    sol::state lua;
    Scene* scene = nullptr;
    std::unordered_map<UUID, Ref<ScriptInstance>> entity_instances;
    std::unordered_map<std::string, Ref<ScriptClass>> entity_classes;
};
static ScriptEngineData* s_Data = nullptr;

void ScriptEngine::init() {
    s_Data = new ScriptEngineData();
    s_Data->lua.open_libraries();
    s_Data->lua.set_exception_handler(
        [](lua_State* L, sol::optional<const std::exception&> maybe_exception, sol::string_view description) {
            std::cout << "EXCEPTION\n";
            return sol::stack::push(L, description);
        });
    sol::state lua(sol::c_call<decltype(&my_panic), &my_panic>);

    SCION_CORE::Scripting::GLMBindings::CreateGLMBindings(s_Data->lua);
    sol_ImGui::Init(s_Data->lua);

    load_entity_classes();
}

void ScriptEngine::shutdown() { delete s_Data; }

void ScriptEngine::on_runtime_start(Scene* scene) { s_Data->scene = scene; }

void ScriptEngine::on_runtime_stop(Scene* scene) {
    s_Data->scene = nullptr;
    s_Data->entity_instances.clear();
}

bool ScriptEngine::class_exists(const std::string& class_name) {
    return s_Data->entity_classes.find(class_name) != s_Data->entity_classes.end();
}

void ScriptEngine::on_create_entity(Entity entity) {
    const auto& sc = entity.getComponent<ScriptComponent>();
    if (class_exists(sc.class_name)) {
        UUID ent_id = entity.getUUID();
        Ref<ScriptInstance> instance =
            create_ref<ScriptInstance>(s_Data->entity_classes[sc.class_name], entity, &s_Data->lua);
        s_Data->entity_instances[ent_id] = instance;

        instance->invoke_on_create();
    }
}

void ScriptEngine::on_update_entity(Entity entity, double dt) {
    const auto& sc = entity.getComponent<ScriptComponent>();
    UUID uuid = entity.getUUID();

    auto iter = s_Data->entity_instances.find(uuid);
    if (iter != s_Data->entity_instances.end()) {
        Ref<ScriptInstance> instance = iter->second;
        instance->reload_if_modified();
        instance->invoke_on_update();

#ifdef ENABLE_IM_LUA_END_STACK
        // bool wasEmpty = endStack.empty();
        while (!endStack.empty()) {
            ImEndStack(endStack.back());
            endStack.pop_back();
        }
#endif

    }
}

Scene* ScriptEngine::get_scene() { return s_Data->scene; }

void ScriptEngine::load_entity_classes() {
    std::ranges::for_each(std::filesystem::directory_iterator{"/home/cschilling/spacetraders_tui/gui/scripts"}, [](const auto& dir_entry) {
        if (dir_entry.is_regular_file() && dir_entry.path().extension() == ".lua") {
            std::cout << "loading " << dir_entry.path() << "\n";
            // std::ifstream fs(dir_entry.path());
            // std::stringstream ss;
            // ss << fs.rdbuf();

            Ref<ScriptClass> sc = create_ref<ScriptClass>();
            sc->script_file = dir_entry.path();

            s_Data->entity_classes[dir_entry.path().filename()] = sc;
        }
    });
    // s_Data.entity_classes[""]
}
