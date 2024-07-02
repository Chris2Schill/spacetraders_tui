local ContractsData = {}

local LIMIT = 20


sptr.api.get_contracts = function()
    local contracts = _G.apis.spacetraders.contracts:get_contracts(tostring(1), tostring(LIMIT))
    if contracts ~= nil then
        local pending_contracts = {}
        local active_contracts = {}
        for i, contract in ipairs(contracts.data) do
            if contract.accepted then
                active_contracts[contract.id] = contract
            else
                pending_contracts[contract.id] = contract
            end
        end
        sptr.g.pending_contracts = pending_contracts
        sptr.g.active_contracts  = active_contracts
    else
        log_error("Failed to get contracts")
    end
end


function ContractsData:init()
    sptr.api.get_contracts()
end


function ContractsData:destroy()
end

return ContractsData
