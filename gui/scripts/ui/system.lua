local SystemUI = {}

local COL2_XPOS = 100

WindowOpen = true

function SystemUI:init()
    Listener = {
        connections = {},
        on_system_selected = function(evt)
            System = sptr.api.get_system(evt.systemSymbol)
            WindowOpen = true
        end,
    }
    Listener.connections[1] = dispatcher:connect(sptr.events.system_selected, Listener.on_system_selected)
end

function make_coord_text(item)
    local coord = "(" .. item.x .. "," .. item.y .. ")"
    return coord
end

function draw_waypoint(wp)
    local header = wp.symbol .. " - " .. wp.type
    if ImGui.CollapsingHeader(header) then
        ImGui.Indent(20)
        ImGui.Text("Type"); ImGui.SameLine(COL2_XPOS); ImGui.Text(wp.type)
        ImGui.Text("Coord"); ImGui.SameLine(COL2_XPOS); ImGui.Text(make_coord_text(wp))
        ImGui.Unindent(20)
    end
end

function draw_waypoints(waypoints)
    if ImGui.CollapsingHeader("Waypoints") then
        ImGui.Indent(20)
        for i, wp in ipairs(waypoints) do
            draw_waypoint(wp)
        end
        ImGui.Unindent(20)
    end
end

function draw_system(system)
    ImGui.Text("System"); ImGui.SameLine(COL2_XPOS); ImGui.Text(system.symbol)
    ImGui.Text("Type"); ImGui.SameLine(COL2_XPOS); ImGui.Text(system.type)
    ImGui.Text("Coord"); ImGui.SameLine(COL2_XPOS); ImGui.Text(make_coord_text(system))
    draw_waypoints(system.waypoints)
end

function SystemUI:update(dt)
    WindowOpen = ImGui.Begin("System", WindowOpen, ImGuiWindowFlags.NoBackground)
    if WindowOpen then
        if System ~= nil then
            draw_system(System)
        end
        ImGui.End()
    end
    -- test(dt)
end

function SystemUI:destroy()
end

-- MyNode = nil
-- MyNodeTransform = nil
-- Time = 0
--
-- function test(dt)
--     ImGui.Begin("Test", true, ImGuiWindowFlags.NoBackground)
--     if MyNode == nil then
--         if ImGui.Button("Create MyNode") then
--             MyNode = E.scene:createBasicEntity("Node1")
--             -- MyNode:addComponent(ScriptComponent("node.lua"))
--             MyNodeTransform = MyNode:addComponent(TransformComponent(vec3(10,0, 0)))
--             MyNode:addComponent(CircleComponent(40))
--         end
--     else
--         if ImGui.Button("Destroy MyNode") then
--             E.scene:destroyEntity(MyNode)
--             MyNode = nil
--         end
--
--         if ImGui.Button("Animate") then
--             Time = 0
--         end
--         -- print(MyNode.transform.translation.x)
--         MyNodeTransform.translation.x = ImGui.DragFloat("X", MyNodeTransform.translation.x)
--         MyNodeTransform.translation.y = ImGui.DragFloat("Y", MyNodeTransform.translation.y)
--         MyNodeTransform.translation.z = ImGui.DragFloat("Z", MyNodeTransform.translation.z)
--
--         Time = Time + dt
--         Time = clamp(Time, 0, 1)
--         local xy = lerp(0, 10, Time)
--         MyNodeTransform.translation.x = xy;
--         MyNodeTransform.translation.y = xy;
--
--         print(tostring(MyNodeTransform))
--     end
--
--     ImGui.End()
-- end

return SystemUI
