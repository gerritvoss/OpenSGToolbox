-- Create a Material for the Geometry
local BlinnMat = OSG.getFieldContainer("Blinn Material")
if(not BlinnMat) then
    BlinnMat = OSG.createFieldContainer("LambertMaterial")
    BlinnMat:setName("Blinn Material")
end

BlinnMat:setFieldValue("Color", OSG.Color3f(1,1,0))
--BlinnMat:setFieldValue("AmbientColor", OSG.Color3f(1,1,0))
BlinnMat:setFieldValue("Diffuse", 0.2)

-- Create a Sphere Geometry
local SphereGeo = OSG.getFieldContainer("Sphere Geo")
if(not SphereGeo) then
    SphereGeo = OSG.makeSphereGeo(2,3.0)
    SphereGeo:setName("Sphere Geo")
end

SphereGeo:setFieldValue("material", BlinnMat)

local SphereNode = OSG.getFieldContainer("Sphere Node")
if(not SphereNode) then
    SphereNode = OSG.createFieldContainer("Node")
    SphereNode:setName("Sphere Node")

    OSG.getFieldContainer("Scene Node"):pushFieldValue("children", SphereNode)
end

SphereNode:setFieldValue("core", SphereGeo)
