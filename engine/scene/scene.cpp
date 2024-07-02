#include "scene.h"

#include "SFML/Graphics/Rect.hpp"
#include "components.h"
#include "engine/input/input_system.h"
#include "engine/scene/entity.h"
#include "engine/script_engine/script_engine.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Cursor.hpp>
#include <SFML/Window/Window.hpp>
#include <entt/core/type_info.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <iostream>

// sf::ContextSettings settings {
//     .majorVersion = 4,
//     .minorVersion = 4,
//     .antialiasingLevel = 8,
// };
//
struct SceneData {
    SceneData()
        : window(sf::VideoMode({window_width, window_height}), "SpaceTraders", sf::Style::Default,
                 sf::State::Windowed) {
        window.setPosition({0, 0});
        window.setFramerateLimit(60);
        auto ret = ImGui::SFML::Init(window);
        if (!ret) {
            std::cerr << "Error Initializing SFML\n";
        }

        // if (cursor.loadFromSystem(sf::Cursor::Type::SizeTopLeft)) {
        //     window.setMouseCursor(cursor);
        // } else {
        //     LOG_CORE_ERROR("Failed to set cursor style");
        // }
    }
    ~SceneData() { ImGui::SFML::Shutdown(); }

    unsigned int window_width = 1280;
    unsigned int window_height = 800;
    float initial_aspect_ratio = static_cast<float>(window_width) / static_cast<float>(window_height);

    sf::RenderWindow window;
    sf::Clock deltaClock;
    sf::Cursor cursor;
};

void sortRegistry(entt::registry& reg) {
    reg.sort<TransformComponent>(
        [](const TransformComponent& lhs, const TransformComponent& rhs) { return lhs.translation.z >= rhs.translation.z; });
}

void Scene::init_script(entt::registry& reg, entt::entity entity) {
    if (is_running) {
        LOG_CORE_TRACE("Scene::init_script");
        Entity e = {entity, this};
        ScriptEngine::on_init_entity(e);

        if (!is_paused) {
            ScriptEngine::on_start_entity(e);
        }
    }
}

void Scene::release_script(entt::registry& reg, entt::entity entity) {
    if (is_running) {
        Entity e = {entity, this};
        ScriptEngine::on_destroy_entity(e);
    }
}

Scene::Scene() {
    // auto ent = createEntity("PrimaryCamera");
    // auto& cam = ent.addComponent<SceneCamera>();
    // cam.SetPerspective(90, 0.5, 200);
    // cam.SetViewportSize(500, 500);

    registry.on_construct<ScriptComponent>().connect<&Scene::init_script>(this);
    registry.on_destroy<ScriptComponent>().connect<&Scene::release_script>(this);

    pData = create_ref<SceneData>();
}

Entity Scene::createEntityWithUUID(UUID uuid, const std::string& name) {
    LOG_CORE_TRACE("Created basic entity with UUID {}", name);
    Entity e = {registry.create(), this};
    e.addComponent<IDComponent>(uuid);
    e.addComponent<TransformComponent>();
    e.addComponent<PriorityComponent>(0);
    auto& tag = e.addComponent<TagComponent>();
    tag.tag = name.empty() ? "Entity" : name;
    entityMap[uuid] = e;
    return e;
}

Entity Scene::createEntity(const std::string& name) { return createEntityWithUUID(UUID(), name); }

Entity Scene::createBasicEntity(const std::string& name) {
    LOG_CORE_TRACE("Created basic entity {}", name);
    Entity e = {registry.create(), this};
    auto uuid = UUID();
    e.addComponent<IDComponent>(uuid);
    e.addComponent<PriorityComponent>(0);
    auto& tag = e.addComponent<TagComponent>();
    tag.tag = name.empty() ? "Entity" : name;
    entityMap[uuid] = e;
    return e;
}

Entity Scene::createEntityActor(const std::string& name, const std::string& script) {
    LOG_CORE_TRACE("Created entity actor {}", name);
    Entity ent = createEntity(name);
    ent.addComponent<ScriptComponent>(script);
    return ent;
}

