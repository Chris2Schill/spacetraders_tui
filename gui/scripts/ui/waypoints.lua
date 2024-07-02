local WaypointsUI = {
    systemSymbol = "",
}

function WaypointsUI:init()
    Listener = {
        connections = {},
        on_system_selected = function(evt)
            self.systemSymbol = evt.systemSymbol
            sptr.api.get_system_waypoints(evt.systemSymbol)
        end,
    }
    Listener.connections[1] = dispatcher:connect(sptr.events.system_selected, Listener.on_system_selected)
end

local function draw_table(t)
    for k, v in pairs(t) do
        if istable(v) then
            if k == "traits" then
                if ImGui.CollapsingHeader("traits") then
                    ImGui.Indent(20)
                    draw_list(v)
                    ImGui.Unindent(20)
                end
            else
                if ImGui.CollapsingHeader(k) then
                    ImGui.Indent(20)
                    draw_table(v)
                    ImGui.Unindent(20)
                end
            end
        else
            ImGui.TextWrapped(k .. ": " .. tostring(v))
        end
    end
end

local function draw_list(l)
    for _, v in ipairs(l) do
        if istable(v) then
            if ImGui.CollapsingHeader(v.symbol) then
                draw_table(v)
            end
        else
            ImGui.TextWrapped(inspect.inspect(v))
        end
    end
end

function WaypointsUI:update(dt)
    ImGui.Begin("Waypoints", true, ImGuiWindowFlags.NoBackground)
    local system_waypoints = sptr.g.system_waypoints[self.systemSymbol]
    if system_waypoints ~= nil then
        draw_table(system_waypoints)
    end
    ImGui.End()
end

function WaypointsUI:destroy()
end

return WaypointsUI
