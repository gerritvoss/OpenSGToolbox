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

#include "OSGSolidBackground.h"

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

//Animation
#include "OSGKeyframeSequences.h"
#include "OSGKeyframeAnimator.h"
#include "OSGFieldAnimation.h"
#include "OSGAnimationGroup.h"

#include "OSGLineChunk.h"
#include "OSGMaterialChunk.h"
#include "OSGChunkMaterial.h"
// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE

// forward declaration so we can have the interesting stuff upfront
std::vector<Pnt3f> smooth(const std::vector<Pnt3f>& Path, UInt32 SubDivs = 1);
NodeTransitPtr createPathGeometry(const std::vector<Pnt3f>& Path);
AnimationTransitPtr setupAnimation(const std::vector<Pnt3f>& Path,
                                   Transform* const transCore);
void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);

void keyPressed(KeyEventDetails* const details,
                Node* const sceneGeoNode,
                Node* const octreeNode)
{
    if(details->getKey() == KeyEventDetails::KEY_Q && details->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        dynamic_cast<WindowEventProducer*>(details->getSource())->closeWindow();
    }
    switch(details->getKey())
    {
        case KeyEventDetails::KEY_1:
            if(sceneGeoNode->getTravMask() != 0)
            {
                sceneGeoNode->setTravMask(0);
            }
            else
            {
                sceneGeoNode->setTravMask(1);
            }
            break;
        case KeyEventDetails::KEY_2:
            if(octreeNode->getTravMask() != 0)
            {
                octreeNode->setTravMask(0);
            }
            else
            {
                octreeNode->setTravMask(1);
            }
            break;
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

        // Tell the Manager what to manage
        sceneManager.setWindow(TutorialWindow);

        UInt32 SceneMask(1),
               NanobotMask(2),
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

        //Make the Nanobot Node
        BoostPath NanobotFilePath(".//Data//Nanobot.osb");
        NodeRecPtr NanobotGeoNode =
            SceneFileHandler::the()->read(NanobotFilePath.string().c_str());

        //Get the Transform node for the Nanobot
        TransformRecPtr NanobotTransform = Transform::create();
        Matrix NanobotMatrix;
        NanobotMatrix.setTranslate(0.0f,0.0f,12.0f);
        NanobotMatrix.setScale(0.06f);
        NanobotTransform->setMatrix(NanobotMatrix);
        NodeRecPtr NanobotNode = makeNodeFor(NanobotTransform);
        NanobotNode->addChild(NanobotGeoNode);
        NanobotNode->setTravMask(NanobotMask);



        //Construct the Root Node
        NodeRecPtr RootNode = makeCoredNode<Group>();
        RootNode->addChild(SceneGeometryNode);
        RootNode->addChild(NanobotNode);
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

        //Create a visualization of the octree
        SLOG << "Started Building Visualization" << std::endl;
        StartTime = getSystemTime();
        NodeRecPtr OctreeVisNode = OctreeVisualization::createOctreeVisualization(TheOctree, 100);
        SLOG << "Building Visualization: " << getSystemTime() - StartTime << " s" << std::endl;
        RootNode->addChild(OctreeVisNode);

        //Create the Path Geometry
        //Generate the Path
        OctreeAStarAlgorithm AlgorithmObj;
        SLOG << "Started AStar Search" << std::endl;
        StartTime = getSystemTime();
        Pnt3f Start(-2.01f,1.01f,10.01f),Goal(-3.01f,-0.01f,-7.01f);
        std::vector<Pnt3f> NanobotPath =
            AlgorithmObj.search(TheOctree,Start,Goal);
        NanobotPath.front() = Start;
        NanobotPath.back() = Goal;
        NanobotPath = smooth(NanobotPath,4);
        SLOG << "Finished AStar Search: " << getSystemTime() - StartTime << " s" << std::endl;

        NodeRecPtr PathNode = createPathGeometry(NanobotPath);
        PathNode->setTravMask(PathMask);
        RootNode->addChild(PathNode);

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

        TutorialWindow->connectKeyPressed(boost::bind(keyPressed,
                                                      _1,
                                                      SceneGeometryNode.get(),
                                                      OctreeVisNode.get()));

        AnimationRecPtr TheAnimation = setupAnimation(NanobotPath, NanobotTransform);
        TheAnimation->attachUpdateProducer(TutorialWindow);
        TheAnimation->start();

        //Set the background
        SolidBackgroundRecPtr TheBackground = SolidBackground::create();
        TheBackground->setColor(Color3f(0.0f,0.0f,0.0f));

        // tell the manager what to manage
        sceneManager.setRoot  (RootNode);
        sceneManager.getWindow()->getPort(0)->setBackground(TheBackground);

        // show the whole RootNode
        sceneManager.showAll();

        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "01AStarPathing");

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

NodeTransitPtr createPathGeometry(const std::vector<Pnt3f>& Path)
{

    //*******************Create the Geometry for the box
    GeoUInt8PropertyRecPtr type = GeoUInt8Property::create();
    //Volume bound box
    type->push_back(GL_LINE_STRIP);

    GeoUInt32PropertyRefPtr lens = GeoUInt32Property::create();
    //Volume bound box
    lens->push_back(Path.size());

    Color3f CoolColor(1.0f,0.0f,1.0f),
            HotColor(1.0f,0.0f,0.0f);

    GeoUInt32PropertyRefPtr index = GeoUInt32Property::create();
    GeoPnt3fPropertyRefPtr points = GeoPnt3fProperty::create();
    GeoVec3fPropertyRefPtr colors = GeoVec3fProperty::create();

    //Volume bound box
    Color3f Color;
    Real32 t;
    for(UInt32 i(0) ; i<Path.size() ; ++i)
    {
        t = static_cast<Real32>(i)/static_cast<Real32>(Path.size());
        Color = (t*CoolColor) + ((1.0f-t)*HotColor);
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
    DefaultLineChunk->setWidth(2.0f);

    MaterialChunkRecPtr DefaultMaterialChunk = MaterialChunk::create();
    DefaultMaterialChunk->setLit(false);

    ChunkMaterialRecPtr DefaultChunkMaterial = ChunkMaterial::create();
    DefaultChunkMaterial->addChunk(DefaultMaterialChunk);
    DefaultChunkMaterial->addChunk(DefaultLineChunk);

    PathGeo->setMaterial(DefaultChunkMaterial);

    return makeNodeFor(PathGeo);
}

std::vector<Pnt3f> smooth(const std::vector<Pnt3f>& Path, UInt32 SubDivs)
{
    assert(Path.size() >= 2);

    std::vector<Pnt3f> Result;
    Result.push_back(Path.front());
    Pnt3f prevPos, curPos, nextPos;
    Vec3f curTan;
    Vec3f nextTan;
    Real32 c(0.1f);
    for(UInt32 i(1) ; i<Path.size()-2 ; ++i)
    {
        prevPos = Path[i-1];
        curPos = Path[i];
        nextPos = Path[i+1];
        curTan = (1.0f - c)*(nextPos - prevPos);
        nextTan = (1.0f - c)*(Path[i+2] - curPos);
        Real32 h00,h01,h02,h03;

        Result.push_back(Path[i]);
        //tangent.normalize();
        for(UInt32 j = 0; j < SubDivs; ++j)
        {
            Real32 t(static_cast<Real32>(j+1)/static_cast<Real32>(SubDivs+1)),
                   t2(t*t),
                   t3(t2*t);;

            h00 = 2.0f*t3 - 3.0f*t2 + 1.0f;
            h01 = t3 - 2.0*t2 + t;
            h02 = -2.0f*t3 + 3.0f*t2;
            h03 = t3 - t2;             

            Pnt3f Pos = (h00 * curPos
                      + h01 * curTan).subZero() 
                      + (h02 * nextPos 
                      + h03 * nextTan).subZero();
            Result.push_back(Pos);
        }
    }
    Result.push_back(Path.back());

    return Result;
}

AnimationTransitPtr setupAnimation(const std::vector<Pnt3f>& Path, Transform* const transCore)
{
    //Transformation Keyframe Sequence
    KeyframeTransformationSequenceRecPtr TransformationKeyframes = KeyframeTransformationSequenceMatrix4f::create();
    Matrix TempMat;
    TempMat.setScale(0.1f);
    Real32 TotalTime(20.0f);
    Real32 SeqTime;
    Real32 TotalPathDistance(0.0f);
    for(UInt32 i(0) ; i<Path.size()-1 ; ++i)
    {
        TotalPathDistance += Path[i].dist(Path[(i+1)]);
    }

    Real32 CumPathDistance(0.0f);
    Quaternion Rotation;
    Vec3f Direction;
    for(UInt32 i(0) ; i<Path.size() ; ++i)
    {
        SeqTime = (CumPathDistance/TotalPathDistance) *TotalTime;
        Direction = Path[(i+1)%Path.size()]-Path[i];
        Direction[1] = 0.0f;
        Direction.normalize();
        Rotation = Quaternion(Vec3f(0.0f,0.0f,1.0f),Direction);
        TempMat.setTransform(Vec3f(Path[i]),Rotation,Vec3f(0.1f,0.1f,0.1f));
        TransformationKeyframes->addKeyframe(TempMat,SeqTime);

        if(i<Path.size()-1)
        {
            CumPathDistance += Path[i].dist(Path[(i+1)]);
        }
    }

    //Animator
    KeyframeAnimatorRecPtr TheAnimator = KeyframeAnimator::create();
    TheAnimator->setKeyframeSequence(TransformationKeyframes);

    //Animation
    FieldAnimationRecPtr TheAnimation = FieldAnimation::create();
    TheAnimation->setAnimator(TheAnimator);
    TheAnimation->setInterpolationType(Animator::CUBIC_INTERPOLATION);
    TheAnimation->setCycling(-1);
    TheAnimation->setAnimatedField(transCore, std::string("matrix"));

    return AnimationTransitPtr(TheAnimation);
}

