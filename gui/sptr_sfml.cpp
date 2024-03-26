#include "SFML/Window/ContextSettings.hpp"
#include "imgui-SFML.h"
#include "imgui.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "engine/script_engine/script_engine.h"
#include "layers/main_dockspace.h"
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
    sf::ContextSettings settings;
    settings.majorVersion = 4;
    settings.minorVersion = 4;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode({1400, 700}), "SpaceTraders", sf::Style::Default, sf::State::Windowed,
                            settings);
    window.setPosition({0, 0});
    window.setFramerateLimit(60);
    auto ret = ImGui::SFML::Init(window);
    if (!ret) {
        std::cerr << "Error Initializing SFML\n";
    }

    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowPadding = ImVec2(3, 3);
    style.FramePadding = ImVec2(4, 2);
    // style.WindowPadding = ImVec2(0, 0);
    // style.FramePadding = ImVec2(0, 0);
    style.FrameRounding = 2;
    style.ScrollbarRounding = 12;
    style.TabRounding = 4;

    scene = create_ref<Scene>();

    Entity imwin1 = scene->createBasicEntity("ImGuiWindow1");
    imwin1.addComponent<ScriptComponent>("agent.lua");

    Entity imwin2 = scene->createBasicEntity("ImGuiWindow");
    imwin2.addComponent<ScriptComponent>("ships.lua");
    // imwin1.addComponent<ScriptComponent>("imgui.lua");
    // imwin1.addComponent<ImGuiRenderComponent>(create_ref<MainDockspaceLayer>());

    ScriptEngine::init();

    scene->startRuntime();

    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        double dt = deltaClock.getElapsedTime().asSeconds();

        ImGui::SFML::Update(window, deltaClock.restart());
        display(window);
        try {
            scene->onUpdateRuntime(dt);
            scene->onUpdateSimulation(dt);

        } catch (const std::exception& e) {
            std::cerr << "Exception thrown in lua: " << e.what();
        }
        ImGui::SFML::Render(window);
        window.display();
    }

    scene->stopRuntime();

    ScriptEngine::shutdown();

    ImGui::SFML::Shutdown();
}
