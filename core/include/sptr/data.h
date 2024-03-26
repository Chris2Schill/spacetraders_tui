#pragma once

#include <entt/entt.hpp>
#include <thread>
#include <variant>
#include <vector>

#include <CppRestOpenAPIClient/api/AgentsApi.h>
#include <CppRestOpenAPIClient/api/ContractsApi.h>
#include <CppRestOpenAPIClient/api/FleetApi.h>
#include <CppRestOpenAPIClient/api/SystemsApi.h>

#include "CppRestOpenAPIClient/model/Extract_resources_request.h"
#include "CppRestOpenAPIClient/model/Navigate_ship_200_response_data.h"
#include "CppRestOpenAPIClient/model/Navigate_ship_request.h"
#include "CppRestOpenAPIClient/model/SellCargoRequest.h"
#include "CppRestOpenAPIClient/model/ShipNavRoute.h"
#include "events.h"
#include "sptr.h"
#include <engine/core/base.h>
#include <engine/scene/components.h>
#include <engine/scene/entity.h>
#include <engine/scene/scene.h>

#define API_ERROR_GUARD_START try {
#define API_ERROR_GUARD_END                                                                                            \
    }                                                                                                                  \
    catch (const api::ApiException& ex) {                                                                              \
        notcute::log_debug("{}", ex.what());                                                                           \
        sptr::event_bus::Dispatcher::getInstance().post(sptr::event::LogEvent{ex.what()});                             \
        auto ss = std::dynamic_pointer_cast<std::stringstream>(ex.getContent());                                       \
        if (nullptr != ss) {                                                                                           \
            notcute::log_debug("{}", ss->str());                                                                       \
            sptr::event_bus::Dispatcher::getInstance().post(sptr::event::LogEvent{ss->str()});                         \
        }                                                                                                              \
    }

namespace sptr {

inline static const glm::vec3 UNIVERSE_SCALE = {1.f, 1.f, 1.f};

inline std::vector<std::string> tokenize(const std::string& str, char delim) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    while (getline(ss, token, delim)) {
        tokens.push_back(token);
    }
    return tokens;
}

inline std::vector<User> load_users() {
    mINI::INIFile file("users.ini");
    mINI::INIStructure ini;
    file.read(ini);

    std::vector<User> users;

    for (auto& [section, data] : ini) {
        User u;
        u.name = section;
        u.token = data.get("token");

        std::transform(u.name.begin(), u.name.end(), u.name.begin(), [](unsigned char c) { return std::toupper(c); });

        users.push_back(u);
    }
    return users;
}

using Agent = std::shared_ptr<api::Agent>;
using Contract = std::shared_ptr<api::Contract>;
using Contracts = std::vector<Contract>;
using Waypoint = std::shared_ptr<api::Waypoint>;
using Waypoints = std::vector<Waypoint>;
using Ship = std::shared_ptr<api::Ship>;
using Ships = std::vector<Ship>;
using ShipRequirements = std::shared_ptr<api::ShipRequirements>;
using ShipEngine = std::shared_ptr<api::ShipEngine>;
using ShipFrame = std::shared_ptr<api::ShipFrame>;
using ShipFuel = std::shared_ptr<api::ShipFuel>;
using ShipMount = std::shared_ptr<api::ShipMount>;
using ShipReactor = std::shared_ptr<api::ShipReactor>;
using ShipNavRoute = std::shared_ptr<api::ShipNavRoute>;
using Shipyard = std::shared_ptr<api::Shipyard>;
using ShipyardShip = std::shared_ptr<api::ShipyardShip>;
using ShipRegistration = std::shared_ptr<api::ShipRegistration>;
using ShipMount = std::shared_ptr<api::ShipMount>;
using ShipMounts = std::vector<ShipMount>;
using ShipModule = std::shared_ptr<api::ShipModule>;
using ShipModules = std::vector<ShipModule>;
using ShipCrew = std::shared_ptr<api::ShipCrew>;
using ShipCargo = std::shared_ptr<api::ShipCargo>;
using ShipCargoItem = std::shared_ptr<api::ShipCargoItem>;
using Market = std::shared_ptr<api::Market>;
using MarketTradeGood = std::shared_ptr<api::MarketTradeGood>;
using MarketTransaction = std::shared_ptr<api::MarketTransaction>;
using TradeGood = std::shared_ptr<api::TradeGood>;

