-- Creating a particle system/emitter/affector

-- create distibutions for emitter
local PosDistrib = OSG.getFieldContainer("Cone Distribution")
if(not PosDistrib) then
	PosDistrib = OSG.createFieldContainer("ConeDistribution3D")
	PosDistrib:setName("Cone Distribution")
end

PosDistrib:setFieldValue("Position",OSG.Pnt3f(0.0,0.0,0.0))
PosDistrib:setFieldValue("Direction",OSG.Vec3f(0.0,0.0,1.0))
PosDistrib:setFieldValue("Spread",2.0)
PosDistrib:setFieldValue("Min",1.0)
PosDistrib:setFieldValue("Max",1.1)
PosDistrib:setFieldValue("SurfaceOrVolume",0) -- 0 = Volume


-- create emitter
local Generator = OSG.getFieldContainer("TestGen")
if(not Generator) then
print("Creating Generator...")
	Generator = OSG.createFieldContainer("RateParticleGenerator")
	Generator:setName("TestGen")
print("Generator created ok")
end
Generator:setFieldValue("PositionFunction",PosDistrib)
Generator:setFieldValue("GenerationRate",300)



-- create particle system
local ParticleSys = OSG.getFieldContainer("My Particle System")
ParticleSys:pushFieldValue("Generators",Generator)
ParticleSys:setFieldValue("MaxParticles",200)


-- create drawer
local PSPointDrawer = OSG.getFieldContainer("PntDrawer")
if(not PSPointDrawer) then
 PSPointDrawer = OSG.createFieldContainer("PointParticleSystemDrawer")
 PSPointDrawer:setName("PntDrawer")
end


-- create material
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


-- already set up 
local PSCore = OSG.getFieldContainer("My Particle System Core")

PSCore:setFieldValue("System", ParticleSys)
PSCore:setFieldValue("Drawer", PSPointDrawer)
PSCore:setFieldValue("material", BlinnMat)

--setting up Particle System Node
local ParticleSystemNode = OSG.getFieldContainer("PS Node")
if(not SphereNode) then
    ParticleSystemNode = OSG.createFieldContainer("Node")
    ParticleSystemNode:setName("PS Node")
end
ParticleSystemNode:setFieldValue("core", PSCore)

OSG.getFieldContainer("Scene Node"):pushFieldValue("children", ParticleSystemNode)


