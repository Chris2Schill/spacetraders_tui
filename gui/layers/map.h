#pragma once

#include <engine/scene/components.h>
#include <engine/app/layer.h>

#include "../coordinate_conversions.h"
#include "sptr/data.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/WindowHandle.hpp>
#include <app.h>
#include <imgui-sfml/imgui-SFML.h>
#include <sptr/sptr.h>

#include <imgui.h>

extern sf::RenderWindow* gRenderWindow;

// static void ShowImage(bool& p_open, sf::Sprite sprite)
// {
//     ImGui::SetNextWindowPos(ImVec2(100,100));
//     if (!ImGui::Begin("Example: Image", &p_open))
//     {
//         ImGui::End();
//         return;
//     }
//     ImGui::Image(sprite);
//     ImGui::End();
// }

struct MapLayer : public Layer {
    MapLayer() {
        // scale(1.0);

        // GLFWwindow* glfwwin = Application::getWindow();
        // wl_surface* wlsurface = glfwGetWaylandWindow(glfwwin);

        // sf::WindowHandle wh;
        // wh.

        // sfw =  new sf::Window(ha)
        // if (fb.create({100, 100})) {
        //     std::cerr << "Error creating fb texture\n";
        // }
        // ImVec2 dim = ImGui::GetContentRegionAvail();
        // if (fb.create({(unsigned)dim.x, (unsigned)dim.y})) {
        if (fb.create({1000, 1000})) {
            std::cerr << "Error creating fb texture\n";
        }

        if (!font.loadFromFile("/home/cschilling/spacetraders/spacetraders_tui/resources/fonts/LUCON.TTF")) {
            std::cerr << "Error loading font\n";
        }

        for (int i = 0; i < 1000; ++i) {
            float x = (rand() % 2000) - 1000;
            float y = (rand() % 2000) - 1000;

            sf::CircleShape star(1.f * zoom);
            star.setFillColor(sf::Color::White);
            star.setPosition({x, y});
            stars.push_back(star);
            // fb.draw(dot);
        }

        sptr::get_event_bus()->subscribe<sptr::event::MapCenterOnWaypoint>(
            this, [this](const sptr::event::MapCenterOnWaypoint& e) {
                auto wp = sptr::GameState::instance().get_waypoint(e.waypointSymbol);
                set_screen_center({wp->getX(), wp->getY()});
            });
    }

    void render_ships();
    void render_stars();
    void render_system_center() {
        sf::CircleShape circle(20.f);
        circle.setFillColor(sf::Color::Yellow);
        circle.setPosition({0, 0});
        circle.setOrigin({circle.getRadius(), circle.getRadius()});
        fb.draw(circle);
    }

    float get_text_width(const sf::Text& text) { return 40; }

    void render_waypoints();

    glm::vec2 screen_center() { return pan_amount; }
    void set_screen_center(const glm::vec2& center) { pan_amount = center; }

