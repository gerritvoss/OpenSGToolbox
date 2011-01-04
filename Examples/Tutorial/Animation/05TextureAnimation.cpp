// 
// OpenSGToolbox Tutorial: 05TextureAnimation 
//
// Demonstrates a texture animation. 
//

// General OpenSG configuration, needed everywhere
#include "OSGConfig.h"

// Methods to create simple geometry: boxes, spheres, tori etc.
#include "OSGSimpleGeometry.h"

// A little helper to simplify scene management and interaction
#include "OSGSimpleSceneManager.h"

#include "OSGChunkMaterial.h"
#include "OSGMaterialChunk.h"
#include "OSGTextureObjChunk.h"
#include "OSGImageFileHandler.h"

#include "OSGComponentTransform.h"
#include "OSGTransform.h"
#include "OSGTypeFactory.h"

#include "OSGFieldContainerFactory.h"
#include "OSGNameAttachment.h"

#include "OSGContainerUtils.h"

// Input
#include "OSGKeyListener.h"
#include "OSGWindowUtils.h"

//Animation
#include "OSGKeyframeSequences.h"
#include "OSGKeyframeAnimator.h"
#include "OSGFieldAnimation.h"

// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE

// forward declaration so we can have the interesting stuff upfront
AnimationTransitPtr setupAnimation(ChunkMaterial* const TheBoxMaterial);
void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);

void animationCycled(AnimationEventDetails* const details)
{
    std::cout << "Animation Cycled.  Cycle Count: " << dynamic_cast<Animation*>(details->getSource())->getCycles() << std::endl;
}

