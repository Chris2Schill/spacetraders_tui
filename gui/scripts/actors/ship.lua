local Ship = {
    anims = {}
}

local OrbitAnimation = require("anim.orbit")

local Red = vec4(255,0,0,200)
local White = vec4(255,255,255,200)
local Invis = vec4(0, 0, 0, 0)

local colors = {
    default = {
        fill = Red,
        outline = Invis,
    },
    hovered = {
        fill = Red,
        outline = Invis,
    }
}

function Ship:init()
    local tag = self.entity:getComponent(TagComponent).tag
    self.ship = sptr.g.ships[tag]
    self.ship.entity = self
end

function Ship:start()
    if not self.entity:hasComponent(CircleComponent) then
        local cc = self.entity:addComponent(CircleComponent(0.1,3))
        cc.fillColor = colors.default.fill
        cc.outlineColor = colors.default.outline
    end

    local tf = self.entity:getComponent(TransformComponent)
    tf.translation = vec3(self.ship.nav.route.origin.x, self.ship.nav.route.origin.y, 0)

    self.anims.orbit = OrbitAnimation.new(self, tf.translation.x)
    self.anims.orbit.dist = 2
end

function Ship:is_docked()
    return self.ship.nav.status == "DOCKED"
end
function Ship:is_in_orbit()
    return self.ship.nav.status == "IN_ORBIT"
end

local function check_hover()
    if Ship.hovered then
        local mx, my = ImGui.GetMousePos()
        ImGui.SetNextWindowPos(mx+10, my)
        ImGui.OpenPopup("Tooltip")
        if ImGui.BeginPopup("Tooltip") then
            ImGui.Text(Ship.ship.registration.name)

            if Ship.ship.fuel.capacity > 0 then
                local pct = Ship.ship.fuel.current / Ship.ship.fuel.capacity
                ImGui.ProgressBar(pct, 100, 20, "Fuel ("..(pct*100).."%)")
            end
            ImGui.EndPopup()
        end
    end
end

function Ship:refuel()
    local _1, _2, _3 = _G.apis.spacetraders.fleet:refuel_ship(self.ship.registration.name,{})
    print(inspect(_1))
    print(inspect(_2))
    print(inspect(_3))
    sptr.api.get_ships()
end

function Ship:orbit()
    if self:is_docked() then
        sptr.api.orbit_ship(self.ship)
        sptr.api.get_ships()
    end
end

function Ship:dock()
    if self:is_in_orbit() then
        sptr.api.dock_ship(self.ship)
        sptr.api.get_ships()
    end
end

function Ship:extract_resources()
    if self:is_in_orbit() then
        local success = sptr.api.extract_resources(self.ship)
        if (success) then
            sptr.api.get_ships()
        end
    end
end

function Ship:navigate(waypointSymbol)
    local shipSymbol = self.ship.registration.name
    local response, _2, err = _G.apis.spacetraders.fleet:navigate_ship(shipSymbol, {waypointSymbol = waypointSymbol})
    if err ~= nil then
        log_warn(err)
    else
        log_info(inspect(response))
    end
end

function Ship:update(dt)
    self.ship = sptr.g.ships[self.ship.registration.name]
    check_hover()

    local wp = sptr.g.waypoints[self.ship.nav.waypointSymbol]
    local system = sptr.g.systems[self.ship.nav.systemSymbol]
    local tf = self.entity:getComponent(TransformComponent)

    local wp_position = self.scene:findEntityByName(wp.symbol):getComponent(TransformComponent).translation

    if self:is_docked() then
        -- tf.translation = vec3(system.x+wp.x, system.y+wp.y-8, 1)
        tf.translation = vec3(wp_position.x, wp_position.y-4, 1)
    elseif self:is_in_orbit() then

        local around_pos = self.scene:findEntityByName(wp.symbol):getComponent(TransformComponent).translation
        self.anims.orbit:set_around_pos(wp_position)
        self.anims.orbit:update(dt)
    end

    if self.ship.cooldown.remainingSeconds > 0 then
        local cd = self.ship.cooldown.remainingSeconds
        cd = clamp(cd - dt, 0, 999999999)
        self.ship.cooldown.remainingSeconds = cd
    end
end

function Ship:destroy()
end

function Ship:on_hover_enter()
    local cc = self.entity:getComponent(CircleComponent)
    cc.fillColor = colors.hovered.fill
    cc.outlineColor = colors.hovered.outline
    self.hovered = true;
end

function Ship:on_hover_leave()
    local cc = self.entity:getComponent(CircleComponent)
    cc.outlineColor = vec4(255, 255, 255, 255)
    cc.fillColor = colors.default.fill
    cc.outlineColor = colors.default.outline
    self.hovered = false;
end

return Ship
