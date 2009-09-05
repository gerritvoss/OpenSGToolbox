local SphereNode = OSG.makeSphere(2,3.0)

local SphereNodeClone = SphereNode:deepClone("")

local SceneNode = OSG.getFieldContainer("Scene Node")

SceneNode:pushFieldValue("children", SphereNodeClone)