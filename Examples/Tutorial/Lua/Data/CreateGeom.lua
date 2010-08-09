-- Create a Material for the Geometry
local BlinnMat = OSG.getFieldContainer("Blinn Material")
if(not BlinnMat) then
    BlinnMat = OSG.createFieldContainer("SimpleMaterial")
    BlinnMat:setName("Blinn Material")
end

BlinnMat:setFieldValue("ambient", OSG.Color3f(0.2,0.2,0.2))
BlinnMat:setFieldValue("diffuse", OSG.Color3f(0.6,0.6,0.6))
BlinnMat:setFieldValue("specular", OSG.Color3f(1.0,1.0,1.0))
BlinnMat:setFieldValue("shininess", 50.0)

-- Create a Sphere Geometry
local SphereGeo = OSG.getFieldContainer("Sphere Geometry")
if(not SphereGeo) then
    SphereGeo = OSG.makeSphereGeo(2,3.0)
    SphereGeo:setName("Sphere Geometry")
end

SphereGeo:setFieldValue("material", BlinnMat)

local SphereNode = OSG.getFieldContainer("Sphere Node")
if(not SphereNode) then
    SphereNode = OSG.createFieldContainer("Node")
    SphereNode:setName("Sphere Node")

    OSG.getFieldContainer("Scene Node"):pushFieldValue("children", SphereNode)
end

SphereNode:setFieldValue("core", SphereGeo)
