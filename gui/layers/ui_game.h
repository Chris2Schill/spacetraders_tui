#pragma once

#include "layer.h"
#include <sptr/sptr.h>

#include <imgui.h>
#include <vector>

#include "agent.h"
#include "contracts.h"
#include "eventlog.h"
#include "map.h"
#include "market.h"
#include "ship_details.h"
#include "ships.h"
#include "shipyard.h"
#include "waypoints.h"
#include <engine/scene/entity.h>
#include <engine/scene/scene.h>

#include <engine/renderer/renderer.h>

#include <imgui_demo.cpp>

struct UIGame : public Layer {
    UIGame() {
        scene = create_ref<Scene>();

        sptr::DataProvider::instance().init_ships_and_starting_system();

        layers.push_back(std::make_shared<AgentLayer>());
        layers.push_back(std::make_shared<ContractsLayer>());
        layers.push_back(std::make_shared<ShipsLayer>());
        layers.push_back(std::make_shared<WaypointsLayer>());
        layers.push_back(std::make_shared<ShipDetailsLayer>());
        layers.push_back(std::make_shared<MapLayer>());
        layers.push_back(std::make_shared<EventLogLayer>());
        layers.push_back(std::make_shared<ShipyardLayer>());
        layers.push_back(std::make_shared<MarketplaceLayer>());

        // Renderer::s_SceneData.quads = create_ref<VertexArray>();
        // add_quad(0,0, 40, 40);
    }

    void update() override {
        for (auto& layer : layers) {
            layer->update();
        }
    }

    // void add_quad(float xPos, float yPos, float width, float height) {
    //
    //     float xPosLeft = xPos - width / 2;
    //     float yPosBottom = yPos - height / 2;
    //
    //     glm::vec3 normOutScreen(0, 0, 1);
    //
    //     std::vector<Vertex> vertices =
    //     {
    //         // // Position                                         Normal                 Color
    //         Vertex{ glm::vec3(xPosLeft, yPosBottom, 0.0),              normOutScreen,  glm::vec3(1.0, 1.0, 1.0), glm::vec2(1, 0) },
    //         // { glm::vec3(xPosLeft+width, yPosBottom, 0.0),        normOutScreen,  glm::vec3(1.0, 1.0, 1.0), glm::vec2(1, 1) },
    //         // { glm::vec3(xPosLeft+width, yPosBottom+height, 0.0), normOutScreen,  glm::vec3(1.0, 1.0, 1.0), glm::vec2(0, 1) },
    //         // { glm::vec3(xPosLeft, yPosBottom+height, 0.0),       normOutScreen,  glm::vec3(1.0, 1.0, 1.0), glm::vec2(0, 0) } 
    //     };
    //
    //     std::vector<unsigned int> indices =
    //     {
    //         0, 1, 2,
    //         2, 3, 0
    //     };
    //
    //     auto vbl = std::make_shared<VertexBufferLayout>();
    //     vbl->push<float>(3);
    //     vbl->push<float>(3);
    //     vbl->push<float>(3);
    //
    //     auto vb = std::make_shared<VertexBuffer>(&vertices[0],
    //                                             sizeof(Vertex)*vertices.size());
    //
    //     auto va = std::make_shared<VertexArray>();
    //     va->addBuffer(vb, vbl);
    //
    //     auto ib = std::make_shared<IndexBuffer>(&indices[0], indices.size());
    //
    //     va->unbind();
    //     vb->unbind();
    //     ib->unbind();
    //     
    //     Renderer::s_SceneData.quads->addBuffer(vb, vbl);
    // }

    void render() override {
        ImGui::ShowDemoWindow();
        for (auto& layer : layers) {
            layer->render();
        }
        // ImGui::Begin("SPTR");
        // ImGui::End();

        // Entity camera = scene.getPrimaryCameraEntity();
        // if (!camera) {
        //     return;
        // }

        // Renderer::beginScene(camera.getComponent<CameraComponent>().camera,
        //                      camera.getComponent<TransformComponent>().getTransform());
    }

    Ref<Scene> scene;

  private:
    std::vector<LayerPtr> layers;
};
