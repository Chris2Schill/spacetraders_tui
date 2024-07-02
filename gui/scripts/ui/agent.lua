local AgentUI = {}


function AgentUI:init()
end

function AgentUI:update(dt)
    -- print(inspect.inspect(my_agent))
    -- print("------ update -------")
    local my_agent = sptr.g.my_agent

    if my_agent ~= nil then
        ImGui.Begin(my_agent.symbol, true, ImGuiWindowFlags.NoBackground)
        -- ImGui.LabelText("$" .. my_agent.credits, "Credits")
        ImGui.Text("Credits"); ImGui.SameLine(100); ImGui.Text("$"..my_agent.credits)
        ImGui.Text("Faction"); ImGui.SameLine(100); ImGui.Text("$"..my_agent.startingFaction)
        ImGui.Text("Headquarters"); ImGui.SameLine(100); ImGui.Text("$"..my_agent.headquarters)
        -- ImGui.LabelText(my_agent.startingFaction, "Faction")
        -- ImGui.LabelText(my_agent.headquarters, "Headquarters")
        ImGui.End()
    end
end

function AgentUI:destroy()
end

return AgentUI
