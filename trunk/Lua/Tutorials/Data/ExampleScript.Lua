print("Hello World")

FCFact = OSG.FieldContainerFactory_the()

AButton = FCFact:createNode("Node")

print(OSG.getFieldValue(AButton, "PreferredSize"))