local inspect = require('inspect').inspect

function draw_key_value(k, v)
    ImGui.Text(k .. ":"); ImGui.SameLine(140); ImGui.Text(v)
end

function draw_speed_of(obj)
    draw_key_value("Speed", obj.condition)
end

function draw_condition_of(obj)
    draw_key_value("Condition", obj.condition)
end

function draw_requirements_for(obj)
    local req = obj.requirements
    if req ~= nil then
        if ImGui.TreeNode("Requirements") then
            if req.crew ~= nil and req.crew > 0 then
                draw_key_value("Crew", req.crew)
            end
            if req.power ~= nil and req.power > 0 then
                draw_key_value("Power", req.power)
            end
            if req.slots ~= nil and req.slots > 0 then
                draw_key_value("Slots", req.slots)
            end
            ImGui.TreePop()
        end
    end
end

function draw_description_of(obj)
    ImGui.TextWrapped(obj.description)
    ImGui.Spacing()
end

function draw_power_output_of(obj)
    draw_key_value("Power Output", obj.powerOutput)
end

function draw_fuel_capacity_of(obj)
    draw_key_value("Fuel Capacity", obj.fuelCapacity)
end

function draw_module_slots_of(obj)
    draw_key_value("Module Slots", obj.moduleSlots)
end

function draw_mounting_points_of(obj)
    draw_key_value("Mounting Points", obj.mountingPoints)
end

function draw_integrity_of(obj)
    draw_key_value("Integrity", obj.integrity)
end

function draw_registration(registration)
    if registration ~= nil then
        ImGui.Text(registration.role .. " - " .. registration.factionSymbol)
    end
end

function draw_fuel(fuel)
    if fuel ~= nil then
        if fuel.capacity > 0 then
            local pct = fuel.current / fuel.capacity
            ImGui.ProgressBar(pct, 100, 20, "Fuel (" .. (pct * 100) .. "%)")
        end
    end
end

function draw_frame(frame)
    local header = "Frame - " .. frame.name .. " (c" .. frame.condition .. ")"
    if ImGui.CollapsingHeader(header) then
        ImGui.Indent(20)
        draw_description_of(frame)
        draw_condition_of(frame)
        draw_fuel_capacity_of(frame)
        draw_module_slots_of(frame)
        draw_mounting_points_of(frame)
        draw_requirements_for(frame)
        ImGui.Unindent(20)
    end
end

function draw_engine(engine)
    local header = "Engine - " .. engine.name .. " (s" .. engine.speed .. ",c" .. engine.condition .. ")"
    if ImGui.CollapsingHeader(header) then
        ImGui.Indent(20)
        draw_description_of(engine);
        draw_speed_of(engine);
        draw_condition_of(engine);
        draw_integrity_of(engine)
        draw_requirements_for(engine);
        ImGui.Unindent(20)
    end
end

function draw_reactor(reactor)
    local header = "Reactor - " .. reactor.name .. " (po" .. reactor.powerOutput .. ")"
    if ImGui.CollapsingHeader(header) then
        ImGui.Indent(20)
        draw_description_of(reactor)
        draw_power_output_of(reactor)
        draw_requirements_for(reactor)
        ImGui.Unindent(20)
    end
end

function draw_crew(crew)
    local current = crew.current or 0
    local header = "Crew (" .. current .. "/" .. crew.capacity .. ")"
    if ImGui.CollapsingHeader(header) then
        ImGui.Indent(20)
        if crew.wages then
            draw_key_value("Wage $/h", crew.wages)
        end

        ImGui.Unindent(20)
    end
end

function draw_mounts(mounts)
    if ImGui.CollapsingHeader("Mounts") then
        ImGui.Indent(20)
        for _, mount in ipairs(mounts) do
            if ImGui.CollapsingHeader(mount.name) then
                ImGui.Indent(20)
                draw_key_value("Strength", mount.strength)
                if mount.deposits then
                    if ImGui.CollapsingHeader("Deposits") then
                        ImGui.Indent(20)
                        for _, dep in ipairs(mount.deposits) do
                            ImGui.Text(dep)
                        end
                        ImGui.Unindent(20)
                    end
                    ImGui.Unindent(20)
                end
            end
        end
        ImGui.Unindent(20)
    end
end

function draw_modules(modules)
    if ImGui.CollapsingHeader("Modules") then
        ImGui.Indent(20)
        for _, module in ipairs(modules) do
            if ImGui.CollapsingHeader(module.name) then
                ImGui.Indent(20)
                draw_description_of(module);
                draw_key_value("Range", module.range);
                draw_key_value("Capacity", module.capacity);
                draw_requirements_for(module);
                ImGui.Unindent(20)
            end
        end
        ImGui.Unindent(20)
    end