Entity Scene::getPrimaryCameraEntity() {
    auto view = registry.view<CameraComponent, TagComponent>();
    for (auto ent : view) {
        auto& tag = view.get<TagComponent>(ent);
        if (tag.tag == "PrimaryCamera") {
            return Entity{ent, this};
        }
    }
    throw std::runtime_error("Could not find primary camera entity");
}

void Scene::startRuntime() {
    LOG_CORE_TRACE("Scene::startRuntime()");

    is_running = true;

    // start_physics();

    ScriptEngine::on_runtime_start(this);

    // Init
    {
        auto view = registry.view<ScriptComponent>();
        for (auto e : view) {
            Entity entity = {e, this};
            ScriptEngine::on_init_entity(entity);
        }
    }

    is_paused = false;

    // Start
    {
        auto view = registry.view<ScriptComponent>();
        for (auto e : view) {
            ScriptEngine::on_start_entity({e, this});
        }
    }
}

void Scene::stopRuntime() {
    auto view = registry.view<ScriptComponent>();
    for (auto e : view) {
        ScriptEngine::on_stop_entity({e, this});
    }

    ScriptEngine::on_runtime_stop(this);
    is_running = false;
    is_paused = true;
}

void Scene::step(double dt) {

    onUpdateWindow();

    ImGui::SFML::Update(pData->window, pData->deltaClock.restart());

    pData->window.clear();
    try {
        onUpdateRuntime(dt);

    } catch (const std::exception& e) {
        LOG_ERROR("Exception thrown in lua: {}", e.what());
    }

    onUpdateSimulation(dt);
}

void Scene::onUpdateWindow() {
    sf::RenderWindow& window = pData->window;
    sf::Event event;
    while (window.pollEvent(event)) {
        ImGui::SFML::ProcessEvent(window, event);

        if (event.type == sf::Event::Closed) {
            is_running = false;
            window.close();
        }

        if (event.type == sf::Event::Resized) {
            LOG_CORE_INFO("Window Resized");
            // pData->window_width = event.size.width;
            // pData->window_height = event.size.height;
            // float new_width = pData->initial_aspect_ratio * pData->window_height;
            // float new_height = pData->window_width / pData->initial_aspect_ratio;
            // float offset_width = (pData->window_width - new_width) / 2.0;
            // float offset_height = (pData->window_height - new_height) / 2.0;
            //
            Entity primaryCamera = getPrimaryCameraEntity();
            sf::View& view = primaryCamera.getComponent<CameraComponent>().view;
            //
            // // sf::View view = pData->window.getView();
            // if (pData->window_width >= pData->initial_aspect_ratio * pData->window_height) {
            //     auto rect =
            //         sf::FloatRect({offset_width / pData->window_width, 0.0}, {new_width / pData->window_width, 1.0});
            //     view.setViewport(rect);
            // } else {
            //     view.setViewport(sf::FloatRect({0.0, offset_height / pData->window_height},
            //                                    {1.0, new_height / pData->window_height}));
            // }
            view = sf::View(sf::FloatRect({0, 0}, {(float)event.size.width, (float)event.size.height}));
            // pData->window.setView(view);
            // view.setViewport({{0,0},{1,1}});

            pData->window.setView(view);
        }
    }
}

void Scene::onUpdateSimulation(double dt) {}

void Scene::onUpdateRuntime(double dt) {
    if (is_running && !is_paused) {

        while (!toBeDestroyed.empty()) {
            Entity e = toBeDestroyed.front();
            toBeDestroyed.pop();

            entt::entity handle = static_cast<entt::entity>(e);
            registry.destroy(handle);
        }

        registry.sort<PriorityComponent>([](const auto& lhs, const auto& rhs) { return lhs.priority > rhs.priority; });
        auto view = registry.view<ScriptComponent, PriorityComponent>();
        view.use<PriorityComponent>();
        for (auto e : view) {
            Entity entity = {e, this};
            ScriptEngine::on_update_entity(entity, dt);
        }
        ScriptEngine::update_dispatcher();
    }
}

