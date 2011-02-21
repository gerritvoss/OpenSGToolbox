require("helpOpenSG")

help.setPrint(_G.print)

help(help.setPrint)

help.setPrint(printToOutput)

--Redirect to Output TextField
function printToOutput(helpText)
    local OutputTextArea = OSG.getFieldContainer("Message TextArea")

    OutputTextArea:setFieldValue("Text", helpText)
end

--Get general help for OSG
help(OSG)

--Get help for an object
local AButton = OSG.createFieldContainer("FieldAnimation")
help(AButton)