#include <ncfw/notcurses_app.h>

#include <sstream>

#include <notcurses/notcurses.h>
#include <ncpp/Selector.hh>

#include <ncfw/logger.h>

namespace ncfw
{

std::vector<ncpp::Pile*> piles;

Application* Application::instance = nullptr;

Application::Application(const std::string& name)
    :name(name)
{
    EVENT_SUBSCRIBE<ChangeContext>(this, &Application::onEvent);


    instance = this;

    // panels[PANEL_MAIN_MENU]->reparent(piles[0]);
    // panels[PANEL_DASHBOARD]->reparent(piles[1]);


    // panels.push_back(new MyAgentPanel(10, 50, 0, 0));
    // panels.push_back(new ContractsPanel(10, 50, 15, 0));
    // // panels.push_back(new WaypointsReel());
    // panels.push_back(new WaypointsPanel2());

    // panels[PANEL_MYAGENT]->refresh();
    // panels[PANEL_MYAGENT]->is_selected = true;
}

void Application::onEvent(const ChangeContext& e) {
    context = contexts[e.contextId];
}

Application::~Application()
{
    instance = nullptr;
}

void Application::handle_input()
{
    // timespec timeout = {.tv_sec = 1, .tv_nsec = 0 };
    
    ncinput ni;
    char c = nc.get(false, &ni);

    if (c != 0) {
        std::stringstream ss;
        ss << "key_pressed: " << c;
        log_debug(ss.str());
    }

    bool handled = context->offer_input(&ni);
    if (handled) { log_debug("context handled input"); return; }

    switch (ni.id) {
        case 'r':
        {
           context->refresh(); 
           break;
        }
    }
}

void Application::run()
{
    while (isRunning)
    {
        try {
            context->update();
            context->show();

            handle_input();
        } catch(const std::exception& e) {
            log_debug(std::string("unhandled exception: ") + e.what());
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
}

}// end namespace sptr
