local inspect = require("inspect")

ApiKey     = require('openapiclient.api.apikey')
DefaultApi = require("openapiclient.api.default_api")
AgentsApi = require("openapiclient.api.agents_api")
FleetApi = require("openapiclient.api.fleet_api")

local token =
"eyJhbGciOiJSUzI1NiIsInR5cCI6IkpXVCJ9.eyJpZGVudGlmaWVyIjoiRkFUSE9SU0VOSVBTIiwidmVyc2lvbiI6InYyLjIuMCIsInJlc2V0X2RhdGUiOiIyMDI0LTAzLTI0IiwiaWF0IjoxNzExMzgyNTMwLCJzdWIiOiJhZ2VudC10b2tlbiJ9.OlvQa9W9GXppxpJZLSNsHbHR2V9kD5jlRnmFdq9qMaIow-ZHH3734q7a9oM11IUTIHVOpWmk1-dpuPGC1QKg7X6Ib_E160IiqHV08e6s9JHt07G-vySMsbA6iaI5cJp4zAGHp2ydgpBe6JwH5gU4bcGl6xmstLV3LVdsIIht73gRFt3oZKl-TsZYAnHvr8n-HHw7RMTZL1NM0alxUZldscc3wgIcfpr87dxYGNbFPCGlVx58IzNNMjhOwjw4ffcV3yy34W8iQTyhd5x9vMaNrHe_JuQPPtGhN1xy0qB4QFokuZPcV_2zK72X8DqtOds6ASMMtwCwPVWEl9URIda4xg"

ApiKey.api_key = token

local authority = "api.spacetraders.io"
local basePath = "/v2"
local scheme = { "https" }

local agentsApi = AgentsApi.new(authority, basePath, scheme)
local fleetsApi = FleetApi.new(authority, basePath, scheme)

Components  = {
    TransformComponent = {

    },
    SystemComponent = {

    },
    RenderComponent = {

    },
}

local myagent = {x = 1}

function OnCreate()
    myagent, _ = agentsApi:get_my_agent()
    print(inspect.inspect(myagent))
end

function OnUpdate(dt)
    -- myagent, _ = agentsApi:get_my_agent()
    -- print(inspect.inspect(myagent))
    ImGui.Begin("Test")
    ImGui.Text(inspect.inspect(myagent))
    ImGui.End("Test")
end

