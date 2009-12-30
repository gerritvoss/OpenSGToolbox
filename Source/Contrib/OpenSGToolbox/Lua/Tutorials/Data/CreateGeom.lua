-- Create a Material for the Geometry
local BlinnMat = OSG.getFieldContainer("Blinn Material")
if(not BlinnMat) then
    BlinnMat = OSG.createFieldContainer("BlinnMaterial")
    BlinnMat:setName("Blinn Material")
end

BlinnMat:setFieldValue("Color", OSG.Color3f(1,1,1))
BlinnMat:setFieldValue("AmbientColor", OSG.Color3f(0,0,0))
BlinnMat:setFieldValue("SpecularColor", OSG.Color3f(0,0,1))
BlinnMat:setFieldValue("SpecularEccentricity", 0.5)
BlinnMat:setFieldValue("SpecularRolloff", 0.95)
BlinnMat:setFieldValue("Diffuse", 0.65)

-- Create a Sphere Geometry
local SphereGeo = OSG.getFieldContainer("Sphere Geometry")
if(not SphereGeo) then
    SphereGeo = OSG.makeSphereGeo(2,3.0)
    SphereGeo:setName("Sphere Geometry")
    -- Generate the tangents for the geometry
    OSG.calcVertexTangents(OSG.GeometryPtr_dcast(SphereGeo), 0 ,SphereGeo:getType():findFieldDescription("texCoords6"):getFieldId(),SphereGeo:getType():findFieldDescription("texCoords7"):getFieldId())
end

SphereGeo:setFieldValue("material", BlinnMat)

local SphereNode = OSG.getFieldContainer("Sphere Node")
if(not SphereNode) then
    SphereNode = OSG.createFieldContainer("Node")
    SphereNode:setName("Sphere Node")

    OSG.getFieldContainer("Scene Node"):pushFieldValue("children", SphereNode)
end

SphereNode:setFieldValue("core", SphereGeo)
