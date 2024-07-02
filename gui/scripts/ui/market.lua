local MarketUI = {}

local WindowOpen = true

function MarketUI:init()
    Listener = {
        connections = {},
        on_market_selected = function(evt)
            self.market = evt.market
        end
    }
    Listener.connections[1] = dispatcher:connect(sptr.events.market_selected, Listener.on_market_selected)
end

function MarketUI:get_trade_goods(good_type)
    self.selected = {}
    self.selected.good = good_type

    if self.market.tradeGoods ~= nil then
        for _,good in ipairs(self.market.tradeGoods) do
            if good.symbol == good_type.symbol then
                self.selected.good_info = good
            end
        end
    end
end

function MarketUI:update(dt)
    WindowOpen = ImGui.Begin("Market", WindowOpen, ImGuiWindowFlags.NoBackground)
    if self.market ~= nil then
        ImGui.Text(self.market.symbol)
        if ImGui.Button("Refresh") then
            self.market = sptr.api.get_market(sptr.g.waypoints[self.market.symbol], true)
        end
        -- print(inspect(self.market))
        if ImGui.CollapsingHeader("Imports") then
            ImGui.Indent(20)
            for _, import in ipairs(self.market.imports) do
                if ImGui.Selectable(import.name) then
                    self:get_trade_goods(import)
                end
            end
            ImGui.Unindent(20)
        end
        if ImGui.CollapsingHeader("Exports") then
            ImGui.Indent(20)
            for _, export in ipairs(self.market.exports) do
                if ImGui.Selectable(export.name) then
                    self:get_trade_goods(export)
                end
            end
            ImGui.Unindent(20)
        end
        -- ImGui.Text(inspect(self.market))
    end
    -- ImGui.DockSpace(6966)
    ImGui.End()

    if self.selected.good ~= nil then
        -- ImGui.SetNextWindowDockID(6966)
        local show = ImGui.Begin("Goods", true, ImGuiWindowFlags.NoBackground)
        if not show then self.selected.good = nil end

        local good = self.selected.good
        ImGui.Text("You want to trade?")
        ImGui.Separator()

        --     for _,good in ipairs(self.goods) do
        --         ImGui.Selectable(good.sym)
        --     end
        ImGui.Text(good.name)
        ImGui.Indent(20)
        ImGui.TextWrapped(good.description)


        if self.selected.good_info ~= nil then
            local good_info = self.selected.good_info
            ImGui.Text("Activity: "..good_info.activity)
            ImGui.Text("Supply: "..good_info.supply)
            ImGui.Text("Trade Volume: "..good_info.tradeVolume)

            if good_info.type == "EXPORT" then
                if ImGui.Button("Buy $"..good_info.purchasePrice) then
                end
            end

            if good_info.type == "IMPORT" then
                if ImGui.Button("Sell $"..good_info.sellPrice) then
                end
            end
        end


        ImGui.Unindent(20)
        -- ImGui.Text(inspect(self.selected.good_info))

        ImGui.End()
    end
end

return MarketUI
