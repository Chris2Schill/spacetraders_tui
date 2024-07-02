#include "engine/input/input_system.h"

#include "engine/scene/components.h"
#include "engine/scene/scene.h"
#include "engine/script_engine/script_engine.h"
#include "input/coordinate_conversions.h"
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/WindowBase.hpp>

Coord<ScreenSpace> InputSystem::get_mouse_position(const sf::WindowBase* win) {
    if (win) {
        auto pos = sf::Mouse::getPosition(*win);
        return {{pos.x, pos.y}};
    } else {
        auto pos = sf::Mouse::getPosition();
        return {{pos.x, pos.y}};
    }
}

void InputSystem::on_runtime_update(Scene* scene) {
    Coord<WorldSpace> mouse_pos = scene->get_mouse_position();

    {
        auto view = scene->view<ScriptComponent, CircleComponent, TransformComponent>();
        for (auto ent : view) {
            auto& transform = view.get<TransformComponent>(ent);
            auto& circle = view.get<CircleComponent>(ent);

            Coord<WorldSpace> circlePos = {{transform.translation.x, transform.translation.y}};

            Coord<WorldSpace> dist = mouse_pos - circlePos;
            bool hovered = glm::length(dist.pos) < circle.shape.getRadius();
            ScriptEngine::on_hover_entity({ent, scene}, hovered);
        }
    }

    {
        auto view = scene->view<ScriptComponent, SpriteComponent, TransformComponent>();
        for (auto ent : view) {
            auto& sprite = view.get<SpriteComponent>(ent);
            auto rect = sprite.sprite->getGlobalBounds();
            bool hovered = rect.contains({mouse_pos.pos.x, mouse_pos.pos.y});
            ScriptEngine::on_hover_entity({ent, scene}, hovered);
        }
    }
}
