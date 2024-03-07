#pragma once

#include <vector>
#include <algorithm>
#include <GLFW/glfw3.h>

namespace input
{

class Mouse
{

public:
    struct Event
    {
        int button;
        int action;
        double xpos;
        double ypos;
    };

    struct Listener
    {
        virtual void handleMouseEvent(Event event) = 0;
    };

    static void registerForMouseEvents(Listener* listener)
    {
        listeners.push_back(listener);
    }
    static void unregisterForMouseEvents(Listener* listener)
    {
        listeners.erase(std::remove(listeners.begin(),
                                    listeners.end(),
                                    listener));
    }

    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
    {
        if (listeners.empty()) return;

        notify({button, action, 0.0, 0.0});
    }

    static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
    {
        if (listeners.empty()) return;

        notify({-1, -1, xpos, ypos});
    }

private:
    static void notify(Event e)
    {
        for (auto l : listeners)
        {
            l->handleMouseEvent(e);
        }
    }

    static std::vector<Listener*> listeners;
};

} // namespace input