struct ShipComponent {
    std::shared_ptr<models::Ship> ship;
    double flight_time = 0;
};
struct WaypointComponent {
    std::shared_ptr<models::Waypoint> waypoint;
};

struct GameState {
    Ref<Scene> scene = create_ref<Scene>();

    struct Entities {
        std::unordered_map<std::string, Entity> ships;
        std::unordered_map<std::string, Entity> waypoints;
    } entities;

    std::vector<User> users;
    const User* active_user;
    Agent my_agent;
    Contracts pending_contracts;
    Contracts active_contracts;
    Ships ships;
    int waypointsCombo = 0;

    struct Selection {
        Entity ship;
        Entity waypoint;
        Shipyard shipyard = nullptr;
        Market market = nullptr;

    } selected;

    GameState() {
        users = load_users();
        gs_instance = this;
    }

    void set_active_user(const User* u) {
        active_user = u;
        sptr::set_user(*active_user);
    }

    sptr::Ship get_selected_ship() {
        if (selected.ship) {
            return selected.ship.getComponent<ShipComponent>().ship;
        }
        return nullptr;
    }

    void set_selected_ship(Ship ship) { selected.ship = entities.ships.at(ship->getSymbol()); }

    Waypoint get_waypoint(const std::string& waypointSymbol) {
        auto iter = entities.waypoints.find(waypointSymbol);
        if (iter != entities.waypoints.end()) {
            return iter->second.getComponent<WaypointComponent>().waypoint;
        }
        return nullptr;
    }

    inline static GameState* gs_instance = nullptr;
    inline static GameState& instance() { return *gs_instance; }
    inline static std::vector<User>& get_users() { return gs_instance->users; }
};

struct DataProvider {
    inline static DataProvider* dp_instance = nullptr;
    static DataProvider& instance() { return *dp_instance; }

    struct apis {
        ::api::AgentsApi agents = ::api::AgentsApi(sptr::get_api_client());
        ::api::ContractsApi contracts = ::api::ContractsApi(sptr::get_api_client());
        ::api::SystemsApi systems = ::api::SystemsApi(sptr::get_api_client());
        ::api::FleetApi fleet = ::api::FleetApi(sptr::get_api_client());
    } apis;

    DataProvider(GameState* gs) : gs(gs) {
        dp_instance = this;
        bus.subscribe<Agent>(this, &DataProvider::receive_agent);
        bus.subscribe<Contracts>(this, &DataProvider::receive_contracts);
        bus.subscribe<Waypoints>(this, &DataProvider::receive_waypoints);
        bus.subscribe<Ships>(this, &DataProvider::receive_ships);
        bus.subscribe<Shipyard>(this, &DataProvider::receive_shipyard);
        bus.subscribe<Market>(this, &DataProvider::receive_marketplace);
        bus.subscribe<Ref<models::Navigate_ship_200_response_data>>(this, &DataProvider::receive_ship_navigate_success);
    }

    void init_ships_and_starting_system() {

        auto agent_request = apis.agents.getMyAgent();
        auto ships_request = apis.fleet.getMyShips({}, {});

        agent_request.wait();
        ships_request.wait();

        receive_agent(agent_request.get()->getData());
        receive_ships(ships_request.get()->getData());

        // load the system of the command ship
        // TODO: is it safe to assume we always have a command ship?? We start with one but
        // it may get destroyed or scrapped? Probably should fallback onto a ship
        for (auto [symbol, entity] : gs->entities.ships) {
            const ShipComponent& sc = entity.getComponent<ShipComponent>();
            if (sc.ship->getRegistration()->getRole()->getValue() ==
                    models::ShipRole::eShipRole::ShipRole_COMMAND) {
                gs->selected.ship = entity;
                break;
            }
        }

        // request_waypoints();
        request_contracts();
    }

    void request_agent() {
        sptr::event_bus::Dispatcher::getInstance().post(sptr::event::LogEvent{"Request agents"});
        apis.agents.getMyAgent().then([this](auto x) {
            API_ERROR_GUARD_START
            auto agent = x.get()->getData();
            std::scoped_lock lock(mtx);
            event_queue.push(agent);
            API_ERROR_GUARD_END
        });
    }
    void receive_agent(const Agent& agent) { gs->my_agent = agent; }

    void request_contracts() {
        apis.contracts.getContracts({}, {}).then([this](auto task) {
            API_ERROR_GUARD_START
            Contracts new_contracts = task.get()->getData();
            std::scoped_lock lock(mtx);
            event_queue.push(new_contracts);
            API_ERROR_GUARD_END
        });
    }

