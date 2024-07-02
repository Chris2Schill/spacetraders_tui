local PrimaryCamera = {}

local function post_camera_moved_event(transform)
    local camera_moved = sptr.events.camera_moved()
    -- local view = PrimaryCamera.entity:getComponent(CameraComponent).view

    camera_moved.transform = transform
    -- camera_moved.view_size = view:getSize()

    dispatcher:trigger(camera_moved)
end

function PrimaryCamera:set_translation(translation)
    self.transform = self.entity:getComponent(TransformComponent)
    self.transform.translation.x = translation.x
    self.transform.translation.y = translation.y
    self.transform.translation.z = translation.z
    post_camera_moved_event(self.transform)
end

function PrimaryCamera:init()
    Listener = {
        connections = {},
        on_set_camera_position = function(evt)
            self:set_translation(evt.translation)
        end,
    }
    Listener.connections[1] = dispatcher:connect(sptr.events.set_camera_position, Listener.on_set_camera_position)
end

function PrimaryCamera:zoom(amnt)
    local view = self.entity:getComponent(CameraComponent).view
    view:zoom(amnt)
    -- self.zoom = self.zoom * amnt
    self.transform.scale = self.transform.scale * amnt
    post_camera_moved_event(self.transform)
end

function PrimaryCamera:update(dt)
    self.transform = self.entity:getComponent(TransformComponent)

    ImGui.Begin("Camera", true, ImGuiWindowFlags.NoBackground)

    ImGui.Text("Zoom")
    ImGui.SameLine()
    if ImGui.Button("+") then
        self:zoom(0.5)
    end
    ImGui.SameLine()
    if ImGui.Button("-") then
        self:zoom(2)
    end


    local x, xchanged = ImGui.DragFloat("X", self.transform.translation.x)
    local y, ychanged = ImGui.DragFloat("Y", self.transform.translation.y)
    if xchanged or ychanged then
        self:set_translation(vec3(x, y, 0))
    end

    ImGui.End()

    self:check_drag()
end

Dragging = false
LastHeldPos = vec2(0,0)

function PrimaryCamera:check_drag()
    -- local no_window_clicked = not ImGui.IsAnyItemHovered()
    -- print(tostring(no_window_clicked))
    local dragging = ImGui.IsMouseDown(ImGuiMouseButton.ImGuiMouseButton_Left)
    if not Dragging and dragging then
        local mx, my = ImGui.GetMousePos()
        LastHeldPos = vec2(mx, my)
    end

    if dragging then
        local mx, my = ImGui.GetMousePos()
        local heldPos = vec2(mx, my)

        local delta = LastHeldPos - heldPos
        delta = delta * self.transform.scale.x
        self:set_translation(vec3(self.transform.translation.x+delta.x, self.transform.translation.y+delta.y, 0))

        LastHeldPos = heldPos
    end

    Dragging = dragging
end

function PrimaryCamera:destroy()
    log_trace("Destroyed Primary Camera")
end

return PrimaryCamera
