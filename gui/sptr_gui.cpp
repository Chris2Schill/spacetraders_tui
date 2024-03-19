#include <app.h>

#include <sptr/sptr.h>
#include <imgui.h>
#include <imgui_internal.h>

#include "layers/main_dockspace.h"
#include "sptr/api.h"

static void *onIniSettingsReadOpen(ImGuiContext *context,
                                   ImGuiSettingsHandler *handler,
                                   const char *name) {
  ImGuiID id = ImHashStr(name);
  ImGuiWindowSettings *settings = ImGui::FindWindowSettingsByID(id);
  if (!settings) {
    settings = ImGui::CreateNewWindowSettings(name);
    settings->ID = id;
    settings->WantApply = true;
  }
  return static_cast<void *>(settings);
}

static void onIniSettingsReadLine(ImGuiContext *, ImGuiSettingsHandler *handler,
                                  void *entry, const char *line) {
  // HalLayer* halLayer = static_cast<HalLayer*>(handler->UserData);
  // int value;
  // if (sscanf(line, "ShowConnectionSettings=%d", &value) == 1) {
  // halLayer->showConnectionSettings = static_cast<bool>(value); } else if
  // (sscanf(line, "ShowAppConsole=%d", &value) == 1) { halLayer->showAppConsole
  // = static_cast<bool>(value); } else if (sscanf(line, "ShowDebugLog=%d",
  // &value) == 1) { halLayer->showAppLog = static_cast<bool>(value); } else if
  // (sscanf(line, "ShowStyleEditor=%d", &value) == 1) {
  // halLayer->showStyleEditor = static_cast<bool>(value); } else if
  // (sscanf(line, "ShowDemoWindow=%d", &value) == 1) { halLayer->showDemoWindow
  // = static_cast<bool>(value); }
}

static void onIniSettingsWriteAll(ImGuiContext *ctx,
                                  ImGuiSettingsHandler *handler,
                                  ImGuiTextBuffer *buf) {
  // HalLayer* halLayer = static_cast<HalLayer*>(handler->UserData);
  // buf->appendf("[%s][HalLayer]\n", handler->TypeName);
  // buf->appendf("ShowConnectionSettings=%d\n",
  // halLayer->showConnectionSettings); buf->appendf("ShowAppConsole=%d\n",
  // halLayer->showAppConsole); buf->appendf("ShowDebugLog=%d\n",
  // halLayer->showAppLog); buf->appendf("ShowStyleEditor=%d\n",
  // halLayer->showStyleEditor); buf->appendf("ShowDemoWindow=%d\n",
  // halLayer->showDemoWindow); buf->appendf("\n");
}

class SpaceTradersApp : public Application {
public:
  SpaceTradersApp() : Application("Space Traders") {
    layers.push_back(new MainDockspaceLayer);

    ImGuiStyle &style = ImGui::GetStyle();
    style.WindowPadding = ImVec2(3, 3);
    style.FramePadding = ImVec2(4, 2);
    style.FrameRounding = 2;
    style.ScrollbarRounding = 12;
    style.TabRounding = 4;

    // ImGuiSettingsHandler iniHandler = {};
    // iniHandler.TypeName = "UserData";
    // iniHandler.TypeHash = ImHashStr("UserData");
    // iniHandler.ReadOpenFn = onIniSettingsReadOpen;
    // // iniHandler.ReadLineFn = onIniSettingsReadLine;
    // // iniHandler.WriteAllFn = onIniSettingsWriteAll;
    // iniHandler.UserData = static_cast<void *>(this);
    // ImGui::AddSettingsHandler(&iniHandler);
    // ImGui::LoadIniSettingsFromDisk("imgui.ini");
  }
};

// template<typename... Component>
// void printComponents(ComponentGroup<Component...>) {
//
//     ([&]()
//     {
//         // print<Component>();
//     }(), ...);
// }

int main() {

  // printComponents(ComponentGroup<RigidBodyComponent, CameraComponent>{});
  sptr::MAIN_THREAD_ID = std::this_thread::get_id();
  SpaceTradersApp app;
  app.run_fixed_timestep();

  // getchar();
}
