function setOutputText(text)
   local MessageTextArea = OSG.getFieldContainer("Message TextArea")
   MessageTextArea:setFieldValue("Text", text)
end

setOutputText("Hello World!!!!")
