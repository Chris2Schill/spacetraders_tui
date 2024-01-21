#pragma once


#include <ncpp/NotCurses.hh>
#include <notcute/notcute.hpp>
#include <notcute/list_widget.hpp>
#include <notcute/dialog.hpp>
#include <notcute/edittext.hpp>
#include <notcute/frame_widget.hpp>
#include <notcute/main_window.hpp>

#include <CppRestOpenAPIClient/api/DefaultApi.h>

#include "notcute/include/notcute/logger.hpp"
#include "sptr_api.h"


class UserListWidgetItem : public notcute::ListItem {
public:
    UserListWidgetItem(sptr::User* user) :user(user) {}

    notcute::Widget* get_widget() override { return nullptr; }

    sptr::User* get_user() { return user; }

    std::string to_string() const override {
        return user->name;
    }

private:
    sptr::User* user;
};

class TitleWidget : public notcute::TextWidget {
public:
    TitleWidget(notcute::Widget* parent = nullptr)
        : notcute::TextWidget(title(), parent, LAY_LEFT){
        set_scrolling(true);
    }

    void draw(ncpp::Plane* p) {
        ncpp::Cell c(' ');
        c.set_bg_rgb8(255,0,0);
        c.set_bg_alpha(0);
        // p->set_bg_alpha(1000000000);

        uint64_t channels = c.get_channels();
        // uint32_t fg = channels & NCCHANNELS_INIT
        uint32_t fg = NCCHANNEL_INITIALIZER(0,0,0);

        // ncchannel_set_alpha(uint32_t* channel, unsigned alpha){
        // c.set_bg_alpha(ncpp::Cell::AlphaBlend);
        // p->polyfill(0,0,c);

        p->set_fg_palindex(1);
        p->set_bg_alpha(NCALPHA_OPAQUE);
        p->set_bg_palindex(2);
        notcute::TextWidget::draw(p);
        // p->polyfill(0,0,c);
    }

    static const std::string& title() {
       static const std::string t = 
           "  _____ _____        _____ ______   _______ _____            _____  ______ _____   _____ \n"
           " / ____|  __ \\ /\\   / ____|  ____| |__   __|  __ \\     /\\   |  __ \\|  ____|  __ \\ / ____|\n"
           "| (___ | |__) /  \\ | |    | |__       | |  | |__) |   /  \\  | |  | | |__  | |__) | (___  \n"
           " \\___ \\|  ___/ /\\ \\| |    |  __|      | |  |  _  /   / /\\ \\ | |  | |  __| |  _  / \\___ \\ \n"
           " ____) | |  / ____ \\ |____| |____     | |  | | \\ \\  / ____ \\| |__| | |____| | \\ \\ ____) |\n"
           "|_____/|_| /_/    \\_\\_____|______|    |_|  |_|  \\_\\/_/    \\_\\_____/|______|_|  \\_\\_____/ ";
       return t;
    }
};

class MainMenu : public notcute::Widget {
public:
    MainMenu(Widget* parent = nullptr)
        : Widget(parent)
    {
        set_name("MainMenu");
        layout = new notcute::VBoxLayout(this);

        title = new TitleWidget(this);
        title->set_name("main_menu_title");
        title->get_layout()->set_behave(LAY_TOP);
        layout->add_widget(title);

        desc = new notcute::TextWidget("A cute little space game", this);
        desc->set_scrolling(true),
        desc->get_layout()->set_behave(LAY_BOTTOM);
        desc->get_layout()->set_margins_ltrb(0, 1, 0, 0);
        desc->set_name("main_menu_desc");
        layout->add_widget(desc);

        sptr::load_saved_users();

        notcute::ListWidget* user_list = new notcute::ListWidget(this);
        user_list->get_layout()->set_size(10, 25);
        user_list->get_layout()->set_behave(LAY_HCENTER);
        user_list->set_focus();
        user_list->set_name("user_list");
        user_list->set_title("Agents");
        for (auto& user : sptr::get_users()) {
            user_list->add_item(new UserListWidgetItem(&user));
        }
        user_list->add_text("REGISTER NEW AGENT");
        layout->add_widget(user_list);

        user_list->item_selected.connect([this, user_list](notcute::ListItem* item){
                if (item->to_string() == "REGISTER NEW AGENT") {
                    auto* new_user = register_new_agent();
                    if (new_user) {
                        user_list->add_item(new UserListWidgetItem(new_user));
                    }
                    user_list->set_focus();
                }
                else if  (UserListWidgetItem* ui = dynamic_cast<UserListWidgetItem*>(item); ui) {
                    const sptr::User* user = ui->get_user();
                    sptr::set_user(*user);
                    user_selected(*user);
                    done_showing();
                }
            });
    }

    sptr::User* register_new_agent() {

        notcute::FullScreenDialog dialog("Enter New Agent Name");
        dialog.exec();
        Widget::get_focused_widget() = nullptr;

        if (dialog.get_was_canceled()) {
            return nullptr;
        }

        const std::string& new_agent_name = dialog.get_entry();

        try{
            static api::DefaultApi api(sptr::get_api_client());
            auto request = std::make_shared<api::Register_request>();
            request->setSymbol(new_agent_name);
            auto faction = std::make_shared<api::FactionSymbol>();
            faction->setValue(models::FactionSymbol::eFactionSymbol::FactionSymbol_COSMIC);
            request->setFaction({faction});
            auto task = api.r_register(request);
            task.wait();
            auto new_agent = task.get()->getData();
            // notcute::log_debug(fmt::format("NEW USER RESP: {}", new_agent->toJson().serialize()));

            sptr::User newUser;
            newUser.name = new_agent->getAgent()->getSymbol();
            newUser.token = new_agent->getToken();
            sptr::get_users().push_back(newUser);
            sptr::write_saved_users();

            return &sptr::get_users().back();
        }
        catch(const std::exception& e){
            notcute::log_debug(e.what());
        }
        return nullptr;
    }

    // Signals
    boost::signals2::signal<void(const sptr::User& user)> user_selected;

    notcute::TextWidget* title = nullptr;
private:

    notcute::TextWidget* desc = nullptr;
    notcute::Layout* layout = nullptr;
};
