#pragma once

// #include "engine/core/log.h"
#include "engine/scene/entity.h"
#include "engine/scene/components.h"
#include "engine/scene/scene.h"
#include "engine/script_engine/entt_registry_lua_bindings.hpp"
#include "engine/script_engine/meta_helper.hpp"
#include <sol/raii.hpp>
#include <sol/sol.hpp>
#include <entt/entt.hpp>
#include <entt/core/hashed_string.hpp>

#include "engine/script_engine/meta_helper.hpp"
#include "engine/input/input_system.h"

static void register_events(sol::state& lua) {

}


static void register_enums(sol::state& lua) {
    lua.new_enum("InputSystem",
            "WHEEL_UP", InputSystem::WHEEL_UP,
            "WHEEL_DOWN", InputSystem::WHEEL_DOWN);
}

static void register_entity(sol::state& lua) {
  // sol::state_view lua{ls};
  // auto entity_module = lua["EntityMod"].get_or_create<sol::table>();

  using namespace entt::literals;

  lua.new_usertype<Entity>("Entity",
    "type_id", &entt::type_hash<Entity>::value,

    // sol::meta_function::construct,
    sol::call_constructor,
    sol::factories(
    []() { return Entity{}; },
    [](entt::entity e, Scene* scene) {
      return Entity{e, scene};
    }),

    "getComponent",
      [](Entity &self, const sol::object &type_or_id,
         sol::this_state s) {
          const auto maybe_any =
            invoke_meta_func(deduce_type(type_or_id), "getComponent"_hs,
              &self, s);
          return maybe_any ? maybe_any.cast<sol::reference>() : sol::lua_nil_t{};
    },
    "addComponent",
      [](Entity &self, const sol::table &comp,
         sol::this_state s) {
          const auto maybe_any =
            invoke_meta_func(get_type_id(comp), "addComponent"_hs,
              &self, comp, s);
          return maybe_any ? maybe_any.cast<sol::reference>() : sol::lua_nil_t{};
    },
    "hasComponent",
      [](Entity &self, const sol::table &comp,
         sol::this_state s) {
          LOG_CORE_TRACE("Entity:hasComponent() (lua)");
          const auto maybe_any =
            invoke_meta_func(deduce_type(comp), "hasComponent"_hs,
              &self);
        return maybe_any ? maybe_any.cast<bool>() : false;
    },
    "getUUID", [](Entity& e) { return e.getUUID(); }, 
    "is_valid", [](const Entity& e) { return static_cast<bool>(e); }
  );
}

static void register_scene(sol::state& lua) {

  lua.new_usertype<Scene>("Scene",
    "type_id", &entt::type_hash<Scene>::value,

    sol::call_constructor,
    sol::factories([]() {
      return Scene{};
    }),
    "getEntityByUUID", [](Scene& scene, const UUID& uuid) { return scene.getEntityByUUID(uuid); },
    "findEntityByName", [](Scene& scene, const std::string& name) { return scene.findEntityByName(name); },
    "createEntity", [](Scene& scene, const std::string& name) { return scene.createEntity(name); },
    "createBasicEntity", [](Scene& scene, const std::string& name) { return scene.createBasicEntity(name); },
    "createEntityActor", [](Scene& scene, const std::string& name, const std::string& script) { return scene.createEntityActor(name, script); },
    "destroyEntity", [](Scene& scene, Entity& e) { return scene.destroyEntity(e); }
  );
}

static void register_tag(sol::state& lua) {
  register_meta_component<TagComponent>();
  lua.new_usertype<TagComponent>("TagComponent",
    "type_id", &entt::type_hash<TagComponent>::value,

    sol::call_constructor,
    sol::factories([](const std::string& tag) {
      return TagComponent{tag};
    }),
    "tag", &TagComponent::tag
  );
}

static void register_id(sol::state& lua) {

  register_meta_component<UUID>();
  lua.new_usertype<UUID>("UUID",
    "type_id", &entt::type_hash<UUID>::value,

    sol::call_constructor,
    sol::factories([](uint64_t uuid) {
      return UUID(uuid);
    }),
    sol::meta_function::to_string, [](UUID id) { return std::to_string(static_cast<uint64_t>(id)); }
  );

  register_meta_component<IDComponent>();
  lua.new_usertype<IDComponent>("IDComponent",
    "type_id", &entt::type_hash<IDComponent>::value,

    sol::call_constructor,
    sol::factories([](UUID id) {
      return IDComponent{id};
    }),
    "uuid", [](const IDComponent& idc) { return idc.uuid; }
  );
}

