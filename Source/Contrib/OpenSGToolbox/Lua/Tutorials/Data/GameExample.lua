function setPlayerHealth(health)
   local HealthBar = OSG.getFieldContainer("Player Health Bar")
   local HealthModel = HealthBar:getFieldValue("RangeModel")
   HealthModel:setFieldValue("InternalValue", health)
   setOutputText(string.format("%.2f", HealthModel:getFieldValue("InternalValue")))
end

function getPlayerHealth()
   local HealthBar = OSG.getFieldContainer("Player Health Bar")
   local HealthModel = HealthBar:getFieldValue("RangeModel")
   return HealthModel:getFieldValue("InternalValue")
end

function setOutputText(text)
   local MessageTextArea = OSG.getFieldContainer("Message TextArea")
   MessageTextArea:setFieldValue("Text", text)
end


local CharacterHealthModel = OSG.getFieldContainer("Player Health Bar")

if(CharacterHealthModel == nil) then
    local CharacterHealthModel = OSG.createFieldContainer("DefaultBoundedRangeModel")
    CharacterHealthModel:setFieldValue("InternalMinimum", 0)
    CharacterHealthModel:setFieldValue("InternalMaximum", 100)
    CharacterHealthModel:setFieldValue("InternalValue", 40)

    local AProgressBar = OSG.createFieldContainer("ProgressBar")

    AProgressBar:setFieldValue("RangeModel", CharacterHealthModel)
    AProgressBar:setName("Player Health Bar")

    local TheButtonPanel = OSG.getFieldContainer("Button Panel")

    TheButtonPanel:pushFieldValue("Children", AProgressBar)
end

setPlayerHealth(getPlayerHealth() -10)

