#pragma once

#include <vector>
#include <algorithm>
#include <functional>
#include <map>
#include <GLFW/glfw3.h>

namespace input
{

class Keyboard
{
public:


    struct Event
    {
        int key;
        int scancode;
        int action;
        int mods;
    };

    struct key_state
    {
        int key;
        int state;
        std::function<void(key_state)> actionWhenPressed;
    };

    struct Listener
    {
        std::map<int, input::Keyboard::key_state> keyPressedMap;

        void updateKeyPressedMap(Event event)
        {
            auto iter = keyPressedMap.find(event.key);
            if (iter != keyPressedMap.end())
            {
                input::Keyboard::key_state& keyState = iter->second;

                keyState.state = event.action;
            }
        }

        virtual void handleKeyboardEvent(Event event) = 0;
    };

    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        notify({key, scancode, action, mods});
    }

    static void registerForKeyboardEvents(Listener* listener)
    {
        listeners.push_back(listener);
    }
    static void unregisterForKeyboardEvents(Listener* listener)
    {
        listeners.erase(std::remove(listeners.begin(),
            listeners.end(),
            listener));
    }

private:
    static void notify(Event e)
    {
        for (auto l : listeners)
        {
            l->updateKeyPressedMap(e);
            l->handleKeyboardEvent(e);
        }
    }

    static std::vector<Listener*> listeners;
};


} // namespace input

