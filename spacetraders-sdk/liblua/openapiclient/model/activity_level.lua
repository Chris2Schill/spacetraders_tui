--[[
  SpaceTraders API

  SpaceTraders is an open-universe game and learning platform that offers a set of HTTP endpoints to control a fleet of ships and explore a multiplayer universe.  The API is documented using [OpenAPI](https://github.com/SpaceTradersAPI/api-docs). You can send your first request right here in your browser to check the status of the game server.  ```json http {   \"method\": \"GET\",   \"url\": \"https://api.spacetraders.io/v2\", } ```  Unlike a traditional game, SpaceTraders does not have a first-party client or app to play the game. Instead, you can use the API to build your own client, write a script to automate your ships, or try an app built by the community.  We have a [Discord channel](https://discord.com/invite/jh6zurdWk5) where you can share your projects, ask questions, and get help from other players.   

  The version of the OpenAPI document: 2.0.0
  Contact: joel@spacetraders.io
  Generated by: https://openapi-generator.tech
]]

-- activity_level class
local activity_level = {}
local activity_level_mt = {
	__name = "activity_level";
	__index = activity_level;
}

local function cast_activity_level(t)
	return setmetatable(t, activity_level_mt)
end

local function new_activity_level()
	return cast_activity_level({
	})
end

return {
	cast = cast_activity_level;
	new = new_activity_level;
}