end

function draw_cooldown(cooldown)
    if ImGui.CollapsingHeader("Cooldown") then
        ImGui.Indent(20)
        ImGui.Text(inspect(cooldown))
        ImGui.Unindent(20)
    end
end

function draw_route(route)
    if route then
        draw_key_value("Destination", route.destination.symbol)
        ImGui.Text("Destination: "..route.destination.symbol..
                   " ("..route.destination.type..")")
        draw_key_value("Departure Time", route.departureTime)
        draw_key_value("Arrival Time", route.arrival)
    end
end

function draw_nav(nav)
    if nav then
        draw_key_value("Status", nav.status)
        draw_key_value("Flight Mode", nav.flightMode)
        draw_route(nav.route)
    end
end

function draw_cargo(ship)
    local cargo = ship.cargo
    local header = "Cargo ("..cargo.units.."/"..cargo.capacity..")"
    if ImGui.CollapsingHeader(header) then
        ImGui.Indent(20)
        for _, item in ipairs(cargo.inventory) do

            local item_header = item.name .. "("..item.units..")"
            if ImGui.CollapsingHeader(item_header) then
                ImGui.Indent(20)
                draw_description_of(item);
                ImGui.PushID(item.name.."SellBtn")
                if ImGui.Button("Sell") then
                    sptr.api.sell_cargo(ship.name, item.name, item.units);
                end
                ImGui.PopID()
                ImGui.Unindent(20)
            end
        end
        ImGui.Unindent(20)
    end
end

function draw_ship_details(ship)
    ImGui.Text(ship.registration.name)
    ImGui.Separator()
    draw_registration(ship.registration)
    draw_nav(ship.nav)
    draw_fuel(ship.fuel)
    draw_ship_controls(ship)
    draw_frame(ship.frame)
    draw_engine(ship.engine)
    draw_reactor(ship.reactor)
    draw_crew(ship.crew)
    draw_mounts(ship.mounts)
    draw_modules(ship.modules)
    draw_cooldown(ship.cooldown)
    draw_cargo(ship)
end

function draw_ship_controls(ship)
    ImGui.Indent(20)
    local ship_actor = ship.get_actor()
    if ship_actor:is_docked() then
        if ImGui.Button("To Orbit") then
            ship.get_actor():orbit()
        end
        ImGui.SameLine()
        if ImGui.Button("Refuel") then
            ship.get_actor():refuel()
        end
    elseif ship_actor:is_in_orbit() then
        if ImGui.Button("Dock") then
            ship.get_actor():dock()
        end
        ImGui.SameLine()
        if ImGui.Button("Extract ".."("..ship.cooldown.remainingSeconds..")") then
            ship.get_actor():extract_resources()
        end
    end

    ImGui.PushID(ship.registration.name .. "ViewBtn")
    if ImGui.Button("View") then
        local set_camera_pos = sptr.events.set_camera_position()
        print("UUID=" .. tostring(ship_actor.entity:getUUID()))
        local tc = ship_actor.entity:getComponent(TransformComponent)
        set_camera_pos.translation = vec3(tc.translation.x, tc.translation.y, tc.translation.z)
        dispatcher:trigger(set_camera_pos)
    end
    ImGui.PopID()
    -- draw_table(ship)
    ImGui.Unindent(20)
end

function draw_ship_tabs(ship)
    if ship.registration ~= nil then
        -- if ImGui.BeginTabBar(ship.registration.name .. "Tabs") then
            -- if (ImGui.BeginTabItem("Details")) then
                draw_ship_details(ship)
            --     ImGui.EndTabItem()
            -- end
            -- if (ImGui.BeginTabItem("Control")) then
            --     ImGui.EndTabItem()
            -- end
            -- ImGui.EndTabBar()
        -- end
    end
end

local ShipDetailsWindow = {}
local ShipDetailsWindow_mt = {
    __name = "ShipDetailsWindow",
    __index = ShipDetailsWindow
}

function new_ship_details_window(ship)
    local o = {
        ship = ship,
        is_open = false,
    }
    return setmetatable(o, ShipDetailsWindow_mt)
end

function ShipDetailsWindow:print_name()
    print(self.ship.symbol)
end

function ShipDetailsWindow:open()
    self.is_open = true
end

function ShipDetailsWindow:close()
    self.is_open = false
end

function ShipDetailsWindow:update(ship)
    self.ship = ship

    -- print("open="..tostring(self.is_open))
    if self.is_open then
        self.is_open = ImGui.Begin(self.ship.registration.name, self.is_open, ImGuiWindowFlags.NoBackground)
        if (self.is_open) then
            draw_ship_tabs(self.ship)
            ImGui.End()
        end
    end
end

return {
    new = new_ship_details_window
}
