local Skybox = {}

function Skybox:bind_to_camera(camera_transform)
    local transform = self.entity:getComponent(TransformComponent)
    transform.translation = camera_transform.translation
    transform.rotation = camera_transform.rotation
    transform.scale = camera_transform.scale

    transform.translation.x = transform.translation.x
    transform.translation.y = transform.translation.y
    transform.translation.z = 3
end

function Skybox:start()
    Listener = {
        connections = {},
        on_camera_moved = function(evt)
            self:bind_to_camera(evt.transform)
        end,
    }
    Listener.connections[1] = dispatcher:connect(sptr.events.camera_moved, Listener.on_camera_moved)

    if not self.entity:hasComponent(SpriteComponent) then
        self.entity:addComponent(SpriteComponent("space.jpg"))
    end


    local camera = self.scene:findEntityByName("PrimaryCamera")
    self:bind_to_camera(camera:getComponent(TransformComponent))
end

local function zoom_camera(amount)
    local camera_instance = Skybox.scene:findEntityByName("PrimaryCamera"):getComponent(ScriptComponent).instance
    camera_instance:zoom(amount)
end

function Skybox:on_scrolled(dir)

    local c_tbl = {
        [0] = function() zoom_camera(0.75) end,
        [1] = function() zoom_camera(1.25) end,
    }

    c_tbl[dir]()
end

function Skybox:update(dt)
end

return Skybox
