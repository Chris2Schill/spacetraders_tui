#pragma once

#include "panel.h"

class LogPanel : public Panel {
public:
    LogPanel()
        : plane(new ncpp::Plane(10, 50, 0, 51))
    {
        plane->set_scrolling(true);
    }

    void hide() {}
    void show() {}
    void update() override {}
    void refresh() override {}

    void setLog(const std::string& log)
    {
        plane->erase();
        plane->perimeter_rounded(0, 0, 0);
        plane->printf(1, 1, "%s",log.c_str());
    }

private:
    ncpp::Plane* plane;
};

