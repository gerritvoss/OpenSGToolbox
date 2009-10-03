-- Particle System Mainupulattion

-- create distibutions for emitter
-- position distribution
local PosDistrib = OSG.getFieldContainer("Cone Distribution")
if(not PosDistrib) then
	PosDistrib = OSG.createFieldContainer("ConeDistribution3D")
	PosDistrib:setName("Cone Distribution")
end

PosDistrib:setFieldValue("Position",OSG.Pnt3f(0.0,0.0,0.0))
PosDistrib:setFieldValue("Direction",OSG.Vec3f(0.0,1.0,0.0))
PosDistrib:setFieldValue("Spread",2.0)
PosDistrib:setFieldValue("Min",1.0)
PosDistrib:setFieldValue("Max",1.1)
PosDistrib:setFieldValue("SurfaceOrVolume",0) -- 0 = Volume

-- converter for position to velocity
local PntToVecConverter = OSG.getFieldContainer("Type Converter")
if(not PntToVecConverter) then
	PntToVecConverter = OSG.createFieldContainer("DataConverter")
	PntToVecConverter:setName("Type Converter")
end
PntToVecConverter:setFieldValue("ToTypeName", "Vec3f")

-- converter for velocity function
local VelDistrib = OSG.getFieldContainer("Velocity Distrib")
if(not VelDistrib) then
	VelDistrib = OSG.createFieldContainer("CompoundFunction")
	VelDistrib:setName("Velocity Distrib")
end

VelDistrib:pushFieldValue("Functions", PosDistrib)
VelDistrib:pushFieldValue("Functions", PntToVecConverter)

-- create lifespan distribution
local LifeDistrib = OSG.getFieldContainer("Life Distrib")
if(not LifeDistrib) then
	LifeDistrib = OSG.createFieldContainer("GaussianNormalDistribution1D")
	LifeDistrib:setName("Life Distrib")
end

LifeDistrib:setFieldValue("Mean", 5.0)
LifeDistrib:setFieldValue("StandardDeviation", 1.0)

-- create particle generator
local Generator = OSG.getFieldContainer("TestGen")
if(not Generator) then
	Generator = OSG.createFieldContainer("RateParticleGenerator")
	Generator:setName("TestGen")

end
Generator:setFieldValue("PositionFunction",PosDistrib)
Generator:setFieldValue("VelocityFunction",VelDistrib)
Generator:setFieldValue("GenerationRate",300)
Generator:setFieldValue("LifespanFunction",LifeDistrib)

-- creating an affector
local VortexAffector = OSG.getFieldContainer("The Vortex")
if( not VortexAffector) then
	VortexAffector = OSG.createFieldContainer("VortexParticleAffector")
	VortexAffector:setName("The Vortex")
end
VortexAffector:setFieldValue("VortexAxis", OSG.Vec3f(0.0,1.0,0.0))
VortexAffector:setFieldValue("Magnitude", -1.0)
VortexAffector:setFieldValue("Beacon", OSG.createFieldContainer("Node"))


-- create particle system
local ParticleSys = OSG.getFieldContainer("My Particle System")
ParticleSys:pushFieldValue("Generators",Generator)
ParticleSys:setFieldValue("MaxParticles",2000)
--ParticleSys:pushFieldValue("Affectors",VortexAffector)

-- create drawer
local PSPointDrawer = OSG.getFieldContainer("PntDrawer")
if(not PSPointDrawer) then
 PSPointDrawer = OSG.createFieldContainer("PointParticleSystemDrawer")
 PSPointDrawer:setName("PntDrawer")
end
PSPointDrawer:setFieldValue("PointSizeScaling",3.0)


-- create material

PointChunk = OSG.createFieldContainer("PointChunk")
PointChunk:setFieldValue("smooth","true")
PointChunk:setFieldValue("size", 2.0)


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
BlinnMat:pushFieldValue("chunks", PointChunk)

-- this particle system should already be set up in the scene
local PSCore = OSG.getFieldContainer("My Particle System Core")

PSCore:setFieldValue("System", ParticleSys)
PSCore:setFieldValue("Drawer", PSPointDrawer)
PSCore:setFieldValue("material", BlinnMat)

--setting up Particle System Node
local ParticleSystemNode = OSG.getFieldContainer("PS Node")

if(not ParticleSystemNode) then
    ParticleSystemNode = OSG.createFieldContainer("Node")
    ParticleSystemNode:setName("PS Node")
end


-- final step to make particle system visible in the scene
ParticleSystemNode:setFieldValue("core", PSCore)
OSG.getFieldContainer("Root Node"):pushFieldValue("children", ParticleSystemNode)

OSG.getFieldContainer("Torus Geometry Node"):setFieldValue("travMask", 0)

