local WaypointsData = {}

local LIMIT = 20

local function get_system_waypoints_helper(systemSymbol, page, limit, type, traits)

    local wps = _G.apis.spacetraders.systems:get_system_waypoints(systemSymbol,
        tostring(page),
        tostring(limit),
        type,
        traits)

    if wps == nil then
        return wps
    end

    -- TODO: there might be a bug when there are exactly multiples of 20 waypoints
    if #wps.data == LIMIT then
        local more_wps = get_system_waypoints_helper(systemSymbol, page + 1, limit, type, traits)
        if more_wps ~= nil then
            wps.data = TableConcat(wps.data, more_wps.data)
            return wps
        end
    end


    return wps
end

sptr.api.get_system_waypoints = function(systemSymbol, page, limit, type, traits)
    log_trace("sptr.api.get_system_waypoints(" .. systemSymbol .. ")")

    if sptr.g.system_waypoints[systemSymbol] ~= nil then
        return sptr.g.system_waypoints[systemSymbol]
    end

    local wps
    if page ~= nil and limit ~= nil then
        wps = get_system_waypoints_helper(systemSymbol, page, limit, type, traits)
    else
        wps = get_system_waypoints_helper(systemSymbol, 1, LIMIT, type, traits)
    end

    if wps ~= nil then
        sptr.g.system_waypoints[systemSymbol] = {}
        for _, waypoint in ipairs(wps.data) do
            sptr.g.system_waypoints[systemSymbol][waypoint.symbol] = waypoint
            sptr.g.waypoints[waypoint.symbol] = waypoint
            WaypointsData.scene:createEntityActor(waypoint.symbol, "actors/waypoint.lua")
        end
        return sptr.g.system_waypoints[systemSymbol]
    end

    log_error("Failed to get_system_waypoints("..systemSymbol..")")
    return nil
end

return WaypointsData
