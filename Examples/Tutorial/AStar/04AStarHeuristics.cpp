// OpenSG Tutorial Example: Hello World
//
// Minimalistic OpenSG program
// 
// This is the shortest useful OpenSG program 
// (if you remove all the comments ;)
//
// It shows how to use OpenSG together with GLUT to create a little
// interactive rootNode viewer.
//

// General OpenSG configuration, needed everywhere
#include "OSGConfig.h"

// Methods to create simple geometry: boxes, spheres, tori etc.
#include "OSGSimpleGeometry.h"

// A little helper to simplify rootNode management and interaction
#include "OSGSimpleSceneManager.h"
#include "OSGSceneFileHandler.h"

#include "OSGComponentTransform.h"
#include "OSGTransform.h"
#include "OSGTypeFactory.h"


#include "OSGFieldContainerFactory.h"
#include "OSGNameAttachment.h"

// Input
#include "OSGWindowUtils.h"

#include "OSGOctree.h"
#include "OSGOctreeUtils.h"
#include "OSGOctreeAStarAlgorithm.h"
#include <boost/filesystem/convenience.hpp>
#include "OSGTypedGeoIntegralProperty.h"
#include "OSGTypedGeoVectorProperty.h"

#include "OSGLineChunk.h"
#include "OSGDepthChunk.h"
#include "OSGMaterialChunk.h"
#include "OSGChunkMaterial.h"
// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE

// forward declaration so we can have the interesting stuff upfront
NodeTransitPtr createPathGeometry(const std::vector<Pnt3f>& Path,
                                  const Color3f& Color,
                                  Real32 LineWidth);
void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);

void keyPressed(KeyEventDetails* const details)
{
    if(details->getKey() == KeyEventDetails::KEY_Q && details->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        dynamic_cast<WindowEventProducer*>(details->getSource())->closeWindow();
    }
}

void mousePressed(MouseEventDetails* const details, SimpleSceneManager *mgr)
{
    mgr->mouseButtonPress(details->getButton(), details->getLocation().x(), details->getLocation().y());
}
void mouseReleased(MouseEventDetails* const details, SimpleSceneManager *mgr)
{
    mgr->mouseButtonRelease(details->getButton(), details->getLocation().x(), details->getLocation().y());
}

void mouseMoved(MouseEventDetails* const details, SimpleSceneManager *mgr)
{
    mgr->mouseMove(details->getLocation().x(), details->getLocation().y());
}

void mouseDragged(MouseEventDetails* const details, SimpleSceneManager *mgr)
{
    mgr->mouseMove(details->getLocation().x(), details->getLocation().y());
}


Real32 chebyshevDistanceCost(Octree::OTNodePtr node,
                             const Pnt3f& Location,
                             Real32 CostPerUnit)
{
    Pnt3f Target;
    node->getVolume().getCenter(Target);
	return CostPerUnit * osgMax(osgAbs(Location.x() - Target.x()),
                                osgMax(osgAbs(Location.y() - Target.y()),
                                       osgAbs(Location.z() - Target.z())));
}