void Scene::renderScene(Entity camera) {

    // Camera setup
    {
        auto& cc = camera.getComponent<CameraComponent>();
        const auto& tf = camera.getComponent<TransformComponent>();
        const auto& pos = tf.getPosition();
        cc.view.setCenter({pos.x, pos.y});
        pData->window.setView(cc.view);
    }

    registry.sort<TransformComponent>(
        [](const TransformComponent& lhs, const TransformComponent& rhs) { return lhs.translation.z > rhs.translation.z; });

    // Sprites
    {
        auto view = registry.view<SpriteComponent, TransformComponent>();
        view.use<TransformComponent>();
        for (auto e : view) {
            SpriteComponent& sc = view.get<SpriteComponent>(e);
            TransformComponent& tc = view.get<TransformComponent>(e);
            const auto pos = tc.getPosition();
            sc.sprite->setPosition({pos.x, pos.y});
            sc.sprite->setColor({(uint8_t)sc.color.r, (uint8_t)sc.color.g, (uint8_t)sc.color.b, (uint8_t)sc.color.a});
            auto rect = sc.sprite->getLocalBounds();
            sc.sprite->setOrigin({rect.width/2, rect.height/2});

            sc.sprite->setScale({tc.scale.x, tc.scale.y});
            // sc.sprite->setTextureRect( {
            //         {(int)pos.x, (int)pos.y},
            //         {(int)sc.dimensions.x, (int)sc.dimensions.y}}
            //     );
            pData->window.draw(*sc.sprite);
        }
    }

    // Circles
    {
        auto view = registry.view<CircleComponent, TransformComponent>();
        view.use<TransformComponent>();
        for (auto e : view) {
            CircleComponent& cc = view.get<CircleComponent>(e);
            TransformComponent& tc = view.get<TransformComponent>(e);
            


            const auto pos = tc.getPosition();
            cc.shape.setPosition({pos.x, pos.y});
            cc.shape.setOrigin({cc.shape.getRadius(), cc.shape.getRadius()});
            sf::Color fill(cc.fillColor.r, cc.fillColor.g, cc.fillColor.b, cc.fillColor.a);
            sf::Color outline(cc.outlineColor.r, cc.outlineColor.g, cc.outlineColor.b, cc.outlineColor.a);
            cc.shape.setFillColor(fill);
            cc.shape.setOutlineColor(outline);
            cc.shape.setOutlineThickness(1);

            pData->window.draw(cc.shape);
        }
    }

    ImGui::SFML::Render(pData->window);

    pData->window.display();
}

Entity Scene::getEntityByUUID(UUID uuid) {
    auto iter = entityMap.find(uuid);
    if (iter == entityMap.end()) {
        std::cerr << "Could not find entity with UUID " << uuid << "\n";
        return {};
    }
    return {iter->second, this};
}

Entity Scene::findEntityByName(std::string_view name) {
    auto view = registry.view<TagComponent>();
    for (auto entity : view) {
        const TagComponent& tc = view.get<TagComponent>(entity);
        if (tc.tag == name)
            return Entity{entity, this};
    }
    return {};
}

void Scene::destroyEntity(Entity e) {
    LOG_CORE_TRACE("Scene::destroyEntity({})", e.getUUID());
    toBeDestroyed.push(e);
}

double Scene::deltaTime() const {
    if (pData) {
        return pData->deltaClock.getElapsedTime().asSeconds();
    }
    return 0;
}

Coord<WorldSpace> Scene::get_mouse_position() {
    Coord<ScreenSpace> sp = InputSystem::get_mouse_position(&pData->window);

    auto ws = pData->window.mapPixelToCoords({(int)sp.pos.x, (int)sp.pos.y});
    return {{ws.x, ws.y}};
}
