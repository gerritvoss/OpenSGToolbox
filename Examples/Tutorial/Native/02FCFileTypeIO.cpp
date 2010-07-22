// General OpenSG configuration, needed everywhere
#include "OSGConfig.h"

#include "OSGPerspectiveCamera.h"
#include "OSGGradientBackground.h"
#include "OSGPolygonForeground.h"
#include "OSGNode.h"
#include "OSGViewport.h"
#include "OSGSimpleGeometry.h"
#include "OSGTransform.h"
#include "OSGComponentTransform.h"
#include "OSGPointLight.h"
#include "OSGSpotLight.h"
#include "OSGDirectionalLight.h"
#include "OSGGroup.h"
#include "OSGDistanceLOD.h"
#include "OSGBillboard.h"


#include "OSGFCFileHandler.h"

// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE

NodeUnrecPtr createScene(void);

// Initialize OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    {
        //Create some Field Containers
        NodeUnrecPtr Root = createScene();

        FCFileType::FCPtrStore Containers;
        Containers.insert(Root);

        //Use an empty Ignore types vector
        FCFileType::FCTypeVector IgnoreTypes;
        //IgnoreTypes.push_back(Node::getClassType().getId());
        
        //Write the Field Containers to a xml file
        FCFileHandler::the()->write(Containers,BoostPath("./TestFieldContainers.xml"),IgnoreTypes);


        //Read FieldContainers from an XML file
        FCFileType::FCPtrStore NewContainers;
        NewContainers = FCFileHandler::the()->read(BoostPath("./TestFieldContainers.xml"));

        //Write the read FieldContainers to an XML file
        FCFileHandler::the()->write(NewContainers,BoostPath("./TestFieldContainers2.xml"),IgnoreTypes);
    }
    
	// OSG exit
    osgExit();
    std::cout << "Completed Successfully." << std::endl;

    return 0;
}

NodeUnrecPtr createScene(void)
{
	//Create some Field Containers
	/*NodeUnrecPtr ChildNode1 = Node::create();
	ChildNode1->setCore(Group::create());

	NodeUnrecPtr ChildNode2 = Node::create();
	ChildNode2->setCore(Group::create());

	NodeUnrecPtr CameraBeaconNode = Node::create();
	CameraBeaconNode->setCore(Transform::create());
	CameraBeaconNode->addChild(ChildNode1);
	CameraBeaconNode->addChild(ChildNode2);*/

	NodeUnrecPtr BoxNode = makeBox(2.0,0.5,0.5,1,1,1);

	NodeUnrecPtr PlaneNode = makePlane(1.0,1.0,2,2);

	//DistanceLODUnrecPtr TheLODCore = DistanceLOD::create();
	//TheLODCore->getRange().push_back(10.0f);
	//TheLODCore->getRange().push_back(50.0f);


	//NodeUnrecPtr LODNode = Node::create();
	//LODNode->setCore(TheLODCore);
	//LODNode->addChild(BoxNode);
	//LODNode->addChild(PlaneNode);
	
	NodeUnrecPtr BeaconNode = Node::create();
	BeaconNode->setCore(Transform::create());


	SpotLightUnrecPtr SpotLightCore = SpotLight::create();
	SpotLightCore->setBeacon(BeaconNode);

	NodeUnrecPtr TheNode = Node::create();
	TheNode->setCore(SpotLightCore);
    TheNode->addChild(BoxNode);
	//TheNode->updateVolume();

	return BoxNode;
}

