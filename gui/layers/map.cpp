#include "map.h"
#include "SFML/System/Vector3.hpp"
#include "glm/ext/matrix_projection.hpp"
#include "imgui.h"
#include "sptr/data.h"
#include <sstream>

void MapLayer::render_ships() {
    ImVec2 dim = ImGui::GetContentRegionAvail();

    // offsetx = dim.x / 2.0f;
    // offsety = dim.y / 2.0f;

    auto view = sptr::GameState::instance().scene->view<TagComponent, sptr::ShipComponent, TransformComponent>();
    view.each([this](TagComponent& tag, sptr::ShipComponent& wp, TransformComponent& transform) {
        glm::vec3 pos = transform.getPosition();
        sf::Text text(font, tag.tag);
        text.setPosition({pos.x, pos.y + 12});
        text.setCharacterSize(12);
        text.setScale({1.0, -1.0});
        text.setFillColor(sf::Color::Red);
        fb.draw(text);
    });
}

void MapLayer::render_stars() {
    for (const auto& star : stars) {
        fb.draw(star);
    }
}

void MapLayer::check_dragging() {
    bool dragging_now = ImGui::IsMouseDragging(ImGuiMouseButton_Left);

    if (!dragging && dragging_now) {
        // started draggin
        drag_prev = mouse_pos_system_space();
    } else if (dragging && !dragging_now) {
        // stopped draggin
    }

    if (dragging_now) {
        Coord<SystemSpace> drag_pan = mouse_pos_system_space() - drag_prev;
        pan(-drag_pan.pos);
    }

    dragging = dragging_now;

    drag_prev = mouse_pos_system_space();
}


void MapLayer::render_waypoints() {

    render_mouse_coord_debug_window();


    Coord<SystemSpace> mouse_pos_system = mouse_pos_system_space();

    auto view = sptr::GameState::instance().scene->view<TagComponent, TransformComponent, sptr::WaypointComponent>();
    view.each([this, mouse_pos_system](TagComponent& tag, TransformComponent& transform, sptr::WaypointComponent& wp) {
        Coord<SystemSpace> pos = {{transform.getPosition().x,
                                   transform.getPosition().y}};

        Coord<SystemSpace> diff = mouse_pos_system - pos;
        // glm::vec2 diff = glm::vec2(mouse_pos_system.pos.x, mouse_pos_system.pos.y) - glm::vec2(pos.x, pos.y);
        auto length = glm::length(diff.pos);
        bool hovered = length < 10 * zoom;
        auto color = hovered ? sf::Color::Red : sf::Color::Cyan;
        // std::cout << "DIFF=" << diff << ", Length= " << length << "\n";

        if (ImGui::BeginPopup(tag.tag.c_str())) {
            if (ImGui::Selectable("Navigate")) {
                sptr::DataProvider::instance().request_ship_navigate_to_waypoint(
                    {sptr::GameState::instance().get_selected_ship()}, wp.waypoint);
            }
            ImGui::EndPopup();
        }

        sf::CircleShape shape(4.f * zoom);
        // shape.setPointCount(3);
        shape.setFillColor(color);
        shape.setPosition({pos.pos.x, pos.pos.y});
        shape.setOrigin({shape.getRadius(), shape.getRadius()});
        fb.draw(shape);

        if (hovered) {
            // hovering the waypoint
            if (ImGui::IsMouseDown(ImGuiMouseButton_Left)) {
                ImGui::OpenPopup(tag.tag.c_str());
                std::cout << "Opening popup\n";
            }

            sf::Text text(font, tag.tag);
            // std::stringstream ss;
            // ss << "(" << transform.getPosition().x << "," << transform.getPosition().y << ")";
            // sf::Text text(font, ss.str());
            // text.setPosition({pos.x + offset().x - get_text_width(text), pos.y + offset().y - 5});
            text.setScale({zoom, -zoom});
            text.setCharacterSize(20);
            text.setPosition({pos.pos.x - text.getLocalBounds().getSize().x / 2.f * zoom, pos.pos.y - 5});
            text.setFillColor(color);
            fb.draw(text);
        }
        // fb.display();
    });
}

float MapLayer::left() { return pan_amount.x; }
float MapLayer::right() { return pan_amount.x + ImGui::GetWindowContentRegionWidth(); }
float MapLayer::top() { return pan_amount.y + ImGui::GetWindowContentRegionWidth(); }
float MapLayer::bottom() { return pan_amount.y + ImGui::GetWindowContentRegionWidth(); }
