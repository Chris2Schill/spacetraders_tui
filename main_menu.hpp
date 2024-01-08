#pragma once


#include <ncpp/NotCurses.hh>
#include <ncfw/context.hpp>
#include <ncfw/layout.hpp>
#include <ncfw/selector.hpp>
#include <ncfw/framed_context.hpp>
#include <ncfw/reader.hpp>

//#include "spacetraders-sdk/include/CppRestOpenAPIClient/ApiClient.h"
#include <CppRestOpenAPIClient/api/DefaultApi.h>

#include "sptr_api.h"

class MainMenu : public ncfw::VerticalLayout {
public:
    MainMenu() {
        sptr::load_saved_users();

        using namespace ncfw::Align;

        // contexts[ncfw::CONTEXT_MAIN_MENU] = ctx;
        // context = ctx;

        ncplane_options popts = *ncfw::Context::default_options();
        popts.cols = 89;
        popts.rows = 20;

        // ncfw::VerticalLayout* ctx = new ncfw::VerticalLayout(this, popts);
        // ncfw::draw_center_lines(ctx);
        set_alignment(VCenter|HCenter);

        const std::string title = "  _____ _____        _____ ______   _______ _____            _____  ______ _____   _____ "
                                  " / ____|  __ \\ /\\   / ____|  ____| |__   __|  __ \\     /\\   |  __ \\|  ____|  __ \\ / ____|"
                                  "| (___ | |__) /  \\ | |    | |__       | |  | |__) |   /  \\  | |  | | |__  | |__) | (___  "
                                  " \\___ \\|  ___/ /\\ \\| |    |  __|      | |  |  _  /   / /\\ \\ | |  | |  __| |  _  / \\___ \\ "
                                  " ____) | |  / ____ \\ |____| |____     | |  | | \\ \\  / ____ \\| |__| | |____| | \\ \\ ____) |"
                                  "|_____/|_| /_/    \\_\\_____|______|    |_|  |_|  \\_\\/_/    \\_\\_____/|______|_|  \\_\\_____/ ";


        auto title_text = new ncfw::Context(this);
        title_text->resize(6, 89);
        title_text->set_alignment(HCenter); 
        title_text->set_scrolling(true);
        title_text->putstr(title.c_str());
        add(title_text);
        auto mainmenu = new ncfw::Selector(this, &popts);
        mainmenu->item_selected.connect([&](ncfw::SelectorItem* item){
                if (item->get_name() == "REGISTER NEW AGENT") {
                    auto* new_user = register_new_agent();
                    if (new_user) {
                        mainmenu->add_item(new ncfw::SelectorItem(new_user->name, new_user));
                    }
                }
                else {
                    sptr::User* user = item->get_item<sptr::User>();
                    sptr::set_user(*user);
                    user_selected(user);
                }
            });
        mainmenu->set_focusable(true);
        mainmenu->set_alignment(Center);
        for (auto& user : sptr::get_users()) {
            mainmenu->add_item(new ncfw::SelectorItem(user.name, &user));
        }
        mainmenu->add_item(new ncfw::SelectorItem("REGISTER NEW AGENT"));
        add(mainmenu, ncfw::Context::FOCUSED);
    }


    boost::signals2::signal<void(sptr::User* user)> user_selected;

    sptr::User* register_new_agent() {
        
        ncreader_options opts {
            .tchannels = NCCHANNEL_INITIALIZER(255,255,255),
            .flags = NCREADER_OPTION_HORSCROLL | NCREADER_OPTION_CURSOR
        };
        ncplane_options popts {
            .rows = 1,
            .cols = 50,
        };
        ncplane_options popts2 {
            .rows = 4,
            .cols = 50,
        };

        auto mainctx = new ncfw::VerticalLayout();
        auto reader_layout = new ncfw::VerticalLayout(mainctx, &popts2);
        auto plane = new ncfw::FramedContext(reader_layout, &popts);

        auto reader_plane = new ncfw::Context(plane, &popts);
        auto reader = new ncfw::Reader(reader_plane, &opts);

        reader_layout->perimeter_double(0,0,0);
        reader_layout->add(new ncfw::Text("Enter New Agent Name", reader_layout));
        reader_layout->add(plane);
        // reader->printf("BBBBBBB");

        bool quit = false;
        while (!quit) {
            mainctx->show();
            ncinput ni;
            ncpp::NotCurses::get_instance().get(true, &ni);
            reader->offer_input(&ni);
            if (ni.id == NCKEY_ENTER) {
                quit = true;
            }
        }
        auto newName = std::string(reader->get_contents());
        delete mainctx;



        static api::DefaultApi api(sptr::get_api_client());
        auto request = std::make_shared<api::Register_request>();
        request->setSymbol(newName);
        auto faction = std::make_shared<api::FactionSymbol>();
        faction->setValue(models::FactionSymbol::eFactionSymbol::FactionSymbol_COSMIC);
        request->setFaction({faction});
        auto task = api.r_register(request);
        task.wait();
        auto new_agent = task.get()->getData();
        log_debug(fmt::format("NEW USER RESP: {}", new_agent->toJson().serialize()));

        sptr::User newUser;
        newUser.name = new_agent->getAgent()->getSymbol();
        newUser.token = new_agent->getToken();
        sptr::get_users().push_back(newUser);
        sptr::write_saved_users();

        return &sptr::get_users().back();
    }

};