// Initialize GLUT & OpenSG and set up the rootNode
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    {
        // Set up Window
        WindowEventProducerRecPtr TutorialWindow = createNativeWindow();
        TutorialWindow->initWindow();

        SimpleSceneManager sceneManager;
        TutorialWindow->setDisplayCallback(boost::bind(display, &sceneManager));
        TutorialWindow->setReshapeCallback(boost::bind(reshape, _1, &sceneManager));

        //Attach to events
        TutorialWindow->connectMousePressed(boost::bind(mousePressed, _1, &sceneManager));
        TutorialWindow->connectMouseReleased(boost::bind(mouseReleased, _1, &sceneManager));
        TutorialWindow->connectMouseMoved(boost::bind(mouseMoved, _1, &sceneManager));
        TutorialWindow->connectMouseDragged(boost::bind(mouseDragged, _1, &sceneManager));
        TutorialWindow->connectKeyPressed(boost::bind(keyPressed,_1));

        // Tell the Manager what to manage
        sceneManager.setWindow(TutorialWindow);

        UInt32 SceneMask(1),
               PathMask(4);

        BoostPath SceneFilePath(".//Data//CellParts.osb");

        if(argc >= 2)
        {
            SceneFilePath = BoostPath(argv[1]);
            if(!boost::filesystem::exists(SceneFilePath))
            {
                SceneFilePath = BoostPath(".//Data//CellParts.osb");
            }
        }

        //Make Base Geometry Node
        NodeRecPtr SceneGeometryNode =
            SceneFileHandler::the()->read(SceneFilePath.string().c_str());
        SceneGeometryNode->setTravMask(SceneMask);
        if(SceneGeometryNode == NULL)
        {
            SceneGeometryNode = makeTorus(1.0, 10.0, 24, 24);
        }

        //Construct the Root Node
        NodeRecPtr RootNode = makeCoredNode<Group>();
        RootNode->addChild(SceneGeometryNode);
        commitChanges();

        //Create the Octree

        SLOG << "Started Building Octree" << std::endl;
        SLOG << "This may take some time ..." << std::endl;
        Time StartTime;
        StartTime = getSystemTime();
		OctreePtr TheOctree =
            Octree::buildTree(RootNode,SceneMask,6,1.5,true);

        SLOG << "Building Octree: " << getSystemTime() - StartTime << " s" << std::endl;
        Pnt3f Min,Max;
        TheOctree->getRoot()->getVolume();
        SLOG << "Octree: "<< std::endl
             << "    Depth: " << TheOctree->getDepth() << std::endl
             << "    Bounds: " << TheOctree->getRoot()->getVolume().getMin() << "  :  " << TheOctree->getRoot()->getVolume().getMax() << std::endl
             << "    NodeCount: " << TheOctree->getNodeCount() << std::endl
             << "    LeafNodeCount: " << TheOctree->getLeafNodeCount() << std::endl
             << "    BranchNodeCount: " << TheOctree->getBranchNodeCount() << std::endl
             << "    IntersectingNodeCount: " << TheOctree->getIntersectingNodeCount() << std::endl
             << "    IntersectingLeafNodeCount: " << TheOctree->getIntersectingLeafNodeCount() << std::endl;

        //Create the Path Geometry
        //Generate the Path
        Pnt3f Start(-4.01f,1.01f,10.01f),Goal(-4.01f,-0.01f,-7.01f);
        SLOG << "Started Euclidean AStar Search" << std::endl;
        OctreeAStarAlgorithm AlgorithmObj;
        StartTime = getSystemTime();
        std::vector<Pnt3f> EuclideanPath =
            AlgorithmObj.search(TheOctree,Start,Goal);
        EuclideanPath.front() = Start;
        EuclideanPath.back() = Goal;
        SLOG << "Finished Euclidean AStar Search: " << getSystemTime() - StartTime << " s" << std::endl;
        NodeRecPtr EuclideanPathNode = createPathGeometry(EuclideanPath,
                                                          Color3f(0.0f,1.0f,0.0f),
                                                          1.0f);
        EuclideanPathNode->setTravMask(PathMask);
        RootNode->addChild(EuclideanPathNode);

        SLOG << "Started Manhattan AStar Search" << std::endl;
        StartTime = getSystemTime();
        std::vector<Pnt3f> ManhattanPath =
            AlgorithmObj.search(TheOctree,Start,Goal,boost::bind(&OctreeAStarAlgorithm::manhattanDistanceCost, _2, _3, 1.0f));
        ManhattanPath.front() = Start;
        ManhattanPath.back() = Goal;
        SLOG << "Finished Manhattan AStar Search: " << getSystemTime() - StartTime << " s" << std::endl;

        NodeRecPtr ManhattanPathNode = createPathGeometry(ManhattanPath,
                                                          Color3f(1.0f,0.0f,0.0f),
                                                          3.0f);
        ManhattanPathNode->setTravMask(PathMask);
        RootNode->addChild(ManhattanPathNode);

        SLOG << "Started Chebyshev AStar Search" << std::endl;
        StartTime = getSystemTime();
        std::vector<Pnt3f> ChebyshevPath =
            AlgorithmObj.search(TheOctree,Start,Goal,boost::bind(&chebyshevDistanceCost, _2, _3, 1.0f));
        ChebyshevPath.front() = Start;
        ChebyshevPath.back() = Goal;
        SLOG << "Finished Chebyshev AStar Search: " << getSystemTime() - StartTime << " s" << std::endl;

        NodeRecPtr ChebyshevPathNode = createPathGeometry(ChebyshevPath,
                                                          Color3f(0.0f,0.0f,1.0f),
                                                          5.0f);
        ChebyshevPathNode->setTravMask(PathMask);
        RootNode->addChild(ChebyshevPathNode);

        NodeRecPtr StartNode = makeSphere(1.0, 2);
        TransformRecPtr StartNodeTransform = Transform::create();
        Matrix StartNodeMatrix;
        StartNodeMatrix.setTranslate(Start);
        StartNodeMatrix.setScale(0.1f);
        StartNodeTransform->setMatrix(StartNodeMatrix);
        NodeRecPtr StartNodeTransformNode = makeNodeFor(StartNodeTransform);
        StartNodeTransformNode->addChild(StartNode);
        StartNodeTransformNode->setTravMask(PathMask);
        RootNode->addChild(StartNodeTransformNode);

        NodeRecPtr GoalNode = makeSphere(1.0, 2);
        TransformRecPtr GoalNodeTransform = Transform::create();
        Matrix GoalNodeMatrix;
        GoalNodeMatrix.setScale(0.1f);
        GoalNodeMatrix.setTranslate(Goal);
        GoalNodeTransform->setMatrix(GoalNodeMatrix);
        NodeRecPtr GoalNodeTransformNode = makeNodeFor(GoalNodeTransform);
        GoalNodeTransformNode->addChild(GoalNode);
        GoalNodeTransformNode->setTravMask(PathMask);
        RootNode->addChild(GoalNodeTransformNode);


        // tell the manager what to manage
        sceneManager.setRoot  (RootNode);

        // show the whole RootNode
        sceneManager.showAll();

        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "04AStarHeuristics");

        //Enter main Loop
        TutorialWindow->mainLoop();
    }

    osgExit();

    return 0;
}

