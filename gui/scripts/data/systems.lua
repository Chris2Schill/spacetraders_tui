local SystemsData = {}

local LIMIT = 20

local function get_systems(page, depth)
    if depth == 0 then return nil end

    local sys, _, _2 = _G.apis.spacetraders.systems:get_systems(tostring(page), tostring(LIMIT)).data

    if #sys == LIMIT then
        local more_sys = get_systems(page+1, depth-1)
        if more_sys ~= nil then
            sys = TableConcat(sys, more_sys)
        end
    end

    return sys
end

local function createSystemCircleEntity(system)
    -- local ent = SystemsData.scene:createEntity(system.symbol)
    -- ent:addComponent(CircleComponent(30))
    --
    -- local tf = ent:getComponent(TransformComponent)
    -- tf.translation = vec3(system.x, system.y, 0)
end

local function createSystemSpriteEntity(system)
    -- print(inspect(SystemsData))
    SystemsData.scene:createEntityActor(system.symbol, "actors/system.lua")
end

sptr.api.get_system = function(systemSymbol)
    if sptr.g.systems[systemSymbol] == nil then
        local sys = _G.apis.spacetraders.systems:get_system(systemSymbol).data
        if sys ~= nil then
            sptr.g.systems[systemSymbol] = sys;
            createSystemSpriteEntity(sys)
        else
            log_warn("Failed to get_system("..systemSymbol..")")
        end
    end
    return sptr.g.systems[systemSymbol]
end

function SystemsData:init()
    local systems = get_systems(1, 1)
    for i, system in ipairs(systems) do
        -- Data store needs to be set before creating entities
        -- print(system.symbol)
        sptr.g.systems[system.symbol] = system
        createSystemSpriteEntity(system)
        -- print("Created")
    end

end

function SystemsData:update()
end

return SystemsData
