local node = {}

function node:init()
    log_trace("node init")

    -- self.tag       = self.entity:getComponent(TagComponent).tag
    -- self.transform = self.owner:get(self.id(), TransformComponent)
end

function node:update(dt)
    -- log_trace("----------- " .. self.tag .. " update -----------------")


    -- print(self.transform)
    -- if se
    -- local id = self.owner:get(self.id(), IDComponent)
    -- local transform = self.owner:get(self.id(), TransformComponent)
    -- local tx = vec3(1,1,3)
    -- log_trace(inspect.inspect(self))
    -- log_trace(self.scene:findEntityByName("Node1"))
    -- log_trace(inspect.inspect(self.scene:findEntityByName("Node1")))
    -- local node1 = self.scene:findEntityByName("Node1")
    -- local node1Tag = node1:getComponent(TagComponent).tag
    -- log_trace(node1Tag)
    --
    -- local agentEntity = self.scene:findEntityByName("AgentWindow")
    -- local agentWindow = self.getEntityInstance(agentEntity:getUUID())
    -- local agentWindowTag = agentEntity:getComponent(TagComponent)
    --
    -- ImGui.Begin(self.tag)
    -- ImGui.End()
end

function node:destroy()
    log_trace("Destroyed "..self.tag)
end

return node
