#include "map.h"
#include "imgui.h"
#include <sstream>

void MapLayer::render_ships() {
    ImVec2 dim = ImGui::GetContentRegionAvail();

    // offsetx = dim.x / 2.0f;
    // offsety = dim.y / 2.0f;

    auto view = sptr::GameState::instance().scene->view<TagComponent, sptr::ShipComponent, TransformComponent>();
    view.each([this, &dim](TagComponent& tag, sptr::ShipComponent& wp, TransformComponent& transform) {
        glm::vec3 pos = transform.getPosition();
        // sf::CircleShape shape(10.f);
        sf::Text text(font, tag.tag);
        // text.setPosition({pos.x + offset().x + 10, pos.y + offset().y + 12});
        text.setPosition({pos.x, pos.y + 12});
        text.setCharacterSize(12);
        text.setScale({1.0, -1.0});
        text.setFillColor(sf::Color::Red);
        // shape.setFillColor(sf::Color::White);
        // shape.setPosition({pos.x + offsetx, pos.y + offsety});
        // std::cout << "Drew entity at " << pos << "\n";
        // fb.draw(shape);
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

    if (!was_dragging && dragging_now) {
        // started draggin
        drag_prev = mouse_pos();
    } else if (was_dragging && !dragging_now) {
        // stopped draggin
    }

    if (dragging_now) {
        glm::vec2 drag_pan = mouse_pos().pos - drag_prev.pos;
        screen_center += drag_pan;
        pan_amount += drag_pan;
    }

    was_dragging = dragging_now;

    drag_prev = mouse_pos();
}

template <typename T> void printCoord(const std::string& name, Coord<T> coord) {
    ImGui::Value((name + "X").c_str(), coord.pos.x);
    ImGui::Value((name + "Y").c_str(), coord.pos.y);
}

void MapLayer::render_waypoints() {
    auto& io = ImGui::GetIO();
    auto min = ImGui::GetWindowContentRegionMin();
    auto max = ImGui::GetWindowContentRegionMax();
    min.x += ImGui::GetWindowPos().x;
    min.y += ImGui::GetWindowPos().y;

    max.x += ImGui::GetWindowPos().x;
    max.y += ImGui::GetWindowPos().y;

    Coord<ImGuiMainWindowSpace> mPos_mainWindow{{ImGui::GetMousePos().x, ImGui::GetMousePos().y}};
    Coord<ImGuiCurrentSubWindowSpace> mPos_subwindow = toImGuiCurrentWindowSpace(mPos_mainWindow);
    Coord<CameraSpace> mPos_world = toSpaceTradersWorldSpace(mPos_subwindow);

    glm::vec2 mousePosRegion{io.MousePos.x - min.x, io.MousePos.y - min.y};

    ImGui::Begin("MousePos");
    ImGui::Value("MinX", min.x);
    ImGui::Value("MinY", min.y);
    ImGui::Value("MaxX", max.x);
    ImGui::Value("MaxY", max.y);
    ImGui::Value("mousePosRegionX", mousePosRegion.x);
    ImGui::Value("mousePosRegionY", mousePosRegion.y);
    printCoord("MainWindowSpace", mPos_mainWindow);
    printCoord("CurrentSubWindowSpace", mPos_subwindow);
    printCoord("CameraSpace", mPos_world);
    ImGui::Value("was_dragging", was_dragging);
    ImGui::End();

    ImVec2 dim = ImGui::GetContentRegionAvail();
    view.setCenter({offset().x, offset().y});
    fb.setView(view);

    // glm::vec2 total_offset = fromImVec
    // float total_offset = (dim.x / 2.0f) + offset().x;
    // offsety = (dim.y / 2.0f) + offset().y;
    auto view = sptr::GameState::instance().scene->view<TagComponent, TransformComponent, sptr::WaypointComponent>();
    view.each([this, &dim](TagComponent& tag, TransformComponent& transform, sptr::WaypointComponent& wp) {
        glm::vec3 pos = transform.getPosition();
        sf::CircleShape shape(3.f);
        sf::Text text(font, tag.tag);
        // std::stringstream ss;
        // ss << "(" << transform.getPosition().x << "," << transform.getPosition().y << ")";
        // sf::Text text(font, ss.str());
        // text.setPosition({pos.x + offset().x - get_text_width(text), pos.y + offset().y - 5});
        text.setPosition({pos.x , pos.y-5});
        text.setCharacterSize(20);
        // text.setCharacterSize(12);
        text.setScale({1.0, -1.0});
        shape.setFillColor(sf::Color::White);
        // shape.setPosition({pos.x + offset().x, pos.y + offset().y});
        shape.setPosition({pos.x, pos.y});
        // std::cout << "Drew entity at " << pos << "\n";
        fb.draw(shape);
        fb.draw(text);
        // fb.display();
    });
}

float MapLayer::left() { return pan_amount.x; }
float MapLayer::right() { return pan_amount.x + ImGui::GetWindowContentRegionWidth(); }
float MapLayer::top() { return pan_amount.y + ImGui::GetWindowContentRegionWidth(); }
float MapLayer::bottom() { return pan_amount.y + ImGui::GetWindowContentRegionWidth(); }
