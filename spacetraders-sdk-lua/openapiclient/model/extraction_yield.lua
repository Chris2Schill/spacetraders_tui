--[[
  SpaceTraders API

  SpaceTraders is an open-universe game and learning platform that offers a set of HTTP endpoints to control a fleet of ships and explore a multiplayer universe.  The API is documented using [OpenAPI](https://github.com/SpaceTradersAPI/api-docs). You can send your first request right here in your browser to check the status of the game server.  ```json http {   \"method\": \"GET\",   \"url\": \"https://api.spacetraders.io/v2\", } ```  Unlike a traditional game, SpaceTraders does not have a first-party client or app to play the game. Instead, you can use the API to build your own client, write a script to automate your ships, or try an app built by the community.  We have a [Discord channel](https://discord.com/invite/jh6zurdWk5) where you can share your projects, ask questions, and get help from other players.   

  The version of the OpenAPI document: 2.0.0
  Contact: joel@spacetraders.io
  Generated by: https://openapi-generator.tech
]]

-- extraction_yield class
local extraction_yield = {}
local extraction_yield_mt = {
	__name = "extraction_yield";
	__index = extraction_yield;
}

local function cast_extraction_yield(t)
	return setmetatable(t, extraction_yield_mt)
end

local function new_extraction_yield(symbol, units)
	return cast_extraction_yield({
		["symbol"] = symbol;
		["units"] = units;
	})
end

return {
	cast = cast_extraction_yield;
	new = new_extraction_yield;
}