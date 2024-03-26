#include "sptr/data.h"
#include <sptr/system_data_provider.h>

namespace sptr {

std::unordered_map<std::string, SystemData> SystemData::cache;

void request_system_data(const std::string& systemSymbol) {}

void request_all_waypoints(const std::string& system_symbol) {
    // DataProvider::instance()
}

void request_all_marketplace_data(const std::string& system_symbol) {
    auto& dp = DataProvider::instance();
}

void request_waypoints_page(const std::string& system_symbol,
                            boost::optional<std::shared_ptr<models::WaypointTraitSymbol>> traits, int page) {
    auto& dp = DataProvider::instance();

    static const int ITEMS_PER_PAGE = 20;
    auto x = dp.apis.systems.getSystemWaypoints(system_symbol, page, ITEMS_PER_PAGE, {}, traits)
                 .then([&dp, system_symbol, traits, page](auto task) {
                     API_ERROR_GUARD_START
                     auto waypoints = task.get()->getData();
                     dp.on_main_thread([=]() {
                         SystemData& sys = SystemData::cache[system_symbol];

                         for (auto wp : waypoints) {
                             sys.waypoints[wp->getSymbol()] = wp;
                         }

                         if (waypoints.size() == ITEMS_PER_PAGE) {
                             request_waypoints_page(system_symbol, traits, page + 1);
                         }
                     });
                     API_ERROR_GUARD_END
                 });
}

} // namespace sptr
