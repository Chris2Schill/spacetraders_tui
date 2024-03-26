local inspect = require("inspect")

ApiKey     = require('openapiclient.api.apikey')
FleetApi = require("openapiclient.api.fleet_api")

local token =
"eyJhbGciOiJSUzI1NiIsInR5cCI6IkpXVCJ9.eyJpZGVudGlmaWVyIjoiRkFUSE9SU0VOSVBTIiwidmVyc2lvbiI6InYyLjIuMCIsInJlc2V0X2RhdGUiOiIyMDI0LTAzLTI0IiwiaWF0IjoxNzExMzgyNTMwLCJzdWIiOiJhZ2VudC10b2tlbiJ9.OlvQa9W9GXppxpJZLSNsHbHR2V9kD5jlRnmFdq9qMaIow-ZHH3734q7a9oM11IUTIHVOpWmk1-dpuPGC1QKg7X6Ib_E160IiqHV08e6s9JHt07G-vySMsbA6iaI5cJp4zAGHp2ydgpBe6JwH5gU4bcGl6xmstLV3LVdsIIht73gRFt3oZKl-TsZYAnHvr8n-HHw7RMTZL1NM0alxUZldscc3wgIcfpr87dxYGNbFPCGlVx58IzNNMjhOwjw4ffcV3yy34W8iQTyhd5x9vMaNrHe_JuQPPtGhN1xy0qB4QFokuZPcV_2zK72X8DqtOds6ASMMtwCwPVWEl9URIda4xg"
ApiKey.api_key = token

local authority = "api.spacetraders.io"
local basePath = "/v2"
local scheme = { "https" }

local fleetsApi = FleetApi.new(authority, basePath, scheme)

local function istable(t)
    return type(t) == 'table'
end

local ships = {}

function OnCreate()
    ships, _ = fleetsApi:get_my_ships("1", "2")
    print(inspect.inspect(ships))
end

function draw_table(t)
    for k,v in pairs(t) do
        if ImGui.CollapsingHeader(k..(" - "..(v.name or ""))) then
            ImGui.Indent(20)
            -- if istable(v) then
            --     draw_table(v)
            -- else
                ImGui.Text(inspect.inspect(v))
            -- end
            ImGui.Unindent(20)
        end
    end
end

function draw_list(l)
    for i,v in ipairs(l) do
        if ImGui.CollapsingHeader(v.symbol) then
            ImGui.Indent(20)
            if istable(v) then
                draw_table(v)
            else
                ImGui.Text(inspect.inspect(v))
            end
            ImGui.Unindent(20)
        end
    end
end

function OnUpdate(dt)
    ImGui.DockSpaceOverViewport()
    ImGui.Begin("Ships")

    draw_list(ships.data)
    -- for i,ship in ipairs(ships.data) do
    --     if ImGui.CollapsingHeader(ship.symbol) then
    --         for part,partData in pairs(ship) do
    --             -- ImGui.Text(inspect.inspect(v))
    --             ImGui.Indent(20)
    --             if ImGui.CollapsingHeader(part..(" - "..(partData.name or ""))) then
    --                 ImGui.Indent(20)
    --                 for subpart, subpartData in pairs(partData) do
    --                     if ImGui.CollapsingHeader(subpart) then
    --                         ImGui.Indent(2)
    --                         ImGui.Text(inspect.inspect(subpartData))
    --                         ImGui.Unindent(2)
    --                     end
    --                 end
    --                 ImGui.Text(inspect.inspect(partData))
    --                 ImGui.Unindent(20)
    --             end
    --             ImGui.Unindent(20)
    --         end
    --         -- ImGui.Text(inspect.inspect(ship))
    --     end
    -- end
    -- ImGui.CollapsingHeader("Ship1")
    -- ImGui.Text(inspect.inspect(ships.data[1]))
    -- ImGui::Text("test=".._G.test)
    -- ImGui.LabelText("$"..myagent.data.credits, "Credits")
    -- ImGui.LabelText(myagent.data.startingFaction, "Faction")
    -- ImGui.LabelText(myagent.data.headquarters, "Headquarters")
    ImGui.End()

    ImGui.Begin("Test")
    ImGui.Text(inspect.inspect(ships.data[1].crew))
    ImGui.End()
    --
    -- print(inspect.inspect(myagent))
end