    void request_accept_contracts(const Contract& contract) {
        apis.contracts.acceptContract(contract->getId()).then([](auto task) {
            API_ERROR_GUARD_START
            task.get()->getData();
            API_ERROR_GUARD_END
        });
        request_contracts();
    }

    void receive_contracts(const Contracts& contracts) {
        gs->pending_contracts.clear();
        gs->active_contracts.clear();
        for (auto& c : contracts) {
            if (c->isAccepted()) {
                gs->active_contracts.push_back(c);
            } else {
                gs->pending_contracts.push_back(c);
            }
        }
    }

    static const int FIRST_PAGE = 1;
    void request_waypoints(const std::string& system_symbol,
                           boost::optional<std::shared_ptr<models::WaypointTraitSymbol>> traits = {},
                           int page = FIRST_PAGE) {

        sptr::event_bus::Dispatcher::getInstance().post(
            event::LogEvent{fmt::format("Requesting System Waypoints Page {}", page)});

        // if (page == FIRST_PAGE &&
        //     sptr::MAIN_THREAD_ID == std::this_thread::get_id()) {
        //     gs->waypoints.clear();
        // }

        static const int ITEMS_PER_PAGE = 20;
        auto x = apis.systems.getSystemWaypoints(system_symbol, page, ITEMS_PER_PAGE, {}, traits)
                     .then([this, system_symbol, traits, page](auto task) {
                         API_ERROR_GUARD_START
                         auto waypoints = task.get()->getData();
                         std::scoped_lock lock(mtx);
                         event_queue.push(waypoints);
                         if (waypoints.size() == ITEMS_PER_PAGE) {
                             request_waypoints(system_symbol, traits, page + 1);
                         }
                         API_ERROR_GUARD_END
                     });
    }

    void register_entity(const Waypoint wp) {

    }

    void receive_waypoints(const Waypoints& waypoints) {
        for (const auto& wp : waypoints) {

            auto iter = gs->entities.waypoints.find(wp->getSymbol());
            if (iter == gs->entities.waypoints.end()) {

                Entity e = gs->scene->createEntity(wp->getSymbol());
                e.addComponent<WaypointComponent>(wp);
                auto& tf = e.getComponent<TransformComponent>();
                tf.translation = glm::vec3(wp->getX(), wp->getY(), 0);
                tf.translation *= sptr::UNIVERSE_SCALE;
                gs->entities.waypoints.insert({wp->getSymbol(), e});
                continue;
            }

            Entity& waypoint_entity = iter->second;
            waypoint_entity.getComponent<WaypointComponent>().waypoint = wp;
        }
    }

    void request_ships() {
        apis.fleet.getMyShips({}, {}).then([this](auto task) {
            API_ERROR_GUARD_START
            auto ships = task.get()->getData();
            std::scoped_lock lock(mtx);
            event_queue.push(ships);
            API_ERROR_GUARD_END
        });
    }

    void receive_ships(const Ships& ships) {
        for (const auto& ship : ships) {

            auto iter = gs->entities.ships.find(ship->getSymbol());
            if (iter == gs->entities.ships.end()) {

                Entity e = gs->scene->createEntity(ship->getSymbol());
                e.addComponent<ShipComponent>(ship);

                // e.getComponent<TransformComponent>().translation = glm::vec3();
                gs->entities.ships.insert({ship->getSymbol(), e});
                continue;
            }

            Entity& ship_entity = iter->second;
            ship_entity.getComponent<ShipComponent>().ship = ship;
        }
    }

    void request_orbit(const Ships& ships) {
        for (auto& s : ships) {
            apis.fleet.orbitShip(s->getSymbol()).then([](auto task) {
                API_ERROR_GUARD_START
                task.get()->getData();
                API_ERROR_GUARD_END
            });
        }
        request_ships();
    }

    void request_dock_ship(const Ships& ships) {
        for (auto& s : ships) {
            apis.fleet.dockShip(s->getSymbol()).then([](auto task) {
                API_ERROR_GUARD_START
                task.get()->getData();
                API_ERROR_GUARD_END
            });
        }
        request_ships();
    }

