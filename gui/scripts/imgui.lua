function OnCreate()
end

function OnUpdate(dt)
    imgui.SetNextWindowSize(550, 680, imgui.constant.SetCond.FirstUseEver)
    imgui.Begin("Demo", true, imgui.constant.WindowFlags.ShowBorders)
    imgui.End()
end
