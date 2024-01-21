// #include "spacetraders_app.hpp"

#include <notcute/colors.hpp>
#include <notcute/layout.hpp>
#include <notcute/frame_widget.hpp>
#include <notcute/scroll_area.hpp>
#include <notcute/spacer.hpp>

#include "spacetraders_tui.hpp"

int main() {

    using namespace notcute;
    FrameWidget::defaults.frame_title_fg = notcute::WHITE;
    FrameWidget::defaults.frame_fg = notcute::DARK_YELLOW;

    SpaceTradersTui app;
    app.show();


    MainWindow* mw = new notcute::MainWindow();


    // ListWidget* list = new ListWidget(mw); 
    // list->get_layout()->set_size(20,20);
    // list->get_layout()->set_behave(LAY_CENTER | LAY_FILL);
    // // list->set_should_adjust_size_to_contents(true);
    // for (int i = 0; i < 20; ++i) {
    //     list->add_text("BOIII" + std::to_string(i));
    // }
    //
    // mw->get_layout()->add_widget(list);
    // list->set_focus();
    //
    // for (auto _ : {1,2,3,4,5,6}) {
    //     Widget* w1 = new FrameWidget(mw);
    //     w1->set_layout(new VBoxLayout);
    //     mw->get_layout()->add_widget(w1);
    // }


    Widget* content = new Widget(mw);
    content->set_name("scroll_content");
    content->set_layout(new VBoxLayout(50,50));
    ScrollArea* sq = new notcute::ScrollArea(content, mw);
    sq->set_layout(new VBoxLayout(40,40));
    sq->get_layout()->set_behave(LAY_CENTER);
    content->get_layout()->set_behave(LAY_FILL);
    content->get_layout()->set_contain(LAY_COLUMN);
    for (int i = 0; i < 3; ++i) {
        auto frame = new FrameWidget(content);
        frame->set_name("main frame" + std::to_string(i));
        frame->set_title("main frame" + std::to_string(i));
        frame->set_layout(new VBoxLayout(10,10));

        auto inner_frame = new FrameWidget(frame);
        inner_frame->set_layout(new VBoxLayout(5,5));
        inner_frame->set_title("innerf" + std::to_string(i));
        inner_frame->set_name("innerf" + std::to_string(i));
        inner_frame->get_layout()->set_margins_ltrb(1,1,1,1);
        frame->get_layout()->add_widget(inner_frame);

        // auto tw = new TextWidget("tw"+std::to_string(i), inner_frame);
        // tw->get_layout()->set_behave(LAY_CENTER);
        // tw->set_name("tw"+std::to_string(i));
        // tw->get_layout()->set_margins_ltrb(1,1,1,1);
        // inner_frame->get_layout()->add_widget(tw);

        auto list = new ListWidget(inner_frame);
        list->set_name("list");
        list->set_title("list");
        list->add_text("BOIII"+std::to_string(i));
        list->add_text("BOIII"+std::to_string(i));
        list->add_text("BOIII"+std::to_string(i));
        list->add_text("BOIII"+std::to_string(i));
        list->add_text("BOIII"+std::to_string(i));
        list->add_text("BOIII"+std::to_string(i));
        list->add_text("BOIII"+std::to_string(i));
        inner_frame->get_layout()->add_widget(list);

        content->get_layout()->add_widget(frame);
    }
    mw->get_layout()->add_widget(sq);
    sq->set_focus();

    // content->show();
    //
    // content->get_layout()->add_widget(new TextWidget("1", content));
    // content->get_layout()->add_widget(new TextWidget("2", content));
    // content->get_layout()->add_widget(new TextWidget("3AAAAAAA\nNEWLINNN", content));
    // content->get_layout()->add_widget(new TextWidget("4AAAAAAA", content));
    // content->get_layout()->add_widget(new TextWidget("6CCCCCCC", content));
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
    // content->get_layout()->add_widget(new TextWidget("1", content));
    // content->get_layout()->add_widget(new TextWidget("2", content));
    // content->get_layout()->add_widget(new TextWidget("3AAAAAAA\nNEWLINNN", content));
    // content->get_layout()->add_widget(new TextWidget("4AAAAAAA", content));
    // content->get_layout()->add_widget(new TextWidget("6CCCCCCC", content));
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
    // content->get_layout()->add_widget(new Spacer(content));

    // content->show();
    // sq->set_content(content);


    // mw->get_layout()->run_context();
    // mw->get_layout()->print_view_tree_dimensions();
    mw->show();
}