    void request_ship_refuel(const Ship& ship) {
        auto req = std::make_shared<models::Refuel_ship_request>();
        // req->setUnits(
        //     std::ceil(ship->getFuel()->getConsumed()->getAmount() / 100.0f));
        req->setUnits(ship->getFuel()->getConsumed()->getAmount());

        std::string msg = fmt::format("Request refuel ({} units)", req->getUnits());
        sptr::event_bus::Dispatcher::getInstance().post(event::LogEvent{msg});

        apis.fleet.refuelShip(ship->getSymbol(), req).then([this](auto task) {
            API_ERROR_GUARD_START
            task.get()->getData();
            request_ships();
            API_ERROR_GUARD_END
        });
    }

    template <typename Waypoint> void request_ship_navigate_to_waypoint(const Ships& ships, const Waypoint& wp) {
        for (auto& s : ships) {
            auto req = std::make_shared<models::Navigate_ship_request>();
            req->setWaypointSymbol(wp->getSymbol());
            apis.fleet.navigateShip(s->getSymbol(), {req}).then([this, s](auto task) {
                API_ERROR_GUARD_START
                auto response = task.get()->getData();
                event_queue2.push([this, s]() {
                    std::cout << "RESET FLIGHT TIME\n";
                    request_ships();
                    gs->entities.ships.at(s->getSymbol()).getComponent<ShipComponent>().flight_time = 0;
                });
                API_ERROR_GUARD_END
            });
        }
    }

    void receive_ship_navigate_success(const Ref<models::Navigate_ship_200_response_data>& e) {}

    void request_shipyard(const Waypoint& wp) {
        sptr::event_bus::Dispatcher::getInstance().post(event::LogEvent{"Requesting Shipyard"});
        apis.systems.getShipyard(wp->getSystemSymbol(), wp->getSymbol()).then([this](auto task) {
            API_ERROR_GUARD_START
            auto shipyard = task.get()->getData();
            std::scoped_lock lock(mtx);
            event_queue.push(shipyard);
            API_ERROR_GUARD_END
        });
    }
    void receive_shipyard(const Shipyard& sy) { gs->selected.shipyard = sy; }

    void request_ship_extract(const Ship& ship) {
        auto req = std::make_shared<models::Extract_resources_request>();
        apis.fleet.extractResources(ship->getSymbol(), req).then([this](auto task) {
            API_ERROR_GUARD_START
            task.get()->getData();
            request_ships();
            API_ERROR_GUARD_END
        });
    }

    void request_marketplace(const Waypoint& wp) {
        apis.systems.getMarket(wp->getSystemSymbol(), wp->getSymbol()).then([this](auto task) {
            API_ERROR_GUARD_START
            auto market = task.get()->getData();
            std::scoped_lock lock(mtx);
            event_queue.push(market);
            API_ERROR_GUARD_END
        });
    }
    void receive_marketplace(const Market& mp) { gs->selected.market = mp; }

    void request_sell_cargo(const Ship& ship, const ShipCargoItem& item, int amount) {
        auto req = std::make_shared<models::SellCargoRequest>();
        req->setSymbol(item->getSymbol());
        req->setUnits(amount);
        apis.fleet.sellCargo(ship->getSymbol(), req).then([](auto task) {
            API_ERROR_GUARD_START
            task.get()->getData();
            API_ERROR_GUARD_END
        });
    }

    void request_purchase_ship(const std::string& waypointSymbol, const ShipyardShip& ship) {
        auto req = std::make_shared<models::Purchase_ship_request>();
        req->setWaypointSymbol(waypointSymbol);
        req->setShipType(ship->getType());
        apis.fleet.purchaseShip(req);
        request_ships();
    }

    void update() { process_events(); }

    void process_events() {
        if (!event_queue.empty()) {
            std::scoped_lock lock(mtx);
            while (!event_queue.empty()) {
                Event& e = event_queue.front();
                std::visit([this](auto&& arg) { this->bus.post(arg); }, e);
                event_queue.pop();
            }
        }

        if (!event_queue2.empty()) {
            std::scoped_lock lock(mtx);
            while (!event_queue2.empty()) {
                auto& foo = event_queue2.front();
                foo();
                event_queue2.pop();
            }
        }
    }

    template<typename Callable>
    void on_main_thread(Callable&& func) {
        std::scoped_lock lock(mtx);
        event_queue2.push(func);
    }

    sptr::event_bus::Dispatcher bus;
    using Event = std::variant<Agent, Contracts, Waypoints, Ships, Shipyard, Market,
                               Ref<models::Navigate_ship_200_response_data>>;

    GameState* gs = nullptr;
    std::mutex mtx;
    std::queue<Event> event_queue;
    std::queue<std::function<void()>> event_queue2;
};

} // namespace sptr
