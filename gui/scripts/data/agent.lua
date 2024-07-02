local AgentData = {}

sptr.api.get_my_agent = function()
    log_trace("requesting my agent")
    sptr.g.my_agent = _G.apis.spacetraders.agents:get_my_agent().data
    sptr.g.my_agent.add_credits = function(amount)
        sptr.g.my_agent.credits = sptr.g.my_agent.credits + amount
    end
end

function AgentData:init()
    sptr.api.get_my_agent()
    self.count = 0
end

function AgentData:update(dt)
    self.count = self.count + 1
    if self.count > 3000 then
        sptr.api.get_my_agent()
        self.count = 0
    end
end

return AgentData