// Redraw the window
void display(SimpleSceneManager *mgr)
{
    mgr->redraw();
}

// React to size changes
void reshape(Vec2f Size, SimpleSceneManager *mgr)
{
    mgr->resize(Size.x(), Size.y());
}

NodeTransitPtr createPathGeometry(const std::vector<Pnt3f>& Path,
                                  const Color3f& Color,
                                  Real32 LineWidth)
{

    //*******************Create the Geometry for the box
    GeoUInt8PropertyRecPtr type = GeoUInt8Property::create();
    //Volume bound box
    type->push_back(GL_LINE_STRIP);

    GeoUInt32PropertyRefPtr lens = GeoUInt32Property::create();
    //Volume bound box
    lens->push_back(Path.size());

    GeoUInt32PropertyRefPtr index = GeoUInt32Property::create();
    GeoPnt3fPropertyRefPtr points = GeoPnt3fProperty::create();
    GeoVec3fPropertyRefPtr colors = GeoVec3fProperty::create();

    //Volume bound box
    Real32 t;
    for(UInt32 i(0) ; i<Path.size() ; ++i)
    {
        index->push_back(i);
        points->push_back(Path[i]);
        colors->push_back(Color);
    }

    GeometryRecPtr PathGeo = Geometry::create();
    PathGeo->setTypes     (type);
    PathGeo->setLengths   (lens);
    PathGeo->setIndices   (index);
    PathGeo->setPositions (points);
    PathGeo->setColors    (colors);

    //Create the material for the line
    LineChunkRecPtr DefaultLineChunk = LineChunk::create();
    DefaultLineChunk->setWidth(LineWidth);

    DepthChunkRecPtr DefaultDepthChunk = DepthChunk::create();
    DefaultDepthChunk->setReadOnly(true);

    MaterialChunkRecPtr DefaultMaterialChunk = MaterialChunk::create();
    DefaultMaterialChunk->setLit(false);

    ChunkMaterialRecPtr DefaultChunkMaterial = ChunkMaterial::create();
    DefaultChunkMaterial->addChunk(DefaultMaterialChunk);
    DefaultChunkMaterial->addChunk(DefaultLineChunk);
    DefaultChunkMaterial->addChunk(DefaultDepthChunk);
    DefaultChunkMaterial->setSortKey(100.0f - LineWidth);

    PathGeo->setMaterial(DefaultChunkMaterial);

    return makeNodeFor(PathGeo);
}

