local UI = {}

function UI:init()
end

function UI:createUIEntity(tag, script)
    local entity = self.scene:findEntityByName(tag)
    if not entity:is_valid() then
        entity = self.scene:createBasicEntity(tag)
        entity:addComponent(ScriptComponent(script))
    end
    return entity
end

function UI:start()
    self.scene:createEntityActor("Skybox", "skybox.lua")
    self:createUIEntity("MarketUI", "ui/market.lua")
    self:createUIEntity("ShipyardsUI", "ui/shipyards.lua")
    self:createUIEntity("ShipyardUI", "ui/shipyard.lua")
    -- skybox:addComponent(ScriptComponent("skybox.lua"))
    -- skybox:addComponent(SpriteComponent("space.jpg"))
    -- skybox:getComponent(TransformComponent)
end


function UI:update(dt)
    -- log_trace("------ ui update -------")
    ImGui.PushStyleColor(ImGuiCol.WindowBg, 0.1, 0.1, 0.1, 0.5)
    ImGui.DockSpaceOverViewport(ImGuiDockNodeFlags.PassthruCentralNode)
    ImGui.PopStyleColor(1)

    ImGui.Begin("MouseDebug")
    local mouse_pos = get_mouse_position()
    ImGui.Text("MouseXY"); ImGui.SameLine(100); ImGui.Text("("..mouse_pos.x..","..mouse_pos.y..")")
    ImGui.End()
end

function UI:destroy()
end

return UI
