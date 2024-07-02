local System = {}

function System:start()
    local tag = self.entity:getComponent(TagComponent).tag
    self.system = sptr.g.systems[tag]
    local tc = self.entity:getComponent(TransformComponent)
    tc.translation = vec3(self.system.x, self.system.y, 1.1)
    tc.scale = vec3(0.05, 0.05, 0)

    if not self.entity:hasComponent(SpriteComponent) then
        self.entity:addComponent(SpriteComponent("sun.jpg"))
    else
        log_error("System " .. self.system.symbol .. " already had sprite component")
    end

    self.SpriteComponent = self.entity:getComponent(SpriteComponent)

    if self.system.type == "RED_STAR" then
        self.SpriteComponent.color = vec4(200,100,0,255)
    elseif self.system.type == "ORANGE_STAR" then
        self.SpriteComponent.color = vec4(255,255,0,255)
    elseif self.system.type == "BLUE_STAR" then
        self.SpriteComponent.color = vec4(0,255,0,255)
    elseif self.system.type == "UNSTABLE" then
        self.SpriteComponent.color = vec4(255,0,0,255)
    else
        self.SpriteComponent.color = vec4(255,255,255,255)
    end

end

function System:update(dt)
    if self.hovered then
        local mx, my = ImGui.GetMousePos()
        ImGui.SetNextWindowPos(mx + 10, my)
        ImGui.OpenPopup("Tooltip")
        if ImGui.BeginPopup("Tooltip") then
            ImGui.Text(self.system.symbol)
            ImGui.EndPopup()
        end
        if ImGui.IsMouseDown(ImGuiMouseButton.ImGuiMouseButton_Left) then
            -- sptr.api.get_system(self.system.symbol)
            local system_selected = sptr.events.system_selected()
            system_selected.systemSymbol = self.system.symbol
            dispatcher:trigger(system_selected)
        end
    end
end

function System:destroy()
end

function System:on_hover_enter()
    self.hovered = true;
end

function System:on_hover_leave()
    self.hovered = false;
end

return System
