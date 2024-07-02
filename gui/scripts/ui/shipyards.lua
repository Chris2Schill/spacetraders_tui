local ShipyardsUI = {
    selected = {}
}

WindowOpen = true

function ShipyardsUI:init()
    Listener = {
        connections = {},
        on_system_selected = function(evt)
            self.selected.system = sptr.g.systems[evt.systemSymbol]
            if self.selected.system ~= nil then
                sptr.api.get_shipyards(self.selected.system)
            end
            WindowOpen = true
        end,
    }
    Listener.connections[1] = dispatcher:connect(sptr.events.system_selected, Listener.on_system_selected)
end

local function draw_shipyard(shipyard)
    -- ImGui.Begin("Debug")
    -- ImGui.Text(inspect(shipyard))
    -- ImGui.End()
    ImGui.PushID(shipyard.symbol.."shipyard")
    if ImGui.Selectable(shipyard.symbol) then
        local shipyard_selected = sptr.events.shipyard_selected()
        shipyard_selected.shipyard = shipyard
        dispatcher:trigger(shipyard_selected)
    end
    ImGui.PopID()
end

function ShipyardsUI:update(dt)
    WindowOpen = ImGui.Begin("Shipyards", WindowOpen, ImGuiWindowFlags.NoBackground)

    if self.selected.system ~= nil then
        local system = self.selected.system
        for _,shipyard in ipairs(sptr.g.system_shipyards[system.symbol]) do
            draw_shipyard(shipyard)
        end
    end
    ImGui.End()
end

return ShipyardsUI
