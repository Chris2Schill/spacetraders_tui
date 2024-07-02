local ShipsUI = {
    subwindows = {}
}


package.loaded["ui.ship_details_window"] = nil
local ShipDetailsWindow = require("ui.ship_details_window")

function ShipsUI:init()
end

function ShipsUI:start()
end
--
-- function draw_table(t)
--     for k, v in pairs(t) do
--         if istable(v) then
--             if ImGui.CollapsingHeader(k .. (" - " .. (v.name or ""))) then
--                 ImGui.Indent(20)
--                 -- draw_table(v)
--                 ImGui.Unindent(20)
--             end
--         elseif (type(v) == "function") then
--         else
--             ImGui.TextWrapped(k .. ": " .. v)
--         end
--     end
-- end
--
-- function draw_list(l)
--     for i, v in ipairs(l) do
--         if istable(v) then
--             if ImGui.CollapsingHeader(v.symbol) then
--                 draw_table(v)
--             end
--         else
--             ImGui.TextWrapped(inspect.inspect(v))
--         end
--     end
-- end
--
-- function draw_ship(ship)
--     if ImGui.CollapsingHeader(ship.registration.name) then
--         ImGui.Indent(20)
--         if ship.nav.status == "DOCKED" then
--             if ImGui.Button("To Orbit") then
--                 _G.apis.spacetraders.fleet:orbit_ship(ship.registration.name)
--                 sptr.api.get_ships()
--             end
--             ImGui.SameLine()
--             if ImGui.Button("Refuel") then
--                 -- sptr.actors[ship.registration.name]:refuel()
--                 sptr.get_actor(ship.registration.name, ShipsUI.scene):refuel()
--                 -- ship.refuel()
--             end
--         elseif ship.nav.status == "IN_ORBIT" then
--             if ImGui.Button("Dock") then
--                 _G.apis.spacetraders.fleet:dock_ship(ship.registration.name)
--                 sptr.api.get_ships()
--             end
--             ImGui.SameLine()
--             if ImGui.Button("Extract ".."("..ship.cooldown.remainingSeconds..")") then
--                 local _1, _2, err = _G.apis.spacetraders.fleet:extract_resources(ship.registration.name, {})
--                 if err == nil then
--                     print(inspect(_1))
--                     sptr.api.get_ships()
--                     print("Extracted")
--                 else
--                     log_warn(err)
--                 end
--             end
--         end
--         -- draw_table(ship)
--         ImGui.Unindent(20)
--     end
-- end

function ShipsUI:update(dt)
    -- ImGui.Text(inspect(sptr.g.ships))
    ImGui.Begin("Ships", true, ImGuiWindowFlags.NoBackground)
        if ImGui.Button("Refresh") then
            sptr.api.get_ships()
        end

    for name,ship in pairs(sptr.g.ships) do
        if ImGui.Selectable(name) then
            if self.subwindows[name] == nil then
                self.subwindows[name] = ShipDetailsWindow.new(ship)
            end
            self.subwindows[name]:open()
        end
    end

    for name,subwindow in pairs(self.subwindows) do
        subwindow:update(sptr.g.ships[name])
    end

    ImGui.End()
end

function ShipsUI:destroy()
end

return ShipsUI
