local ContractsWindow = {}

local function render_contract(contract)
    if ImGui.TreeNode(contract.id) then
        ImGui.Text("Faction"); ImGui.SameLine(100); ImGui.Text(contract.factionSymbol)
        ImGui.Text("Type"); ImGui.SameLine(100); ImGui.Text(contract.type)
        if ImGui.TreeNode("Terms") then
            ImGui.Text("Deadline"); ImGui.SameLine(); ImGui.Text(contract.terms.deadline)

            if ImGui.TreeNode("Payment") then
                ImGui.Text("On Accepted:"); ImGui.SameLine(); ImGui.Text("$" .. contract.terms.payment.onAccepted)
                ImGui.Text("On Fulfilled:"); ImGui.SameLine(); ImGui.Text("$" .. contract.terms.payment.onFulfilled)
                ImGui.TreePop();
            end


            local goods = contract.terms.deliver
            if ImGui.TreeNode("Deliver") then
                for _, good in ipairs(goods) do
                    ImGui.Text(good.tradeSymbol..
                        " -> ".. good.destinationSymbol..": "..
                        good.unitsFulfilled .. "/" .. good.unitsRequired)
                end
                ImGui.TreePop()
            end

            if not contract.accepted then
                if ImGui.Button("Accept") then
                    _G.apis.spacetraders.contracts:accept_contract(contract.id);
                    sptr.api.get_contracts()
                end
            end

            ImGui.TreePop()
        end
        ImGui.TreePop()
    end
end

local function render_contracts(title, contracts)
    local count = 0
    for _, contract in pairs(contracts) do
        count = count + 1
    end

    for _, contract in pairs(contracts) do
        if ImGui.TreeNode(title.." (" .. count .. ")") then
            render_contract(contract)
            ImGui.TreePop()
        end
    end
end

function ContractsWindow:update(dt)
    ImGui.Begin("Contracts", true, ImGuiWindowFlags.NoBackground)
    render_contracts("Pending", sptr.g.pending_contracts)
    render_contracts("Accepted", sptr.g.active_contracts)
    ImGui.End()
end

return ContractsWindow
