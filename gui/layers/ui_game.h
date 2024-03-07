#pragma once

#include "layer.h"
#include <sptr/sptr.h>

#include <imgui.h>

#include "agent.h"
#include "contracts.h"
#include "ships.h"
#include "waypoints.h"
#include "ship_details.h"
#include "map.h"
#include "shipyard.h"
#include "eventlog.h"
#include "market.h"
#include <engine/scene/entity.h>
#include <engine/scene/scene.h>

#include <engine/renderer/renderer.h>

#include <imgui_demo.cpp>

struct UIGame : public Layer {
  UIGame() {
    layers.push_back(std::make_shared<AgentLayer>());
    layers.push_back(std::make_shared<ContractsLayer>());
    layers.push_back(std::make_shared<ShipsLayer>());
    // layers.push_back(std::make_shared<WaypointsLayer>());
    layers.push_back(std::make_shared<ShipDetailsLayer>());
    layers.push_back(std::make_shared<MapLayer>());
    layers.push_back(std::make_shared<EventLogLayer>());
    layers.push_back(std::make_shared<ShipyardLayer>());
    layers.push_back(std::make_shared<MarketplaceLayer>());
  }

  void update() override {
    for (auto &layer : layers) {
      layer->update();
    }
  }

  void render() override {
    ImGui::ShowDemoWindow();
    for (auto &layer : layers) {
      layer->render();
    }
    // ImGui::Begin("SPTR");
    // ImGui::End();

    Entity camera = scene.getPrimaryCameraEntity();
    if (!camera) {
      return;
    }
    // Renderer::beginScene(camera.getComponent<CameraComponent>().camera,
    // camera.getComponent<TransformComponent>().getTransform());
  }

  Scene scene;

private:
  std::vector<LayerPtr> layers;
};
