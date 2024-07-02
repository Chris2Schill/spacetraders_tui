local OrbitAnimation = require("anim.orbit")

local Waypoint = {
    anims = {}
}

local Yellow = vec4(255, 255, 0, 200)
local White = vec4(255, 255, 255, 200)
local Invis = vec4(0, 0, 0, 0)
local Cyan = vec4(0, 255, 255, 200)
local Green = vec4(100, 200, 0, 200)
local Gray = vec4(100, 100, 100, 200)
local Brown = vec4(82, 58, 40, 200)

local colors = {
    default = {
        fill = Yellow,
        outline = Invis,
    },
    hovered = {
        fill = Yellow,
        outline = Invis,
    }
}

ContextMenuPos = vec2(0, 0)
ContextMenuOpen = false

function Waypoint:start()
    local tag = self.entity:getComponent(TagComponent).tag
    self.waypoint = sptr.g.waypoints[tag]

    if self.waypoint.type == "PLANET" then
        if not self.entity:hasComponent(SpriteComponent) then
            local sc = self.entity:addComponent(SpriteComponent("planet.png"))

            local tf = self.entity:getComponent(TransformComponent)
            tf.scale = vec3(0.009, 0.009, 0.009)
        end
    end
    if not self.entity:hasComponent(CircleComponent) then
        local radius = 1 -- default
        --TODO: REMOVE
        if self.waypoint.type == "PLANET" then
            radius = 0
        end

        local cc = self.entity:addComponent(CircleComponent(radius))

        if self.waypoint.type == "MOON" then
            colors.default.fill = Gray
            colors.default.outline = Invis
            colors.hovered.fill = Gray
            colors.hovered.outline = Invis
        elseif self.waypoint.type == "ASTEROID" or
           self.waypoint.type == "ENGINEERED_ASTEROID" or
           self.waypoint.type == "ASTEROID_FIELD" then

            colors.default.fill = Brown
            colors.default.outline = Invis
            colors.hovered.fill = Brown
            colors.hovered.outline = Invis

        elseif has_trait(self.waypoint, "SHIPYARD") then
            colors.default.fill = Green
            colors.default.outline = Invis
            colors.hovered.fill = Green
            colors.hovered.outline = Invis
        elseif has_trait(self.waypoint, "MARKETPLACE") then
            colors.default.fill = Cyan
            colors.default.outline = Invis
            colors.hovered.fill = Cyan
            colors.hovered.outline = Invis
        end

        cc.fillColor = colors.default.fill
        cc.outlineColor = colors.default.outline
    end

    local system = sptr.g.systems[self.waypoint.systemSymbol]
    if system ~= nil then
        local tf = self.entity:getComponent(TransformComponent)
        tf.translation = vec3(self.waypoint.x + system.x, self.waypoint.y + system.y, 0)

        self.anims.orbit = OrbitAnimation.new(self, vec3(system.x, system.y, 1), 0.001)

        -- If no orbit then we orbit the system, set the distance of the orbit to the relative distance
        -- from system center
        if self.waypoint.orbits == nil then
            self.anims.orbit.dist = distance(vec2(0,0), vec2(self.waypoint.x, self.waypoint.y))
        end
    end
end

function Waypoint:update(dt)

    if self.waypoint.orbits ~= nil then
        local around_pos = self.scene:findEntityByName(self.waypoint.orbits):getComponent(TransformComponent).translation
        self.anims.orbit:set_around_pos(around_pos)
    end
    self.anims.orbit:update(dt)

    if self.hovered and not ContextMenuOpen then

        local mx, my = ImGui.GetMousePos()
        ImGui.SetNextWindowPos(mx + 10, my)
        ImGui.OpenPopup("Tooltip")

        if ImGui.BeginPopup("Tooltip") then
            ImGui.Text(self.waypoint.symbol.. " - " .. self.waypoint.type)

            ImGui.Separator()
            for _,trait in ipairs(self.waypoint.traits) do
                if trait.symbol == "MARKETPLACE" then
                    -- print(inspect(get_marketplace(self.waypoint)))
                    -- print(inspect(get_marketplace(self.waypoint).exports))
                end
                ImGui.Text(trait.name)
            end
            -- ImGui.Text(inspect(self.waypoint))

            ImGui.EndPopup()
        end
        MouseDown = ImGui.IsMouseDown(ImGuiMouseButton.ImGuiMouseButton_Right)
        if MouseDown then
            ContextMenuOpen = true
            ContextMenuPos = vec2(mx + 10, my)
        end

        if ImGui.IsMouseClicked(ImGuiMouseButton.ImGuiMouseButton_Left) then
            local market = sptr.api.get_market(self.waypoint)
            if has_trait(self.waypoint, "MARKETPLACE") then
                local market_selected = sptr.events.market_selected()
                market_selected.market = market
                dispatcher:trigger(market_selected)
            end
        end
    end

    if ContextMenuOpen then
        ImGui.SetNextWindowPos(ContextMenuPos.x, ContextMenuPos.y)
        ImGui.OpenPopup(self.waypoint.symbol .. "contextmenu")
        if ImGui.BeginPopup(self.waypoint.symbol .. "contextmenu") then
            for name, ship in pairs(sptr.g.ships) do
                if ImGui.CollapsingHeader(name) then
                    if ImGui.Button("Navigate") then
                        ship.get_actor():navigate(self.waypoint.symbol)
                        ImGui.CloseCurrentPopup()
                        ContextMenuOpen = false
                    end
                end
            end
            if ImGui.Button("Close") then
                ImGui.CloseCurrentPopup()
                ContextMenuOpen = false
            end
            ImGui.EndPopup()
        end
    end
    -- print(MouseDown)
end

function Waypoint:destroy()
end

function Waypoint:on_hover_enter()
    local cc = self.entity:getComponent(CircleComponent)
    cc.fillColor = colors.hovered.fill
    cc.outlineColor = colors.hovered.outline
    self.hovered = true;
    -- print(inspect(market))
    -- print(tostring(has_marketplace(self.waypoint)))
    -- print(inspect(market))
end

function Waypoint:on_hover_leave()
    local cc = self.entity:getComponent(CircleComponent)
    cc.fillColor = colors.default.fill
    cc.outlineColor = colors.default.outline
    self.hovered = false;
end

return Waypoint
