local inspect = require("inspect")

ApiKey   = require('openapiclient.api.apikey')
AgentsApi = require("openapiclient.api.agents_api")

local token =
"eyJhbGciOiJSUzI1NiIsInR5cCI6IkpXVCJ9.eyJpZGVudGlmaWVyIjoiRkFUSE9SU0VOSVBTIiwidmVyc2lvbiI6InYyLjIuMCIsInJlc2V0X2RhdGUiOiIyMDI0LTAzLTI0IiwiaWF0IjoxNzExMzgyNTMwLCJzdWIiOiJhZ2VudC10b2tlbiJ9.OlvQa9W9GXppxpJZLSNsHbHR2V9kD5jlRnmFdq9qMaIow-ZHH3734q7a9oM11IUTIHVOpWmk1-dpuPGC1QKg7X6Ib_E160IiqHV08e6s9JHt07G-vySMsbA6iaI5cJp4zAGHp2ydgpBe6JwH5gU4bcGl6xmstLV3LVdsIIht73gRFt3oZKl-TsZYAnHvr8n-HHw7RMTZL1NM0alxUZldscc3wgIcfpr87dxYGNbFPCGlVx58IzNNMjhOwjw4ffcV3yy34W8iQTyhd5x9vMaNrHe_JuQPPtGhN1xy0qB4QFokuZPcV_2zK72X8DqtOds6ASMMtwCwPVWEl9URIda4xg"
ApiKey.api_key = token

local authority = "api.spacetraders.io"
local basePath = "/v2"
local scheme = { "https" }

local agentsApi = AgentsApi.new(authority, basePath, scheme)

local myagent = {}

function OnCreate()
    myagent, _ = agentsApi:get_my_agent()
    print(inspect.inspect(myagent))
    _G.test = 10
end

function OnUpdate(dt)
    ImGui.DockSpaceOverViewport()
    ImGui.Begin(myagent.data.symbol)
    ImGui.LabelText("$"..myagent.data.credits, "Credits")
    ImGui.LabelText(myagent.data.startingFaction, "Faction")
    ImGui.LabelText(myagent.data.headquarters, "Headquarters")
    ImGui.End()

    -- print(inspect.inspect(myagent))
end

