SphereNode = OSG.makeSphere(2,3.0)

SphereNode2 = SphereNode:deepClone("")

SceneNode = OSG.getFieldContainer("Scene Node")

SceneNode:pushFieldValue("children", SphereNode2)