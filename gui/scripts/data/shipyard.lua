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

sptr.api.get_shipyards = function(system)

    if sptr.g.system_shipyards[system.symbol] ~= nil then
        return sptr.g.system_shipyards[system.symbol]
    end

    log_trace("sptr.api.get_shipyards("..system.symbol..")")
    sptr.g.system_shipyards[system.symbol] = {}

    local waypoints = sptr.g.system_waypoints[system.symbol]
    for waypointSymbol,waypoint in pairs(waypoints) do
        if has_trait(waypoint, "SHIPYARD") then
            local shipyard = _G.apis.spacetraders.systems:get_shipyard(system.symbol, waypointSymbol)
            if shipyard ~= nil then
                sptr.g.shipyards[waypointSymbol] = shipyard.data
                sptr.g.system_shipyards[system.symbol][
                    #sptr.g.system_shipyards[system.symbol]+1
                ] = shipyard.data
            else
                log_warn("Failed to get shipyard: "..waypointSymbol)
            end
        end
    end

    if #sptr.g.system_shipyards[system.symbol] == 0 then
        sptr.g.system_shipyards[system.symbol] = nil
    end

    return sptr.g.system_shipyards[system.symbol]
end
