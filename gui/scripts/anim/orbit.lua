local OrbitAnimation = {}
local OrbitAnimation_mt = {
    __name = "OrbitAnimation",
    __index = OrbitAnimation
}

local function new_orbit_animation(orbiter, around_pos, speed)
    -- local x = math.random() + math.random(0, 3)
    local o = {
        orbiter = orbiter,
        around_pos = around_pos,
        orbit = math.random() + math.random(0,6),
        speed = speed or 0.1,
        dist = math.random(6,11),
    }
    print("orbit="..o.orbit)
    return setmetatable(o, OrbitAnimation_mt)
end

function OrbitAnimation:set_around_pos(pos)
    self.around_pos = pos
end

function OrbitAnimation:update(dt)
    local tf = self.orbiter.entity:getComponent(TransformComponent)

    self.orbit = self.orbit + (dt*self.speed)
    if self.orbit > (2*math.pi) then
        self.orbit = 0
    end
    local x = math.cos(self.orbit)*self.dist
    local y = math.sin(self.orbit)*self.dist
    tf.translation.x =  self.around_pos.x+x
    tf.translation.y = self.around_pos.y+y
end

return  {
    new = new_orbit_animation
}
