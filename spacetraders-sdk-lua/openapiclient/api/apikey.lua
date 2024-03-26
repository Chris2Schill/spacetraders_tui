local M = {
    api_key = "",
}

function add_authoriation_header(headers)
	headers:upsert("authorization", "Bearer "..M.api_key)
end

return M
