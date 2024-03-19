#include "imgui-SFML.h"
#include "imgui.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "layers/main_dockspace.h"

sf::RenderWindow* gRenderWindow = nullptr;

void display(sf::RenderWindow& window) {
    gRenderWindow = &window;
    window.clear();

    static MainDockspaceLayer main_dockspace;
    main_dockspace.update();
    main_dockspace.render();


    // window.draw(sprite);
}


int main() {
    // ImGuiIO& io = ImGui::GetIO(); (void)io;
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    // io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

    sf::RenderWindow window(sf::VideoMode({1400, 700}), "ImGui + SFML = <3");
    window.setPosition({0,0});
    window.setFramerateLimit(60);
    auto ret = ImGui::SFML::Init(window);
    if (!ret) {
        std::cerr << "Error Initializing SFML\n";
    }


    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());
        display(window);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}
