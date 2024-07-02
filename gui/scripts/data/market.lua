sptr.api.get_market = function(waypoint, force)
    log_trace("sptr.api.get_market")
    local refresh = force or false
    if sptr.g.marketplaces[waypoint.symbol] ~= nil and not refresh then
        return sptr.g.marketplaces[waypoint.symbol]
    end

    local market = _G.apis.spacetraders.systems:get_market(waypoint.systemSymbol, waypoint.symbol)
    if market ~= nil then
        sptr.g.marketplaces[waypoint.symbol] = market.data
        return market.data
    end
    return nil
end

sptr.api.get_shipyard = function(waypoint, force)
    log_trace("sptr.api.get_shipyard")
    local refresh = force or false
    if sptr.g.shipyards[waypoint.symbol] ~= nil and not refresh then
        return sptr.g.shipyards[waypoint.symbol]
    end

    local shipyard = _G.apis.spacetraders.systems:get_shipyard(waypoint.systemSymbol, waypoint.symbol)
    if shipyard ~= nil then
        sptr.g.shipyards[waypoint.symbol] = shipyard.data
        return shipyard.data
    end
    return nil
end
