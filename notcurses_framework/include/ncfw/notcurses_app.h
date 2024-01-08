#pragma once

#include <string>
#include <vector>

#include <notcurses/notcurses.h>
#include <ncpp/NotCurses.hh>
#include <ncpp/Pile.hh>

#include "context.hpp"
#include "event_bus.h"


namespace ncfw
{

extern std::vector<ncpp::Pile*> piles;

class Application
{
public:
    Application(const std::string& name);
    virtual ~Application();

    virtual void run();
    virtual void handle_input();
    virtual void quit() { isRunning = false; }

    const std::string& getName() const { return name; }
    virtual void onEvent(const ChangeContext& e);

    static Application& get() { return *instance; }

protected:
    ncpp::NotCurses nc;
    bool isRunning = true;
    static Application* instance;
    std::string name;
    Context* context = nullptr;
    std::unordered_map<eContext, Context*> contexts;
};

}
