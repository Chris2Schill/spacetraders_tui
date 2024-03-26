--[[
  SpaceTraders API

  SpaceTraders is an open-universe game and learning platform that offers a set of HTTP endpoints to control a fleet of ships and explore a multiplayer universe.  The API is documented using [OpenAPI](https://github.com/SpaceTradersAPI/api-docs). You can send your first request right here in your browser to check the status of the game server.  ```json http {   \"method\": \"GET\",   \"url\": \"https://api.spacetraders.io/v2\", } ```  Unlike a traditional game, SpaceTraders does not have a first-party client or app to play the game. Instead, you can use the API to build your own client, write a script to automate your ships, or try an app built by the community.  We have a [Discord channel](https://discord.com/invite/jh6zurdWk5) where you can share your projects, ask questions, and get help from other players.   

  The version of the OpenAPI document: 2.0.0
  Contact: joel@spacetraders.io
  Generated by: https://openapi-generator.tech
]]

-- ship_nav_flight_mode class
local ship_nav_flight_mode = {}
local ship_nav_flight_mode_mt = {
	__name = "ship_nav_flight_mode";
	__index = ship_nav_flight_mode;
}

local function cast_ship_nav_flight_mode(t)
	return setmetatable(t, ship_nav_flight_mode_mt)
end

local function new_ship_nav_flight_mode()
	return cast_ship_nav_flight_mode({
	})
end

return {
	cast = cast_ship_nav_flight_mode;
	new = new_ship_nav_flight_mode;
}
