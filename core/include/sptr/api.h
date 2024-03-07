#pragma once

#include <cctype>
#include <algorithm>

#include <notcute/logger.hpp>
#include <notcute/ini.h>
#include <CppRestOpenAPIClient/api/AgentsApi.h>



namespace sptr {

    inline static std::thread::id MAIN_THREAD_ID;

    struct User {
        std::string name;
        std::string token;
    };

    const User& get_user();
    void set_user(const User& user);

    inline std::vector<User>& get_users() {
        static std::vector<User> users;
        return users;
    }

    inline void load_saved_users() {
        mINI::INIFile file("users.ini");
        mINI::INIStructure ini;
        file.read(ini);

        get_users().clear();

        for (auto& [section,data] : ini) {
            User u;
            u.name = section;
            u.token = data.get("token");

            std::transform(u.name.begin(), u.name.end(), u.name.begin(),
                           [](unsigned char c){ return std::toupper(c); });

            get_users().emplace_back(u);
            // notcute::log_debug("user.name = {}", u.name);
            // notcute::log_debug("user.token = {}", u.token);
        }
    }

    inline void write_saved_users() {
        mINI::INIFile file("users.ini");

        mINI::INIStructure ini;
        for (auto& user : get_users()) {
            ini[user.name]["token"] = user.token;
        }

        file.generate(ini);
    }

    // inline std::string read_player_token() {
    //     std::ifstream f("userdata.cfg");
    //     std::string str;
    //     f >> str;
    //     return str;
    // }
    
    inline std::shared_ptr<api::ApiClient> create_api_client() {
        // std::string apiKey = read_player_token();
        // log_debug("api token = {}", apiKey);

        auto configuration = std::make_shared<api::ApiConfiguration>();
        configuration->setBaseUrl("https://api.spacetraders.io/v2");
        // configuration->setApiKey("", apiKey);
        // configuration->getDefaultHeaders()["Authorization"] = "Bearer " + apiKey;
        return std::make_shared<api::ApiClient>(configuration);
    }


    inline std::shared_ptr<api::ApiClient> get_api_client() {
        static auto c = create_api_client();
        return c;
    }

    inline std::string pretty_json(std::string json)
    {
        int tabs, tokens; //here tokens are  { } , :
        tokens = -1;
        char ch;
        std::stringstream fin(json);
        std::stringstream fout;
        while (fin.get(ch))
        {

            if (ch == '{')
            {
                tokens++;

                //open braces tabs
                tabs = tokens;
                if (tokens > 0)
                    fout << "\n";
                while (tabs)
                {
                    fout << "\t";
                    tabs--;
                }
                fout << ch << "\n";

                //json key:value tabs
                tabs = tokens + 1;
                while (tabs)
                {
                    fout << "\t";
                    tabs--;
                }
            }
            else if (ch == ':')
            {
                fout << " : ";
            }
            else if (ch == ',')
            {
                fout <<  ",\n";
                tabs = tokens + 1;
                while (tabs)
                {
                    fout << "\t";
                    tabs--;
                }
            }
            else if (ch == '}')
            {
                tabs = tokens;
                fout << "\n";
                while (tabs)
                {
                    fout << "\t";
                    tabs--;
                }

                fout << ch << "\n";
                tokens--;
                tabs = tokens + 1;

                while (tabs)
                {
                    fout << "\t";
                    tabs--;
                }
            }
            else
            {
                if (ch == '\n' || ch == '\t')
                    continue;
                else
                    fout << ch;
            }
        }
        return fout.str();
    }
}
