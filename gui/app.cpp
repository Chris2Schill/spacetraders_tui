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
#include "app.h"

#include <string>
#include <chrono>
#include <thread>
#include <notcute/logger.hpp>


// Set to true to quit the application
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::microseconds;
using std::chrono::duration;
typedef duration<double> seconds;
typedef std::chrono::time_point<high_resolution_clock> time_point;

Application* Application::instance = nullptr;

Application::Application(const std::string& name)
    :name(name)
    ,imguiLayer(name)
{
    instance = this;
    imguiLayer.init();
}
Application::~Application()
{
    instance = nullptr;
    imguiLayer.shutdown();

    for (auto layer : layers)
    {
        delete layer;
    }
}

void Application::run()
{
    while (isRunning)
    {
        for (auto& layer : layers)
        {
            layer->update();
        }

        imguiLayer.beginFrame();
        for (auto& layer : layers)
        {
            layer->render();
        }
        imguiLayer.endFrame();
    }
}

void Application::run_in_existing_gameloop()
{
    if (endFrame)
    {
        ImGui::End();
        imguiLayer.endFrame();
        endFrame = false;
    }

    for (auto& layer : layers)
    {
        layer->update();
    }
    imguiLayer.beginFrame();
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::Begin(name.c_str(), NULL,ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking);
    for (auto& layer : layers)
    {
        layer->render();
    }
    endFrame = true;
}

void Application::run_fixed_timestep()
{
    const microseconds dt(static_cast<int>(1000000.0 / targetFps));
    const unsigned int MAX_STEPS = 1;

    microseconds totalSimulationTime(0);
    microseconds accumulator(0);

    time_point currentTime = high_resolution_clock::now();

    while (isRunning)
    {
        time_point now = high_resolution_clock::now();
        microseconds frameTime = duration_cast<microseconds>(now - currentTime);
        currentTime = now;

        accumulator += frameTime;

        unsigned int currentStep = 0; 
        while (accumulator >= dt && currentStep++ < MAX_STEPS && isRunning)
        {
            time_point frameStart = high_resolution_clock::now();
            try
            {
                for (auto& layer : layers)
                {
                    layer->update();
                }

                imguiLayer.beginFrame();
                for (auto& layer : layers)
                {
                    layer->render();
                }
                imguiLayer.endFrame();
            }
            catch (const std::exception& e)
            {
                quit();
                // LOG(ERR) << "Unexpected exit: " << e.what();
            }
            microseconds frameDuration = duration_cast<microseconds>(high_resolution_clock::now() - frameStart);

            if (frameDuration > dt)
            {
                // LOG(WARNING) << "Frame Overrun: expected = " << duration_cast<duration<double, std::milli>>(dt).count()
                //     << " ms, actual = " << (duration_cast<duration<double, std::milli>>(frameDuration).count()) << " ms.";
            }
#ifndef NDEBUG
            else
            {
                // LOG(INFO) << "Frame Time: expected = " << duration_cast<duration<double, std::milli>>(dt).count()
                //     << " ms, actual = " << (duration_cast<duration<double, std::milli>>(frameDuration).count()) << " ms.";
            }
#endif

            accumulator -= dt;
            totalSimulationTime += dt;
        }

        std::this_thread::sleep_for(microseconds(1));
    }
}

double Application::get_timestep() const {
    auto dt = std::chrono::microseconds(static_cast<int>(1000000.0 / targetFps));
    return std::chrono::duration_cast<std::chrono::duration<double>>(dt).count();
}

void Application::setWindowPos(int x, int y)
{
    imguiLayer.setWindowPos(x,y);
}

void Application::resizeWindow(int width, int height)
{
    imguiLayer.resizeWindow(width, height);
}

