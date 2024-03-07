#pragma once

#include "layer.h"

#include <sptr/sptr.h>

#include <imgui.h>

struct MapLayer : public Layer {
  MapLayer() {

    scale(1.0);
  }

  void render() {
    const sptr::GameState &gs = sptr::GameState::instance();

    ImGui::Begin("Map");

    if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_MouseWheelY))) {
      // scale(2);
      std::cout << "mousewheel\n";
    }

    for (int y = 0; y < dim; y++)
      for (int x = 0; x < dim; x++) {
        if (x > 0)
          ImGui::SameLine();
        ImGui::PushID(y * dim + x);
        if (ImGui::Selectable("-", selected[y][x] != 0, 0, ImVec2(10, 10))) {
          // Toggle clicked cell + toggle neighbors
        }
        ImGui::PopID();
      }

    ImGui::End();
  }

  void scale(float scale) {
    dim *= scale;
    cellsize *= 1.0 / scale;
    selected.resize(dim);
    for (int x = 0; x < dim; ++x) {
      selected[x].resize(dim);
    }
  }

  std::vector<std::vector<char>> selected;
  int dim = 50;
  int cellsize = 10;
};
