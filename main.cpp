// #include "spacetraders_app.hpp"

#include "main_menu.hpp"
#include "notcute/include/notcute/box.hpp"
#include "spacetraders_tui.hpp"
#include <notcute/frame_widget.hpp>
#include <notcute/scroll_area.hpp>
#include <notcute/spacer.hpp>

int main() {

    // SpaceTradersTui app;
    // app.show();

    using namespace notcute;

    MainWindow* mw = new notcute::MainWindow();
    mw->debug_set_plane_color(100,0,0);


    ScrollArea* sq = new notcute::ScrollArea(nullptr, mw);
    sq->debug_set_plane_color(0,0,100);
    sq->get_layout()->set_behave(LAY_CENTER);


    Widget* content = new Widget(sq);
    content->set_name("scroll_content");
    content->set_layout(new VBoxLayout(10,10));
    content->debug_set_plane_color(0,100,0);

    sq->set_content(content);

    content->get_layout()->set_behave(LAY_FILL);
    content->get_layout()->set_contain(LAY_COLUMN);

    for (int i = 0; i < 2; ++i) {
        auto frame = new FrameWidget(content);
        frame->set_layout(new VBoxLayout(10,10));

        auto inner_frame = new FrameWidget(frame);
        inner_frame->set_layout(new VBoxLayout(10,10));
        frame->get_layout()->add_widget(inner_frame);
        // auto tw = new TextWidget("5BB", frame);
        // tw->get_layout()->set_margins_ltrb(1,1,1,1);
        // frame->get_layout()->add_widget(tw);

        content->get_layout()->add_widget(frame);
    }

    // content->get_layout()->add_widget(new TextWidget("1", content));
    // content->get_layout()->add_widget(new TextWidget("2", content));
    // content->get_layout()->add_widget(new TextWidget("3AAAAAAA\nNEWLINNN", content));
    // content->get_layout()->add_widget(new TextWidget("4AAAAAAA", content));
    // // content->get_layout()->add_widget(new TextWidget("6CCCCCCC", content));
    // content->get_layout()->add_widget(new Spacer(content));
    // content->get_layout()->add_widget(new TextWidget("7DDDDDDE", content));
    // content->get_layout()->add_widget(new TextWidget("EEEEEEEE", content));
    // content->get_layout()->add_widget(new TextWidget("FFFFFFFF", content));
    // content->get_layout()->add_widget(new TextWidget("GGGGGGGG", content));
    // content->get_layout()->add_widget(new TextWidget("HHHHHHHH", content));
    // content->get_layout()->add_widget(new TextWidget("IIIIIIII", content));
    // content->get_layout()->add_widget(new TextWidget("JJJJJJJJ", content));
    // content->get_layout()->add_widget(new TextWidget("LLLLLLLL", content));
    // content->get_layout()->add_widget(new TextWidget("MMMMMMMM", content));
    // content->get_layout()->add_widget(new TextWidget("NNNNNNNNNNNNN", content));
    // content->get_layout()->add_widget(new TextWidget("NNNNNNNNNNNNN", content));
    // content->get_layout()->add_widget(new TextWidget("NNNNNNNNNNNNN", content));
    // content->get_layout()->add_widget(new TextWidget("NNNNNNNNNNNNN", content));
    // content->get_layout()->add_widget(new TextWidget("NNNNNNNNNNNNN", content));
    // content->get_layout()->add_widget(new TextWidget("NNNNNNNNNNNNN", content));
    // content->get_layout()->add_widget(new TextWidget("NNNNNNNNNNNNN", content));
    // content->get_layout()->add_widget(new TextWidget("NNNNNNNNNNNNN", content));
    // content->get_layout()->add_widget(new TextWidget("BBBBBBBBBB", content));
    // content->get_layout()->add_widget(new TextWidget("BBBBBBBBBB", content));
    // content->get_layout()->add_widget(new TextWidget("BBBBBBBBBB", content));
    // content->get_layout()->add_widget(new TextWidget("BBBBBBBBBB", content));


    mw->get_layout()->add_widget(sq);

    mw->get_layout()->run_context();
    mw->get_layout()->print_view_tree_dimensions();
    sq->set_focus();
    // mw->set_draw_line_numbers();
    mw->show();
}

