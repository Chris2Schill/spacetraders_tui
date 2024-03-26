#pragma once

#include <glm/glm.hpp>
#include <imgui.h>
#include <SFML/Graphics/RenderTexture.hpp>

namespace MouseConversions {
inline glm::vec2 imguiTosfml(const glm::vec2& pos) { return pos * glm::vec2(0.f, -1.f); }
} // namespace MouseConversions

inline glm::vec2 fromImVec(const ImVec2 vec) { return {vec.x, vec.y}; }

// Coordinate systems
struct ImGuiMainWindowSpace {};
struct ImGuiCurrentSubWindowSpace {};
struct ViewSpace {};
struct SystemSpace {};
struct WorldSpace  {};

template <typename T> struct Coord {
    glm::vec2 pos;

    Coord<T>& operator+=(const Coord<T>& rhs) { pos = pos + rhs.pos; return *this; }
    Coord<T>& operator-=(const Coord<T>& rhs) { pos = pos - rhs.pos; return *this; }
    Coord<T>& operator*=(const Coord<T>& rhs) { pos = pos * rhs.pos; return *this; }
    Coord<T>& operator/=(const Coord<T>& rhs) { pos = pos / rhs.pos; return *this; }
    Coord<T>& operator+=(const glm::vec2& rhs) { pos = pos + rhs; return *this; }
    Coord<T>& operator-=(const glm::vec2& rhs) { pos = pos - rhs; return *this; }
    Coord<T>& operator*=(const glm::vec2& rhs) { pos = pos * rhs; return *this; }
    Coord<T>& operator/=(const glm::vec2& rhs) { pos = pos / rhs; return *this; }

    friend Coord<T> operator+(Coord<T> lhs, const glm::vec2& v) { lhs += v; return lhs; }
    friend Coord<T> operator-(Coord<T> lhs, const glm::vec2& v) { lhs -= v; return lhs; }
    friend Coord<T> operator*(Coord<T> lhs, const glm::vec2& v) { lhs *= v; return lhs; }
    friend Coord<T> operator/(Coord<T> lhs, const glm::vec2& v) { lhs /= v; return lhs; }
    friend Coord<T> operator+(Coord<T> lhs, const Coord<T>& v) { lhs += v; return lhs; }
    friend Coord<T> operator-(Coord<T> lhs, const Coord<T>& v) { lhs -= v; return lhs; }
    friend Coord<T> operator*(Coord<T> lhs, const Coord<T>& v) { lhs *= v; return lhs; }
    friend Coord<T> operator/(Coord<T> lhs, const Coord<T>& v) { lhs /= v; return lhs; }
};

inline Coord<ImGuiMainWindowSpace> mouse_pos() {
    return {{ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y}};
}

inline Coord<ImGuiCurrentSubWindowSpace> toImGuiCurrentWindowSpace(Coord<ImGuiMainWindowSpace> coord) {
    glm::vec2 min = fromImVec(ImGui::GetWindowContentRegionMin()) + fromImVec(ImGui::GetWindowPos());
    return {coord.pos - min};
};

// Shifts from a top-left origin to a bottom-left origin
inline Coord<ViewSpace> toViewSpace(Coord<ImGuiCurrentSubWindowSpace> coord, float win_height) {
    return {{coord.pos.x, win_height - coord.pos.y}};
};

inline Coord<SystemSpace> toSystemSpace(Coord<ViewSpace> coord, const sf::RenderTexture& fb) {
    auto pos  = fb.mapPixelToCoords({(int)coord.pos.x, (int)coord.pos.y});
    return {{pos.x, pos.y}};
};
