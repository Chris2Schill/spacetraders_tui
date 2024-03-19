#pragma once

#include "engine/scene/components.h"
#include "layer.h"

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

namespace MouseConversions {
inline glm::vec2 imguiTosfml(const glm::vec2& pos) { return pos * glm::vec2(0.f, -1.f); }
} // namespace MouseConversions

inline glm::vec2 fromImVec(const ImVec2 vec) { return {vec.x, vec.y}; }

// enum class coord{
//     ImGuiScreenSpace,
//     CameraSpace,
// };

// Coordinate systems
struct ImGuiMainWindowSpace {};
struct ImGuiCurrentSubWindowSpace {};
struct CameraSpace {};
struct SpaceTradersUnivserseSpace {};

template <typename T> struct Coord {
    glm::vec2 pos;

    // void operator+(glm::vec2 v) { pos + v; }
    Coord<T>& operator+=(const glm::vec2& rhs) { return {pos + rhs}; }
    Coord<T>& operator-=(const glm::vec2& rhs) { return {pos - rhs}; }
    Coord<T>& operator*=(const glm::vec2& rhs) { return {pos * rhs}; }
    Coord<T>& operator/=(const glm::vec2& rhs) { return {pos / rhs}; }
    friend Coord<T> operator+(Coord<T> lhs, const glm::vec2& v) {
        lhs += v;
        return lhs;
    }
    friend Coord<T> operator-(Coord<T> lhs, const glm::vec2& v) {
        lhs -= v;
        return lhs;
    }
    friend Coord<T> operator*(Coord<T> lhs, const glm::vec2& v) {
        lhs *= v;
        return lhs;
    }
    friend Coord<T> operator/(Coord<T> lhs, const glm::vec2& v) {
        lhs /= v;
        return lhs;
    }

    // Coord(Coord<T>& rhs) { pos = rhs.pos; }
};

// template <typename From, typename To> Coord<To> convert(From) {
//     bool mouse_pos_convert_implemented = false;
//     assert(mouse_pos_convert_implemented);
// };

inline Coord<ImGuiCurrentSubWindowSpace> toImGuiCurrentWindowSpace(Coord<ImGuiMainWindowSpace> mp) {
    glm::vec2 min = fromImVec(ImGui::GetWindowContentRegionMin());
    return {mp.pos - min};
};

inline Coord<CameraSpace> toSpaceTradersWorldSpace(Coord<ImGuiCurrentSubWindowSpace> mp) {
    return {mp.pos * glm::vec2(1.f, -1.f)};
};

// template<>
// mouse_pos<coordinate_systems

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

            sf::CircleShape star(1.f);
            star.setFillColor(sf::Color::White);
            star.setPosition({x, y});
            stars.push_back(star);
            // fb.draw(dot);
        }
    }

    void update() {
        check_dragging();
        if (ImGui::GetIO().MouseWheel > 0) {
            view.zoom(0.5);
        } else if (ImGui::GetIO().MouseWheel < 0) {
            view.zoom(2);
        }
    }

    void render_ships();
    void render_stars();
    void render_system_center() {
        sf::CircleShape shape(7.f);
        shape.setFillColor(sf::Color::Yellow);
        shape.setPosition({0,0});
        fb.draw(shape);
    }

    float get_text_width(const sf::Text& text) { return 40; }

    void render_waypoints();

    glm::vec2 offset() { return pan_amount * glm::vec2(-1.f, -1.f); }

    void render() {

        ImGui::Begin("Map");
        ImGui::Text("Zoom");
        ImGui::SameLine();
        if (ImGui::Button("+")) {
            view.zoom(0.5);
        }
        ImGui::SameLine();
        if (ImGui::Button("-")) {
            view.zoom(2);
        }
        ImGui::SameLine();
        if (ImGui::Button("Reset")) {
            reset_zoom();
        }
        ImGui::Text((std::to_string(scale.x) + "x").c_str());

        fb.clear();
        render_stars();
        render_waypoints();
        render_ships();
        render_system_center();
        fb.display();

        ImVec2 dim = ImGui::GetContentRegionAvail();
        if (!fb.create({(unsigned)dim.x, (unsigned)dim.y})) {
            // if (!fb.create({1000,1000})) {
            std::cerr << "Error creating fb texture\n";
            ImGui::End();
            return;
        }

        const sf::Texture& tex = fb.getTexture();
        sf::Sprite sprite(tex);

        ImGui::Image(sprite);

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

    void pan(glm::vec2 delta) { pan_amount += delta; }

    float left();
    float right();
    float top();
    float bottom();

    void reset_zoom() { view.zoom(1); }

    void check_dragging();

    Coord<CameraSpace> mouse_pos() {
        Coord<ImGuiMainWindowSpace> mPos_mainWindow{{ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y}};
        Coord<ImGuiCurrentSubWindowSpace> mPos_subwindow = toImGuiCurrentWindowSpace(mPos_mainWindow);
        Coord<CameraSpace> mPos_world = toSpaceTradersWorldSpace(mPos_subwindow);
        return mPos_world;
    }

    sf::Font font;
    sf::RenderTexture fb;
    std::vector<std::vector<char>> selected;
    std::vector<sf::CircleShape> stars;
    int dim = 50;
    int cellsize = 10;
    bool was_dragging = false;
    Coord<CameraSpace> drag_prev;
    glm::vec2 pan_amount{0.f, 0.0f};
    glm::vec2 screen_center{0.f, 0.f};
    glm::vec3 scale{1.f, 1.f, 1.f};
    int64_t mouse_wheel_counter = 0;
    sf::View view;
    float zoom = 1.0f;

};
