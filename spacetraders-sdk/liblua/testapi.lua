ApiKey = require('openapiclient.api.apikey')
DefaultApi = require("openapiclient.api.default_api")
AgentsApi = require("openapiclient.api.agents_api")
FleetApi = require("openapiclient.api.fleet_api")

local inspect = require("inspect")

local token =
"eyJhbGciOiJSUzI1NiIsInR5cCI6IkpXVCJ9.eyJpZGVudGlmaWVyIjoiRkFUSE9SU0VTSElUIiwidmVyc2lvbiI6InYyLjIuMCIsInJlc2V0X2RhdGUiOiIyMDI0LTAzLTEwIiwiaWF0IjoxNzEwOTYyNjE5LCJzdWIiOiJhZ2VudC10b2tlbiJ9.EBM5HSuaEIytC_j2ByAkYsHY0NTg3bx1_338mjWYeFE0gbOuuqOoLEymU48Ksnum93vxf7IcCoFV23u_iz2O5qLT_hO2Uid6WYxi8987_PDgX5_ZarFZBz4FGD_HGjYcnaHR3p3M2HosKLOfCFMddgqbKDZvuhc78gtk4LipeKVFAGVUVpr9HNgu-FQbzYxrjvolnAGRrH9PRBpdID-9ppE4tPG6lc4Le6xkr7j_4i0YnBo7ho7bpvmt10dwxaGrsxvPg-Ke_HY-oQ8h0OMpyTaN9q9ZiNVq_hVTSdvr5txhZJxTTLp0C2PVeAJPd027cbXcVtAQYnIcnf4X3K86gA"
ApiKey.api_key = token

-- local basePath = "localhost:80";
local authority = "api.spacetraders.io"
local basePath = "/v2"
local scheme = { "https" }

local agentsApi = AgentsApi.new(authority, basePath, scheme)
local fleetsApi = FleetApi.new(authority, basePath, scheme)

-- local defaultApi = DefaultApi.new(authority, basePath, scheme)
-- local err, status, body = defaultApi:register({
--     symbol = "FATHORSENIPS2",
--     faction = "COSMIC",
-- })

-- print(err)
-- print(status)
-- print(body)
-- fleetsApi.api_key = token
function dump(o, indent)
    local depth = indent or ""
    if type(o) == 'table' then
        local s = depth..'{\n'
        for k, v in pairs(o) do
            if type(k) ~= 'number' then k = '"' .. k .. '"' end
            s = depth..s .. '[' .. k .. '] = ' .. dump(v, depth.."    ") .. ',\n'
        end
        return s .. '}\n'
    else
        return tostring(o)
    end
end

-- function printTable(table)
--     for k,v in pairs(table) do
--         print(k.."="..v)
--     end
-- end
--
local myagent, _ = agentsApi:get_my_agent()
-- print(dump(myagent))


local myships, _ = fleetsApi:get_my_ships("1", "2")
-- print(dump(myships))
print(inspect.inspect(myships))



-- print(err)
-- -- printTable(err)
-- print(status)
-- print(body)

-- fleetsApi:get_my_ships('1','2')


-- require("fleet_api")
-- [fathorsenips]
-- token=eyJhbGciOiJSUzI1NiIsInR5cCI6IkpXVCJ9.eyJpZGVudGlmaWVyIjoiRkFUSE9SU0VOSVBTIiwidmVyc2lvbiI6InYyLjIuMCIsInJlc2V0X2RhdGUiOiIyMDI0LTAzLTEwIiwiaWF0IjoxNzEwMTc1NzA4LCJzdWIiOiJhZ2VudC10b2tlbiJ9.FSxXlPKUqr1e0RnCIfVpGnEba_CvrvVQvL-Th_liOGOh5vx0Qxt2ZuCzLZmPPRl1UEbzxPKuEHbtaeDcjG8Egwfw5RD8VdhmhaoB0zpG26sh3DF6Hgmo1jANBlMQ1sGcJ1Dyx8nP0j0KBFScbX9aBhYv3NqGdfYZhQcy-vdu84_QKXHbnfslDM7_eqEM7DZ1hfRLYbFNtWqNmy8aH49ShiVEOq7F-gQeon-5ByEQIatNVB7wVpAfk2Hjvy4rFrel8n5RjpdKnPnh-35LUJlN1ALHeJajf-FoJBTBJPgY6cmlYj8ZMod4DOfY8l78E8XeG-xc63vb1ZXJcef2IoDYaA
-- [fathorseshit]
