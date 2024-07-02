local SystemsWindow = {}

function SystemsWindow:start()
end

function SystemsWindow:update(dt)
    ImGui.Begin("Systems", true, ImGuiWindowFlags.NoBackground)
    for symbol, system in pairs(sptr.g.systems) do
        if ImGui.Selectable(symbol .. " - " .. system.type) then
            local system_selected = sptr.events.system_selected()
            system_selected.systemSymbol = system.symbol
            dispatcher:trigger(system_selected)

            local set_camera_pos = sptr.events.set_camera_position()
            set_camera_pos.translation = vec3(system.x, system.y, 0)
            dispatcher:trigger(set_camera_pos)
        end
    end
    ImGui.End()
end

return SystemsWindow
