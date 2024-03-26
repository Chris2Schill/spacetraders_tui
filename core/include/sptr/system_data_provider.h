#pragma once

#include "data.h"
#include <unordered_map>

namespace sptr {

static const int REQUEST_PER_SECOND = 2;

void request_system_data(const std::string& systemSymbol);
void request_all_waypoints(const std::string& systemSymbol);

void request_waypoints_page(const std::string& system_symbol,
                            boost::optional<std::shared_ptr<models::WaypointTraitSymbol>> traits = {}, int page = 1);

struct MarketData {
    Market market;
    Waypoint waypoint;
};

struct ShipyardData {
    Shipyard shipyard;
    Waypoint waypoint;
};

struct ImportGoodData {
    std::vector<Waypoint> waypoints;
};

struct ExportGoodData {

    std::vector<Waypoint> waypoints;
};

struct SystemData {
    std::string symbol;
    std::unordered_map<std::string, Waypoint> waypoints;
    std::vector<MarketData> marketplaces;
    std::vector<ShipyardData> shipyards;

    static std::unordered_map<std::string, SystemData> cache;
};

} // namespace sptr
