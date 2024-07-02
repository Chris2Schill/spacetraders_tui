local ShipyardUI = {}

function ShipyardUI:init()
    Listener = {
        connections = {},
        on_shipyard_selected = function(evt)
            self.shipyard = evt.shipyard
            _G.selected_shipyard = evt.shipyard
        end
    }
    Listener.connections[1] = dispatcher:connect(sptr.events.shipyard_selected, Listener.on_shipyard_selected)
    self.shipyard = _G.selected_shipyard
end

local function draw_key_value(k, v)
    ImGui.Text(k .. ":"); ImGui.SameLine(140); ImGui.Text(v)
end

local function draw_speed_of(obj)
    draw_key_value("Speed", obj.condition)
end

local function draw_condition_of(obj)
    draw_key_value("Condition", obj.condition)
end

local function draw_requirements_for(obj)
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

local function draw_description_of(obj)
    ImGui.TextWrapped(obj.description)
    ImGui.Spacing()
end

local function draw_power_output_of(obj)
    draw_key_value("Power Output", obj.powerOutput)
end
local function draw_fuel_capacity_of(obj)
    draw_key_value("Fuel Capacity", obj.fuelCapacity)
end
local function draw_module_slots_of(obj)
    draw_key_value("Module Slots", obj.moduleSlots)
end
local function draw_mounting_points_of(obj)
    draw_key_value("Mounting Points", obj.mountingPoints)
end
local function draw_integrity_of(obj)
    draw_key_value("Integrity", obj.integrity)
end

local function draw_registration(registration)
    if registration then
        ImGui.Text(registration.role .. " - " .. registration.faction)
    end
end
local function draw_fuel(fuel)
    if fuel ~= nil then
        if fuel.capacity > 0 then
            local pct = fuel.current / fuel.capacity
            ImGui.ProgressBar(pct, 100, 20, "Fuel (" .. (pct * 100) .. "%)")
        end
    end
end
local function draw_frame(frame)
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
local function draw_engine(engine)
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
local function draw_reactor(reactor)
    local header = "Reactor - " .. reactor.name .. " (po" .. reactor.powerOutput .. ")"
    if ImGui.CollapsingHeader(header) then
        ImGui.Indent(20)
        draw_description_of(reactor)
        draw_power_output_of(reactor)
        draw_requirements_for(reactor)
        ImGui.Unindent(20)
    end
end
local function draw_crew(crew)
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
local function draw_mounts(mounts)
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
local function draw_modules(modules)
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
local function draw_cooldown(cooldown)
end

local function draw_ship(ship)
    ImGui.Text(ship.name)
    ImGui.Separator()
    draw_registration(ship.registration)
    draw_fuel(ship.fuel)
    draw_frame(ship.frame)
    draw_engine(ship.engine)
    draw_reactor(ship.reactor)
    draw_crew(ship.crew)
    draw_mounts(ship.mounts)
    draw_modules(ship.modules)
    draw_cooldown(ship.cooldown)
end

local function draw_ships(ships)
    -- ImGui.Text(inspect(ships))
    for _, ship in ipairs(ships) do
        -- if ImGui.CollapsingHeader(ship.name) then
            if ImGui.Selectable(ship.name) then
                ShipyardUI.selected_ship = ship
            end
        -- end
    end
    -- ImGui.Text(inspect(ships))
end

function ShipyardUI:update(dt)
    ImGui.Begin("Shipyard", true, ImGuiWindowFlags.NoBackground)
    if self.shipyard ~= nil then
        -- print(inspect(self.shipyard_ships))
        if self.shipyard.ships ~= nil then
            draw_ships(self.shipyard.ships)
            -- print(inspect(self.shipyard_ships))
        end
    end
    if self.selected_ship then
        ImGui.Begin("Shipyard Ship Details")
        draw_ship(self.selected_ship)
        if ImGui.Button("Buy $"..self.selected_ship.purchasePrice) then
            local success = sptr.api.purchase_ship(self.shipyard.symbol, self.selected_ship)
            if success then
                sptr.api.get_ships()
            end
        end
        -- print(inspect(self.selected_ship))
        ImGui.End()
    end

    ImGui.End()
    -- print(inspect(self.selected_ship.type))
end

return ShipyardUI
