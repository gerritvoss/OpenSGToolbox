local ButtonPanel = OSG.getFieldContainer("Button Panel")

local AButton = OSG.FieldContainerFactory_the():createFieldContainer("Label")

AButton:setFieldValue("Text", "Bla")

ButtonPanel:setFieldValue("Children", AButton, 1)