static void register_transform(sol::state &lua) {
    register_meta_component<TransformComponent>();
  lua.new_usertype<TransformComponent>("TransformComponent",
    "type_id", &entt::type_hash<TransformComponent>::value,

    sol::call_constructor,
    sol::factories(
        []() { return TransformComponent(); },
        [](glm::vec3 translation) { return TransformComponent(translation); }
    ),
    "translation", &TransformComponent::translation,
    "rotation", &TransformComponent::rotation,
    "scale", &TransformComponent::scale,

    sol::meta_function::to_string, &TransformComponent::to_string
  );
}

static void register_script_component(sol::state& lua) {
    register_meta_component<ScriptComponent>();
    lua.new_usertype<ScriptComponent>("ScriptComponent",
      "type_id", &entt::type_hash<ScriptComponent>::value,

      sol::call_constructor,
      sol::factories([](const std::string& classname) {
        return ScriptComponent{classname};
      }),
      "class_name", &ScriptComponent::class_name,
      "instance", &ScriptComponent::instance,

      sol::meta_function::to_string, [](ScriptComponent& sc) { return sc.class_name; }
    );
}

static void register_circle_component(sol::state& lua) {
    register_meta_component<CircleComponent>();
    lua.new_usertype<CircleComponent>("CircleComponent",
      "type_id", &entt::type_hash<CircleComponent>::value,

      sol::call_constructor,
      sol::factories(
          [](float radius) { return CircleComponent{radius}; },
          [](float radius, int pointCount) { return CircleComponent(radius, pointCount); },
          []() { return CircleComponent(); }),
      "fillColor", &CircleComponent::fillColor,
      "outlineColor", &CircleComponent::outlineColor
    );
}

static void register_sf_camera_component(sol::state& lua) {

    lua.new_usertype<sf::View>("SFView",
      "type_id", &entt::type_hash<sf::View>::value,

      sol::call_constructor,
      sol::factories(
          []() { return sf::View(); }),
      "zoom", [](sf::View& v, float zoom) { v.zoom(zoom); },
      "getSize", [](sf::View& v) { return glm::vec2(v.getSize().x, v.getSize().y); }
    );

    register_meta_component<CameraComponent>();
    lua.new_usertype<CameraComponent>("CameraComponent",
      "type_id", &entt::type_hash<CameraComponent>::value,

      sol::call_constructor,
      sol::factories(
          []() { return CameraComponent(); }),

      "view", &CameraComponent::view
    );
}

static void register_sf_sprite_component(sol::state& lua) {

    register_meta_component<SpriteComponent>();
    lua.new_usertype<SpriteComponent>("SpriteComponent",
      "type_id", &entt::type_hash<SpriteComponent>::value,

      sol::call_constructor,
      sol::factories(
          [](const std::string& file) { return SpriteComponent(file); }),
      "color", &SpriteComponent::color
    );
}


static void register_priority_component(sol::state& lua) {

    register_meta_component<PriorityComponent>();
    lua.new_usertype<PriorityComponent>("PriorityComponent",
      "type_id", &entt::type_hash<PriorityComponent>::value,

      sol::call_constructor,
      sol::factories(
          [](int priority) { return PriorityComponent{priority}; })
    );
}

// static void register_rect_component(sol::state& lua) {
//
//     register_meta_component<RectComponent>();
//     lua.new_usertype<RectComponent>("RectComponent",
//       "type_id", &entt::type_hash<RectComponent>::value,
//
//       sol::call_constructor,
//       sol::factories(
//           [](const glm::vec2& dim) { return RectComponent{dim}; })
//     );
// }

inline void register_components(sol::state& lua) {
    register_tag(lua);
    register_id(lua);
    register_transform(lua);
    register_scene(lua);
    register_entity(lua);
    register_script_component(lua);
    register_sf_camera_component(lua);
    register_circle_component(lua);
    register_sf_sprite_component(lua);
    register_priority_component(lua);
    // register_rect_component(lua);
    register_events(lua);
    register_enums(lua);
}

