require("help")

--[[ OSG support ]]
local function OpenSGLuaHelp(obj)
    --FieldContainers
    if swig_type(obj) == "OSG::FieldContainerRefPtr *" then
        local FieldContainerType = obj:getType()
        if FieldContainerType then
            local ret = {class = FieldContainerType:getName()}
            ret["Main"] = FieldContainerType:getDocumentation()
            for FieldIndex=1,FieldContainerType:getNumFieldDescs() do
                local FieldDesc = FieldContainerType:getFieldDesc(FieldIndex)
                ret[FieldDesc:getName()] = FieldDesc:getDocumentation()
            end
            return ret
        else
            return nil
        end
    end

    return nil
end

function help.supportOpenSGLua()
	if not OSG then
		error("Cannot load help OSG support: OSG not found.", 2)
	end

	help.addHelpExtension(OpenSGLuaHelp)

	help.docstring{
		[[Introspection-based wrapper of OpenSceneGraph functionality.]],
		functions = {
			"loadObjectFile",
			"saveObjectFile",
			"loadWrapper",
			"NodeCallback",
			"getTypes",
			"getTypeInfo",
			"createByName"
		}
	}.applyTo(OSG)
	
	help.supportOpenSGLua = function()
		help.print("OSG help support already enabled!")
	end
end
--[[ Auto-enable Support for OSG ]]

-- If there's something called OSG, assume it is OSG the
-- OpenSG and OpenSGToolbox Lua-wrapper
if OSG then
	help.supportOpenSGLua()
end

