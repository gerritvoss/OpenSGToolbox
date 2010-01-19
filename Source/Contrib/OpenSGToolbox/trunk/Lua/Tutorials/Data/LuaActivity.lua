function printMethodDesc(AnEventProducer)
    for MethodId=1,AnEventProducer:getNumMethodDescs() do
        print(AnEventProducer:getMethodDescription(MethodId):getCName())
    end
end

local NewLuaButton = OSG.getFieldContainer("Exc Lua Func Button")

if(NewLuaButton == nil) then
    --Create the Button
    NewLuaButton = OSG.createFieldContainer("Button")

    NewLuaButton:setName("Exc Lua Func Button")
    NewLuaButton:setFieldValue("Text", "Exc Lua Func")

    --Attach the Button to the Panel
    local ButtonPanel = OSG.getFieldContainer("Button Panel")
    ButtonPanel:pushFieldValue("Children", NewLuaButton)
end

print(NewLuaButton:getType():getCName())
printMethodDesc(NewLuaButton:getProducerType())

--Create a lua activity
local ALuaActivity = OSG.createFieldContainer("LuaActivity")
ALuaActivity:setFieldValue("Code", "function handleEvent(Event, MethodId)\nprint('Text of Source Button', Event:getFieldValue('Source'):getFieldValue('Text'))\nend")
ALuaActivity:setFieldValue("EntryFunction", "handleEvent")


local WindEvntProd = OSG.getFieldContainer("Tutorial Window Event Producer")
local ACursorActivity = OSG.createFieldContainer("CursorActivity")
ACursorActivity:setFieldValue("ActivityType", 2)
ACursorActivity:setFieldValue("CursorType", 8)
ACursorActivity:setFieldValue("WindowEventProducer", WindEvntProd)

--Attach this activity to the Button's Activity Event
NewLuaButton:attachActivity(ALuaActivity, "ActionPerformed")
NewLuaButton:attachActivity(ACursorActivity, "ActionPerformed")