// The SimpleSceneManager to manage simple applications
void keyPressed(KeyEventDetails* const details, WindowEventProducer* const TutorialWindow)
{
    if(details->getKey() == KeyEventDetails::KEY_Q &&
       details->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        TutorialWindow->closeWindow();
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

void mouseWheelMoved(MouseWheelEventDetails* const details, SimpleSceneManager *mgr)
{
    if(details->getUnitsToScroll() > 0)
    {
        for(UInt32 i(0) ; i<details->getUnitsToScroll() ;++i)
        {
            mgr->mouseButtonPress(Navigator::DOWN_MOUSE,details->getLocation().x(),details->getLocation().y());
            mgr->mouseButtonRelease(Navigator::DOWN_MOUSE,details->getLocation().x(),details->getLocation().y());
        }
    }
    else if(details->getUnitsToScroll() < 0)
    {
        for(UInt32 i(0) ; i<abs(details->getUnitsToScroll()) ;++i)
        {
            mgr->mouseButtonPress(Navigator::UP_MOUSE,details->getLocation().x(),details->getLocation().y());
            mgr->mouseButtonRelease(Navigator::UP_MOUSE,details->getLocation().x(),details->getLocation().y());
        }
    }
}

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    OSG::preloadSharedObject("OSGFileIO");
    OSG::preloadSharedObject("OSGImageFileIO");
    // OSG init
    osgInit(argc,argv);
    {
        // Set up Window
        WindowEventProducerRecPtr TutorialWindow = createNativeWindow();

        //Initialize Window
        TutorialWindow->initWindow();

        SimpleSceneManager sceneManager;
        TutorialWindow->setDisplayCallback(boost::bind(display, &sceneManager));
        TutorialWindow->setReshapeCallback(boost::bind(reshape, _1, &sceneManager));

        // Tell the Manager what to manage
        sceneManager.setWindow(TutorialWindow);

        //Attach to events
        TutorialWindow->connectMousePressed(boost::bind(mousePressed, _1, &sceneManager));
        TutorialWindow->connectMouseReleased(boost::bind(mouseReleased, _1, &sceneManager));
        TutorialWindow->connectMouseMoved(boost::bind(mouseMoved, _1, &sceneManager));
        TutorialWindow->connectMouseDragged(boost::bind(mouseDragged, _1, &sceneManager));
        TutorialWindow->connectMouseWheelMoved(boost::bind(mouseWheelMoved, _1, &sceneManager));
        TutorialWindow->connectKeyPressed(boost::bind(keyPressed, _1, TutorialWindow.get()));

        //Box Geometry
        GeometryUnrecPtr BoxGeometry = makeBoxGeo(1.0,1.0,1.0,1,1,1);
        ChunkMaterialUnrecPtr TheBoxMaterial = ChunkMaterial::create();
        BoxGeometry->setMaterial(TheBoxMaterial);

        NodeUnrecPtr BoxGeometryNode = Node::create();
        BoxGeometryNode->setCore(BoxGeometry);

        //Make Box Node
        NodeUnrecPtr BoxNode = Node::create();
        TransformUnrecPtr BoxNodeTrans;
        BoxNodeTrans = Transform::create();

        BoxNode->setCore(BoxNodeTrans);
        BoxNode->addChild(BoxGeometryNode);

        //Make Main Scene Node
        NodeUnrecPtr scene = Node::create();
        ComponentTransformUnrecPtr Trans;
        Trans = ComponentTransform::create();
        scene->setCore(Trans);

        // add the torus as a child
        scene->addChild(BoxNode);

        //Setup the Animation
        AnimationUnrecPtr TheAnimation = setupAnimation(TheBoxMaterial);
        TheAnimation->attachUpdateProducer(TutorialWindow);
        TheAnimation->start();

        // tell the manager what to manage
        sceneManager.setRoot  (scene);

        // show the whole scene
        sceneManager.showAll();

        //Open Window
        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);

        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "05TextureAnimation");

        //Main Loop
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

AnimationTransitPtr setupAnimation(ChunkMaterial* const TheBoxMaterial)
{
    std::vector<ImageUnrecPtr> _Images;
    std::vector<BoostPath> _ImagePaths;
    _ImagePaths.push_back(BoostPath("./Data/Anim001.jpg"));
    _ImagePaths.push_back(BoostPath("./Data/Anim002.jpg"));
    _ImagePaths.push_back(BoostPath("./Data/Anim003.jpg"));
    _ImagePaths.push_back(BoostPath("./Data/Anim004.jpg"));
    _ImagePaths.push_back(BoostPath("./Data/Anim005.jpg"));

    //Make the textures
    for(UInt32 i(0) ; i<_ImagePaths.size(); ++i)
    {
        ImageUnrecPtr AnimFrameImage = ImageFileHandler::the()->read(_ImagePaths[i].string().c_str());

        _Images.push_back(AnimFrameImage);
    }

    TextureObjChunkUnrecPtr AnimFrameTexture = TextureObjChunk::create();
    AnimFrameTexture->setImage(_Images.front());

    //Box Material
    MaterialChunkUnrecPtr TheMaterialChunk = MaterialChunk::create();
    TheMaterialChunk->setAmbient(Color4f(0.4,0.4,0.4,1.0));
    TheMaterialChunk->setDiffuse(Color4f(0.8,0.8,0.8,1.0));
    TheMaterialChunk->setSpecular(Color4f(1.0,1.0,1.0,1.0));

    TheBoxMaterial->addChunk(AnimFrameTexture);

    //Texture Keyframe Sequence
    KeyframeFCPtrSequenceUnrecPtr TextureKeyframes = KeyframeFCPtrSequence::create();
    for(UInt32 i(0) ; i<_Images.size(); ++i)
    {
        TextureKeyframes->addKeyframe(_Images[i],static_cast<Real32>(i)*0.5f);
    }

    //Animator
    KeyframeAnimatorUnrecPtr TutorialTextureAnimator = KeyframeAnimator::create();
    TutorialTextureAnimator->setKeyframeSequence(TextureKeyframes);

    //Animation
    FieldAnimationUnrecPtr TutorialTextureAnimation = FieldAnimation::create();
    TutorialTextureAnimation->setAnimator(TutorialTextureAnimator);
    TutorialTextureAnimation->setInterpolationType(Animator::STEP_INTERPOLATION);
    TutorialTextureAnimation->setCycling(-1);
    TutorialTextureAnimation->setAnimatedField(AnimFrameTexture,TextureObjChunk::ImageFieldId);

    return AnimationTransitPtr(TutorialTextureAnimation);
}