    void render() {

        ImGui::Begin("Map");

        // ImGui::Text("Zoom");
        // ImGui::SameLine();
        // if (ImGui::Button("+")) {
        //     zoom *= 0.5f;
        // }
        // ImGui::SameLine();
        // if (ImGui::Button("-")) {
        //     zoom *= 2.f;
        // }
        // ImGui::SameLine();
        // if (ImGui::Button("Reset")) {
        //     reset_zoom();
        // }
        // ImGui::Text((std::to_string(scale.x) + "x").c_str());

        ImVec2 dim = ImGui::GetContentRegionAvail();
        view.setSize(sf::Vector2f{dim.x, dim.y} * zoom);
        view.setCenter({screen_center().x, screen_center().y});
        fb.setView(view);
        fb.setSmooth(true);

        fb.clear();
        render_stars();
        render_waypoints();
        render_ships();
        render_system_center();
        fb.display();

        if (!fb.create({(unsigned)dim.x, (unsigned)dim.y})) {
            // if (!fb.create({1000,1000})) {
            std::cerr << "Error creating fb texture\n";
            ImGui::End();
            return;
        }

        const sf::Texture& tex = fb.getTexture();
        sf::Sprite sprite(tex);

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0, 0});
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, {0, 0});
        ImGui::Image(sprite);
        if (ImGui::IsItemHovered()) {
            check_dragging();
            if (ImGui::GetIO().MouseWheel > 0) {
                zoom *= 0.5f;
            } else if (ImGui::GetIO().MouseWheel < 0) {
                zoom *= 2.f;
            }
        }
        ImGui::PopStyleVar(2);

        ImGui::End();
    }

    // void scale(float scale) {
    //     dim *= scale;
    //     cellsize *= 1.0 / scale;
    //     selected.resize(dim);
    //     for (int x = 0; x < dim; ++x) {
    //         selected[x].resize(dim);
    //     }
    // }

    void pan(glm::vec2 delta) { pan_amount += delta * zoom; }

    float left();
    float right();
    float top();
    float bottom();

    void reset_zoom() { zoom = 1; }
    void check_dragging();

    template <typename T> void printCoord(const std::string& name, Coord<T> coord) {
        ImGui::Text("%s: (%g, %g)", name.c_str(), coord.pos.x, coord.pos.y);
    }

    void render_mouse_coord_debug_window() {
        auto min = ImGui::GetWindowContentRegionMin();
        auto max = ImGui::GetWindowContentRegionMax();

        Coord<ImGuiMainWindowSpace> mPos_mainWindow = mouse_pos();
        Coord<ImGuiCurrentSubWindowSpace> mPos_subwindow = toImGuiCurrentWindowSpace(mPos_mainWindow);

        Coord<ViewSpace> mPos_view = toViewSpace(mPos_subwindow, max.y - min.y);
        Coord<SystemSpace> mPos_system = toSystemSpace(mPos_view, fb);

        ImGui::Begin("MousePos");
        if (ImGui::Button("ResetPan")) {
            pan_amount = {0, 0};
            zoom = 1;
        }
        printCoord("MousePosMainWindowSpace", mPos_mainWindow);
        printCoord("MousePosCurrentSubWindowSpace", mPos_subwindow);
        printCoord("MousePosViewSpace", mPos_view);
        printCoord("MousePosSystemSpace", mPos_system);
        printCoord("PanAmount", Coord<ViewSpace>{{pan_amount.x, pan_amount.y}});
        printCoord("ViewSize", Coord<ViewSpace>{{view.getSize().x, view.getSize().y}});
        printCoord("ViewCenter", Coord<ViewSpace>{{view.getCenter().x, view.getCenter().y}});
        ImGui::Value("dragging", dragging);
        ImGui::End();
    }

    Coord<SystemSpace> mouse_pos_system_space() {
        Coord<ImGuiMainWindowSpace> mPos_mainWindow = mouse_pos();
        Coord<ImGuiCurrentSubWindowSpace> mPos_subwindow = toImGuiCurrentWindowSpace(mPos_mainWindow);
        auto min = ImGui::GetWindowContentRegionMin();
        auto max = ImGui::GetWindowContentRegionMax();
        float win_height = max.y - min.y;
        Coord<ViewSpace> mPos_view = toViewSpace(mPos_subwindow, win_height);
        return toSystemSpace(mPos_view, fb);
    }

    sf::Font font;
    sf::RenderTexture fb;
    std::vector<std::vector<char>> selected;
    std::vector<sf::CircleShape> stars;
    int dim = 50;
    int cellsize = 10;
    bool dragging = false;
    Coord<SystemSpace> drag_prev;
    glm::vec2 pan_amount{0.f, 0.0f};
    glm::vec3 scale{1.f, 1.f, 1.f};
    int64_t mouse_wheel_counter = 0;
    sf::View view;
    float zoom = 1.0f;
};
