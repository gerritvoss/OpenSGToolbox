function setOutputText(text)
   MessageTextArea = OSG.getFieldContainer("Message TextArea")
   MessageTextArea:setFieldValue("Text", text)
end

setOutputText("Hello World!!!!")
