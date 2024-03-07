#pragma once

#include <thread>
#include <variant>
#include <vector>

#include <CppRestOpenAPIClient/api/AgentsApi.h>
#include <CppRestOpenAPIClient/api/ContractsApi.h>
#include <CppRestOpenAPIClient/api/FleetApi.h>
#include <CppRestOpenAPIClient/api/SystemsApi.h>

#include "CppRestOpenAPIClient/model/Extract_resources_request.h"
#include "CppRestOpenAPIClient/model/Navigate_ship_request.h"
#include "CppRestOpenAPIClient/model/SellCargoRequest.h"
#include "CppRestOpenAPIClient/model/ShipNavRoute.h"
#include "events.h"
#include "sptr.h"

#define API_ERROR_GUARD_START try {
#define API_ERROR_GUARD_END                                                    \
    }                                                                          \
    catch (const api::ApiException& ex) {                                      \
        notcute::log_debug("{}", ex.what());                                   \
        sptr::event_bus::Dispatcher::getInstance().post(                       \
            sptr::event::LogEvent{ex.what()});                                 \
        auto ss =                                                              \
            std::dynamic_pointer_cast<std::stringstream>(ex.getContent());     \
        if (nullptr != ss) {                                                   \
            notcute::log_debug("{}", ss->str());                               \
            sptr::event_bus::Dispatcher::getInstance().post(                   \
                sptr::event::LogEvent{ss->str()});                             \
        }                                                                      \
    }

namespace sptr {

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

        std::transform(u.name.begin(), u.name.end(), u.name.begin(),
                       [](unsigned char c) { return std::toupper(c); });

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

struct GameState {
    std::vector<User> users;
    const User* active_user;
    Agent my_agent;
    Contracts pending_contracts;
    Contracts active_contracts;
    Ships ships;
    Waypoints waypoints;
    int waypointsCombo = 0;

    struct Selection {
        Ship ship = nullptr;
        Waypoint waypoint = nullptr;
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

    inline static GameState* gs_instance = nullptr;
    inline static GameState& instance() { return *gs_instance; }
    inline static std::vector<User>& get_users() { return gs_instance->users; }
};

inline Waypoint get_waypoint(const Ship& ship) {
    GameState& gs = GameState::instance();
    for (auto wp : gs.waypoints) {
        if (wp->getSymbol() == ship->getNav()->getWaypointSymbol()) {
            return wp;
        }
    }
    return nullptr;
}

struct DataProvider {
    inline static DataProvider* dp_instance = nullptr;
    static DataProvider& instance() { return *dp_instance; }

    struct apis {
        ::api::AgentsApi agents = ::api::AgentsApi(sptr::get_api_client());
        ::api::ContractsApi contracts =
            ::api::ContractsApi(sptr::get_api_client());
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
    }

    void remote_data_load_init() {
        request_agent();
        request_contracts();
        request_ships();
    }

    void request_agent() {
        sptr::event_bus::Dispatcher::getInstance().post(
            sptr::event::LogEvent{"Request agents"});
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
    void request_waypoints(
        const std::string& system_symbol,
        boost::optional<std::shared_ptr<models::WaypointTraitSymbol>> traits =
            {},
        int page = FIRST_PAGE) {

        sptr::event_bus::Dispatcher::getInstance().post(event::LogEvent{
            fmt::format("Requesting System Waypoints Page {}", page)});

        if (page == FIRST_PAGE &&
            sptr::MAIN_THREAD_ID == std::this_thread::get_id()) {
            gs->waypoints.clear();
        }

        static const int ITEMS_PER_PAGE = 20;
        auto x = apis.systems
                     .getSystemWaypoints(system_symbol, page, ITEMS_PER_PAGE,
                                         {}, traits)
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

    void receive_waypoints(const Waypoints& waypoints) {
        for (auto wp : waypoints) {
            // const std::string& symbol = wp->getSymbol();
            // auto tokens = tokenize(symbol, '-');
            gs->waypoints.push_back(wp);
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
        if (gs->selected.ship) {
            for (auto& s : ships) {
                if (s->getSymbol() == gs->selected.ship->getSymbol()) {
                    gs->selected.ship = s;
                    break;
                }
            }
        }
        gs->ships = ships;
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

        std::string msg =
            fmt::format("Request refuel ({} units)", req->getUnits());
        sptr::event_bus::Dispatcher::getInstance().post(event::LogEvent{msg});

        apis.fleet.refuelShip(ship->getSymbol(), req).then([this](auto task) {
            API_ERROR_GUARD_START
            task.get()->getData();
            request_ships();
            API_ERROR_GUARD_END
        });
    }

    template <typename Waypoint>
    void request_ship_navigate_to_waypoint(const Ships& ships,
                                           const Waypoint& wp) {
        for (auto& s : ships) {
            auto req = std::make_shared<models::Navigate_ship_request>();
            req->setWaypointSymbol(wp->getSymbol());
            apis.fleet.navigateShip(s->getSymbol(), {req}).then([](auto task) {
                API_ERROR_GUARD_START
                task.get()->getData();
                API_ERROR_GUARD_END
            });
        }
        request_ships();
    }

    void request_shipyard(const Waypoint& wp) {
        sptr::event_bus::Dispatcher::getInstance().post(
            event::LogEvent{"Requesting Shipyard"});
        apis.systems.getShipyard(wp->getSystemSymbol(), wp->getSymbol())
            .then([this](auto task) {
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
        apis.fleet.extractResources(ship->getSymbol(), req).then([](auto task) {
            API_ERROR_GUARD_START
            task.get()->getData();
            API_ERROR_GUARD_END
        });
    }

    void request_marketplace(const Waypoint& wp) {
        apis.systems.getMarket(wp->getSystemSymbol(), wp->getSymbol())
            .then([this](auto task) {
                API_ERROR_GUARD_START
                auto market = task.get()->getData();
                std::scoped_lock lock(mtx);
                event_queue.push(market);
                API_ERROR_GUARD_END
            });
    }
    void receive_marketplace(const Market& mp) { gs->selected.market = mp; }

    void request_sell_cargo(const Ship& ship, const ShipCargoItem& item,
                            int amount) {
        auto req = std::make_shared<models::SellCargoRequest>();
        req->setSymbol(item->getSymbol());
        req->setUnits(amount);
        apis.fleet.sellCargo(ship->getSymbol(), req).then([](auto task) {
            API_ERROR_GUARD_START
            task.get()->getData();
            API_ERROR_GUARD_END
        });
    }

    void request_purchase_ship(const std::string& waypointSymbol,
                               const ShipyardShip& ship) {
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
    }

    sptr::event_bus::Dispatcher bus;
    using Event =
        std::variant<Agent, Contracts, Waypoints, Ships, Shipyard, Market>;

    GameState* gs = nullptr;
    std::mutex mtx;
    std::queue<Event> event_queue;
};

} // namespace sptr
