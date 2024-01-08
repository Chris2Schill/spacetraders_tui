#pragma once

#include <ncpp/Plane.hh>
#include "sptr_api.h"

#include <ncfw/logger.h>
#include "panels/panel.h"
#include <ncfw/selector.hpp>
#include "panels/my_agent.h"
#include "panels/log_panel.h"
#include "panels/framed_plane.h"
#include "panels/contracts_panel.h"
// #include "panels/waypoints_panel.h"




// class ScrollablePlanePanel : public FramedPlane {
// public:
//     ScrollablePlanePanel(int rows, int cols, int y, int x)
//         : FramedPlane(rows, cols, y, x)
//         , currentIndex(0, rows)
//     {
//     }
//
//     void update() override {
//         update_frame();
//
//         // contents->erase();
//         for (unsigned i = currentIndex.get_value(), row = 0; i < lines.size(); ++i, row++) {
//             contents->printf(row, 0, lines[i].c_str());
//         }
//         // for (unsigned i = currentIndex.get_value(), row = 0; i < lines.size(); ++i, row++) {
//         //     contents->printf(row, 0, lines[i].c_str());
//         // }
//     }
//
//     void erase() {
//         lines.clear();
//     }
//     
//     void setLines(const std::vector<std::string>& lines) {
//         this->lines = lines;
//     }
//
//     void putstr(std::string str) {
//         lines.push_back(str);
//     }
//
//     void handle_input(char c) override {
//         switch(c) {
//             case 'j': {
//                 currentIndex.next();
//                 log_debug(fmt::format("current idx = {}", currentIndex.get_value()));
//                 break;
//             }
//             case 'k': {
//                 currentIndex.prev();
//                 log_debug(fmt::format("current idx = {}", currentIndex.get_value()));
//                 break;
//             }
//         }
//     }
//
// protected:
//
//     RingIndex currentIndex;
//     std::vector<ncpp::Plane*> planes;
//     
// };


// class VerticalFramedPlaneList : public FramedPlane {
//
//     void update() override {
//         int row, col = 1;
//
//         for (auto panel : panels) {
//             int x = panel->get_x();
//             int y = panel->get_y();
//
//             panel->move(y, x);
//             
//
//         }
//     }
//
// private:
//     std::vector<FramedPlane*> panels; 
// };
//
