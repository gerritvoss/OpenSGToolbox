// OpenSG Tutorial Example: Hello World
//
// Minimalistic OpenSG program
// 
// This is the shortest useful OpenSG program 
// (if you remove all the comments ;)
//
// It shows how to use OpenSG together with GLUT to create a little
// interactive scene viewer.
//

// General OpenSG configuration, needed everywhere
#include <OpenSG/OSGConfig.h>

#include <OpenSG/OSGPerspectiveCamera.h>
#include <OpenSG/OSGGradientBackground.h>
#include <OpenSG/OSGPolygonForeground.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGViewport.h>

#include <OpenSG/Toolbox/OSGFCFileHandler.h>

// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE

NodePtr createScene(void);

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);
    
	//Create some Field Containers
	NodePtr Root = createScene();


	/*PerspectiveCameraPtr ThePerspectiveCamera = PerspectiveCamera::create();
	beginEditCP(ThePerspectiveCamera);
		ThePerspectiveCamera->setBeacon(Root);
		ThePerspectiveCamera->setFov   (deg2rad(60.f));
		ThePerspectiveCamera->setNear  (0.1f);
		ThePerspectiveCamera->setFar   (10000.f);
	endEditCP(ThePerspectiveCamera);

	GradientBackgroundPtr TheGradientBackground = GradientBackground::create();
	TheGradientBackground->addLine(Color3f(1.0f,0.0f,0.0f), 0.0f);
	TheGradientBackground->addLine(Color3f(0.0f,1.0f,0.0f), 0.5f);
	TheGradientBackground->addLine(Color3f(0.0f,0.0f,1.0f), 1.0f);

	PolygonForegroundPtr ThePolygonForeground = PolygonForeground::create();
	ThePolygonForeground->getPositions().push_back(Pnt2f(0.0f,1.0f));

	ViewportPtr TheViewport = Viewport::create();
	TheViewport->setRoot(Root);
	TheViewport->setCamera(ThePerspectiveCamera);
	TheViewport->setBackground(TheGradientBackground);
	TheViewport->getForegrounds().push_back(ThePolygonForeground);*/

	FCFileType::FCPtrStore Containers;
	Containers.insert(Root);

	//Save the Field Containers to a binary file
	//FCFileHandler::the()->write(Containers,Path("./TestFieldContainers.fcb"));

	FCFileType::FCTypeVector IgnoreTypes;
	//IgnoreTypes.push_back(Node::getClassType().getId());
	//Save the Field Containers to a xml file
	FCFileHandler::the()->write(Containers,Path("./TestFieldContainers.xml"),IgnoreTypes);


	FCFileType::FCPtrStore NewContainers;
	NewContainers = FCFileHandler::the()->read(Path("./TestFieldContainers.xml"));

	FCFileHandler::the()->write(NewContainers,Path("./TestFieldContainers2.xml"),IgnoreTypes);
    
	// OSG exit
    osgExit();

    return 0;
}

#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGComponentTransform.h>
#include <OpenSG/OSGPointLight.h>
#include <OpenSG/OSGSpotLight.h>
#include <OpenSG/OSGDirectionalLight.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGDistanceLOD.h>
#include <OpenSG/OSGBillboard.h>

#include <OpenSG/OSGSimpleGeometry.h>
NodePtr createScene(void)
{
	//Create some Field Containers
	/*NodePtr ChildNode1 = Node::create();
	ChildNode1->setCore(Group::create());

	NodePtr ChildNode2 = Node::create();
	ChildNode2->setCore(Group::create());

	NodePtr CameraBeaconNode = Node::create();
	CameraBeaconNode->setCore(Transform::create());
	CameraBeaconNode->addChild(ChildNode1);
	CameraBeaconNode->addChild(ChildNode2);*/

	NodePtr BoxNode = makeBox(1.0,1.0,1.0,1,1,1);

	NodePtr PlaneNode = makePlane(1.0,1.0,2,2);

	//DistanceLODPtr TheLODCore = DistanceLOD::create();
	//TheLODCore->getRange().push_back(10.0f);
	//TheLODCore->getRange().push_back(50.0f);


	//NodePtr LODNode = Node::create();
	//LODNode->setCore(TheLODCore);
	//LODNode->addChild(BoxNode);
	//LODNode->addChild(PlaneNode);
	
	NodePtr BeaconNode = Node::create();
	BeaconNode->setCore(Transform::create());


	SpotLightPtr SpotLightCore = SpotLight::create();
	SpotLightCore->setBeacon(BeaconNode);

	NodePtr TheNode = Node::create();
	TheNode->setCore(SpotLightCore);
	//TheNode->updateVolume();

	return TheNode;
}

