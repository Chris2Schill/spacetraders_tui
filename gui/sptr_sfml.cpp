#include "SFML/Window/ContextSettings.hpp"
#include "SFML/Window/Cursor.hpp"
#include "engine/scene/components.h"
#include "imgui-SFML.h"
#include "imgui.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "engine/core/log.h"
#include "engine/script_engine/script_engine.h"
#include "engine/input/input_system.h"
// #include "layers/main_dockspace.h"
#include "lua.h"

sf::RenderWindow* gRenderWindow = nullptr;
Ref<Scene> scene;

// struct ImGuiRenderComponent {
//     ImGuiRenderComponent(Ref<Layer> layer) : layer(layer) {};
//     Ref<Layer> layer = nullptr;
// };
//
// void render_imgui(Ref<Scene> scene) {
//
//     auto view = scene->view<ImGuiRenderComponent>();
//     for (auto e : view) {
//         ImGuiRenderComponent& imrc = view.get<ImGuiRenderComponent>(e);
//         imrc.layer->render();
//     }
// }

void display(sf::RenderWindow& window) {
    gRenderWindow = &window;
    window.clear();

    // render_imgui(scene);
    // static MainDockspaceLayer main_dockspace;
    // main_dockspace.update();
    // main_dockspace.render();

    // window.draw(sprite);
}

int main() {
    // ImGuiIO& io = ImGui::GetIO(); (void)io;
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    // io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
    Log::Init();

    ScriptEngine::init();
    ScriptEngine::safe_script_file_global("../../gui/scripts/globals.lua");

    scene = create_ref<Scene>();

    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowPadding = ImVec2(3, 3);
    style.FramePadding = ImVec2(4, 2);
    // style.WindowPadding = ImVec2(0, 0);
    // style.FramePadding = ImVec2(0, 0);
    style.FrameRounding = 2;
    style.ScrollbarRounding = 12;
    style.TabRounding = 4;

    auto addScriptEntity = [](std::string name, std::string script) {
        Entity ent = scene->createBasicEntity(name);
        ent.addComponent<ScriptComponent>(script);
        return ent;
    };

    Entity primaryCamera = scene->createEntity("PrimaryCamera");
    primaryCamera.addComponent<CameraComponent>();
    primaryCamera.addComponent<ScriptComponent>("primary_camera.lua");

    // Entity skybox = scene->createEntity("Skybox");
    // skybox.addComponent<ScriptComponent>("skybox.lua");
    // skybox.addComponent<SpriteComponent>("space.jpg");
    // PriorityComponent& skybox_pc = skybox.getComponent<PriorityComponent>();
    // skybox_pc.priority = 2;

    addScriptEntity("AgentsData",  "data/agent.lua");
    addScriptEntity("SystemsData", "data/systems.lua");
    addScriptEntity("ShipsData", "data/ships.lua");
    addScriptEntity("WaypointsData", "data/waypoints.lua");
    addScriptEntity("ContractsData", "data/contracts.lua");

    Entity ui = addScriptEntity("UI", "ui/ui.lua");
    PriorityComponent& pc = ui.getComponent<PriorityComponent>();
    pc.priority = 1;

    addScriptEntity("AgentWindow",     "ui/agent.lua");
    addScriptEntity("SystemsWindow",   "ui/systems.lua");
    addScriptEntity("SystemWindow",    "ui/system.lua");
    addScriptEntity("ShipsWindow",     "ui/ships.lua");
    addScriptEntity("WaypointsWindow", "ui/waypoints.lua");
    addScriptEntity("ContractsWindow", "ui/contracts.lua");


    scene->startRuntime();

    while (scene->isRunning()) {
        double dt = scene->deltaTime();
        scene->step(dt);
        InputSystem::on_runtime_update(&(*scene));
        scene->renderScene(primaryCamera);
    }

    scene->stopRuntime();

    scene = nullptr;

    ScriptEngine::shutdown();
}

// struct position {
//     float x, y;
// };
// int main() {
//     entt::registry registry;
//
//     for(auto i = 0u; i < 100u; ++i) {
//         const auto entity = registry.create();
//         // registry.emplace<position>(entity, position());
//         registry.emplace<TransformComponent>(entity, TransformComponent());
//         // if(i % 2 == 0) { registry.emplace<velocity>(entity, i * .1f, i * .1f); }
//     }
//
//     // registry.sort<position>([](const auto& lhs, const auto& rhs){ return lhs.x < rhs.x; });
//     // registry.sort<TransformComponent>([](const auto& lhs, const auto& rhs){ return true; });
//     registry.sort<TransformComponent>(
//         [](const TransformComponent& lhs, const TransformComponent& rhs) { return lhs.translation.z > rhs.translation.z; });
//
// }
