// ==========================================================================
// UNLIMITED RIGHTS
// Contract No. W900KK-23-D-0001/W900KK-23-F-00023
// [Flight School Training Support Services (FSTSS)]
//
// Contractor Name: Applied Visual Technology, Inc.
//                  (d/b/a AVT Simulation)
//
// Contractor Address: 4715 Data Court
//                     Orlando, Florida 32817
//
// SECURITY CLASSIFICATION: Unclassified
//
// WARNING: This software contains data whose export is restricted by the Arms
// Export Control Act (Title 22, U.S.C., Section 2751 et seq.) or the Export
// Administration Act of 1979, as amended, Title 50, U.S.C, APP. 2401 et seq.
//
// Copyright © 2023, 2024
// Applied Visual Technology, Inc. (d/b/a AVT Simulation)
// Unpublished Work - All Rights Reserved
// ==========================================================================
#pragma once

#include <vector>

#if _WIN32
#    include <winsock2.h>
#elif linux
#    include <arpa/inet.h>
#endif

#include "layer.h"
#include "glfw_opengl_imgui_layer.h"


class Application
{
public:
    Application(const std::string& name);
    virtual ~Application();

    void run(); // normal fast as can be
    void run_fixed_timestep(); // limit framerate
    void run_in_existing_gameloop(); // inject into existing game loop
    void quit() { isRunning = false; }

    void setWindowPos(int xpos, int ypos);
    void resizeWindow(int width, int height);

    const std::string& getName() const { return name; }

    static Application& get() { return *instance; }
    static Application* get_instance() { return instance; }

protected:
    std::string name;
    bool isRunning = true;
    ImGuiLayer imguiLayer;
    std::vector<Layer*> layers;
    static Application* instance;
    bool endFrame = false;
    int targetFps = 30;
};

