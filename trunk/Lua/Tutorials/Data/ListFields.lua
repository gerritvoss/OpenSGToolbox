function setOutputText(text)
   local MessageTextArea = OSG.getFieldContainer("Message TextArea")
   MessageTextArea:setFieldValue("Text", text)
end

function listFields(TheFC)

local NumFields = TheFC:getType():getNumFieldDescs()
local i = 0;
setOutputText(string.format("There are %d fields in %s\n",NumFields, TheFC:getName()))

local txt = {}
for i=1,NumFields do
	local FCDesc = TheFC:getType():getFieldDescription(i)
	local TypeDesc = FCDesc:getFieldType()
	txt[i] = string.format("%d: %s, %s",i,FCDesc:getCName(),TypeDesc:getCName())
	end
setOutputText(table.concat(txt, "\n"))
end

local ANode = OSG.getFieldContainer("A Node")
if(not ANode) then
    ANode = OSG.createFieldContainer("Node")
    ANode:setName("A Node")
end
