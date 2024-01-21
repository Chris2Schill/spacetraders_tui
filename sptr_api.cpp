#include "sptr_api.h"
#include "notcute/logger.hpp"

#include <thread>

namespace sptr {

static const User* user = nullptr;

void set_user(const User& user) {
    sptr::user = &user;

    auto new_config = std::make_shared<api::ApiConfiguration>();
    *new_config = *get_api_client()->getConfiguration();
    new_config->setBaseUrl("https://api.spacetraders.io/v2");
    new_config->setApiKey("", user.token);
    new_config->getDefaultHeaders()["Authorization"] = "Bearer " + user.token;
    get_api_client()->setConfiguration(new_config);
    get_api_client()->setResponseHandler([](web::http::status_code code, const web::http::http_headers&){
            if (code != 200) {
                notcute::log_debug("Http Response not 200: " + std::to_string(code));
            }
        });
}

const User& get_user() {
    if (!user) {
        throw std::runtime_error("Current User ptr is null");
    }
    return *user;
}

}

// namespace sptr::net {
//
// std::thread net_thread;
//
// void start() {
//     net_thread = std::thread([]{
//             trantor::Logger::setLogLevel(trantor::Logger::kTrace);
//             drogon::app().run();
//         });
// }
//
// void stop() {
//     if (drogon::app().isRunning()) {
//         drogon::app().quit();
//         net_thread.join();
//     }
// }
//
// drogon::HttpClient& client() {
//     static auto c = drogon::HttpClient::newHttpClient(
//             "https://api.spacetraders.io"
//         );
//
//     return *c;
// }
//
//
// } // end namespace sptr::net
//
// namespace sptr::api {
//     void request_get_agent_info(const std::string& token) {
//
//         sptr::net::client().getLoop()->queueInLoop(drogon::async_func(
//                 [=]() -> drogon::Task<void>{
//                     auto req = drogon::HttpRequest::newHttpRequest();
//                     req->setMethod(drogon::Get);
//                     req->setPath("/v2/my/agent");
//                     std::cout << "request info with token " << token << "\n";
//                     req->addHeader("Authorization", "Bearer " + token);
//                     auto response = co_await sptr::net::client().sendRequestCoro(req, 2);
//                     std::cout << "got it\n";
//                     event_bus::Dispatcher::getInstance().post(std::string(response->getBody()));
//                 }
//             ));
//     }
//
//     void request_view_contracts() {
//         // curl 'https://api.spacetraders.io/v2/my/contracts' \
//         //  --header 'Authorization: Bearer INSERT_TOKEN_HERE'
//     }
//
//     void request_accept_contracts() {
//          // curl --request POST \
//          // --url 'https://api.spacetraders.io/v2/my/contracts/:contractId/accept' \
//          // --header 'Authorization: Bearer INSERT_TOKEN_HERE'
//     }
//
//     void request_get_starting_waypoint() {
//          // curl 'https://api.spacetraders.io/v2/systems/:systemSymbol/waypoints/:waypointSymbol' \
//          // --header 'Authorization: Bearer INSERT_TOKEN_HERE'
//     }
//
//     void request_get_find_shipyard() {
//          // curl 'https://api.spacetraders.io/v2/systems/:systemSymbol/waypoints?traits=SHIPYARD' \
//          // --header 'Authorization: Bearer INSERT_TOKEN_HERE'
//     }
//
//
//     void request_get_view_available_ships() {
//          // curl 'https://api.spacetraders.io/v2/systems/:systemSymbol/waypoints/:shipyardWaypointSymbol/shipyard' \
//          // --header 'Authorization: Bearer INSERT_TOKEN_HERE'
//     }
//
//     void request_post_purchase_ship() {
//          // curl --request POST \
//          // --url 'https://api.spacetraders.io/v2/my/ships' \
//          // --header 'Authorization: Bearer INSERT_TOKEN_HERE' \
//          // --header 'Content-Type: application/json' \
//          // --data '{
//          //    "shipType": "SHIP_MINING_DRONE",
//          //    "waypointSymbol": ":shipyardWaypointSymbol"
//          //   }'
//     }
//
//     void request_get_find_engineered_asteroid() {
//         // curl 'https://api.spacetraders.io/v2/systems/:systemSymbol/waypoints?type=ENGINEERED_ASTEROID' \
//         //  --header 'Authorization: Bearer INSERT_TOKEN_HERE'
//         
//     }
//
//     void request_post_enter_orbit() {
//         // curl --request POST \
//         // --url 'https://api.spacetraders.io/v2/my/ships/:miningShipSymbol/orbit' \
//         // --header 'Authorization: Bearer INSERT_TOKEN_HERE'
//     }
//
//     void navigate_to_waypoint() {
//         // curl --request POST \
//         // --url 'https://api.spacetraders.io/v2/my/ships/:miningShipSymbol/navigate' \
//         // --header 'Authorization: Bearer INSERT_TOKEN_HERE' \
//         // --header 'Content-Type: application/json' \
//         // --data '{
//         // "waypointSymbol": ":asteroidWaypointSymbol"
//         // }'
//     }
//
//     void request_post_dock_ship() {
//         // curl --request POST \
//         //     --url 'https://api.spacetraders.io/v2/my/ships/:miningShipSymbol/dock' \
//         //     --header 'Authorization: Bearer INSERT_TOKEN_HERE'
//     }
// }
