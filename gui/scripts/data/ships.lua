local ShipsData = {}


local function startWithCommandShip()
    for name, ship in pairs(sptr.g.ships) do
        if ship.registration.role == "COMMAND" then
            local system_selected = sptr.events.system_selected()
            system_selected.systemSymbol = ship.nav.systemSymbol
            dispatcher:trigger(system_selected)

            -- local system = sptr.g.systems[ship.nav.systemSymbol]
            -- local set_camera_pos = sptr.events.set_camera_position()
            -- set_camera_pos.translation = vec3(system.x, system.y, 0)
            -- dispatcher:trigger(set_camera_pos)
        end
    end
end

local function setGlobalShipsMap(ships)
    for i, ship in pairs(ships) do
        local name = ship.registration.name
        local should_create_entity = sptr.g.ships[name] == nil
        sptr.g.ships[name] = ship
        if should_create_entity then
            ShipsData.scene:createEntityActor(ship.registration.name, "actors/ship.lua")
        end

        ship.sptr_internal = {}
        sptr.g.ships[name].get_actor = function()
            local actor = sptr.g.ships[name].sptr_internal.actor
            if actor == nil then
                actor = sptr.get_actor(name, ShipsData.scene)
                sptr.g.ships[name].sptr_internal.actor = actor
            end
            return actor
        end
    end
end

sptr.api.get_ships = function()
    local ships, _, err = _G.apis.spacetraders.fleet:get_my_ships("1", "20")
    if ships ~= nil then
        setGlobalShipsMap(ships.data)
    else
        log_warn(inspect.inspect(err))
    end
    return ships
end

sptr.api.orbit_ship = function(ship)
    _G.apis.spacetraders.fleet:orbit_ship(ship.registration.name)
end

sptr.api.dock_ship = function(ship)
    _G.apis.spacetraders.fleet:dock_ship(ship.registration.name)
end

sptr.api.extract_resources = function(ship)
    local response, _2, err = _G.apis.spacetraders.fleet:extract_resources(ship.registration.name, {})
    if err == nil then
        -- print(inspect(response))
        print("Extracted")
    else
        log_warn(err)
    end
    return response
end

sptr.api.purchase_ship = function(waypointSymbol, ship)
    local req = {
        waypointSymbol = waypointSymbol,
        shipType = ship.type
    }
    local response, err1, err2 = _G.apis.spacetraders.fleet:purchase_ship(req)
    return response
end

function ShipsData:start()
    local ships = sptr.api.get_ships()
    if ships ~= nil then
        startWithCommandShip()
    end
end

function ShipsData:update(dt)
    -- ImGui.Text(inspect(sptr.g.ships["FATHORSENIPS2-1"].nav))
end

return ShipsData
