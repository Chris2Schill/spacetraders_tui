#pragma once

#include <mutex>
#include <vector>
#include <sstream>
#include <ncpp/NotCurses.hh>
#include <ncpp/Selector.hh>
#include <ncfw/logger.h>
#include "../sptr_api.h"



enum ePanel {
    PANEL_MAIN_MENU, 
    PANEL_DASHBOARD, 
    PANEL_MYAGENT,
    PANEL_CONTRACTS,
    PANEL_WAYPOINTS,
};

class Panel
{
public:
    virtual ~Panel() = default;
    virtual void update()  = 0;
    virtual void refresh() = 0;
    virtual bool offer_input(ncinput* ni) { return false; }
    virtual void reparent(ncpp::Plane* newParent) {};

    bool is_selected = false;
    std::mutex mtx;
};


class RingIndex {
public:
    RingIndex(int min, int max) 
        : min(min)
        , max(max)
        , value(0)
    {}

    void next() {
        value++;
        if (value > max) {
            value = max;
        }
    }
    void prev() {
        value--;
        if (value < min) {
            value = min;
        }
    }

    int get_min() const { return min; }
    void set_min(int m) { min = m; }

    int get_max() const { return max; }
    void set_max(int m) {  max = m; }

    int get_value() const { return value; }
    bool set_value(int v) { 
        if (min <= value && value <= max) {
            value = v;
            return true;
        }
        return false;
    }

private:
    int min;
    int max;
    int value;
};

inline std::vector<std::string> tokenize(const std::string& str, char delim)
{
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    while (getline(ss, token, delim))
    {
        tokens.push_back(token);
    }
    return tokens;
}
