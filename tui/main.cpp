// #include "spacetraders_app.hpp"

#include <notcute/colors.hpp>
#include <notcute/layout.hpp>
#include <notcute/frame_widget.hpp>
#include <notcute/scroll_area.hpp>
#include <notcute/spacer.hpp>

#include "notcute/notcute.hpp"
#include "spacetraders_tui.hpp"

int main() {

    using namespace notcute;
    FrameWidget::defaults.frame_title_fg = notcute::WHITE;
    FrameWidget::defaults.frame_fg = notcute::WHITE;

    {
        SpaceTradersTui app;
        app.show();
    }

    report_closing_diagnostic();
}

